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
#define BOTAO_ATIVADOA !(PIND & (1<<PIND2))
#define BOTAO_ATIVADOB !(PIND & (1<<PIND3))

void enviaDado(char dado)
{
	PORTB = dado;
	PORTC |= (0x01);
	PORTC &= ~(0x02);
	PORTC |= (0x04);
	_delay_ms(20);
	PORTC &= ~(0x04);	
}

void enviaMensagem(char mensagem[])
{
	for (int i = 0; i < strlen(mensagem); i++)
	{
		enviaDado(mensagem[i]);
	}
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
	//UDR0 = byteRecebido;
	enviaDado(byteRecebido);
}

ISR(PCINT2_vect)
{
	//enviaDado('A');
	if(BOTAO_ATIVADOA){
		enviaDado('A');
		//PORTD2 = 0;
	}
	
	if(BOTAO_ATIVADOB){ 
		enviaDado('B');
		//PORTD3 = 1;
	}
}


int main(void)
{
	DDRD = 0x00;
	PORTD = 0x0c;
	USART_init(BRC);
	DDRB = 0xff;
	DDRC = 0x07;
	PORTB = 0xff;
	PCMSK2 |= (1<<PCINT18);
	PCMSK2 |= (1<<PCINT19);
	PCICR |= (1<<PCIE2);
	sei();
	inicializa();
    while (1) 
    {
		 
    }
}

