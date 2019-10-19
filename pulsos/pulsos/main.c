/*
 * pulsos.c
 *
 * Created: 03/10/2019 20:22:53
 * Author : João Marcus | Elysson | Paulo Ricardo | Nivardo
 */ 

#define F_CPU 8000000UL //8 MHz
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void delay_ms(int tempo)
{
	for (int i = 0; i < tempo; i++) _delay_ms(1);
}

/*
*Entrada: velocidade em km/h | distancia em metros
*Saida: variação de tempo em milissegundos
*/
int calculaTempo(int distancia, int velocidade)
{
	int variacaoDeTempo = (distancia*1000*3.6)/velocidade;
	return variacaoDeTempo;
}

/*
*Entrada: número da porta em que haverá pulso
*/
void criaPulso(int numeroDaPorta)
{
	PORTB |= (1 << numeroDaPorta);
	PORTB &= ~(1 << numeroDaPorta);
}

/*
*Entrada: variação do tempo em milissegundos
*/
void enviaPulsos(int variacaoDeTempo)
{
	criaPulso(0); //Pulso na porta B0
	delay_ms(variacaoDeTempo); //Espera tempo em ms
	criaPulso(1); //Pulso na porta B1
}

ISR(INT0_vect)
{
	enviaPulsos(calculaTempo(5, 50));
	delay_ms(1000);
	enviaPulsos(calculaTempo(5, 100));
	delay_ms(1000);
	enviaPulsos(calculaTempo(5, 65));
	delay_ms(1000);
	enviaPulsos(calculaTempo(5, 120));
}

int main(void)
{
	DDRB = 0xff;
	PORTB = 0x00;
	
	DDRD = 0x00;
	PORTD = 0x0c;
	
	EICRA |= (1 << ISC01);		//Ativa registrador interrupção externa
	EIMSK |= (1 << INT0);		//Ativa interrupção de int0
	
	sei();
	
    while (1)
    {
		
    }
}
