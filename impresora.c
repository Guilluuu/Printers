#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "impresora.h"
#include "lista.h"
#include <unistd.h> /*BIBLIOTECA PARA EDITAR LOS MENÚS Y LAS PANTALLAS DE CARGA*/

void cargar_impresoras(FILE *file, TLISTA cadena_impresoras)
{
    TIPOELEMENTOLISTA impresora;

    printf("\033[1m\nCargando impresoras...\n\033[0m");

    if (file == NULL)
    {
        printf("\033[1;33mADVERTENCIA:\033[0m El archivo no está creado.\n");
    }
    else
    {
        while (fscanf(file, "%s %s %s %s", impresora.nome, impresora.marca, impresora.modelo, impresora.ubicacion) == 4) /*MIENTRAS SE ESCANEEN 4 PARÁMETROS*/
        {
            crearCola(&impresora.cola_impresion);                                              /*CREA LA COLA DE IMPRESIÓN DE LAS IMPRESORAS*/
            insertarElementoLista(&cadena_impresoras, finLista(cadena_impresoras), impresora); /*AÑADE LAS IMPRESORAS A LA LISTA*/
            printf("\033[36mInsertando impresora:\033[0m %s %s %s %s\n", impresora.nome, impresora.marca, impresora.modelo, impresora.ubicacion);
            usleep(500000); /*CARGA...*/
        }
    }

    printf("\033[1;32mCarga completa.\n\033[0m");
    usleep(1000000);
    printf("\033[2J\033[H");
}

void actualizararchivo(FILE *file, TLISTA cadena_impresoras)
{
    TIPOELEMENTOLISTA impresora;
    while (!esListaVacia(cadena_impresoras)) /*LEE LA PRIMERA POSICIÓN DE LA LISTA HASTA QUE ESTÉ LA LISTA VACÍA*/
    {
        TPOSICION pos = primeroLista(cadena_impresoras);
        recuperarElementoLista(cadena_impresoras, pos, &impresora);
        destruirCola(&impresora.cola_impresion);                                                                /*DESTRUYE LA COLA DE IMPRESIÓN DE TODAS LAS IMPRESORAS*/
        suprimirElementoLista(&cadena_impresoras, pos);                                                         /*ELIMINA LA IMPRESORA DE LA LISTA*/
        fprintf(file, "%s %s %s %s\n", impresora.nome, impresora.marca, impresora.modelo, impresora.ubicacion); /*ESCRIBE EL NOMBRE DE LA IMPRESPRA EN EL ARCHIVO*/
    }
}

void imprimir_cadena_impresoras(TLISTA cadena_impresoras)
{
    if (esListaVacia(cadena_impresoras)) // SI LA LISTA ESTÁ VACÍA
    {
        printf("\033[1;33mADVERTENCIA:\033[0m La lista de impresoras está vacía.\n");
    }
    else
    {
        TIPOELEMENTOLISTA impresora;
        TPOSICION pos = primeroLista(cadena_impresoras);
        printf("\033[1m\nImpresoras cargadas:\n\033[0m\n");
        while (pos != finLista(cadena_impresoras)) /*AVANZA LA POSICIÓN HASTA LA ÚLTIMA DE LA LISTA*/
        {
            recuperarElementoLista(cadena_impresoras, pos, &impresora);
            printf("\033[36mNombre: \033[0m%s \033[36mMarca: \033[0m%s \033[36mModelo: \033[0m%s \033[36mUbicación: \033[0m%s\n",
                   impresora.nome, impresora.marca, impresora.modelo, impresora.ubicacion); /*IMPRIME EL ELEMENTP EN "pos" DE LA LISTA*/
            pos = siguienteLista(cadena_impresoras, pos);
        }
    }
}

TPOSICION encontrar_impresora(TLISTA lista, TIPOELEMENTOLISTA impresora_encontrar, int *error) /*ENCUENTRA LA POSICIÓN DE UNA IMPRESORA EN LA LISTA DADO EL NOMBRE, DEVUELVE ERROR SI NO LA ENCUENTRA*/
{

    TPOSICION pos = primeroLista(lista);
    TIPOELEMENTOLISTA elemento_actual;

    while (pos != finLista(lista)) /*RECORRE TODA LA LISTA HASTA EL FINAL O HASTA QUE ENCUENTRA LA IMPRESORA*/
    {
        recuperarElementoLista(lista, pos, &elemento_actual);
        if (!strcmp(impresora_encontrar.nome, elemento_actual.nome))
        {
            return pos;
            *error = 1;
        }
        pos = siguienteLista(lista, pos);
    }
    *error = 0; /*NO SE HA ENCONTRADO LA IMPRESORA*/
    return pos;
}

