#include "uart.h"

void USART_Init(USART_TypeDef *USART_num, Baudrate_t Baudrate)
{
	if(USART_num == USART1)
	{
		//Enable the USART1 clock
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
		//Config pin A9  - TXD
		GPIO_Init(GPIOA, 9, OUT_HIGH, AF_PP);
		//Config pin A10 - RXD
		GPIO_Init(GPIOA, 10, IN, PU_PD);
	}
	else if(USART_num == USART2)
	{
		//Enable the USART2 clock
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
		//Config pin A2  - TXD
		GPIO_Init(GPIOA, 2, OUT_HIGH, AF_PP);
		//Config pin A3 - RXD
		GPIO_Init(GPIOA, 3, IN, PU_PD);
	}
	else if(USART_num == USART3)
	{
		//Enable the USART clock
		RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
		//Config pin B10  - TXD
		GPIO_Init(GPIOB, 10, OUT_HIGH, AF_PP);
		//Config pin B11 - RXD
		GPIO_Init(GPIOB, 11, IN, PU_PD);
	}
	//Select the desired baud rate
	USART_num->BRR = Baudrate;
	
	USART_num->CR1 |= USART_CR1_TE  //Transmitter enable
								 | USART_CR1_RE		//Receiver enable
								 | USART_CR1_UE;  //USART enable

}

void USART_Transmit(USART_TypeDef *USART_num, uint8_t *data, uint32_t length)
{
	for(int i=0; i<length; i++)
		{
			USART1->DR = data[i];
			while(!(USART_num->SR & USART_SR_TC)); //Transmission complete
		}
}

void USART_Receive(USART_TypeDef *USART_num, uint8_t *data, uint32_t length)
{
	while(!(USART_num->SR & USART_SR_RXNE));
	for(int i=0; i<length; i++)
	{
		data[i] = USART_num->DR;
		while((USART_num->SR & USART_SR_RXNE));
	}
}