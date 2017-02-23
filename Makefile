prog: lexico.l sintactico.y funciones.c list.c
	bison -d sintactico.y
	mv sintactico.tab.h sintactico.h
	mv sintactico.tab.c sintactico.c
	flex lexico.l
	mv lex.yy.c lexico.c
	gcc -o ejecutable sintactico.c lexico.c funciones.c list.c stack.c -I. -lm

clean:
	rm lexico.c sintactico.c sintactico.h programa.asm prog *~
