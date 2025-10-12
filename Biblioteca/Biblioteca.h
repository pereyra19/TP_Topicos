#ifndef BIBLIOTECA_H_INCLUDED
#define BIBLIOTECA_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<ctype.h>

#define TODO_OK 0
#define ERR_LINEA -1
#define ERR_FECHA -2
#define ERR_ARCH -3
#define TAMLINEA 190


typedef struct{
    char codigo[21];
    char descripcion[31];
    char clasificador[31];
    double incide_ipc;
    double v_m_ipc;
    double v_i_a_IPC;
    char region[10];
    char periodo_codificado[20]; // ojo en el enunciado es int,
}
Tipc;

//----------------Archivos--------------------
#define nomArchDivisiones "serie_ipc_divisiones(in).csv"
#define nomArchTemp "archTemp.csv"

//---------------Puntero a funcion
typedef int (*Convertir)(char *linea);

//---------------FUNCIONES---------------------
FILE *abrirArchivos(const char *nomArch,const char *modo);
int recorrerArchivoDiv(Convertir convertir);
#01
int decodificadorFecha(char *linea);
#02
int convertirFecha(char *linea);


#endif // BIBLIOTECA_H_INCLUDED
