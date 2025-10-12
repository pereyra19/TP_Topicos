#include"Biblioteca.h"

FILE *abrirArchivos(const char *nomArch,const char *modo)
{
    FILE *arch = fopen(nomArch,modo);
    if(!arch)
    {
        printf("error al abrir el archivo %s",nomArch);
        return NULL;
    }

    return arch;
}

int recorrerArchivoDiv(Convertir convertir)
{
    char linea[TAMLINEA+1];
    int ret = TODO_OK;

    FILE *archDiv = abrirArchivos(nomArchDivisiones,"rt");
    if(!archDiv)
    {
        return ERR_ARCH;
    }

    FILE *archTemp = abrirArchivos(nomArchTemp,"wt");
    if(!archTemp)
    {
        fclose(archDiv);
        return ERR_ARCH;
    }

    fgets(linea,TAMLINEA+1,archDiv); // lee los titulos
    fprintf(archTemp,"%s",linea); // sin \n ya que la linea no se edito

    while(fgets(linea,TAMLINEA+1,archDiv) && ret == TODO_OK)
    {
        ret = convertir(linea);

        if(ret == TODO_OK)
        {
            fprintf(archTemp,"%s\n",linea);
        }
    }

    if(ret != TODO_OK)
    {
        fclose(archDiv);
        fclose(archTemp);
        remove(nomArchTemp);
        return ret;
    }

    fclose(archDiv);
    fclose(archTemp);
    remove(nomArchDivisiones);
    rename(nomArchTemp,nomArchDivisiones);

    return TODO_OK;
}

int decodificadorFecha(char *linea)
{
    int ret = TODO_OK;
    char *lim, *act;

    lim = strrchr(linea,'\n');

    if(lim)
    {
        *lim = '\0';

        lim = strrchr(linea,';');
        act = lim + 1;

        while(*act != '\0' && ret == TODO_OK)
        {
            switch (*act)
            {
                case '7':
                    *act = '0';
                    break;
                case '4':
                    *act = '1';
                    break;
                case '9':
                    *act = '2';
                    break;
                case '8':
                    *act = '3';
                    break;
                case '0':
                    *act = '4';
                    break;
                case '6':
                    *act = '5';
                    break;
                case '1':
                    *act = '6';
                    break;
                case '3':
                    *act = '7';
                    break;
                case '2':
                    *act = '8';
                    break;
                case '5':
                    *act = '9';
                    break;
                default:                     //verifica si se ingreso otro tipo de dato
                    ret = ERR_FECHA;
                    break;
            }

            act++;
        }
    }
    else
        ret = ERR_LINEA;

    if(ret!= TODO_OK)
    {
        return ret;
    }

    return TODO_OK;
}

int convertirFecha(char *linea)
{
    int ret = TODO_OK;
    char *lim, *act, *unidad,*decena, *pfecha;
    int num;
    char fecha[20];
    pfecha = fecha;

    lim = strrchr(linea,'\n');

    if(lim)
    {
        *lim = '\0';

        lim = strrchr(linea,';');
        act = lim + 1;
        unidad = (act + strlen(act) - 1);
        decena = (act + strlen(act) - 2);

        num = (*decena - '0') * 10 + (*unidad - '0');

            switch(num)
            {
                case 1:
                    strcpy(pfecha, "Enero-");
                    break;
                case 2:
                    strcpy(pfecha, "Febrero-");
                    break;
                case 3:
                    strcpy(pfecha, "Marzo-");
                    break;
                case 4:
                    strcpy(pfecha, "Abril-");
                    break;
                case 5:
                    strcpy(pfecha, "Mayo-");
                    break;
                case 6:
                    strcpy(pfecha, "Junio-");
                    break;
                case 7:
                    strcpy(pfecha, "Julio-");
                    break;
                case 8:
                    strcpy(pfecha, "Agosto-");
                    break;
                case 9:
                    strcpy(pfecha, "Septiembre-");
                    break;
                case 10:
                    strcpy(pfecha, "Octubre-");
                    break;
                case 11:
                    strcpy(pfecha, "Nombiembre-");
                    break;
                case 12:
                    strcpy(pfecha, "Diciembre-");
                    break;
            }

            pfecha += strlen(pfecha); //mueve el puntero para a la ult pos

            for(int i=0;i<4;i++)
            {
                *pfecha = *act;
                act++;
                pfecha++;
            }
            *pfecha = '\0';

            strcpy(lim+1,fecha); // se copia fecha por que el puntero pfecha esta apuntando a la ult pos

    }
    else
        ret = ERR_LINEA;


    if(ret!= TODO_OK)
    {
        return ret;
    }

    return TODO_OK;
}


