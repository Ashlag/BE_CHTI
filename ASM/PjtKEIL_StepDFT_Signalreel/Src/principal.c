

#include "DriverJeuLaser.h"

extern int DFT_ModuleAuCarre( short int * Signal64ech, char k);

// Ecrire sur un tableau les valeurs acquise par notre plaque �l�ctronique
// 64 Valeurs � 320kHZ
// periodicit� ~5 ms
short int dma_buf[64];
//tab de tab
short int dftab[64];
void DFT(short int * dma) {
	for(int i=0; i<64; i++) {
		 dftab[i]=DFT_ModuleAuCarre(dma,i);
	}
}
void callbackSystick(void) {
	Start_DMA1(64);

	Wait_On_End_Of_DMA1();
		
	DFT(dma_buf);
	Stop_DMA1;
}




	
	
int main(void)
{

	// ===========================================================================
	// ============= INIT PERIPH (faites qu'une seule fois)  =====================
	// ===========================================================================
	Init_TimingADC_ActiveADC_ff( ADC1, 72 );
	Single_Channel_ADC( ADC1, 2 );
	Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );
	Init_ADC1_DMA1( 0, dma_buf );

	// Apr�s ex�cution : le coeur CPU est clock� � 72MHz ainsi que tous les timers

	CLOCK_Configure();

	///// ADC

	// Systick
	Systick_Period_ff(360000); // x*1/72MHz = 5 ms -> x = 360000
	Systick_Prio_IT(2, callbackSystick);
	SysTick_On;
	SysTick_Enable_IT;

	///
	// Traiter le signal DFT r�cup�r�






	//============================================================================	


	while	(1)
	{
	}
}

