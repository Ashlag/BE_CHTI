	PRESERVE8
	THUMB   
	
	include ../Driver/DriverJeuLaser.inc

; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly


;Section RAM (read write):
	area    maram,data,readwrite
		
FlagCligno dcd 0

	
; ===============================================================================================
	


		
;Section ROM code (read only) :		
	area    moncode,code,readonly
	export timer_callback
; écrire le code ici		

timer_callback proc
	
	push {R4, R5, LR}
	ldr R5, =FlagCligno
	ldr R4, [R5]
	mov R0, #1

	cmp R4, #1
	bne PasEgal
	;if
	mov R4, #0
	bl GPIOB_Set

	b Continue
PasEgal
	;else
	mov R4, #1
	bl GPIOB_Clear

Continue
	str R4, [R5]
	
	pop {R4, R5, PC}
	
	endp

		
	END	