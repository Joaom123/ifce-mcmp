/*
 * fotosensorVelocidade.c
 *
 * Created: 03/10/2019 20:22:53
 * Author : João Marcus | Elysson | Paulo Ricardo | Nivardo
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
#include <stdio.h>

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

void exibeMensagem(char mensagem[])
{
	for(int i = 0; i < strlen(mensagem); i++)
	{
		enviaDado(mensagem[i]);
	}
}


//Exibe a velocidade no lcd
void exibeVelocidade(int velocidade)
{
	char mensagem[3];
	sprintf(mensagem, "%d", velocidade);
	exibeMensagem(mensagem);
}

void inicializa()
{
	enviaComando(0x38);
	enviaComando(0x0E);
	enviaComando(0x06);
	enviaComando(0x01);
}

//distancia em metros
//tempo em ms
int calculaVelocidade(int distancia, int variacaoDeTempo)
{
	int velocidade = (distancia*1000*3.6)/variacaoDeTempo;
	return velocidade; //Velocidade em km/h
}


//TODO
int calculaDistancia()
{
	return 0;
}

unsigned int contador;

ISR(INT0_vect)
{
	contador = 0;
}


ISR(INT1_vect)
{
	int velocidade = calculaVelocidade(3, contador);
	exibeVelocidade(velocidade);
	exibeMensagem("km/h");
}

//Conta a cada x ms
ISR(TIMER0_OVF_vect)
{
	contador++;
}

int main(void)
{
	DDRD = 0x00;
	PORTD = 0x0c;
	DDRB = 0xff;
	DDRC = 0x07;
	PORTB = 0xff;
	
	EICRA |= (1 << ISC01);		//Ativa registrador interrupção externa
	EIMSK |= (1 << INT0)|(1 << INT1);		//Ativa interrupção de int0 e int1
	
	TIMSK0 |= (1 << TOIE0); //Ativa timer overflow interrupt
	
	sei();
	
	inicializa();
	
	TCCR0B |= (1 << CS02);		//Prescaler 256

    while (1) 
    {
		
    }
}

