

#include "DriverJeuLaser.h"

extern int DFT_ModuleAuCarre( short int * Signal64ech, char k);
extern short int LeSignal;
// Ecrire sur un tableau les valeurs acquise par notre plaque �l�ctronique
// 64 Valeurs � 320kHZ
// periodicit� ~5 ms
short int dma_buf[64];
//tab de tab
int dftab[64];
void DFT() {
	for(int i=0; i<64; i++) {
		 dftab[i]=DFT_ModuleAuCarre(dma_buf,i);
	}
}

void DFTtest() {
		 dftab[1]=DFT_ModuleAuCarre(&LeSignal,1);
}


void callbackSystick(void) {
	Start_DMA1(64);

	Wait_On_End_Of_DMA1();
		
	DFT();
	Stop_DMA1;
}




	
	
int main(void)
{

	// ===========================================================================
	// ============= INIT PERIPH (faites qu'une seule fois)  =====================
	// ===========================================================================
	
	CLOCK_Configure();

	Init_TimingADC_ActiveADC_ff( ADC1, 72 );
	Single_Channel_ADC( ADC1, 2 );
	Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );
	Init_ADC1_DMA1( 0, dma_buf );

	// Apr�s ex�cution : le coeur CPU est clock� � 72MHz ainsi que tous les timers


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

