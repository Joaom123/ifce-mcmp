/*
 * 2-7Seg-Botao.c
 *
 * Created: 20/08/2019 20:46:22
 * Author : joaom
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "numeros.h"

#define BOTAO_ATIVADO (PIND & (1<<PIND7))

/*
*
*/
ISR(PCINT2_vect)
{
	if (BOTAO_ATIVADO)
	{
		adicionaUnidade(PORTD, &PORTD);
	}
}

int main(void)
{
	//Configuração das portas
	DDRD = 0x7f;		//Todas as portas de D como output e 7D como input
	PORTD = 0x3F;		//Todas as portas de D como 0
	DDRB = 0xff;		//Todas as portas de B como output
	PORTB = 0x3F;		//Todas as portas de B como 0
	
	PCMSK2 |= (1<<PCINT23);
	PCICR |= (1<<PCIE2);
	
	sei();
	
    while (1) 
    {
		
    }
}

