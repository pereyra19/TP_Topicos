#ifndef BIBLIOTECA_H_INCLUDED
#define BIBLIOTECA_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<ctype.h>
#include<windows.h>

#define TODO_OK 0
#define ERR_LINEA -1
#define ERR_FECHA -2
#define ERR_ARCH -3
#define TAMLINEA 190

typedef struct{
    char codigo[21];
    char descripcion[60];
    char clasificador[40];
    double incide_ipc;
    double v_m_ipc;
    double v_i_a_IPC;
    char region[16];
    char periodo_codificado[20];
}
Tipc;


//------------------Macro--------------------
#define ES_LETRA(c) (((c) >= 'A' && (c) <= 'Z') || ((c) >= 'a' && (c) <= 'z'))
#define ES_NUM(x) ((x)>= '0' && (x)<='9')
//----------------Archivos--------------------
#define nomArchDivisiones "serie_ipc_divisiones.csv"
#define nomArchTemp "archTemp.csv"

//---------------Puntero a funcion
typedef int (*Convertir)(char *linea);

//---------------FUNCIONES---------------------
FILE *abrirArchivos(const char *nomArch,const char *modo);
int recorrerArchivoDiv(Convertir convertir);
void convertirFloat(char *S1);
#01
int decodificadorFecha(char *linea);
#02
int convertirFecha(char *linea);
#03
int normalizarDiv(char *linea);
void normalizarDescripcion(char *S1);
#04

#endif // BIBLIOTECA_H_INCLUDED
