/*
 * configurationFile.h
 *
 * Created: 17.01.2019 17:43:09
 *  Author: Gabi
 */ 

/*	EIFR ? External Interrupt Flag Register
 *  EIMSK ? - - - - - - INT0, INT1		// External Interrupt Mask Register
 *  EICRA ? - - - - ISC11, ISC10, ISC01, ISC00		// External Interrupt Control Register A
					00 low lvl interrupts 
					01 toggle interrupts   
					10 falling edge   
					11 rise edge
 *  TCCR0A ?  COM0A1 COM0A0 COM0B1 COM0B0 - WGM01 WGM00 //Timer/Counter Control Register A
 *  TCCR0B ? FOC0A FOC0B – – WGM02 CS02 CS01 CS00 //for the prescaler
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
 *  OCR0B ? Output Compare Register B
 */

#ifndef CONFIGURATIONFILE_H_
#define CONFIGURATIONFILE_H_

void int0_setup(){
	DDRD &= ~0b100;
	//EICRA |= 0b11;
	EICRA |= (1 << ISC00 && 1 << ISC01);
	//EIMSK |= 0b1;
	EIMSK |= (1 << INT0);	
}

void timer0_setup(){
// set compare match register for 100000 Hz increments
OCR0A = 159; // = 16000000 / (1 * 100000) - 1 (must be <256)
// turn on CTC mode
TCCR0B |= (1 << WGM01);
// Set CS02, CS01 and CS00 bits for 1 prescaler
TCCR0B |= (0 << CS02) | (0 << CS01) | (1 << CS00);
// enable timer compare interrupt
}

#endif /* CONFIGURATIONFILE_H_ */