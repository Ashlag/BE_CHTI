

#include "DriverJeuLaser.h"
#include "GestionSon.h"

int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Apr�s ex�cution : le coeur CPU est clock� � 72MHz ainsi que tous les timers
CLOCK_Configure();

Timer_1234_Init_ff( TIM4, 6552); //x*1/72MHz = 91 �s -> x = 6552
Active_IT_Debordement_Timer( TIM4, 2, callbackSon ); 
PWM_Init_ff(TIM3, 3, 720); //-> 10^5 de fr�quence
GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);



	
	

//============================================================================	
	
startSon(); //test startSon
while	(1)
	{
		
	}
}

