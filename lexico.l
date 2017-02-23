%{ 
#include "sintactico.h" 
#include "stdlib.h" 
#include "funciones.h" 
#include "stack.h" 
#include <string.h> 
#include <stdlib.h> 
char token[100], variable[100], tipoTermino[100]; 
int atribucion=0, noEstaIf=0, cuerpoIf=0, noEstaElse=0, cuerpoElse=0, cuerpoWhile = 0, noEstaWhile=0, finArchivo = 0; 
int parametroIf=0,  parametroWhile=0; 
Parametros parametros; 
Stack stack; 
extern FILE *ArchivoStart; 
extern int condicion; 
extern int mientras; 
%} 

blanco [ \t\n]+ 
digito [0-9] 
letra [a-zA-Z] 
numeroEntero {digito}+ 
numeroReal {numeroEntero}("."{numeroEntero})? 
identificador {letra}+({digito}|{letra})* 
Entero "int" 
float "float" 
main "main" 
igual "=" 
si "if" 
sino "else" 
parentesisIzquierda "(" 
parentesisDerecha ")" 
llaveIzquierda "{" 
llaveDerecha "}" 
PtoComa ";" 
comparacion "==" 
mayorIgual ">=" 
menorIgual "<=" 
mayorQue ">" 
menorQue "<" 
diferente "!=" 
mientras "while" 

%% 

{blanco} { /* Eliminar espacios en blanco*/ } 
{main} { 
	crearArchivoStart(); 

	return(MAIN); 
} 
{numeroEntero} { 
	if(atribucion) 
	{ 
		atribuir(variable, yytext); 
		atribucion=0; 
	} 

	if(parametroIf || parametroWhile) 
	{ 
		strcpy(tipoTermino, "numero"); 
		popularParametros(&parametros, yytext, tipoTermino); 
	} 
 
	return(NUMERO_ENTERO); 
} 

{numeroReal} { 
	if(atribucion) 
	{ 
		atribuir(variable, yytext); 
		atribucion=0; 
	} 

	if(parametroIf || parametroWhile) 
	{ 
		strcpy(tipoTermino, "numero"); 
		popularParametros(&parametros, yytext, tipoTermino); 
	} 

	return(NUMERO_REAL); 
} 

{si} { 
	parametroIf=1; 
	noEstaIf=1; 
	return(IF); 
} 

{sino} { 
	noEstaElse=1; 
	return(ELSE); 
} 

{mientras} { 
	noEstaWhile = 1; 
	parametroWhile=1; 
	return(WHILE); 
} 

"for" return(FOR); 

{Entero} { 
	strcpy(token, yytext); 
	return(INT); 
} 

{float} { 
	strcpy(token, yytext); 
	return(FLOAT); 
} 

"+" return(SUMA); 
"-" return(RESTA); 
"*" return(MULTIPLICACION); 
"/" return(DIVISION); 

{parentesisIzquierda} { 
	insertarElementoPila(&stack, '('); 
	return(PARENTESIS_IZQUIERDA); 
} 

{parentesisDerecha} { 
	eliminarElementoPila(&stack); 

	if(!stack.top) 
	{ 
		parametroWhile=0; 
		parametroIf=0; 
	} 

	return(PARENTESIS_DERECHA); 
} 

{igual} { 
	atribucion=1; 
	return(IGUAL); 
} 

{comparacion} { 
	strcpy(parametros.operador,yytext); 
	return(COMPARACION); 
} 

{mayorIgual} { 
	strcpy(parametros.operador,yytext); 
	return(MAYOR_IGUAL); 
} 

{menorIgual} { 
	strcpy(parametros.operador,yytext); 
	return(MENOR_IGUAL); 
} 

{mayorQue} { 
	strcpy(parametros.operador,yytext); 
	return(MAYOR_QUE); 
} 

{menorQue} { 
	strcpy(parametros.operador,yytext); 
	return(MENOR_QUE); 
} 

{diferente} { 
	strcpy(parametros.operador,yytext); 
	return(DIFERENTE); 
} 

"&&" return(E); 
"||" return(OU); 
"++" return(INCREMENTO); 
"--" return(DECREMENTO); 

{llaveIzquierda} { 
	if(noEstaIf) 
		cuerpoIf=1; 

	if(noEstaElse) 
		cuerpoElse=1; 
	if(noEstaWhile) 
		cuerpoWhile = 1; 
	 
	finArchivo++; 

	return(LLAVE_IZQUIERDA); 
} 

{llaveDerecha} { 
	if(noEstaIf == 1) 
	{ 
		noEstaIf=0; 
		cuerpoIf=0; 
		ArchivoStart = fopen("start.asm", "a"); 
		fprintf(ArchivoStart, "\n\t\tJMP finCondicion%d", condicion - 1); 
		fclose(ArchivoStart); 
	} 
	else if(noEstaElse == 1) 
	{ 
		noEstaElse=0; 
		cuerpoElse=0; 
		ArchivoStart = fopen("start.asm", "a"); 
		fprintf(ArchivoStart, "\n\t\tfinCondicion%d:", condicion - 1); 
		fclose(ArchivoStart); 
	} 
	else if(noEstaWhile == 1) 
	{ 
		noEstaWhile=0; 
		cuerpoWhile=0; 
		ArchivoStart = fopen("start.asm", "a"); 
		fprintf(ArchivoStart, "\n\tJMP Mientras%d", mientras); 
		fprintf(ArchivoStart,"\n\n\tCondicion%d:",condicion-1); 
		fclose(ArchivoStart); 
	} 
	finArchivo--; 
	if(!finArchivo) 
	{ 
		exit(0); 
	} 
 
	return(LLAVE_DERECHA); 
} 

{PtoComa} { 
	/* Reiniciando todas las  variables */ 
	strcpy(token, ""); 
	strcpy(variable, ""); 
	strcpy(tipoTermino, ""); 
	atribucion=0; 
	parametroIf=0; 
	parametroWhile=0; 

	return(PTOCOMA); 
} 

"," return(COMA); 
"\"" return(ASPAS); 

{identificador} { 
	strcpy(variable,yytext); 

	if(strcmp(token, "")!=0) 
		declaracionVariable(token, yytext); 
	 
	if(parametroIf || parametroWhile) 
	{ 
		strcpy(tipoTermino, "variable"); 
		popularParametros(&parametros, yytext, tipoTermino); 
	} 

	 
	return(IDENTIFICADOR); 
} 

 
%% 

yywrap () { 
return 0; 
}


