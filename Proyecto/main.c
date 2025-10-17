/*●	Se deberá entregar un archivo con el siguiente formato:
TP_Tópicos_2025_2c_miercoles_{NOMBRE_DE_GRUPO}.zip
Por ejemplo: Si el grupo se llamase “Invisible” -y sus integrantes fueran Spinetta, Pomo y Machi- el archivo debería llamarse TP_Tópicos_2025_2c_miercoles_INVISIBLE.zip
●	El trabajo práctico tiene valor de parcial y consta de una entrega (grupal) y una defensa (individual).
●	Se debe cumplimentar con la consigna completa.
●	Que funcione mínimo para todos los casos de prueba que presentan.
●	Vectores y cadenas de texto deberán ser manipulados utilizando aritmética de punteros.
●	Las soluciones tienen que ser eficientes.
●	En el uso de memoria, por tanto, no declare vectores o matrices auxiliares si no es necesario.
●	En cantidad de ciclos de procesador y en el caso de matrices las soluciones deben ser óptimas.
●	Los recorridos de archivos tienen que ser mínimos.
●	Nunca acceda a memoria que no le pertenece.
●	Declare variables al inicio del bloque y no utilice VLA (Variable length arrays).
●	Se evaluará la prolijidad general.
●	Código prolijo, dividido en funciones.
●	Nombres descriptivos.
●	Nombres significativos de variables.
●	Las soluciones tienen que estar desarrolladas en ANSI C para garantizar tanto como sea posible compatibilidad multiplataforma.
●	Nunca mezcle funciones de manipulación de archivos de texto con funciones de operación de archivos binarios.
*/

#include"..\Biblioteca\Biblioteca.h"



int main()
{
    SetConsoleOutputCP(CP_UTF8);   /* forza CP 65001 (UTF-8) para la salida de la consola */
    SetConsoleCP(CP_UTF8);         /* (opcional) entrada desde consola en UTF-8 */


    int ret=TODO_OK;


    ret = recorrerArchivoDiv(decodificadorFecha);

    if(ret == TODO_OK)
    {
        ret = recorrerArchivoDiv(convertirFecha);
    }
    if(ret == TODO_OK)
    {
        ret = recorrerArchivoDiv(normalizarDiv);
    }

    if(ret!= TODO_OK)
    {
        printf("problemas en... ");
    }

    return 0;
}

