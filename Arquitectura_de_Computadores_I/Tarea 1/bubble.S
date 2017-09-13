			;		@autor Malcolm Davis 201271325
			;		Explicación: Se cargan los registros de memoria[la posisión que indica el inspector, en un loop y se compara, si es mayor el primero entonces se hace un cambio.]
			;		list tiene la lista a ordenar y en el registro r1,
			;		list_count tiene el numero de elementos a ordenar y en el registro r2
			;		el puntero actual se almacena en r4, en r5 un contador, r0 se utilizará como zero
			;		en r6 se almacena una bandera para detener el programa
			;		r7 y r8 tienen los elementos a intercambiar/comparar
			;		Instrucciones para ordenar de 9 a 1: 1067
			
list			DCD		9,8,7,6,5,4,3,2,1
list_count	DCD		9
			
			
			
			
bubbleSort	mov		r1, #0x100			; Se carga el primer elemento de la lista
			mov		r2, #0x124			; Se carga el tamaño de la lista
			ldr		r2, [r2]
			cmp		r2, #1				; la cantidad de elementos debe de ser mayor a 1
			ble		bubleEnd				; Termina si no
			sub		r5, r2, #1			; inicia el contador en el tamaño menos 1
			add		r4, r0, r1			; inicia el puntero actual al inicio de la lista
			add		r6, r0, #0			; la bandera para continuar se pone en 0
			
mainLoop		ldr		r7, [r4]				; carga el primer elemento a comparar
			ldr		r8, [r4, #4]			; carga el segundo elemento a comparar
			cmp		r7, r8				; compara los elementos
			ble		noSwap				; si el segundo es mayor no hay cambio
			
			add		r6, r0,#1				; si hay cambio se cambia la bandera de continuar
			str		r7, [r4,#4]			; se hace el swap
			str		r8, [r4]				; se hace el swap
			add		r4, r4, #4			; se aumenta el puntero actual
			
noSwap		subs		r5, r5, #1			; el contador disminuye por 1
			bne		mainLoop				; vuelve al main
			
			
loopEnd		cmp		r6, #0				; compara si hay que seguir
			beq		bubleEnd				; sino hay que seguir[r6==0] TERMINA
			
			add		r6, r0, #0			; se resetea todo
			add		r4, r0,r1
			sub		r5, r2, #1
			b		mainLoop				; vuelve a iniciar el loop
			
			
bubleEnd