void eliminar_impresora(TLISTA *cadena_impresoras)
{
    if (!esListaVacia(*cadena_impresoras))
    {

        int error = 1;
        TIPOELEMENTOLISTA impresora;
        TPOSICION pos;
        printf("Escribe el nombre de la impresora que quieres eliminar: ");
        scanf("%s", impresora.nome);
        printf("\033[2J\033[H");
        pos = encontrar_impresora((*cadena_impresoras), impresora, &error);
        if (error != 0) /*SI LA IMPRESORA SE HA ENCONTRADO*/
        {
            recuperarElementoLista(*cadena_impresoras, pos, &impresora);
            if (!esColaVacia(impresora.cola_impresion))
                destruirCola(&impresora.cola_impresion);
            suprimirElementoLista(cadena_impresoras, pos);
            imprimir_cadena_impresoras(*cadena_impresoras);
        }
        else /*SI LA IMPRESORA NO SE ENCUENTRA*/
        {
            printf("\033[1;33mADVERTENCIA:\033[0m La impresora '%s' no se ha encontrado.\n", impresora.nome);
        }
    }
    else /*SI LA LISTA ES VACÍA*/
    {
        printf("\033[1;33mADVERTENCIA: \033[0mLa lista de impresoras está vacía.\n");
    }
}

void nueva_impresora(TLISTA *cadena_impresoras)
{
    int error = 1;
    TIPOELEMENTOLISTA impresora;
    printf("Introduce nombre/marca/modelo/ubicación: ");
    scanf("%s %s %s %s", impresora.nome, impresora.marca, impresora.modelo, impresora.ubicacion);
    printf("\033[2J\033[H");
    crearCola(&impresora.cola_impresion); /*CREA LA COLA DE LA IMPRESORA*/
    encontrar_impresora(*cadena_impresoras, impresora, &error);
    if (error == 1) /*SI LA IMPRESORA EXISTE*/
    {
        printf("\033[1;33mADVERTENCIA:\033[0m La impresora '%s' ya existe.\n", impresora.nome);
    }
    else /*SI NO EXISTE*/
    {
        insertarElementoLista(cadena_impresoras, finLista(*(cadena_impresoras)), impresora);
        imprimir_cadena_impresoras(*cadena_impresoras);
    }
}

void imprimir_cola_impresion(TLISTA lista, TIPOELEMENTOLISTA impresorabuscar)
{
    if (esListaVacia(lista))
    {
        printf("\033[1;31mADVERTENCIA:\033[0m La lista de impresoras está vacía.\n");
    }
    else /*SI LA LISTA NO ESTÁ VACÍA*/
    {
        int error = 1;
        TPOSICION pos_impresora = encontrar_impresora(lista, impresorabuscar, &error);
        if (error != 0) /*SI SE ENCUENTRA LA IMPRESORA*/
        {
            TIPOELEMENTOLISTA impresora;
            recuperarElementoLista(lista, pos_impresora, &impresora);
            if (esColaVacia(impresora.cola_impresion))
            {
                printf("\033[1;33mADVERTENCIA:\033[0m La cola de impresión está vacía para la impresora '%s'.\n", impresora.nome);
            }
            else
            {
                TIPOELEMENTOCOLA elemento;
                printf("Cola de impresión para la impresora '%s': ", impresora.nome);
                for (int i = 0; i < longitudCola(impresora.cola_impresion); i++) /*ELIMINA EL PRIMER ELEMENTO DE LA COLA, LO MUESTRA Y LO VUELVE A AÑADIR*/
                {
                    consultarPrimerElementoCola(impresora.cola_impresion, &elemento);
                    suprimirElementoCola(&impresora.cola_impresion);
                    anadirElementoCola(&impresora.cola_impresion, elemento);
                    printf("%d ", elemento);
                }
            }
        }
        else /*SI LA IMPRESORA NO SE ENCONTRÓ*/
        {
            printf("\033[1;33mADVERTENCIA:\033[0m La impresora '%s' no se ha encontrado.\n", impresorabuscar.nome);
        }
    }
}

