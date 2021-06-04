

#include "DriverJeuLaser.h"
#include "GestionSon.h"
#include "Affichage_Valise.h"

extern int DFT_ModuleAuCarre( short int * Signal64ech, char k);
extern short int LeSignal;
// Ecrire sur un tableau les valeurs acquise par notre plaque éléctronique
// 64 Valeurs à 320kHZ
// periodicité ~5 ms
short int dma_buf[64];
//tab de tab
int dftab[64];
int X =0x00FFFFFF;// valeur seuil
int scorejoueur[4];
int Joueurtemps[4];
int ctimer=21; // pour prendre le premier tir
int i=0;
int Timeravant=0;

void DFT() {
	for(int i=0; i<64; i++) {
		 dftab[i]=DFT_ModuleAuCarre(dma_buf,i);
	}
}

void DFTtest() {
		 dftab[1]=DFT_ModuleAuCarre(&LeSignal,1);
}

void pointComp() {
		ctimer++;
		if (dftab[17]>X) {
			if((ctimer-Joueurtemps[0])>20){ // si 100 ms sont passés soit un tir de laser
				scorejoueur[0]++;
				Joueurtemps[0] = ctimer;
				startSon();
				Prepare_Afficheur(1,scorejoueur[0]);
				Mise_A_Jour_Afficheurs_LED();
			}
		}
		if (dftab[18]>X) {
			if((ctimer-Joueurtemps[1])>20){ // si 100 ms sont passés soit un tir de laser
			
				scorejoueur[1]++;
				Joueurtemps[1] = ctimer;
				startSon();
				Prepare_Afficheur(2,scorejoueur[1]);
				Mise_A_Jour_Afficheurs_LED();
			}
		}
		if (dftab[19]>X) {
			if((ctimer-Joueurtemps[2])>20){ // si 100 ms sont passés soit un tir de laser
			
				scorejoueur[2]++;
				Joueurtemps[2] = ctimer;
				startSon();
				Prepare_Afficheur(3,scorejoueur[2]);
				Mise_A_Jour_Afficheurs_LED();
			}
		}
		if (dftab[20]>X) {
			if((ctimer-Joueurtemps[3])>20){ // si 100 ms sont passés soit un tir de laser
			
				scorejoueur[3]++;
				Joueurtemps[3] = ctimer;
				startSon();
				Prepare_Afficheur(4,scorejoueur[3]);
				Mise_A_Jour_Afficheurs_LED();
			}
		}
		if (ctimer>240000) {// toutes les 20 mins
			ctimer -= 240000;
			for(int i=0;i<4;i++){
		
				Joueurtemps[i]=0;
			
		}
	}

}
void callbackSystick(void) {
	Start_DMA1(64);

	Wait_On_End_Of_DMA1();
		
	DFT();
	//Mise_A_Jour_Afficheurs_LED(void)
		
	pointComp();
		
	// 18 à  23incrémenter le score
	Stop_DMA1;
}
// Chaque 5 s la cible change

void changecible(){
	if( ctimer- Timeravant > 1000) {
		Prepare_Clear_LED(i);
		i= i+1 %6;
		Timeravant = ctimer;

		Choix_Capteur(i);
		Prepare_Set_LED(i);
	}
}



	
	
int main(void)
{

	// ===========================================================================
	// ============= INIT PERIPH (faites qu'une seule fois)  =====================
	// ===========================================================================
	
	Timer_1234_Init_ff( TIM4, 6552); //x*1/72MHz = 91 µs -> x = 6552
	Active_IT_Debordement_Timer( TIM4, 2, callbackSon ); 
	PWM_Init_ff(TIM3, 3, 720); //-> 10^5 de fréquence
	GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
	PWM_Set_Value_TIM3_Ch3( (unsigned short int)720); // Clock 
	CLOCK_Configure();
	
	
	Init_Affichage();
	for(int i=0;i<4;i++){
		scorejoueur[i]=0;
		Joueurtemps[i]=0;
	}
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
		
	}
}

