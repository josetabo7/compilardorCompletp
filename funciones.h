#ifndef _FUNCIONES_ 
#define _FUNCIONES_ 

typedef struct _Parametros 
{ 
	char termino1[100]; 
	char termino2[100]; 
	char tipoTermino1[10]; 
	char tipoTermino2[10]; 
	char operador[2]; 
} Parametros; 

extern void declaracionVariable(char *token, char *identificador); 
extern void crearArchivoBSS(); 
extern void crearArchivoStart(); 

extern void atribuir(char *variable, char *numero); 

extern void inicializarParametros(Parametros *parametros); 
extern void popularParametros(Parametros *parametros, char *identificador, char *tipoTermino); 
extern void funcionIF(Parametros *Pprametros); 
extern void funcionWhile(Parametros *Pprametros); 
extern void escribirComparacion(Parametros *parametros); 

#endif

