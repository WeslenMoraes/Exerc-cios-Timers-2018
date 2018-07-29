
/* Includes */
#include "stm32f4xx.h"
/**
**===========================================================================
**
**  PINOS UTILIZADOS
**  PC[]={btn0,btn1,btn2,btn3,btn4,btn5,btn6}
**  PB0 = ALTO-FALANTE 8 ohms, 0.5W, com resistor de 220 ohms na alimentação
**
**===========================================================================
*/
/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void)
{
	uint16_t btn;
	uint16_t btnc;
	//					F4		  G4        G#4       A#4       C5        D#5
	//uint16_t notas[]={37.17923, 33.01360, 31.10531, 27.60248, 24.48176, 21.70160};//habilite para tocar pumped up kicks
	//					B4        A4        G4        F4        E4        D4        C4
	uint16_t notas[]={25.99711, 29.30303, 33.01360, 37.17923, 39.44939, 44.40398, 49.96256};

	RCC->AHB1ENR=RCC_AHB1ENR_GPIOBEN|RCC_AHB1ENR_GPIOCEN;
	GPIOB->MODER&=~0x3;
	GPIOB->MODER|=0x1;
	GPIOC->MODER&=~0x3FFF;

	RCC->APB2ENR=RCC_APB2ENR_TIM10EN;
	TIM10->PSC=599;
	TIM10->ARR=53.99422;
	TIM10->CR1=TIM_CR1_CEN;
  /* Infinite loop */
  while (1)
  {

	  btn=GPIOC->IDR&=0x7F;

	  if(btn==0x1)btnc=0;
	  else if(btn==0x2)btnc=1;
	  else if(btn==0x4)btnc=2;
	  else if(btn==0x8)btnc=3;
	  else if(btn==0x10)btnc=4;
	  else if(btn==0x20)btnc=5;
	  else if(btn==0x40)btnc=6;

	  TIM10->ARR=notas[btnc];

	  if(TIM10->SR&TIM_SR_UIF){
		  TIM10->SR=~TIM_SR_UIF;
		  GPIOB->ODR^=0x1;
		  if(btn==0x0)GPIOB->ODR=0x0;
	  }
  }
}
