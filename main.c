#include <stdlib.h>
#include <stdio.h>
#include "impresora.h"
#include "lista.h"
#include "cola.h"
#include <unistd.h>

int main(int argc, char **argv)
{
    TLISTA cadena_impresoras;
    TIPOELEMENTOLISTA impresora;
    TIPOELEMENTOCOLA traballo;
    char opcion;

    crearLista(&cadena_impresoras);
    FILE *file = fopen("impresoras.txt", "r+");
    cargar_impresoras(file, cadena_impresoras);
    do
    {
        printf("\033[1;34m");
        printf("\n┌──────────────────────────────────────────────────────────────┐\n");
        printf("│                      Opciones del Menú                       │\n");
        printf("└──────────────────────────────────────────────────────────────┘\n");
        printf("┌──────────────────────────────────────────────────────────────┐\n");
        printf("│  1) Eliminar impresora       2) Añadir impresora             │\n");
        printf("│  3) Enviar trabajo           4) Trabajos pendientes          │\n");
        printf("│  5) Imprimir trabajo         6) Impresoras con poca carga    │\n");
        printf("│  7) Mostrar impresoras       0) Salir                        │\n");
        printf("└──────────────────────────────────────────────────────────────┘\n");
        printf("\033[0m");

        printf("Ingrese una opción: ");
        scanf(" %c", &opcion);
        printf("\033[2J\033[H");

        switch (opcion)
        {

        case '1':
            eliminar_impresora(&cadena_impresoras);
            break;
        case '2':
            nueva_impresora(&cadena_impresoras);
            break;
        case '3':
            printf("Introduce nombre de la impresora y número de trabajo: ");
            scanf("%s %d", impresora.nome, &traballo);
            printf("\033[2J\033[H");
            enviar_traballo(&cadena_impresoras, impresora, traballo);
            break;
        case '4':
            printf("Nombre de la impresora: ");
            scanf("%s", impresora.nome);
            printf("\033[2J\033[H");
            imprimir_cola_impresion(cadena_impresoras, impresora);
            break;
        case '5':
            printf("Nombre de la impresora: ");
            scanf("%s", impresora.nome);
            printf("\033[2J\033[H");
            imprimir_traballo(cadena_impresoras, impresora);
            break;
        case '6':
            encontrar_impresora_poca_carga(cadena_impresoras);
            break;
        case '7':
            imprimir_cadena_impresoras(cadena_impresoras);
            break;
        case '0':
            FILE *file2 = fopen("impresoras.txt", "w");
            actualizararchivo(file2, cadena_impresoras);
            fclose(file2);
            fclose(file);
            destruirLista(&cadena_impresoras);
            printf("\033[32mGuardando cambios...\n\033[0m");
            usleep(1000000); 
            printf("\033[2J\033[H");
            break;
        default:
            printf("\033[1;33mADVERTENCIA: \033[1;31mOpción incorrecta\n\033[0m");
            break;
        }
    } while (opcion != '0');
    return (EXIT_SUCCESS);
}