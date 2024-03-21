#define MAX_SIZE 20
#include "lista.h"

void eliminar_impresora(TLISTA *cadena_impresoras); /*ELIMINA LA IMPRESORA DE LA LISTA Y DEVUELVE ERROR SI NO LA ENCUENTRA*/
void imprimir_cadena_impresoras(TLISTA cadena_impresoras); /*IMPRIME TODOS LOS ELEMENTOS DE LA LISTA*/
void nueva_impresora(TLISTA *cadena_impresoras); /* AÑADE UNA IMPRESORA A LA LISTA*/
void enviar_traballo(TLISTA* cadena_impresoras, TIPOELEMENTOLISTA impresora_nome, int traballo); /*ENVIA EL CÓDIGO DE UN TRABAJO A LA COLA DE UNA IMPRESORA*/
void imprimir_cola_impresion(TLISTA lista, TIPOELEMENTOLISTA cola); /*IMPRIME LA COLA DE IMPRESIÓN DE UNA IMPRESORA DADA EL NOMBRE*/
void imprimir_traballo(TLISTA cadena_impresoras, TIPOELEMENTOLISTA impresora); /*ELIMINA EL PRIMER ELEMENTO DE LA COLA DE IMPRESION DE IMPRESORA*/
void encontrar_impresora_poca_carga(TLISTA lista); /*ENCUENTRA LAS IMPRESORAS CUYA COLA DE IMPRESION ES MENOR*/
void cargar_impresoras(FILE* file, TLISTA cadena_impresoras); /*CARGA TODAS LAS IMPRESORAS DE impresoras.txt A LA LISTA*/
void actualizararchivo(FILE* file, TLISTA cadena_impresoras); /*ACTUALIZA EL ARCHIVO impresoras.txt AL CERRAR EL PROGRAMA*/

