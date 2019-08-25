/*
 * 4-dig-7-seg-botao.c
 *
 * Created: 24/08/2019 02:01:21
 * Author : João Marcus
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "numeros.h"

#define BOTAO_ATIVADO (PIND & (1<<PIND7))

volatile int digitos[4]; 
int numeroASerExibido = 9990;

/**
*
*/
ISR(PCINT2_vect)
{
	if (BOTAO_ATIVADO)
	{
		numeroASerExibido++;
	}
}

/**
* Liga e desliga um display de 7 seg
*/
void liga_desliga_display()
{
	static int j = 0;
	(j==4)?j=0:j++;
	PORTB &=(0b11110000); //Ativa display na porta j
	PORTB|=(1<<j);
	mostraNumeroNoDisplay(digitos[j]);
}

/**
*	Guarda os dígitos na lista digitos[4]
*	Parâmetros: int numero -> número a ser exibido no display
*/
void guardaDigitos(int numero)
{
	if(numero > 9999) numeroASerExibido=0;
 	int i = 0;
	while(numero)
	{
		digitos[i] = numero%10;
		i++;
		numero = numero/10;
	}
	for (int j=i; j<4; j++) digitos[j] = 0;

}

int main(void)
{
	//Configuração das portas
	DDRD = 0x7f;		//Porta 7D como input e as outras como output
	PORTD = 0x00;		//Valor inicial da port D
	DDRB = 0xff;		//Todas as portas de B como output
	PORTB = 0x01;		//PINB0 como 1 (display das unidades)
	
	PCMSK2 |= (1<<PCINT23);		//Habilitando pin change mask na porta int23
	PCICR |= (1<<PCIE2);		//Habilitando pin change interrupt na pcie2
	
	sei();		//permitindo interrupções globais
	
    while (1) 
    {
		guardaDigitos(numeroASerExibido);
		liga_desliga_display();		
    }
	return 0;
}

