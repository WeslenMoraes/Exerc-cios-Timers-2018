
//SEMÁFORO 2 TEMPOS

/* Includes */
#include "stm32f4xx.h"

/**
**===========================================================================
**
**  Pinos Utilizados
**	PB[]={Vd0,Am0,Vm0,Vd1,Am1,Vm1}
**	6 LED's nas cores verde, amarelo e vermelho, montados em série com resistores 220 ohms
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
	uint8_t t;

	RCC->AHB1ENR=RCC_AHB1ENR_GPIOBEN;
	GPIOB->MODER&=~0xfff;
	GPIOB->MODER|=0x555;

	RCC->APB2ENR=RCC_APB2ENR_TIM10EN;
	TIM10->PSC=999;
	TIM10->ARR=1599;
	TIM10->CR1=TIM_CR1_CEN;

  while (1)
  {
	if(TIM10->SR&TIM_SR_UIF){

		TIM10->SR=~TIM_SR_UIF;

		t++;

		switch(t){
		case 1:
			GPIOB->ODR=0x21;
		break;
		case 8:
			GPIOB->ODR=0x12;
		break;
		case 11:
			GPIOB->ODR=0xc;
		break;
		case 18:
			GPIOB->ODR=0x12;
		break;
		case 20:
			t=0;
		break;
		}
	}
  }//end of while(1)
}//end of main
