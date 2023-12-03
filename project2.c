/*
 *  project2.c
 *  Created on: 1-12-2023
 *  Author: Abdulla Nagy Mohamed
 */

#include<avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned int g_tick=0;
unsigned int g_tick1=0;
unsigned int g_tick2=0;
unsigned int g_tick3=0;
unsigned int g_tick4=0;

unsigned char g_num1=0;
unsigned char g_num2=0;
unsigned char g_num3=0;
unsigned char g_num4=0;
unsigned char g_num5=0;
unsigned char g_num6=0;

#define SEC2 10
#define MIN1 60
#define MIN2 600
#define HOUR1 3600
#define HOUR2 36000

ISR(INT0_vect)             //ISR Code For External Interrupt-0 For 'RESET' StopWatch System.
{
	 g_num1=0;
	 g_num2=0;
	 g_num3=0;
	 g_num4=0;
     g_num5=0;
     g_num6=0;

     TIMSK|=(1<<OCIE1A);
}

ISR(INT1_vect)             //ISR Code For External Interrupt-1 For  'paused'  StopWatch System .
{
	 TIMSK&=~(1<<OCIE1A);
}

ISR(INT2_vect)             //ISR Code For External Interrupt-2 For  'Resume'  StopWatch System .
{
	 TIMSK|=(1<<OCIE1A);
}

ISR(TIMER1_COMPA_vect)     //ISR Code For TIMER-1 Internal Interrupt .
{

      g_tick++;
      g_tick1++;
      g_tick2++;
      g_tick3++;
      g_tick4++;
      g_num1++;


if(g_tick==SEC2)           // Loop-1 To Count , For 'SEC-2 7-Segment' .
{
	   g_num1=0;           //Reset The Counter g_num1 .

	   if(g_num2<5){
	    g_num2++;          // Counter g_num3 incremented by one  .
                   }

       else{
	    g_num2=0;          //Reset The Counter  g_num2 .
         }

g_tick=0;                  //Reset The Counter g_tick .
}


if(g_tick1==MIN1)          // Loop-2 To Count , For 'MIN-1 7-Segment' .
{
	    g_num1=0;          //Reset The Counter  g_num1,2 .
		g_num2=0;

	   if(g_num3<9){
	     g_num3++;         // Counter g_num3 incremented by one   .
                   }

	   else{
	     g_num3=0;         //Reset The Counter g_num3 .
           }

g_tick1=0;
}

if(g_tick2==MIN2)          // Loop-3 To Count , For 'MIN-2 7-Segment' .
{
	    g_num1=0;          // Reset All Counters g_num1,2,3 .
	 	g_num2=0;
		g_num3=0;

       if(g_num4<5){
	     g_num4++;         // Counter g_num4 incremented by one  .
                   }

       else{
	     g_num4=0;         // Reset The Counter g_num4 .
            }

g_tick2=0;                 // Reset The Counter g_tick2 .
}

if(g_tick3==HOUR1)         // Loop-4 To Count , For 'HOUR-1 7-Segment' .
{
	    g_num1=0;          // Reset All Counters g_num1,2,3,4 .
		g_num2=0;
		g_num3=0;
		g_num4=0;

		if(g_num5<9){
	      g_num5++;        // Counter g_num5 incremented by one .
                }

		else{
          g_num5=0;        // Reset The Counter g_num5 .
            }

g_tick3=0;                 // Reset The Counter g_tick3 .

}



if(g_tick4==HOUR2)         // Loop-5 To Count , For 'HOUR-2 7-Segment' .
{
	    g_num1=0;          // Reset All counters g_num1,2,3,4,5  .
		g_num2=0;
		g_num3=0;
		g_num4=0;
		g_num5=0;

       if(g_num6<9){
	    g_num6++;          // Counter g_num6 incremented by one .
                   }

       else{
	     g_num6=0;         // Reset The Counter g_num6 .
           }

g_tick4=0;                 // Reset The Counter g_tick4 .
}


}

void INT0_Init(void)          //External Interrupt-0 Initialization .
{
	DDRD  &= (~(1<<PD2));     //SET PIN-2 PORT-D as Input pin 'For Push Button'.
	PORTD|=(1<<PD2);          //Select and enable 'Internal Pull-up Resistor ' .
	MCUCR |=  (1<<ISC01);     //Select and Enable 'Falling Edge Mode'
	MCUCR &= ~(1<<ISC00);     //.
	GICR  |= (1<<INT0);       //select External Interrupt-0 .

}

