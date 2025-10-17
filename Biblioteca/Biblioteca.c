#include"Biblioteca.h"

//#
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
//#
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

//#01
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
//#02
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

        //los char numericos van desde '0'(48) hasta '9'(57)
        //ejemplo ('6'(54) - '0'(48) = (6))
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
                    strcpy(pfecha, "Noviembre-");
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
//#03
int normalizarDiv(char *linea)
{
    //firts mayuscula - el resto minuscula (respetar espacios)
    Tipc ipc;
    char *lim;
    int ret = TODO_OK;

    lim = strrchr(linea,'\n');

    if(lim)
    {
        *lim = '\0';

        //Periodo_codificado
        lim = strrchr(linea,';');
        strcpy(ipc.periodo_codificado,lim+1);

        //Region
        *lim = '\0';
        lim = strrchr(linea,';');
        strcpy(ipc.region,lim+1);

        //v_i_a_IPC
        *lim = '\0';
        lim = strrchr(linea,';');
        ipc.v_i_a_IPC = atof(lim+1);

        //v_m_IPC
        *lim = '\0';
        lim = strrchr(linea,';');
        ipc.v_m_ipc = atof(lim+1);

        //Indice_IPC
        *lim = '\0';
        lim = strrchr(linea,';');
        ipc.incide_ipc = atof(lim+1);

        //Clasificador
        *lim = '\0';
        lim = strrchr(linea,';');
        strcpy(ipc.clasificador,lim+1);

        //Descripcion
        *lim = '\0';
        lim = strrchr(linea,';');
        strcpy(ipc.descripcion,lim+1);

        //llamada a normalizarDescripcion
        normalizarDescripcion(ipc.descripcion);

        //Codigo
        *lim = '\0';
        strcpy(ipc.codigo,linea);

        sprintf(linea,"%s;%s;%s;%.0f;%.0f;%.0f;%s;%s",ipc.codigo,ipc.descripcion,ipc.clasificador,ipc.incide_ipc,ipc.v_m_ipc,ipc.v_i_a_IPC,ipc.region,ipc.periodo_codificado);
    }
    else
        ret = ERR_LINEA;

    if(ret != TODO_OK)
    {
        return ret;
    }

    return TODO_OK;
}

void normalizarDescripcion(char *S1)
{
    //Los caracteres con acentos ocupan (2 bytes) en memoria.
    //Para saber si el caracter ocupa más de un byte se realiza una operacion AND con una mascara.
    //(1 byte): mascara(0x80) -> bit alto=1 AND valor ASCII (0-127) tienen el bit alto = 0.
    //(2 byte): ((b & 0xE0) == 0xC0)
    char *act = S1;
    int Firts = 1;

    while(*act !='\0')
    {
        if(( ((unsigned char) *act) & 0x80) == 0) // caracter sin acentos ((b & 0x80) == 0)
        {
            if(Firts == 1)
            {
                Firts = 0;
                *act = (char) toupper((unsigned char)*act);
            }
            else
            {
                if(ES_LETRA((unsigned char)*act))
                    //se castea a unsigned ya que las funciones de ctype funcionan con valores hasta 255.
                    *act = (char) tolower((unsigned char)*act);
            }
            act ++;
        }
        else
        {
            // comprobar si el segundo caracter es final de cadena
            if (strncmp(act, "Á", 2) == 0)
                memcpy(act,"á",2);
            else if(strncmp(act,"É",2) == 0)
                memcpy(act,"é",2);
            else if(strncmp(act,"Í",2) == 0)
                memcpy(act,"í",2);
            else if(strncmp(act,"Ó",2) == 0)
                memcpy(act,"ó",2);
            else if(strncmp(act,"Ú",2) == 0)
                memcpy(act,"ú",2);
            else if(strncmp(act,"Ñ",2) == 0)
                memcpy(act,"ñ",2);

            act+=2;
        }
    }
}






