void enviar_traballo(TLISTA *cadena_impresoras, TIPOELEMENTOLISTA impresora, TIPOELEMENTOCOLA traballo)
{
    if (esListaVacia(*cadena_impresoras))
    {
        printf("\033[1;31mADVERTENCIA:\033[0m La lista de impresoras está vacía.\n");
    }
    else
    {
        int error = 1;
        TPOSICION posicion_impresora = encontrar_impresora((*cadena_impresoras), impresora, &error);

        if (error != 0)
        {
            printf("\033[1;32mINFO:\033[0m Enviando trabajo %d a %s. Progreso[", traballo, impresora.nome);
            int progreso;
            for (progreso = 0; progreso <= 10; ++progreso)
            {
                printf("==");
                fflush(stdout);
                usleep(300000);
            }

            printf("] 100%% completado.\n");
            usleep(1000000);
            printf("\033[2J\033[H");
            recuperarElementoLista((*cadena_impresoras), posicion_impresora, &impresora);
            anadirElementoCola(&(impresora.cola_impresion), traballo);
            modificarElementoLista(cadena_impresoras, posicion_impresora, impresora);
            printf("\033[1;32mTrabajo %d enviado a %s.\n\033[0m", traballo, impresora.nome);
        }
        else /*SI NO SE HA ENCONTRADO LA IMPRESORA*/
        {
            printf("\033[1;33mADVERTENCIA:\033[0m La impresora '%s' no se ha encontrado.\n", impresora.nome);
        }
    }
}

void imprimir_traballo(TLISTA cadena_impresoras, TIPOELEMENTOLISTA impresora)
{
    if (esListaVacia(cadena_impresoras))
    {
        printf("\033[1;31mADVERTENCIA:\033[0m La lista de impresoras está vacía.\n");
    }
    else
    {
        {

            int error = 1;
            TPOSICION pos = encontrar_impresora(cadena_impresoras, impresora, &error);

            if (error != 0) /* SI SE ENCUENTRA LA IMPRESORA */
            {
                TIPOELEMENTOLISTA impresora_copia;
                recuperarElementoLista(cadena_impresoras, pos, &impresora_copia);

                if (esColaVacia(impresora_copia.cola_impresion)) /*SI LA COLA ES VACÍA*/
                {
                    printf("\033[1;33mADVERTENCIA:\033[0m La cola de impresión está vacía para la impresora '%s'.\n", impresora_copia.nome);
                }
                else /*SI LA COLA NO ES VACÍA*/
                {
                    TIPOELEMENTOCOLA traballo;
                    consultarPrimerElementoCola(impresora_copia.cola_impresion, &traballo);
                    printf("\033[1;32mINFO:\033[0m Imprimiendo trabajo en la impresora '%s'. Progreso: [", impresora_copia.nome);
                    int progreso;
                    for (progreso = 0; progreso <= 10; ++progreso) /*CARGA*/
                    {
                        printf("==");
                        fflush(stdout);
                        usleep(300000);
                    }

                    printf("] 100%% completado.\n");
                    usleep(1000000);
                    printf("\033[2J\033[H");
                    suprimirElementoCola(&(impresora_copia.cola_impresion));          /*IMPRIME EL TRABAJO*/
                    modificarElementoLista(&cadena_impresoras, pos, impresora_copia); /*ACTUALIA LA IMPRESORA*/
                }
            }
            else /*SI NO SE ENCUENTRA*/
            {
                printf("\033[1;33mADVERTENCIA:\033[0m La impresora '%s' no se ha encontrado.\n", impresora.nome);
            }
        }
    }
}

void encontrar_impresora_poca_carga(TLISTA lista)
{
    if (esListaVacia(lista))
    {
        printf("\033[1;31mADVERTENCIA:\033[0m La lista de impresoras está vacía.\n");
    }
    else
    {
        TPOSICION pos = primeroLista(lista);
        TIPOELEMENTOLISTA impresora;
        recuperarElementoLista(lista, pos, &impresora);
        int tamano_actual, tamano_menor = longitudCola(impresora.cola_impresion);
        while (pos != finLista(lista)) /*GUARDA CUÁL ES EL MENOR TAMAÑO EN LA COLA*/
        {
            recuperarElementoLista(lista, pos, &impresora);
            tamano_actual = longitudCola(impresora.cola_impresion);
            if (tamano_actual < tamano_menor)
                tamano_menor = tamano_actual;
            pos = siguienteLista(lista, pos);
        }
        pos = primeroLista(lista);
        printf("Las impresoras con menos carga de impresión tienen %d trabajos y son: ", tamano_menor);
        while (pos != finLista(lista)) /*DEVUELVE LAS IMPRESORAS QUE SE CORRESPONDEN CON DICHO TAMAÑO*/
        {
            recuperarElementoLista(lista, pos, &impresora);
            tamano_actual = longitudCola(impresora.cola_impresion);
            if (tamano_actual == tamano_menor)
            {

                printf("%s ", impresora.nome);
            }
            pos = siguienteLista(lista, pos);
        }
        printf("\n");
    }
}
