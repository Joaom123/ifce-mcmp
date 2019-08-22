/*
 * 2-7Seg-Botao.c
 *
 * Created: 20/08/2019 20:46:22
 * Author : joaom
 */ 

#include <avr/io.h>
//#define F_CPU 16000000UL //16 MHz
#define F_CPU 1000000UL
#include <util/delay.h>

#define ZERO 0x3F
#define UM 0x06
#define DOIS 0x5B
#define TRES 0x4F
#define QUATRO 0x66
#define CINCO 0x6D
#define SEIS 0x7D
#define SETE 0x07
#define OITO 0x7F
#define NOVE 0x67

uint8_t listaNumeros[10] = {ZERO, UM, DOIS, TRES, QUATRO, CINCO, SEIS, SETE, OITO, NOVE};

void adicionaUnidade(uint8_t valorPorta, volatile uint8_t *port)
{
	_delay_ms(200);
	switch(valorPorta)
	{
		case ZERO:
			*port = UM;
			break;
		
		case UM:
			*port = DOIS;
			break;
		
		case DOIS:
			*port = TRES;
			break;
		
		case TRES:
			*port = QUATRO;
			break;
		
		case QUATRO:
			*port = CINCO;
			break;
		
		case CINCO:
			*port = SEIS;
			break;
			
		case SEIS:
			*port = SETE;
			break;
			
		case SETE:
			*port = OITO;
			break;
			
		case OITO:
			*port = NOVE;
			break;
			
		case NOVE:
			*port = ZERO;
			adicionaUnidade(PORTB, &PORTB);
			break;
	}
}

int main(void)
{
	//Configuração das portas
	DDRD = 0x7f;		//Todas as portas de D como output e 7D como input
	PORTD = 0x3F;		//Todas as portas de D como 0
		
	DDRB = 0xff;		//Todas as portas de B como output
	PORTB = 0x3F;		//Todas as portas de B como 0
	
	
	
    while (1) 
    {
		if(PIND & (1<<PIND7))
		{
			adicionaUnidade(PORTD, &PORTD);
		}
    }
}

