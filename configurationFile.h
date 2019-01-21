/*
 * configurationFile.h
 *
 * Created: 17.01.2019 17:43:09
 *  Author: Gabi
 */ 

/*	EIFR ?
 *  EIMSK ? - - - - - - INT0, INT1		// enable external interrupts
 *  EIKRA ? - - - - ISC11, ISC10, ISC01, ISC00		// 
					00 low lvl interrupts 
					01 toggle interrupts   
					10 falling edge   
					11 rise edge
 *  TCCR0A ?  COM0A1 COM0A0 COM0B1 COM0B0 - WGM01 WGM00
 *  TCCR0B ? FOC0A FOC0B – – WGM02 CS02 CS01 CS00
 *									0 0 0 No clock source (Timer/Counter stopped)
 *									0 0 1 clkI/O/(no prescaling)
 *									0 1 0 clkI/O/8 (from prescaler)
 *									0 1 1 clkI/O/64 (from prescaler)
 *									1 0 0 clkI/O/256 (from prescaler)
 *									1 0 1 clkI/O/1024 (from prescaler)
 *									1 1 0 External clock source on T0 pin. Clock on falling edge.
 *									1 1 1 External clock source on T0 pin. Clock on rising edge.
 *						 WGM02 WGM01 WGM00
 *							  0 0 0 Normal 0xFF Immediate MAX
 *							  0 0 1 PWM, phase correct 0xFF TOP BOTTOM
 *							  0 1 0 CTC OCRA Immediate MAX
 *							  0 1 1 Fast PWM 0xFF BOTTOM MAX
 *							  1 0 0 Reserved – – –
 *							  1 0 1 PWM, phase correct OCRA TOP BOTTOM
 *							  1 1 0 Reserved – – –
 *							  1 1 1 Fast PWM OCRA BOTTOM TOP
 *  TIMSK0 ? – – – – – OCIE0B OCIE0A TOIE0
 *	 						OCIE0B ? Output Compare Match B Interrupt Enable
 *	 						OCIE0A ? Output Compare Match A Interrupt Enable
 *	 						TOIE0  ? Timer/Counter0 Overflow Interrupt Enable
 *  TCNT0 ? Timer/Counter Register
 *  OCR0A ? Output Compare Register A
 *  OCR0b ? Output Compare Register B
 */

#ifndef CONFIGURATIONFILE_H_
#define CONFIGURATIONFILE_H_

void int0_setup(){
	DDRD &= ~2;
	//EICRA |= 0b11;
	EICRA = 0;
	EICRA |= (1 << ISC00 && 1 << ISC01);
	//EIMSK |= 0b1;
	EIMSK |= (1 << INT0);	
}
void timer2_setup(){
	// set compare match register for 1000 Hz increments
	OCR2A = 249; // = 16000000 / (64 * 1000) - 1 (must be <256)
	// turn on CTC mode
	TCCR2B |= (1 << WGM21);
	// Set CS22, CS21 and CS20 bits for 64 prescaler
	TCCR2B |= (1 << CS22) | (0 << CS21) | (0 << CS20);
	// enable timer compare interrupt
	TIMSK2 |= (1 << OCIE2A);
}
void timer0_setup(){
TCCR0A = 0; // set entire TCCR0A register to 0
TCCR0B = 0; // same for TCCR0B
TCNT0  = 0; // initialize counter value to 0
// set compare match register for 100000 Hz increments
OCR0A = 159; // = 16000000 / (1 * 100000) - 1 (must be <256)
// turn on CTC mode
TCCR0B |= (1 << WGM01);
// Set CS02, CS01 and CS00 bits for 1 prescaler
TCCR0B |= (0 << CS02) | (0 << CS01) | (1 << CS00);
// enable timer compare interrupt
}

void timer1_setup(){
		// set compare match register for 1000 Hz increments
		OCR1A = 15999; // = 16000000 / (1 * 1000) - 1 (must be <65536)
		// turn on CTC mode
		TCCR1B |= (1 << WGM12);
		// Set CS12, CS11 and CS10 bits for 1 prescaler
		TCCR1B |= (0 << CS12) | (0 << CS11) | (1 << CS10);
		// enable timer compare interrupt
		TIMSK1 |= (1 << OCIE1A);
}

#endif /* CONFIGURATIONFILE_H_ */