// int decodificadorFecha(FILE *arch)
// {
//     Tipc ipc;
//     char *lim, *act, *periodo, *ini;
//     char linea[TAMLINEA+1];
//     int ret = TODO_OK;

//     rewind(arch);

//     FILE *archTem = abrirArchivos(nomArchTemp,"wt");
//     if(!archTem)
//     {
//         return ERR_ARCH;
//     }

//     periodo = ipc.periodo_codificado;
//     ini = ipc.periodo_codificado;

//     fgets(linea,TAMLINEA+1,arch); //lee los titulos
//     fprintf(archTem,"%s\r\n",linea);

//     while(fgets(linea,TAMLINEA+1,arch) && ret==TODO_OK)
//     {
//         lim = strrchr(linea,'\n');

//         if(lim)
//         {
//             *lim = '\0';
//             lim = strrchr(linea,';');
//             *lim = '\0';
//             act = lim+1;


//             while(*act != '\0' && ret == TODO_OK)
//             {
//                 if(ES_NUMERO(*act))
//                 {
//                     switch (*act)
//                     {
//                         case '7':
//                             *periodo = '0';
//                             break;
//                         case '4':
//                             *periodo = '1';
//                             break;
//                         case '9':
//                             *periodo = '2';
//                             break;
//                         case '8':
//                             *periodo = '3';
//                             break;
//                         case '0':
//                             *periodo = '4';
//                             break;
//                         case '6':
//                             *periodo = '5';
//                             break;
//                         case '1':
//                             *periodo = '6';
//                             break;
//                         case '3':
//                             *periodo = '7';
//                             break;
//                         case '2':
//                             *periodo = '8';
//                             break;
//                         case '5':
//                             *periodo = '9';
//                             break;
//                     }

//                     periodo++;
//                 }

//                 act++;
//             }
//             if(ret == TODO_OK)
//             {
//                 *periodo = '\0';

//                 //Region
//                 lim = strrchr(linea,';');
//                 *lim = '\0';
//                 strcpy(ipc.region,lim+1);

//                 //v_i_a_IPC
//                 lim = strrchr(linea,';');
//                 *lim = '\0';
//                 ipc.v_i_a_IPC = atof(lim+1);
//                 //v_m_ipc
//                 lim = strrchr(linea,';');
//                 *lim = '\0';
//                 ipc.v_m_ipc = atof(lim+1);

//                 //incide_ipc
//                 lim = strrchr(linea,';');
//                 *lim = '\0';
//                 ipc.incide_ipc = atof(lim+1);

//                 //clasificador
//                 lim = strrchr(linea,';');
//                 *lim = '\0';
//                 strcpy(ipc.clasificador,lim+1);

//                 //descripcion
//                 lim = strrchr(linea,';');
//                 *lim = '\0';
//                 strcpy(ipc.descripcion,lim+1);

//                 //codigo
//                 strcpy(ipc.codigo,linea);

//                 fprintf(archTem,"%s;%s;%s;%f;%f;%f;%s;%s\r\n",ipc.codigo,ipc.descripcion,ipc.clasificador,ipc.incide_ipc,ipc.v_m_ipc,ipc.v_i_a_IPC,ipc.region,ipc.periodo_codificado);

