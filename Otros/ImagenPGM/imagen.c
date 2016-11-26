#include "imagen.h"

//Obtiene y verifica el siguiente renglon del archivo
void siguienteRenglon(char cadena[], FILE *f)
{
    int espacios = 0;
    int i = 0;

    //Verifica que el siguiente renglon tenga al menos un caracter
    do
    {
        fgets(cadena, LARGO, f);
        for (i = 0; i < strlen(cadena); i++)
            if (isspace(cadena[i]))
                espacios++;

    }while(espacios == strlen(cadena));

    return;
}

//Checa si el primer renglon posee la caracteristica "P2"
int errorImagen (char cadena[], FILE *f)
{
    siguienteRenglon(cadena, f);
    if (strcmp(cadena, "P2\n"))
    {
        printf("ERROR. La imagen no puede ser analizada, no contiene el formato P2\n");
        printf("La imagen contiene un formato %s\n", cadena);
        return 1;
    }

    return 0;
}

//Obtiene un valor a partir de una cadena (regresando el valor analizado)
int obtenerValor (char cadena[], int *carry)
{
    int i, j;
    int value = 0;
    int digitos = 0;
    int cont = 0;
    char n[4];

    //Analiza si el carry (posición) es igual o mayor que el largo de la cadena, si es así manda que el renglón no es posible analizarlo
    if ((*carry + 1) >= strlen(cadena))
        return -1;

    j = *carry;

    //Verifica si la posicion del carry no está en un espacio, en caso de que sí, lo actualiza
    for (i = j; ; i++)
    {
        if (!isdigit(cadena[i]))
            *carry += 1;
        else
            break;
    }

    //Checa cuantos digitos posee la parte de la cadena a analizar y los extrae en una pequeña cadena (el ciclo termina al encontrar un espacio)
    for (i = *carry; i < strlen(cadena); i++)
    {
        if (isdigit(cadena[i]))
        {
             digitos++;
             n[cont] = cadena[i];
             cont++;
        }

        if (isspace(cadena[i]))
            break;
    }

    //Se le asigna una secuencia de escape de finalización de cadena
    n[cont] = '\0';

    //Si no encontró ninguna dígito en la cadena, manda un mensaje de que el renglón ya no se puede analizar más
    if (digitos == 0)
        return -1;

    //Transforma la cadena a entero
    value = atoi(n);

    //Actualiza el carry, a la nueva posición (saltandose la posición que detuvo el ciclo anterior [espacio])
    *carry = *carry + digitos + 1;


    return value;
}

//Verifica que las medidas del archivo coincidan con las definidas en las constantes
int errorMedidas (char cadena[], FILE *f)
{
    int c = 0;
    int i = 0;
    int n;

    //Verifica si la linea es de comentario, si lo es, pasa al siguiente renglon
    do
    {
        siguienteRenglon(cadena, f);

        for (i = 0; i < strlen(cadena); i++)
            if (cadena[i] == '#')
                break;

    }while(cadena[i] == '#');

    //Usa la función para obtener el número de columnas
    n = obtenerValor(cadena, &c);

    //Compara si es el mismo valor que la constante COLUMNA
    if (n != COLUMNA)
    {
        printf("ERROR. Se debe de verificar el valor de columnas %d != %d\n", COLUMNA, n);
        return 1;
    }

    //Usa la función para obtener el número de renglones
    n = obtenerValor(cadena, &c);

    //Compara si es el mismo valor que la constante RENGLON
    if (n != RENGLON)
    {
        printf("ERROR. Se debe de verificar el valor de renglones\n");
        return 1;
    }

    return 0;
}

//Obtiene el valor máximo que se en cuentra en el archivo
int obtenerMaximo (char cadena[], FILE *f)
{
    int value = 0;

    siguienteRenglon(cadena, f);
    value = atoi(cadena);

    return value;
}

//Funcion que obtiene toda la matriz A[N][M] contenida en el archivo
void obtenerMatrizA (int m[][COLUMNA], FILE *f)
{
    int carry = 0;
    char c[LARGO];
    int i = 0;
    int j = 0;
    int limite = 0;

    siguienteRenglon(c, f);

    //Termina el ciclo hasta que se hayan tomado todos los valores del archivo
    while(limite <= RENGLON*COLUMNA)
    {
        //Si se encuentra un enter, se pasa al siguiente renglón, y se inicializa carry a la primera posición
        if (((c[carry] == '\n') || (c[carry-1] == '\n') || (c[carry+1] == '\n')) && (carry != 0))
        {
            siguienteRenglon(c, f);
            carry = 0;
        }

        //Si el contador j llega al límite de posiciones del arreglo, aumenta en renglones y lo inicializa a 0
        if (j > COLUMNA-1)
        {
            i++;
            j = 0;
        }

        //Saca y convierte el valor a entero y aumenta los contadores en 1
        m[i][j] = obtenerValor(c, &carry);
        limite++;
        j++;
    }

    return;
}

//Funcion que obtiene la matriz B[N][M] que cambia los valor de acuerdo al umbral
void obtenerMatrizB (int m[][COLUMNA], int n[][COLUMNA], int maximo, int t)
{
    int i, j;

    //system("pause");
    //Analiza todo el arreglo m y define los valores para el arreglo n
    for (i = 0; i < RENGLON; i++)
    {
        for (j = 0; j < COLUMNA; j++)
        {
            if (m[i][j] <= t)
                n[i][j] = 0;
            else
                n[i][j] = maximo;
        }
    }

    return;
}

//Modifica la matriz A para obtener los nuevos valores
void modificarMatrizA (int m[][COLUMNA], int maximo, int u)
{
    int i, j;

    //system("pause");
    //Analiza todo el arreglo m y define los valores para el arreglo n
    for (i = 0; i < RENGLON; i++)
    {
        for (j = 0; j < COLUMNA; j++)
        {
            if (m[i][j] <= u)
                m[i][j] = 0;
            else
                m[i][j] = maximo;
        }
    }

    return;
}

//Crea un nuevo archivo llamado "resultado.pgm" dandole formato y caracteristicas a la imagen nueva
void nuevaImagen (int n[][COLUMNA], int numero)
{
    int i;
    int j;
    int cont = 0;
    char c[LARGO];
    FILE *nuevo;
    FILE *imagen;

    nuevo = fopen ("resultado.pgm", "w");
    imagen = fopen (ARCHIVO, "r");

    if (nuevo == NULL || imagen == NULL)
    {
        printf("Error con documentos\n");
        return;
    }

    //Copia las cabeceras de la imagen
    for (i = 0; i < 4; i++)
    {
        siguienteRenglon(c, imagen);
        //printf("%s", c);
        fprintf(nuevo, "%s", c);
    }
    fclose(imagen);

    //Hace la impresión de los valores de la nueva imagen
    for (i = 0; i < RENGLON; i++)
    {
        for (j = 0; j < COLUMNA; j++)
        {
            fprintf(nuevo, "%3d ", n[i][j]);
            cont++;

            if (cont == numero)
            {
                fprintf(nuevo, "\n");
                cont = 0;
            }
        }
    }

    fclose(nuevo);
    return;
}

void imprimirAInt(int arreglo[], int length)
{
    int i;
    for (i = 0; i < length; i++)
        printf("%03d ", arreglo[i]);
    printf("\n");

    return;
}
