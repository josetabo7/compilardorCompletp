%{ 
#include <stdio.h> 
#include <stdlib.h> 
#include "funciones.h" 
#include "list.h" 
#include "stack.h" 

extern List list; 
extern Stack stack; 
%} 

%token MAIN 
%token NUMERO_ENTERO NUMERO_REAL IDENTIFICADOR 
%token INT FLOAT 
%token PARENTESIS_IZQUIERDA PARENTESIS_DERECHA LLAVE_IZQUIERDA LLAVE_DERECHA 
%token IF ELSE 
%token FOR WHILE 
%token PTOCOMA COMA ASPAS 
%token FINARCHIVO 
%left SUMA RESTA 
%left MULTIPLICACION DIVISION 
%left COMPARACION MAYOR_IGUAL MENOR_IGUAL MAYOR_QUE MENOR_QUE DIFERENTE 
%left OU 
%left E 
%left INCREMENTO DECREMENTO 
%right IGUAL 

%start Entrada 

%% 

Entrada: 
   	/* Empty */ 
   	| Entrada finArchivo 
   	| Entrada LLAVE_IZQUIERDA Entrada LLAVE_DERECHA 
   	| Entrada if 
   	| Entrada while 
   	| Entrada for 
   	| Entrada instruccion 
   	| Entrada declaracion 
   	| Entrada main 
	; 

main: 
	INT MAIN PARENTESIS_IZQUIERDA PARENTESIS_DERECHA 
	; 
if: 
	IF PARENTESIS_IZQUIERDA condicion PARENTESIS_DERECHA 
	| ELSE 
	| ELSE if 
	; 
	 
condicion: 
	IDENTIFICADOR 
	| PARENTESIS_IZQUIERDA condicion PARENTESIS_DERECHA 
	| expresion 
	| condicion COMPARACION condicion 
	| condicion OU condicion 
	| condicion E condicion 
	| condicion MAYOR_IGUAL condicion 
	| condicion MENOR_IGUAL condicion 
	| condicion DIFERENTE condicion 
	| condicion MAYOR_QUE condicion 
	| condicion MENOR_QUE condicion 
	; 
	 
expresion: 
   NUMERO_ENTERO 
   |NUMERO_REAL 
   | IDENTIFICADOR 
   | expresion SUMA expresion 
   | expresion RESTA expresion 
   | expresion MULTIPLICACION expresion 
   | expresion DIVISION expresion 
   | PARENTESIS_IZQUIERDA expresion PARENTESIS_DERECHA 
   | IDENTIFICADOR IGUAL expresion 
   ; 
   
while: 
	WHILE PARENTESIS_IZQUIERDA condicion PARENTESIS_DERECHA 
	; 
	 
for: 
	FOR PARENTESIS_IZQUIERDA PTOCOMA PTOCOMA PARENTESIS_DERECHA 
	| FOR PARENTESIS_IZQUIERDA condicion PTOCOMA condicion PTOCOMA condicion PARENTESIS_DERECHA 
	| FOR PARENTESIS_IZQUIERDA variableDeclarada PTOCOMA condicion PTOCOMA condicion PARENTESIS_DERECHA 
	; 
	 
instruccion: 
	PTOCOMA 
	| expresion PTOCOMA 
	; 
	 
declaracion: 
	INT variableDeclarada PTOCOMA 
	| FLOAT variableDeclarada PTOCOMA 
	; 
	 
variableDeclarada: 
	IDENTIFICADOR 
	| IDENTIFICADOR IGUAL expresion 
	| variableDeclarada COMA	variableDeclarada 
	; 

finArchivo: 
	FINARCHIVO {exit(0);} 


%% 

int yyerror(char *s) { 
	printf("%s\n",s); 
} 

int main(void) { 
	inicializarLista(&list); 
	inicializarPila(&stack); 

	crearArchivoBSS(); 
   	yyparse(); 
}