//                 periodo = ini; // volviendo a ipc.periodo_Codficado[0]
//                 *periodo = '\0';
//             }
//         }
//         else
//             ret = ERR_LINEA;
//     }

//     if(ret != TODO_OK)
//     {
//         return ret;
//     }

//     fclose(arch);
//     fclose(archTem);
//     remove(nomArchDivisiones);
//     rename(nomArchTemp,nomArchDivisiones);

//     return TODO_OK;
// }

// int convertirFecha(FILE *arch)
// {
//     Tipc ipc;
//     char *lim, *unidad, *decena, *periodo;
//     char linea[TAMLINEA+1];
//     int ret = TODO_OK, num;

//     FILE *archTem = abrirArchivos(nomArchTemp,"wt");
//     if(!archTem)
//     {
//         return ERR_ARCH;
//     }

//     fgets(linea,TAMLINEA+1,arch); //lee los titulos

//     while(fgets(linea,TAMLINEA+1,arch) && ret==TODO_OK)
//     {
//         lim = strrchr(linea,'\n');

//         if(lim)
//         {
//             *lim = '\0';
//             unidad = lim-1;
//             decena = lim-2;
//             lim = strrchr(linea,';');
//             *lim = '\0';

//             periodo = ipc.periodo_codificado;

//             num = (*decena - '0') * 10 + (*unidad - '0');

//             switch(num)
//             {
//                 case 1:
//                     strcpy(periodo, "Enero-");
//                     break;
//                 case 2:
//                     strcpy(periodo, "Febrero-");
//                     break;
//                 case 3:
//                     strcpy(periodo, "Marzo-");
//                     break;
//                 case 4:
//                     strcpy(periodo, "Abril-");
//                     break;
//                 case 5:
//                     strcpy(periodo, "Mayo-");
//                     break;
//                 case 6:
//                     strcpy(periodo, "Junio-");
//                     break;
//                 case 7:
//                     strcpy(periodo, "Julio-");
//                     break;
//                 case 8:
//                     strcpy(periodo, "Agosto-");
//                     break;
//                 case 9:
//                     strcpy(periodo, "Septiembre-");
//                     break;
//                 case 10:
//                     strcpy(periodo, "Octubre-");

//             }

//             unidad = lim+1; // se mueve al pricipio

//             for(int i=0;i<4;i++)
//             {
//                 *periodo = *unidad++;
//             }

//             *periodo = '\0';

//             //Region
//             lim = strrchr(linea,';');
//             *lim = '\0';
//             strcpy(ipc.region,lim+1);

//             //v_i_a_IPC
//             lim = strrchr(linea,';');
//             *lim = '\0';
//             ipc.v_i_a_IPC = atof(lim+1);
//             //v_m_ipc
//             lim = strrchr(linea,';');
//             *lim = '\0';
//             ipc.v_m_ipc = atof(lim+1);

//             //incide_ipc
//             lim = strrchr(linea,';');
//             *lim = '\0';
//             ipc.incide_ipc = atof(lim+1);

//             //clasificador
//             lim = strrchr(linea,';');
//             *lim = '\0';
//             strcpy(ipc.clasificador,lim+1);

//             //descripcion
//             lim = strrchr(linea,';');
//             *lim = '\0';
//             strcpy(ipc.descripcion,lim+1);

//             //codigo
//             strcpy(ipc.codigo,linea);

//             fprintf(archTem,"%s;%s;%s;%f;%f;%f;%s;%s\n",ipc.codigo,ipc.descripcion,ipc.clasificador,ipc.incide_ipc,ipc.v_m_ipc,ipc.v_i_a_IPC,ipc.region,ipc.periodo_codificado);

//         }
//         else
//             ret = ERR_LINEA;
//     }

//     if(ret != TODO_OK)
//     {
//         return ret;
//     }

//     fclose(arch);
//     fclose(archTem);
//     remove(nomArchDivisiones);
//     rename(nomArchTemp,nomArchDivisiones);
//     return TODO_OK;
// }

