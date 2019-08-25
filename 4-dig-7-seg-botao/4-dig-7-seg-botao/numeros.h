//Definindos os dígitos no display de 7 segmentos
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
* Mostra número no display (PORT D)
* Parâmetros: int numero -> numero de 0 a 9 a ser exibido
*/
void mostraNumeroNoDisplay(int numero)
{
	switch(numero)
	{
		case 0:
			PORTD = ZERO;
			break;
		case 1:
			PORTD = UM;
			break;
		case 2:
			PORTD = DOIS;
			break;
		case 3:
			PORTD = TRES;
			break;
		case 4:
			PORTD = QUATRO;
			break;
		case 5:
			PORTD = CINCO;
			break;
		case 6:
			PORTD = SEIS;
			break;
		case 7:
			PORTD = SETE;
			break;
		case 8:
			PORTD = OITO;
			break;
		case 9:
			PORTD = NOVE;
			break;
		default:
			//PORTD = 0b11111101;
			break;
	}
}