void INT1_Init(void)                  //External Interrupt-1 Initialization .
{
	DDRD  &= (~(1<<PD3));             //SET PIN-3 PORT-D as Input pin 'For Push Button' 'External Pull-Down Resistor'  .
    MCUCR |= (1<<ISC11)|(1<<ISC10);   //Select and Enable 'Raising Edge Mode' .
    GICR  |= (1<<INT1);               //Select External Interrupt-1 .

}

void INT2_Init(void)            //External Interrupt-2 Initialization .
{
	DDRB   &= (~(1<<PB2));      //SET PIN-2 PORT-B as Input pin 'For Push Button'.
	PORTB|=(1<<PB2);            //Select and enable 'Internal Pull-up Resistor ' .
    MCUCSR &= ~(1<<ISC2);       //Select and Enable 'Falling Edge Mode' .
    GICR   |= (1<<INT2);        //select External Interrupt-2 .

}


void TIMER1_INIT(void)                     // TIMER-1 'CTC Mode' Initialization .
{

TCNT1=0;                                   // Start Count from 0 .
OCR1A=980;                                 // count to 980  to count 1 second .
TIMSK|=(1<<OCIE1A);                        // Enable Interrupt for CTC Mode .
TCCR1A=(1<<FOC1A);                         // set for non-PWM needed .
TCCR1B=(1<<CS10)|(1<<CS12)|(1<<WGM12);     // Select CTC Mode With PreScaler 1024 .
}

void Seg7ment (void)
{
	    DDRA |= 0x3F ;   // Configure The First 6 Pins in PORT-A as OutPut Pins .
		PORTA &= 0xC0 ;  // Clear First 4-PINs in PORT-A .
		DDRC |= 0x0F;    // Configure The First 4 Pins in PORT-C as OutPut Pins .
		PORTC &= 0xF0;   // Clear This  PINS .
}

int main(void)
{
    SREG  |= (1<<7);    // The Global Interrupt Enable Pin  (I-Bit) .
    TIMER1_INIT();      // Call TIMER-1 Initialization .
    Seg7ment ();        // Call 7-Segment Initialization .
    INT0_Init();        // Call Interrupt-0 Initialization .
	INT1_Init();        // Call Interrupt-1 Initialization .
	INT2_Init();        // Call Interrupt-2 Initialization .


while(1){

	   PORTA&=0xC0;                                 // Clear First 4-PINS in PORT-A
	   PORTA |=(1<<PA0);                            // Enable   The First 7-Segment  .
	   PORTC = (PORTC & 0xF0) | (g_num1 & 0x0F);    // Display  The g_num1 ON It .
       _delay_us(50);                               // Delay 50 microSecond .

       PORTA&=0xC0;                                 // Clear First 4-PINS in PORT-A
       PORTA |=(1<<PA1);                            // Enable   The Second 7-Segment .
       PORTC = (PORTC & 0xF0) | (g_num2 & 0x0F);    // Display  The g_num2 ON It .
       _delay_us(50);                               // Delay 50 microSecond .

       PORTA&=0xC0;                                 // Clear First 4-PINS in PORT-A
       PORTA |=(1<<PA2);                            // Enable   The Third 7-Segment .
	   PORTC = (PORTC & 0xF0) | (g_num3 & 0x0F);    // Display  The g_num3 ON It .
       _delay_us(50);                               // Delay 50 microSecond .

       PORTA&=0xC0;                                 // Clear First 4-PINS in PORT-A
       PORTA |=(1<<PA3);                            // Enable The Fourth 7-Segment .
       PORTC = (PORTC & 0xF0) | (g_num4 & 0x0F);    // Display The g_num4 ON It  .
       _delay_us(50);                               // Delay 50 microSecond .

       PORTA&=0xC0;                                 // Clear First 4-PINS in PORT-A
       PORTA |=(1<<PA4);                            // Enable The Fifth 7-Segment .
       PORTC = (PORTC & 0xF0) | (g_num5 & 0x0F);    // Display g_num5 ON It .
       _delay_us(50);                               // Delay 50 microSecond .

       PORTA&=0xC0;                                 // Clear First 4-PINS in PORT-A
       PORTA |=(1<<PA5);                            // Enable The Sixth 7-Segment .
       PORTC = (PORTC & 0xF0) | (g_num6 & 0x0F);    // Display g_num6 ON It .
       _delay_us(50);                               // Delay 50 microSecond .

	     }
}
