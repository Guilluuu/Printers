#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "impresora.h"
#include "lista.h"
#include <unistd.h>

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
        while (fscanf(file, "%s %s %s %s", impresora.nome, impresora.marca, impresora.modelo, impresora.ubicacion) == 4)
        {
            crearCola(&impresora.cola_impresion);
            insertarElementoLista(&cadena_impresoras, finLista(cadena_impresoras), impresora);
            printf("\033[36mInsertando impresora:\033[0m %s %s %s %s\n", impresora.nome, impresora.marca, impresora.modelo, impresora.ubicacion);
            usleep(500000);
        }
    }

    printf("\033[1;32mCarga completa.\n\033[0m");
    usleep(1000000);
    printf("\033[2J\033[H");
}

void actualizararchivo(FILE *file, TLISTA cadena_impresoras)
{
    TIPOELEMENTOLISTA impresora;
    while (!esListaVacia(cadena_impresoras))
    {
        TPOSICION pos = primeroLista(cadena_impresoras);
        recuperarElementoLista(cadena_impresoras, pos, &impresora);
        destruirCola(&impresora.cola_impresion);
        suprimirElementoLista(&cadena_impresoras, pos);
        fprintf(file, "%s %s %s %s\n", impresora.nome, impresora.marca, impresora.modelo, impresora.ubicacion);
    }
}

void imprimir_cadena_impresoras(TLISTA cadena_impresoras)
{
    if (esListaVacia(cadena_impresoras))
    {
        printf("\033[1;33mADVERTENCIA:\033[0m La lista de impresoras está vacía.\n");
    }
    else
    {
        TIPOELEMENTOLISTA impresora;
        TPOSICION pos = primeroLista(cadena_impresoras);
        printf("\033[1m\nImpresoras cargadas:\n\033[0m\n");
        while (pos != finLista(cadena_impresoras))
        {
            recuperarElementoLista(cadena_impresoras, pos, &impresora);
            printf("\033[36mNombre: \033[0m%s \033[36mMarca: \033[0m%s \033[36mModelo: \033[0m%s \033[36mUbicación: \033[0m%s\n",
                   impresora.nome, impresora.marca, impresora.modelo, impresora.ubicacion);
            pos = siguienteLista(cadena_impresoras, pos);
        }
    }
}

TPOSICION encontrar_impresora(TLISTA lista, TIPOELEMENTOLISTA impresora_encontrar, int *error)
{

    TPOSICION pos = primeroLista(lista);
    TIPOELEMENTOLISTA elemento_actual;

    while (pos != finLista(lista))
    {
        recuperarElementoLista(lista, pos, &elemento_actual);
        if (!strcmp(impresora_encontrar.nome, elemento_actual.nome))
        {
            return pos;
            *error = 1;
        }
        pos = siguienteLista(lista, pos);
    }
    *error = 0;
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
        if (error != 0)
        {
            recuperarElementoLista(*cadena_impresoras, pos, &impresora);
            if (!esColaVacia(impresora.cola_impresion))
                destruirCola(&impresora.cola_impresion);
            suprimirElementoLista(cadena_impresoras, pos);
            imprimir_cadena_impresoras(*cadena_impresoras);
        }
        else
        {
            printf("\033[1;33mADVERTENCIA:\033[0m La impresora '%s' no se ha encontrado.\n", impresora.nome);
        }
    }
    else
    {
        printf("\033[1;33mADVERTENCIA: \033[0mLa lista de impresoras está vacía.\n");
    }
}

void nueva_impresora(TLISTA *cadena_impresoras)
{
    int error = 1;
    impresora impresora;
    printf("Introduce nombre/marca/modelo/ubicación: ");
    scanf("%s %s %s %s", impresora.nome, impresora.marca, impresora.modelo, impresora.ubicacion);
    printf("\033[2J\033[H");
    crearCola(&impresora.cola_impresion);
    encontrar_impresora(*cadena_impresoras, impresora, &error);
    if (error == 1)
    {
        printf("\033[1;33mADVERTENCIA:\033[0m La impresora '%s' ya existe.\n", impresora.nome);
    }
    else
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
    else
    {
        int error = 1;
        TPOSICION pos_impresora = encontrar_impresora(lista, impresorabuscar, &error);
        if (error != 0)
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
                for (int i = 0; i < longitudCola(impresora.cola_impresion); i++)
                {
                    consultarPrimerElementoCola(impresora.cola_impresion, &elemento);
                    suprimirElementoCola(&impresora.cola_impresion);
                    anadirElementoCola(&impresora.cola_impresion, elemento);
                    printf("%d", elemento);
                }
            }
        }
        else
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
            printf("\033[1;32mINFO:\033[0m Enviando trabajo %d a %s. Progreso[",traballo, impresora.nome);
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
        else
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

            if (error != 0)
            {
                TIPOELEMENTOLISTA impresora_copia;
                recuperarElementoLista(cadena_impresoras, pos, &impresora_copia);

                if (esColaVacia(impresora_copia.cola_impresion))
                {
                    printf("\033[1;33mADVERTENCIA:\033[0m La cola de impresión está vacía para la impresora '%s'.\n", impresora_copia.nome);
                }
                else
                {
                    TIPOELEMENTOCOLA traballo;
                    consultarPrimerElementoCola(impresora_copia.cola_impresion, &traballo);
                    printf("\033[1;32mINFO:\033[0m Imprimiendo trabajo en la impresora '%s'. Progreso: [", impresora_copia.nome);
                    int progreso;
                    for (progreso = 0; progreso <= 10; ++progreso)
                    {
                        printf("==");
                        fflush(stdout); // Para forzar la salida del búfer y mostrar la barra de progreso inmediatamente
                        usleep(300000); // Espera 300 milisegundos (ajusta este valor según lo necesario)
                    }

                    printf("] 100%% completado.\n");
                    usleep(1000000);
                    printf("\033[2J\033[H");
                    suprimirElementoCola(&(impresora_copia.cola_impresion));
                    modificarElementoLista(&cadena_impresoras, pos, impresora_copia);
                }
            }
            else
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
        while (pos != finLista(lista))
        {
            recuperarElementoLista(lista, pos, &impresora);
            tamano_actual = longitudCola(impresora.cola_impresion);
            if (tamano_actual < tamano_menor)
                tamano_menor = tamano_actual;
            pos = siguienteLista(lista, pos);
        }
        pos = primeroLista(lista);
        printf("Las impresoras con menos carga de impresión tienen %d trabajos y son: ", tamano_menor);
        while (pos != finLista(lista))
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
