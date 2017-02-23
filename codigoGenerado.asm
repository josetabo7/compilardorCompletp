	variables globales
start:

	mov [a], 5
	mov [b], 6
	mov [i], 0
	mov [g], 1.4
	mov [h], 2.5

	CMP [a], [b]
	JE Condicion0
	JNE Condicion1

	Condicion0:
		mov [a], 7

	Condicion1:
		mov [b], 4