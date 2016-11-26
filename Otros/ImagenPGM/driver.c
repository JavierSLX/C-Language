#include "imagen.h"
#include <time.h>
#include <assert.h>
#define MAXIMO 255
#define UMBRAL 80

/* Antes de correr las pruebas verifica que todos los valores de las constantes tanto el de driver.c y el de
    imagen.h coincidan con los valores del archivo */

void driverErrorImagen (void);
void driverErrorMedidas (void);
void driverObtenerMaximo (void);
void driverObtenerMatrizA(void);
void driverObtenerMatrizB(void);
void driverNuevaImagen(void);

/*int main()
{
    driverErrorImagen();
    driverErrorMedidas();
    driverObtenerMaximo();
    //driverObtenerMatrizA();
    //driverObtenerMatrizB();
    driverNuevaImagen();
    return 0;
}*/

void driverErrorImagen (void)
{
    int error;
    char prueba[LARGO];
    FILE *f = NULL;

    f = fopen(ARCHIVO, "r");

    if (f == NULL)
    {
        printf("Error al abrir %s\n", ARCHIVO);
        return;
    }

    error = errorImagen(prueba, f);
    assert(error == 0);

    fclose(f);
    return;
}

void driverErrorMedidas (void)
{
    int error;
    char prueba[LARGO];
    FILE *f = NULL;

    f = fopen(ARCHIVO, "r");

    if (f == NULL)
    {
        printf("Error al abrir %s\n", ARCHIVO);
        return;
    }

    siguienteRenglon(prueba, f);
    siguienteRenglon(prueba, f);

    error = errorMedidas(prueba, f);
    assert(error == 0);

    fclose(f);
    return;
}

void driverObtenerMaximo (void)
{
    int valor;
    char prueba[LARGO];
    FILE *f = NULL;

    f = fopen(ARCHIVO, "r");

    if (f == NULL)
    {
        printf("Error al abrir %s\n", ARCHIVO);
        return;
    }

    siguienteRenglon(prueba, f);
    siguienteRenglon(prueba, f);
    siguienteRenglon(prueba, f);

    valor = obtenerMaximo(prueba, f);
    assert(valor == MAXIMO);
    fclose(f);
    return;
}

void driverObtenerMatrizA(void)
{
    int i, j;
    char prueba[LARGO];
    int pA[RENGLON][COLUMNA];
    FILE *f = NULL;

    f = fopen(ARCHIVO, "r");
    if (f == NULL)
    {
        printf("Error al abrir %s\n", ARCHIVO);
        return;
    }

    siguienteRenglon(prueba, f);
    siguienteRenglon(prueba, f);
    siguienteRenglon(prueba, f);
    siguienteRenglon(prueba, f);

    obtenerMatrizA(pA, f);

    for (i = 0; i < RENGLON; i++)
    {
        for (j = 0; j < COLUMNA; j++)
            printf("%03d ", pA[i][j]);
        printf("\n");
    }

    fclose(f);
    return;
}

void driverObtenerMatrizB(void)
{
    int i, j;
    int valorM;
    char prueba[LARGO];
    int A[RENGLON][COLUMNA];
    //int B[RENGLON][COLUMNA]; //Falla al declarar el arreglo cuando es demasiado grande
    FILE *f = NULL;

    f = fopen(ARCHIVO, "r");

    if (f == NULL)
    {
        printf("Error al abrir %s\n", ARCHIVO);
        return;
    }

    siguienteRenglon(prueba, f);
    siguienteRenglon(prueba, f);
    siguienteRenglon(prueba, f);
    valorM = obtenerMaximo(prueba, f);
    obtenerMatrizA(A, f);
    //obtenerMatrizB(A, B, valorM, UMBRAL);
    modificarMatrizA(A, valorM, UMBRAL);

    for (i = 0; i < RENGLON; i++)
    {
        for (j = 0; j < COLUMNA; j++)
            printf("%03d ", A[i][j]);
        printf("\n");
    }

    fclose(f);
    return;
}

void driverNuevaImagen(void)
{
    int i, j;
    int cont = 0;
    int valorM;
    char prueba[LARGO];
    int A[RENGLON][COLUMNA];
    //int B[RENGLON][COLUMNA]; //Falla al declarar el arreglo cuando es demasiado grande
    FILE *f = NULL;
    FILE *p = NULL;

    f = fopen(ARCHIVO, "r");
    p = fopen("prueba.pgm", "w");

    if (f == NULL)
    {
        printf("Error al abrir %s\n", ARCHIVO);
        return;
    }

    siguienteRenglon(prueba, f);
    siguienteRenglon(prueba, f);
    siguienteRenglon(prueba, f);
    valorM = obtenerMaximo(prueba, f);
    obtenerMatrizA(A, f);
    //obtenerMatrizB(A, B, valorM, UMBRAL);
    modificarMatrizA(A, valorM, UMBRAL);

    for (i = 0; i < RENGLON; i++)
    {
        for (j = 0; j < COLUMNA; j++)
        {
            //printf("%3d ", A[i][j]);
            fprintf(p, "%3d ", A[i][j]);
            cont++;

            if (cont == 17)
            {
                //printf("\n");
                fprintf(p, "\n");
                cont = 0;
            }
        }
    }

    nuevaImagen(A, 17);

    fclose(f);
    fclose(p);
    return;
}

