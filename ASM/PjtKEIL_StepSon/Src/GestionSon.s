	PRESERVE8
	THUMB   
		
	;include bruitverre.asm
	import Son
	include ../Driver/DriverJeuLaser.inc

; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly


;Section RAM (read write):
	area    maram,data,readwrite
		
SortieSon dcd 0
index dcd 5512 ;mettre 5512 pour ne pas avoir le 1e son de verre quoi qu'il arrive 

; ===============================================================================================
	


		
;Section ROM code (read only) :		
	area    moncode,code,readonly
; écrire le code ici		
	export SortieSon
	export callbackSon
	export startSon
		
callbackSon proc
	push {LR}
	;SON  est un label, pas une variable. Load Son dans un registre, puis se décaler ? 
	; on mettra Son dans un registre 
	ldr R1, =Son
	ldr R2, =index
	ldr R3, [R2]
	
	;Test fin échantillon sonore
	mov R0, #5512
	cmp R3, R0
	beq reset

	;LDR SortieSon,[Son,index lsl #4] 
	LDRSH R0,[R1,R3, lsl #1]
	;normalisation
	mov R1,#45
	MUL R0,R1
	ASR R0,#12
	add R0,#360
	;Incrémentation
	
	add R3, #1
	;5512 lignes de son, donc si index = 5511 => index :=0
	str R3, [R2]
	; R2 libre post manip d'index, donc utilisable sans push
	ldr R2, =SortieSon
	str R0, [R2]
	
	;bl qui se fait ici pour ne pas utiliser SortieSon mais le PWM
	bl PWM_Set_Value_TIM3_Ch3
	
reset
	
	pop {PC}

	endp
		
startSon proc
	push {LR}
	;on charge l'index et on reinitialise sa valeur pour revenir au début du son
	ldr R1, =index
	ldr R0, [R1]
	mov R0, #0
	str R0, [R1]
	pop {PC}
	endp
		
	END