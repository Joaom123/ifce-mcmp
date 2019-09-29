/*
 * interface-serial.c
 *
 * Created: 24/09/2019 19:21:11
 * Author : João Marcus e Nivardo
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#define F_CPU 1000000
#include <util/delay.h>
#define BAUD 4800
#define BRC ((F_CPU/16/BAUD)-1)

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

void USART_init(unsigned int ubrr)
{	
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
	UCSR0B |= (1 << RXCIE0);
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
}

volatile char byteRecebido;

ISR(USART_RX_vect)
{
	byteRecebido = UDR0;
	UDR0 = byteRecebido;
	enviaDado(byteRecebido);
}

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

