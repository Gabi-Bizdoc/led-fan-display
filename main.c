#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include "IncFile1.h"
#include "configurationFile.h"
#include "handlerFile.h"

volatile char cuvant = 0;

void scrie(char txt){
	PORTB = (txt >> 2);
	PORTD = (txt << 6);
}

int main(void)
{
	cli();
	DDRB = 0b00011111;
	DDRD = 0b11000000;
	processString("TE IUBB");
	int0_setup();
	timer0_setup();
//	timer2_setup();
//	timer1_setup();
	sei();
	while (1) {
		scrie(cuvant);
	}
}


