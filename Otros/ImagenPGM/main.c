#include "imagen.h"

int main()
{
    int error;
    char renglon[LARGO];
    int A[RENGLON][COLUMNA];
    int maximo;
    int umbral;
    FILE *imagen = NULL;

    //Abre la imagen que se va a cambiar
    imagen = fopen(ARCHIVO, "r");

    if (imagen == NULL)
    {
        printf("La imagen %s no puede ser leida\n", ARCHIVO);
        return 1;
    }

    //Checa si la imagen tiene la extensión correcta
    error = errorImagen(renglon, imagen);

    if (error > 0)
        return 1;

    //Checa si las medidas son las mismas que las constantes definidas en imagen.h
    error = errorMedidas(renglon, imagen);

    if (error > 0)
        return 1;

    //Obtiene el valor máximo registrado
    maximo = obtenerMaximo(renglon, imagen);

    //Obtiene la cadena de la imagen (todos los valores numéricos del archivo)
    obtenerMatrizA(A, imagen);

    //Le pide al usuario el valor del umbral
    do
    {
        system("cls");
        printf("Datos obtenidos de %s de manera exitosa!\n", ARCHIVO);
        printf("Coloque el valor de umbral: ");
        scanf("%d", &umbral);

        if (umbral > maximo || umbral < 0)
            printf("Valor %d incorrecto. Este debe de estar entre el valor de 0 a %d\n", umbral, maximo);

    }while(umbral > maximo || umbral < 0);

    //Cambia los valores con los datos de máximo y del umbral
    modificarMatrizA(A, maximo, umbral);

    //Crea un documento con la nueva imagen
    nuevaImagen(A, 20);

    printf("\nImagen modificada satisfactoriamente :v\n");

    fclose(imagen);
    return 0;
}
