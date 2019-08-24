/**
* Número a serem exibidos no display de 7 segmentos
*/
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
