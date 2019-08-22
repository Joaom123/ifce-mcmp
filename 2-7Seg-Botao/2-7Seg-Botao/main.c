/*
 * 2-7Seg-Botao.c
 *
 * Created: 20/08/2019 20:46:22
 * Author : joaom
 */ 

#include <avr/io.h>
//#define F_CPU 16000000L //16 MHz
//#include <util/delay.h>
#include <avr/interrupt.h>


#define BOTAO_ATIVADO (PIND & (1<<PIND7))

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

/**
* Adiciona uma unidade no display 
* Parâmetros:	valorPorta: Valor que está exibido no display
*				*port: Ponteiro referência da porta do display
*/
void adicionaUnidade(uint8_t valorPorta, volatile uint8_t *port)
{
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
			if(port == &PORTD)adicionaUnidade(PORTB, &PORTB);
			break;
	}
}

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

