/*
 * handlerFile.h
 *
 * Created: 17.01.2019 17:43:35
 *  Author: Gabi
 */ 


#ifndef HANDLERFILE_H_
#define HANDLERFILE_H_

volatile unsigned int count_int0_interrupts;

volatile unsigned int count_timer2_interupts = 0;
volatile unsigned int count_timer1_interupts = 0;
volatile unsigned int count_timer0_interupts = 0;
volatile unsigned int ungiActual = 0xFF;
volatile unsigned int ungiDorit = 0xFF;

volatile unsigned int sensorDelay;
volatile int toggle = 1;
volatile char cuvant;

volatile unsigned int perioada_dintre_litere = 0xFFFF;

volatile unsigned int time_spend_high;
volatile unsigned int time_spend_low;

enum Stari{init, calib, exec};
volatile enum Stari state = init;

volatile unsigned int test_unghi_dorit = 0xFF;
volatile int ind = 0;
volatile unsigned int cinci_grade = 0xFF;


ISR(INT0_vect){
	count_timer0_interupts++;
	switch(state)
	{
		case exec:
			if(count_timer0_interupts > sensorDelay)
			{
				if((toggle = !toggle))
				{
					time_spend_high = count_timer0_interupts;
				}
				else
				{
					time_spend_low = count_timer0_interupts;
					cinci_grade = (time_spend_low/72);
					ungiActual = cinci_grade;
					ungiDorit = cinci_grade*36;
					ind = 0;
					
				}
			}
			break;
		case calib:
			sensorDelay = count_timer0_interupts*3;
			state = exec;
			break;
		case init:
			TIMSK0 |= (1 << OCIE0A);
			state = calib;
			break;
	}
	//cuvant = count_int0_interrupts;
	count_timer0_interupts = 0;

}


ISR(TIMER0_COMPA_vect){
	++count_timer0_interupts;
	if(count_timer0_interupts == ungiActual)
	{
		if(ungiActual == ungiDorit)
		{
			if(ind < 7)
			{
				cuvant = M[ind++];
			}
			else
			{
				if(ind < 14)
				{
					cuvant = U[ind-7];
					++ind;
				}
				else
					if(ind < 21)
					{
						cuvant = I[ind-14];
						++ind;
					}
					else
						if(ind < 28)
						{
							cuvant = E[ind-21];
							++ind;
						}
			}
			ungiDorit += cinci_grade;
		}
		ungiActual += cinci_grade;
		
		
	}
	else
	{
		cuvant = 0;
	}
	
}

ISR(TIMER1_COMPA_vect){
	if(++count_timer1_interupts == perioada_dintre_litere)
	{
		count_timer1_interupts = 0;
		ungiActual++;
	}
	if(ungiActual == ungiDorit)
	{
		cuvant = 0xFF;
	}
	else
	{
		cuvant = 0;	
	}
}

ISR(TIMER2_COMPA_vect){
	++count_timer1_interupts;
	
}





#endif /* HANDLERFILE_H_ */