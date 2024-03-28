
/*************************************
 * main.c                            *
 *                                   *
 * Created: 3/25/2024 10:12:33 PM    *
 * Author: Gerson Yaser              *
 * Pin External Interruption         *
 * Turn on ligth with SSR			 *
 *					                 *
 * Device: ATmega328P                *
 * Frequency: 8 MHz to 5V            *
 * Test: It developed in breadboard  *
 *                                   *
 *************************************/

#define F_CPU 8000000UL
#include <xc.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

uint8_t light = 0;

int main(void)
{
	/* PCICR – Pin Change Interrupt Control Register */
	PCICR |= (1 << PCIE0);
	
	/* PCMSK0 – Pin Change Mask Register 0 */
	PCMSK0 |= (1 << PCINT0);
	
	/* Light Pin */
	DDRB |= (1 << DDB1);
	
	sei (); /* Global interruption */
	
    while(1)
    {
		if(light == 1)
		{
			PORTB |= (1 << PORTB1);
			_delay_ms(1000);
			PORTB &= ~(1 << PORTB1);
			_delay_ms(1000);
			PORTB |= (1 << PORTB1);
			_delay_ms(1000);
			PORTB &= ~(1 << PORTB1);
			
			light = 0;
		}
    }
}

ISR (PCINT0_vect)
{
	light = 1;
}