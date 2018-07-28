
/* Includes */
#include "stm32f4xx.h"
#define LED GPIO_ODR_ODR_5
#define multTimer100 10
/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void)
{
	uint8_t sw=0x0, pisc=0;

	RCC->AHB1ENR=RCC_AHB1ENR_GPIOAEN|RCC_AHB1ENR_GPIOCEN;
	GPIOA->MODER&=~(GPIO_MODER_MODER5);
	GPIOA->MODER|=(GPIO_MODER_MODER5_0);
	GPIOC->MODER&=~0xC00F;

	RCC->APB2ENR=RCC_APB2ENR_TIM10EN;
	TIM10->PSC=999;
	TIM10->ARR=1599;
	TIM10->CR1|=TIM_CR1_CEN;

  /* Infinite loop */
  while (1)
  {
	  sw=GPIOC->IDR;
	  sw&=0x83;

	  if(TIM10->SR&TIM_SR_UIF){

		  TIM10->SR=~TIM_SR_UIF;

		  if(pisc==10){
			  pisc=0;
		  }

		  switch(sw){
		  case 0x0://Funcionamento ok
			  GPIOA->ODR=LED;
		  break;
		  case 0x1://Falha de comunicação
			  if(pisc<2)
				  GPIOA->ODR^=LED;
			  else if(pisc>=2)
				  GPIOA->ODR&=~LED;
		  break;
		  case 0x2://Entradas digitais abertas
			  if(pisc<4)
				  GPIOA->ODR^=LED;
			  else if(pisc>=4)
				  GPIOA->ODR&=~LED;
		  break;
		  case 0x3://Termopar aberto
			  if(pisc<6)
				  GPIOA->ODR^=LED;
			  else if(pisc>=6)
				  GPIOA->ODR&=~LED;
		  break;
		  case 0x80://Curto na saída
			  if(pisc<8)
				  GPIOA->ODR^=LED;
			  else if(pisc>=8)
				  GPIOA->ODR&=~LED;
		  break;
		  case 0x81:
			  if(pisc<10)//Fusível aberto
				  GPIOA->ODR^=LED;
			  else if(pisc>=10)
				  GPIOA->ODR&=~LED;
		  break;
		  }

		  pisc++;

	  }

  }//end of while(1)
}//end of main
