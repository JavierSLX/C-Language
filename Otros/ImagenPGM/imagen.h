#ifndef _IMAGEN_H
#define _IMAGEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define COLUMNA 640
#define RENGLON 480
#define LARGO COLUMNA
#define ARCHIVO "balloons.pgm"

void siguienteRenglon(char cadena[], FILE *f);
int errorImagen (char cadena[], FILE *f);
int obtenerValor(char cadena[], int *carry);
int errorMedidas (char cadena[], FILE *f);
int obtenerMaximo (char cadena[], FILE *f);
void obtenerMatrizA (int m[][COLUMNA], FILE *f);
void obtenerMatrizB (int m[][COLUMNA], int n[][COLUMNA], int maximo, int t);
void modificarMatrizA (int m[][COLUMNA], int maximo, int u);
void nuevaImagen (int n[][COLUMNA], int numero);
void imprimirAInt(int arreglo[], int length);

#endif
