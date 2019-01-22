/*
 * utils.h
 *
 * Created: 22.01.2019 10:10:10
 *  Author: Gabi
 */ 


#ifndef UTILS_H_
#define UTILS_H_
#define MAX_TIMER1_OCR 65536 
#define MAX_TIMER0_OCR 65536 
#include "handlerFile.h"
#include "utils.h"
#include <stdlib.h>

char* cuvinte_de_afisat;
int max;

void processString(char* text){
	int i=0;
	char* output = (char*)malloc(sizeof(char)*(7*strlen(text) + 1));
	int index=0;
	while(text[i]!='\0'){
		if(text[i] >= 'A' && text[i] <= 'Z')
		{
			for (int j=0; j<7; j++)
			{
				output[index++] = litere[text[i]-'A'][j];
			}
			
		}
		++i;
	}

	max = index;
	cuvinte_de_afisat = output;
}

int myIndex;

char getNext(){
	if(myIndex > max)
	return 0;
	return cuvinte_de_afisat[myIndex++];
}

void resetIndex(){
	myIndex = 0;
}




const unsigned int prescaler[] = { 0, 1, 8, 64, 256, 1024 };
void configure_timer_1_for(unsigned int t){
	unsigned int i = 1;
	while( (16000000 / (prescaler[i] * t) - 1) > MAX_TIMER1_OCR && i < 6)
	{
		i++;
	}	
	if( i == 6)
	{
		/* TO DO ...
			*	NU INCAPE AICI, acum ce fac?
			*/
	}
	OCR1A = 16000000 / (prescaler[i] * t) - 1;
	TCCR1B |= (1 << WGM12);
	TCCR1B &= (i+0b11111000);
	// 	TIMSK1 |= (1 << OCIE1A); trebuie pornit separat
}

void configure_timer_2_for(unsigned int t){
	unsigned int i = 1;
	while( (16000000 / (prescaler[i] * t) - 1) > MAX_TIMER0_OCR && i < 6)
	{
		i++;
	}
	if( i == 6)
	{
		/* TO DO ...
		 *	NU INCAPE AICI, acum ce fac?
		 */
	}
	OCR2A = 16000000 / (prescaler[i] * t) - 1;
	TCCR2B |= (1 << WGM12);
	TCCR2B &= (i+0b11111000);
	// 	TIMSK1 |= (1 << OCIE1A); trebuie pornit separat
}

void configure_timer_0_for(unsigned int t){
	unsigned int i = 1;
	while( (16000000 / (prescaler[i] * t) - 1) > MAX_TIMER0_OCR && i < 6)
	{
		i++;
	}
	if( i == 6)
	{
		/* TO DO ...
		 *	NU INCAPE AICI, acum ce fac?
		 */
	}
	OCR0A = 16000000 / (prescaler[i] * t) - 1;
	TCCR0B |= (1 << WGM12);
	TCCR0B &= (i+0b11111000);
	// 	TIMSK1 |= (1 << OCIE1A); trebuie pornit separat
}
#endif /* UTILS_H_ */