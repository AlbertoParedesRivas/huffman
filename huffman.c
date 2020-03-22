#include<stdio.h>
#include<stdlib.h>
void registrarSimbolo(char*, float*, int*);
void listarSimbolos(char*, float*, int*);
void eliminarSimbolo(char*, float*, int*);
void modificarSimbolo(char*, float*, int*);
void generarCodigos(char*, float*, char*);
void cargarDiccionario(char*);

void main() {
    int opcion, tamano = 0;
    char *simbolos = NULL;
    float *frecuencias = NULL;
    char **diccionario = NULL;
    simbolos = (char*)malloc(sizeof(char));
    frecuencias = (float*)malloc(sizeof(float));
    if (simbolos == NULL)
    {
        printf("Error al reservar memoria");
        exit(0);
    }
    if (frecuencias == NULL)
    {
        printf("Error al reservar memoria");
        exit(0);
    }
    
    do
    {
        printf("Algoritmo de Huffman para la codificacion de mensajes\n");
        printf("Seleccione una de las siguientes opciones:\n");
        printf("1. Registrar simbolo\n2. Listar simbolos\n3. Eliminar simbolo.\n4. Modificar un simbolo.\n5. Generar codigos.\n6. Guardar diccionario (archivo).\n7. Cargar diccionario (archivo).\n8. Salir.\n");
        scanf("%d", &opcion);
        system("clear");
        switch (opcion)
        {
        case 1:
            registrarSimbolo(simbolos, frecuencias, &tamano);
            break;
        case 2:
            listarSimbolos(simbolos, frecuencias, &tamano);
            break;
        case 3:
            eliminarSimbolo(simbolos, frecuencias, &tamano);
            break;
        case 4:
            modificarSimbolo(simbolos, frecuencias, &tamano);
            break;
        case 5:
            printf("En construccion");
            break;
        case 6:
            
            break;
        case 7:
            
            break;
        case 8:
            printf("Saliendo...\n");
            break;
        default:
            printf("Seleccione una opcion valida.\n");
            break;
        }
    } while (opcion != 8);
    
}

void registrarSimbolo(char *simbolos, float *frecuencias, int *tamano){
    char nuevoSimbolo, *tmpSimbolos;
    float nuevaFrecuencia, *tmpFrecuencias;

    printf("Ingrese el simbolo a registrar\n");
    scanf(" %c", &nuevoSimbolo);
    printf("Ingrese la frecuencia del simbolo\n");
    scanf("%f", &nuevaFrecuencia);

    for (int i = 0; i < *tamano; i++)
    {
        if (simbolos[i] == nuevoSimbolo)
        {
            printf("El simbolo ya se encuentra registrado\n");
            return;
        }
        
    }
    (*tamano)++;
    tmpSimbolos = realloc(simbolos, sizeof(int)*(*tamano));
    if (tmpSimbolos){
        simbolos = tmpSimbolos;
        simbolos[(*tamano)-1] = nuevoSimbolo;
    }else{
        free(tmpSimbolos);
    }
    tmpFrecuencias = realloc(frecuencias, sizeof(float)*(*tamano));
    if (tmpFrecuencias){
        frecuencias = tmpFrecuencias;
        frecuencias[(*tamano)-1] = nuevaFrecuencia;
    }else{
        free(tmpFrecuencias);
    }
}

void listarSimbolos(char *simbolos, float *frecuencias, int *tamano){
    if ((*tamano) == 0){
        printf("No hay simbolos registrados\n");
    }else{
        for (int i = 0; i < (*tamano); i++)
        {
            printf("%c - %.2f\n",simbolos[i], frecuencias[i]);
        }
    }
}

void eliminarSimbolo(char *simbolos, float *frecuencias, int *tamano){
    int posicion_eliminar = -1;
    char simbolo, *tmpSimbolos;
    float *tmpFrecuencias;
    if ((*tamano) == 0){
        printf("No hay simbolos registrados\n");
    }else{
        printf("Ingresa el simbolo a eliminar\n");
        scanf(" %c", &simbolo);
        for (int i = 0; i < (*tamano); i++)
        {
            if(simbolos[i] == simbolo){
                posicion_eliminar = i;
            }
        }
        if (posicion_eliminar == -1){
            printf("El simbolo que se quiere eliminar no se encuentra registrado\n");
            return;
        }
        for (int i = posicion_eliminar; i < (*tamano) - 1; i++)
        {
            simbolos[i] = simbolos[i + 1];
            frecuencias[i] = frecuencias[i + 1];
        }
        (*tamano)--;
        tmpSimbolos = realloc(simbolos, sizeof(int)*(*tamano));
        if (tmpSimbolos){
            simbolos = tmpSimbolos;
        }else{
            free(tmpSimbolos);
        }
        tmpFrecuencias = realloc(frecuencias, sizeof(float)*(*tamano));
        if (tmpFrecuencias){
            frecuencias = tmpFrecuencias;
        }else{
            free(tmpFrecuencias);
        }
    }
}

void modificarSimbolo(char *simbolos, float *frecuencias, int *tamano){
    int posicionModificar = -1;
    char simbolo;
    float nuevaFrecuencia;
    if ((*tamano) == 0)
    {
        printf("No hay simbolos registrados\n");
    }else{
        printf("Ingresa el simbolo a modificar\n");
        scanf(" %c", &simbolo);
        printf("Ingresa el nuevo valor de frecuencia para %c\n", simbolo);
        scanf("%f", &nuevaFrecuencia);

        for (int i = 0; i < (*tamano); i++)
        {
            if (simbolos[i] == simbolo)
            {
                posicionModificar = i;
            }
            
        }
        if (posicionModificar == -1){
            printf("No se encontro el simbolo a modificar\n");
        }else{
            frecuencias[posicionModificar] = nuevaFrecuencia;
        }
    }
    
}