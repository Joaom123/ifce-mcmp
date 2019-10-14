/*
 * interface-serial.c
 *
 * Created: 24/09/2019 19:21:11
 * Author : João Marcus e Nivardo
 */ 

#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#define FOSC 16000000
#define BAUD 28800
#define BRC FOSC/16/BAUD-1

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

void enviaDado(char dado)
{
	PORTB = dado;
	PORTC |= (0x01);
	PORTC &= ~(0x02);
	PORTC |= (0x04);
	_delay_ms(20);
	PORTC &= ~(0x04);	
}

void enviaComando(char comando)
{
	PORTB = comando;
	PORTC &= ~(0x01);
	PORTC &= ~(0x02);
	PORTC |= (0x04);
	_delay_ms(10);
	PORTC &= ~(0x04);
}

void inicializa()
{
	enviaComando(0x38);
	enviaComando(0x0E);
	enviaComando(0x06);
	enviaComando(0x01);
}

/*void USART_init(unsigned int ubrr)
{	
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0A |= (1 << U2X0);
	UCSR0B |= (1 << RXEN0)|(1 << TXEN0);
	UCSR0B |= (1 << RXCIE0);
	UCSR0C = 0x2C;	//	7-bits paridade:par stopbit:2
}*/

//volatile char byteRecebido;

/*ISR(USART_RX_vect)
{
	byteRecebido = UDR0;
	UDR0 = byteRecebido;
	enviaDado(byteRecebido);
}*/

ISR(INT0_vect)
{
	enviaDado('A');
}

ISR(INT1_vect)
{
	enviaDado('B');
}

int main(void)
{
	DDRD = 0x00;
	PORTD = 0x0c;
	USART_init(BRC);
	DDRB = 0xff;
	DDRC = 0x07;
	PORTB = 0xff;
	
	EICRA |= (1 << ISC01);
	EIMSK |= (1 << INT0)|(1 << INT1);
	
	sei();
	inicializa();
    
    while (1) 
    {
		 
    }
}

