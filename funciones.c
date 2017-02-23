#include <stdio.h> 
#include <string.h> 
#include "funciones.h" 
#include "list.h" 
#include "sintactico.h" 
#include <stdlib.h> 

List list; 
FILE *ArchivoAssembly; 
FILE *ArchivoStart; 
FILE *LabelSE; 
FILE *LabelSENAO; 
extern int cuerpoIf; 
extern int cuerpoElse; 
extern int cuerpoWhile; 
extern int parametroIf; 
extern int parametroWhile; 
int condicion=0, mientras=0; 
int ifs=0, elses=0; 

void crearArchivoBSS() 
{ 
	ArchivoAssembly = fopen("TablaSimbolos.asm","w"); 
	fprintf(ArchivoAssembly, "variables globales.bss\n"); 
	fclose(ArchivoAssembly); 
} 

void crearArchivoStart() 
{ 
	ArchivoStart = fopen("codigoGenerado.asm","w"); 
	fprintf(ArchivoStart, "\tcodigo de maquina\nstart:\n"); 
	fclose(ArchivoStart); 
} 

void declaracionVariable(char *token, char *identificador) 
{ 
	ArchivoAssembly = fopen("TablaSimbolos.asm","a"); 

	if(strcmp(token, "int")==0) 
		fprintf(ArchivoAssembly,"\t%s int %lu\n",identificador,sizeof(int)); 
	else if(strcmp(token, "float")==0) 
		fprintf(ArchivoAssembly,"\t%s float %lu\n",identificador,sizeof(double)); 
	 
	char *elemento = (char*)malloc(strlen(identificador)); 
	strcpy(elemento, identificador); 
	 
	insertarElementoLista(&list, elemento, token); 

	fclose(ArchivoAssembly); 

} 

void atribuir(char *variable, char *numero) 
{ 
	char *nuevoValor = (char*)malloc(strlen(numero)); 
	strcpy(nuevoValor, numero); 

	eliminarElementoLista(&list, variable, nuevoValor); 

	ArchivoStart = fopen("codigoGenerado.asm","a"); 
	 
	if(cuerpoIf){ 
		if(!ifs){ 
			fprintf(ArchivoStart,"\n\n\tCondicion%d:",condicion-2); 
			ifs=1; 
		} 
		fprintf(ArchivoStart,"\n\t\tmov [%s], %s",variable,numero); 
	} 
	else if(cuerpoElse){ 
		if(!elses){ 
			fprintf(ArchivoStart,"\n\n\tCondicion%d:",condicion-1); 
			elses=1; 
		} 
		fprintf(ArchivoStart,"\n\t\tmov [%s], %s",variable,numero); 
	} 
	else if(cuerpoWhile){ 
		fprintf(ArchivoStart,"\n\n\tCondicion%d:",condicion-2); 
		fprintf(ArchivoStart,"\n\tmov [%s], %s",variable,numero); 
	} 
	else 
		fprintf(ArchivoStart,"\n\tmov [%s], %s",variable,numero); 
		 
	fclose(ArchivoStart); 
} 

void inicializarParametros(Parametros *parametros) 
{ 
	strcpy(parametros->termino1, ""); 
	strcpy(parametros->termino2, ""); 
	strcpy(parametros->tipoTermino1, ""); 
	strcpy(parametros->tipoTermino2, ""); 
	strcpy(parametros->operador, ""); 
} 

void popularParametros(Parametros *parametros, char *identificador, char *tipoTermino) 
{ 
	if(strcmp(tipoTermino, "variable")==0) 
	{ 
		if(!demandaElementoLista(&list, identificador)) 
			printf("ERROR: Variable %s no declarada\n",identificador); 
	} 

	char *elemento = (char*)malloc(strlen(identificador + 1)); 
	strcpy(elemento, identificador); 

	if(strcmp(parametros->termino1, "")==0) 
	{ 
		strcpy(parametros->tipoTermino1, tipoTermino); 
		strcpy(parametros->termino1, elemento); 
	} 
	else if(strcmp(parametros->termino2, "")==0) 
	{ 
		strcpy(parametros->tipoTermino2, tipoTermino); 
		strcpy(parametros->termino2, elemento); 

		if(parametroIf){ 
			escribirComparacion(parametros); 
		} 
		else if(parametroWhile) 
		{ 
			funcionWhile(parametros); 
			escribirComparacion(parametros); 
		} 
	} 
} 

void escribirComparacion(Parametros *parametros) 
{ 
	ArchivoStart = fopen("codigoGenerado.asm","a"); 

	fprintf(ArchivoStart,"\n\n\tCMP "); 

	if(strcmp(parametros->tipoTermino1, "variable")==0) 
		fprintf(ArchivoStart,"[%s], ",parametros->termino1); 
	else 
		fprintf(ArchivoStart,"%s, ",parametros->termino1); 

	if(strcmp(parametros->tipoTermino2, "variable")==0) 
		fprintf(ArchivoStart,"[%s]\n",parametros->termino2); 
	else 
		fprintf(ArchivoStart,"%s\n",parametros->termino2); 

	if(strcmp(parametros->operador, "==") == 0) 
	{ 
		fprintf(ArchivoStart,"\tJE Condicion%d\n",condicion); 
		condicion++; 
		ifs=0; 

		fprintf(ArchivoStart,"\tJNE Condicion%d",condicion); 
		condicion++; 
		elses=0; 
	} 
	else if(strcmp(parametros->operador, "<=") == 0) 
	{ 
		fprintf(ArchivoStart, "\tJLE Condicion%d\n", condicion); 
		condicion++; 
		ifs = 0; 

		fprintf(ArchivoStart, "\tJNLE Condicion%d", condicion); 
		condicion++; 
		elses = 0; 
	} 
	else if(strcmp(parametros->operador, ">=") == 0) 
	{ 
		fprintf(ArchivoStart, "\tJGE Condicion%d\n", condicion); 
		condicion++; 
		ifs = 0; 

		fprintf(ArchivoStart, "\tJNGE Condicion%d", condicion); 
		condicion++; 
		elses = 0; 
	} 
	else if(strcmp(parametros->operador, "<") == 0) 
	{ 
		fprintf(ArchivoStart, "\tJL Condicion%d\n", condicion); 
		condicion++; 
		ifs = 0; 

		fprintf(ArchivoStart, "\tJNL Condicion%d", condicion); 
		condicion++; 
		elses = 0; 
	} 
	else if(strcmp(parametros->operador, ">") == 0) 
	{ 
		fprintf(ArchivoStart, "\tJG Condicion%d\n", condicion); 
		condicion++; 
		ifs = 0; 

		fprintf(ArchivoStart, "\tJNG Condicion%d", condicion); 
		condicion++; 
		elses = 0; 
	} 
	else if(strcmp(parametros->operador, "!=") == 0) 
	{ 
		fprintf(ArchivoStart, "\tJNE Condicion%d\n", condicion); 
		condicion++; 
		ifs = 0; 

		fprintf(ArchivoStart, "\tJE Condicion%d", condicion); 
		condicion++; 
		elses = 0; 
	} 


	inicializarParametros(parametros); 

	fclose(ArchivoStart); 
} 

void funcionWhile(Parametros *parametros) 
{ 
	ArchivoStart = fopen("codigoGenerado.asm","a"); 
	fprintf(ArchivoStart,"\n\n\tMientras%d:",mientras); 
	fclose(ArchivoStart); 
}

