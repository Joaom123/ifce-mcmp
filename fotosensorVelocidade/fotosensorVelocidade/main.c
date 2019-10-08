/*
 * fotosensorVelocidade.c
 *
 * Created: 03/10/2019 20:22:53
 * Author : Jo�o Marcus | Elysson | Paulo Ricardo | Nivardo
 */ 

#define F_CPU 16000000
#define BAUD 28800
#define BRC F_CPU/16/BAUD-1
#define TX_BUFFER_SIZE 128

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>

//Vari�veis
unsigned int contador; //Dist�ncia entre os sensores em metros
unsigned int distancia;//Tempo em milissegundos
volatile char byteRecebido;
char serialBuffer[TX_BUFFER_SIZE];
uint8_t serialReadPos = 0;
uint8_t serialWritePos = 0;

void appendSerial(char c)
{
	serialBuffer[serialWritePos] = c;
	serialWritePos++;
	if(serialWritePos >= TX_BUFFER_SIZE) serialWritePos = 0;
}

void serialWrite(char mensagem[])
{
	for (uint8_t i = 0; i < strlen(mensagem); i++) appendSerial(mensagem[i]);
	if (UCSR0A & (1 << UDRE0)) UDR0 = 0;
}

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

//Exibe mensagem no LCD
void exibeMensagem(char mensagem[])
{
	for(int i = 0; i < strlen(mensagem); i++) enviaDado(mensagem[i]);
}

void USART_init(unsigned int ubrr)
{
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	
	UCSR0A |= (1 << U2X0);
	
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
	UCSR0B |= (1 << RXCIE0) | (1 << TXCIE0);
	
	UCSR0C = (1 << UCSZ01 ) | (1 << UCSZ00);
}

//Exibe a velocidade no LCD
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

//TODO: calcular distancia entre os sensores
int calculaDistancia()
{
	return 0;
}

ISR(INT0_vect)
{
	contador = 0;
}

ISR(INT1_vect)
{
	int velocidade = calculaVelocidade(distancia, contador);
	exibeVelocidade(velocidade);
	exibeMensagem("km/h");
}

ISR(USART_TX_vect)
{
	//UDR0 = byteRecebido;
	if(serialReadPos != serialWritePos)
	{
		UDR0 = serialBuffer[serialReadPos];
		serialReadPos++;
		
		if(serialReadPos >= TX_BUFFER_SIZE)
		{
			serialReadPos++;
		}
	}
}

//Conta a cada x ms
ISR(TIMER0_OVF_vect)
{
	contador++;
}

ISR(USART_RX_vect)
{
	byteRecebido = UDR0;
	//enviaDado(byteRecebido);
	if(byteRecebido < 54 && byteRecebido > 50){
		//enviaDado(byteRecebido);
		distancia = (unsigned int)(byteRecebido - '0');
		char mensagemASerExibida[50];
		sprintf(mensagemASerExibida, "Distancia selecionada: %d metros\n\r", distancia);
		serialWrite(mensagemASerExibida);
	}else{
		serialWrite("Distancia entre 3 e 5 metros! Entre com um novo valor! \n\r");
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
	
	EICRA |= (1 << ISC01);		//Ativa registrador interrup��o externa
	EIMSK |= (1 << INT0)|(1 << INT1);		//Ativa interrup��o de int0 e int1
	
	TIMSK0 |= (1 << TOIE0); //Ativa timer overflow interrupt
	
	sei();
	
	inicializa();
	
	TCCR0B |= (1 << CS02);		//Prescaler 256
	
	_delay_ms(200);
	serialWrite("Digite o tamanho da dist�ncia em metros:\n\r");

    while (1) 
    {
		
    }
}

