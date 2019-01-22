/*
 * handlerFile.h
 *
 * Created: 17.01.2019 17:43:35
 *  Author: Gabi
 */ 


#ifndef HANDLERFILE_H_
#define HANDLERFILE_H_
#include "utils.h"

volatile unsigned int count_int0_interrupts;

volatile unsigned int count_timer0_interupts = 0;
volatile unsigned int unghiActual = 0xFF;
volatile unsigned int unghiDorit = 0xFF;

volatile unsigned int sensorDelay;
volatile int toggle = 0;
volatile char cuvant;

volatile unsigned int perioada_dintre_litere = 0xFFFF;

volatile unsigned int time_spend_high;
volatile unsigned int time_spend_low;

enum Stari{init, calib, exec};
volatile enum Stari state = init;

volatile unsigned int test_unghi_dorit = 0xFF;

volatile unsigned int cinci_grade = 0xFF;

void resetIndex();

ISR(INT0_vect){
	switch(state)
	{
		case exec:
			if(count_timer0_interupts > sensorDelay)
			{
				if((toggle = !toggle))
				{
					;
				}
				else
				{
					time_spend_low = count_timer0_interupts;
					cinci_grade = (time_spend_low/72);
					unghiActual = cinci_grade;
					unghiDorit = cinci_grade*36;
					resetIndex();
					
				}
			}
			break;
		case calib:
			sensorDelay = count_timer0_interupts*3;
			state = exec;
			break;
		case init:
			TIMSK0 |= (1 << OCIE0A); //porneste timerul T0
			state = calib;
			break;
	}
	//cuvant = count_int0_interrupts;
	count_timer0_interupts = 0;

}

char getNext();

ISR(TIMER0_COMPA_vect){
	++count_timer0_interupts;
	if(count_timer0_interupts == unghiActual)
	{
		if(unghiActual == unghiDorit)
		{
			cuvant = getNext();
			unghiDorit += cinci_grade;
		}
		unghiActual += cinci_grade;
		
	}
	else
	{
		cuvant = 0;
	}
	
}



#endif /* HANDLERFILE_H_ */