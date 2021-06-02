

#include "DriverJeuLaser.h"
#include "GestionSon.h"

extern int DFT_ModuleAuCarre( short int * Signal64ech, char k);
extern short int LeSignal;
// Ecrire sur un tableau les valeurs acquise par notre plaque éléctronique
// 64 Valeurs à 320kHZ
// periodicité ~5 ms
short int dma_buf[64];
//tab de tab
int dftab[64];
int X; // initier à une valeur
int scorejoueur[6];
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
	//Mise_A_Jour_Afficheurs_LED(void)
		
		if (dftab[18]>X) {
			scorejoueur[0]++;
		}
		if (dftab[19]>X) {
			scorejoueur[1]++;
		}
		if (dftab[20]>X) {
			scorejoueur[2]++;
		}
		if (dftab[21]>X) {
			scorejoueur[3]++;
		}
		if (dftab[22]>X) {
			scorejoueur[4]++;
		}
		if (dftab[23]>X) {
			scorejoueur[5]++;
		}
		
	// 18 à  23incrémenter le score
	Stop_DMA1;
}
// Chaque 5 s la cible change
/*
void changecible(){
	if( TIMERMAINTENANT - TimerAvant > 5s) {
		PrepareclearLed(i);
		i= i+1 %6;
		TimerAvant = Timermaintenant;

		Choix_Capteur(i);
		PreparesetLed(i);
		
}*/



	
	
int main(void)
{

	// ===========================================================================
	// ============= INIT PERIPH (faites qu'une seule fois)  =====================
	// ===========================================================================
	
	Timer_1234_Init_ff( TIM4, 6552); //x*1/72MHz = 91 µs -> x = 6552
	Active_IT_Debordement_Timer( TIM4, 2, callbackSon ); 
	PWM_Init_ff(TIM3, 3, 720); //-> 10^5 de fréquence
	GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
	CLOCK_Configure();
	//Init_Affichage();
	// for i 1 à 4
	//Prepare_Afficheur(i;0);
	Init_TimingADC_ActiveADC_ff( ADC1, 72 );
	Single_Channel_ADC( ADC1, 2 );
	Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );
	Init_ADC1_DMA1( 0, dma_buf );

	// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers


	///// ADC

	// Systick
	Systick_Period_ff(360000); // x*1/72MHz = 5 ms -> x = 360000
	Systick_Prio_IT(2, callbackSystick);
	SysTick_On;
	SysTick_Enable_IT;

	///
	// Traiter le signal DFT récupéré





//============================================================================	
	
while	(1)
	{
		//changecible()
	}
}

