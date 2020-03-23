#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void registrarSimbolo(char *, float *, int *);
void listarSimbolos(char *, float *, int *);
void eliminarSimbolo(char *, float *, int *);
void modificarSimbolo(char *, float *, int *);
void generarCodigos(char *, float *, char *);
void cargarDiccionario(char **, char ***, int *, int *);
void mostrarDiccionario(char *, char **, int);
void guardarDiccionario(char *, char **, int, int);
void codificarMensaje(char *, char **, int, int);
void decodificarMensaje(char *, char **, int, int);
struct nodo *generarDiccionario(char *,float *, int, int*, char***);
void mostrarLista(struct nodo *);

struct nodo{
    char letra;
    float frecuencia;
    struct nodo *sig;
    struct nodo *cero;
    struct nodo *uno;
};

int main()
{
    int opcion, tamano = 0;
    char *simbolos = NULL;
    float *frecuencias = NULL;
    char **diccionario = NULL;
    int codigoGenerado = 0;
    struct nodo *arbol;
    simbolos = (char *)malloc(sizeof(char));
    frecuencias = (float *)malloc(sizeof(float));
    diccionario = (char **)malloc(sizeof(char *));
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
        printf("1. Registrar simbolo\n2. Listar simbolos\n3. Eliminar simbolo.\n4. Modificar un simbolo.\n5. Generar diccionario.\n6. Guardar diccionario (archivo).\n7. Cargar diccionario (archivo).\n");
        if (codigoGenerado)
        {
            printf("8. Codificar mensaje\n9. Decodificar mensaje\n10. Salir\n");
            // mostrarDiccionario(simbolos, diccionario, tamano);
            mostrarLista(arbol);
        }
        else
        {
            printf("10. Salir\n");
        }

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
            arbol = generarDiccionario(simbolos, frecuencias, tamano,&codigoGenerado, &diccionario);
            break;
        case 6:
            guardarDiccionario(simbolos, diccionario, tamano, codigoGenerado);
            break;
        case 7:
            cargarDiccionario(&simbolos, &diccionario, &tamano, &codigoGenerado);
            break;
        case 8:
            codificarMensaje(simbolos, diccionario, tamano, codigoGenerado);
            break;
        case 9:
            decodificarMensaje(simbolos, diccionario, tamano, codigoGenerado);
            break;
        case 10:
            printf("Saliendo...\n");
            break;
        default:
            printf("Seleccione una opcion valida.\n");
            break;
        }
    } while (opcion != 10);
    return 0;
}

void registrarSimbolo(char *simbolos, float *frecuencias, int *tamano)
{
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
    tmpSimbolos = realloc(simbolos, sizeof(char) * (*tamano));
    if (tmpSimbolos)
    {
        simbolos = tmpSimbolos;
        simbolos[(*tamano) - 1] = nuevoSimbolo;
    }
    else
    {
        free(tmpSimbolos);
    }
    tmpFrecuencias = realloc(frecuencias, sizeof(float) * (*tamano));
    if (tmpFrecuencias)
    {
        frecuencias = tmpFrecuencias;
        frecuencias[(*tamano) - 1] = nuevaFrecuencia;
    }
    else
    {
        free(tmpFrecuencias);
    }
}

void listarSimbolos(char *simbolos, float *frecuencias, int *tamano)
{
    if ((*tamano) == 0)
    {
        printf("No hay simbolos registrados\n");
    }
    else
    {
        for (int i = 0; i < (*tamano); i++)
        {
            printf("%c - %.2f\n", simbolos[i], frecuencias[i]);
        }
    }
}

void eliminarSimbolo(char *simbolos, float *frecuencias, int *tamano)
{
    int posicion_eliminar = -1;
    char simbolo, *tmpSimbolos;
    float *tmpFrecuencias;
    if ((*tamano) == 0)
    {
        printf("No hay simbolos registrados\n");
    }
    else
    {
        printf("Ingresa el simbolo a eliminar\n");
        scanf(" %c", &simbolo);
        for (int i = 0; i < (*tamano); i++)
        {
            if (simbolos[i] == simbolo)
            {
                posicion_eliminar = i;
            }
        }
        if (posicion_eliminar == -1)
        {
            printf("El simbolo que se quiere eliminar no se encuentra registrado\n");
            return;
        }
        for (int i = posicion_eliminar; i < (*tamano) - 1; i++)
        {
            simbolos[i] = simbolos[i + 1];
            frecuencias[i] = frecuencias[i + 1];
        }
        (*tamano)--;
        tmpSimbolos = realloc(simbolos, sizeof(int) * (*tamano));
        if (tmpSimbolos)
        {
            simbolos = tmpSimbolos;
        }
        else
        {
            free(tmpSimbolos);
        }
        tmpFrecuencias = realloc(frecuencias, sizeof(float) * (*tamano));
        if (tmpFrecuencias)
        {
            frecuencias = tmpFrecuencias;
        }
        else
        {
            free(tmpFrecuencias);
        }
    }
}

void modificarSimbolo(char *simbolos, float *frecuencias, int *tamano)
{
    int posicionModificar = -1;
    char simbolo;
    float nuevaFrecuencia;
    if ((*tamano) == 0)
    {
        printf("No hay simbolos registrados\n");
    }
    else
    {
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
        if (posicionModificar == -1)
        {
            printf("No se encontro el simbolo a modificar\n");
        }
        else
        {
            frecuencias[posicionModificar] = nuevaFrecuencia;
        }
    }
}

void mostrarDiccionario(char *simbolos, char **diccionario, int tamano)
{
    printf("\nDiccionario actual:\n");
    for (int i = 0; i < tamano; i++)
    {
        printf("%c-%s\n", simbolos[i], diccionario[i]);
    }
}

void cargarDiccionario(char **simbolos, char ***diccionario, int *tamano, int *codigoGenerado)
{
    char opcion, buffer[128], nombreArchivo[30], *codigo;
    if ((*tamano) > 0)
    {
        printf("Los simbolos registrados anteriormente seran borrados Desea continuar? [Y/n]\n");
        scanf(" %c", &opcion);
        if (opcion == 'n')
        {
            return;
        }
        else if (opcion == 'Y' || opcion == 'y')
        {
            for (int i = 0; i < (*tamano); i++)
            {
                free((*diccionario)[i]);
            }
            free(*diccionario);
            free(*simbolos);
            *diccionario = NULL;
            *(tamano) = 0;
        }
    }
    printf("Introduzca el nombre del archivo que contiene el diccionario\n");
    scanf("%s", nombreArchivo);
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL)
    {
        printf("Error abriendo el archivo\n");
        return;
    }
    int i = 0;
    int j = 0;
    int tamanoCodigo = 0;
    char *tmpSimbolos, *tmpCodigo, **tmpDiccionario;
    codigo = (char *)malloc(sizeof(char));
    *simbolos = (char *)malloc(sizeof(char));
    *diccionario = (char **)malloc(sizeof(char *));
    while (fgets(buffer, sizeof(buffer), archivo) != NULL)
    {
        j = 0;
        tamanoCodigo = 0;
        while (buffer[j] != '\n')
        {
            if (j == 0)
            {
                (*tamano)++;
                tmpSimbolos = (char *)realloc(*simbolos, sizeof(char) * (*tamano));
                if (tmpSimbolos)
                {
                    *simbolos = tmpSimbolos;
                    (*simbolos)[(*tamano) - 1] = buffer[j];
                }
                else
                {
                    free(tmpSimbolos);
                }
            }
            else if (j != 1)
            {
                tamanoCodigo++;
                tmpCodigo = (char *)realloc(codigo, sizeof(char) * tamanoCodigo);
                if (tmpCodigo)
                {
                    codigo = tmpCodigo;
                    codigo[tamanoCodigo - 1] = buffer[j];
                }
                else
                {
                    free(tmpCodigo);
                }
            }
            // printf("%c", buffer[j]);
            j++;
        }
        tamanoCodigo++;
        tmpCodigo = (char *)realloc(codigo, sizeof(char) * tamanoCodigo);
        if (tmpCodigo)
        {
            codigo = tmpCodigo;
            codigo[tamanoCodigo - 1] = '\0';
        }
        else
        {
            free(tmpCodigo);
        }
        tmpDiccionario = (char **)realloc(*diccionario, sizeof(char *) * (*tamano));
        if (tmpDiccionario)
        {
            *diccionario = tmpDiccionario;
            (*diccionario)[(*tamano) - 1] = (char *)malloc(sizeof(char) * tamanoCodigo);
            strcpy((*diccionario)[(*tamano)-1], codigo);
        }
        else
        {
            free(tmpDiccionario);
        }
        i++;
    }
    fclose(archivo);
    (*codigoGenerado) = 1;
}

void guardarDiccionario(char *simbolos, char **diccionario, int tamano, int codigoGenerado){
    if (codigoGenerado == 1)
    {
        FILE *archivo = fopen("diccionarioGuardado.txt", "w");
        for (int i = 0; i < tamano; i++)
        {
            fprintf(archivo,"%c-%s\n", simbolos[i], diccionario[i]);
        }
        printf("Archivo guardado como: diccionarioGuardado.txt\n");
        fclose(archivo);
    }
    else
    {
        printf("No hay ningun diccionario generado\n");
    }
}

void codificarMensaje(char *simbolos, char **diccionario, int tamano, int codigoGenerado){
    char nombreArchivo[30], caracter;
    int j = 0;
    if(codigoGenerado == 1){
        printf("Introduzca el nombre del archivo que contiene el mensaje\n");
        scanf("%s", nombreArchivo);
        FILE *archivo = fopen(nombreArchivo, "r");
        FILE *archivoCodificado = fopen("mensajeCodificado.txt", "w");
        if (archivo == NULL || archivoCodificado == NULL)
        {
            printf("Error abriendo el archivo\n");
            return;
        }
        while ((caracter = getc(archivo)) != EOF)
        {
            for (int i = 0; i < tamano; i++)
            {
                if (simbolos[i] == caracter)
                {
                    j = 0;
                    while (diccionario[i][j] == '0' || diccionario[i][j] == '1')
                    {
                        fputc(diccionario[i][j],archivoCodificado);
                        j++;
                    }
                    break;
                }
            }
        }
        printf("Mensaje codificado guardado en: mensajeCodificado.txt\n");
        fclose(archivo);
        fclose(archivoCodificado);
    }
}

void decodificarMensaje(char *simbolos, char **diccionario, int tamano, int codigoGenerado){
    char nombreArchivo[30], caracter;
    char *codigo = (char*)malloc(sizeof(char)), *tmpCodigo;
    int tamanoCodigo = 1;
    if (codigoGenerado == 1)
    {
        printf("Introduzca el nombre del archivo que contiene el mensaje codificado\n");
        scanf("%s", nombreArchivo);
        FILE *archivo = fopen(nombreArchivo, "r");
        FILE *archivoDecodificado = fopen("mensajeDecodificado.txt", "w");
        if (archivo == NULL || archivoDecodificado == NULL)
        {
            printf("Error abriendo el archivo\n");
            return;
        }
        while ((caracter = getc(archivo)) != EOF)
        {
            tamanoCodigo++;
            tmpCodigo = (char*)realloc(codigo, sizeof(char)*tamanoCodigo);
            if (tmpCodigo)
            {
                codigo = tmpCodigo;
                codigo[tamanoCodigo-1] = '\0';
                codigo[tamanoCodigo-2] = caracter;
                for (int i = 0; i < tamano; i++)
                {
                    if (strcmp(codigo, diccionario[i]) == 0)
                    {
                        fputc(simbolos[i], archivoDecodificado);
                        tamanoCodigo = 1;
                        break;
                    }
                }
            }
            else
            {
                free(tmpCodigo);
            }
            
        }
        fclose(archivo);
        fclose(archivoDecodificado);
    }
}

struct nodo *generarDiccionario(char *simbolos, float *frecuencias, int tamano, int *codigoGenerado, char ***diccionario){
    struct nodo *tmp, *arbol = (struct nodo*)malloc(sizeof(struct nodo));
    // Generar lista enlazada con los valores necesarios
    for (int i = 0; i < tamano; i++)
    {
        if (i == 0)
        {
            arbol->letra = simbolos[i];
            arbol->frecuencia = frecuencias[i];
            arbol->sig = NULL;
            arbol->cero = NULL;
            arbol->uno = NULL;
        }
        else
        {
            tmp = arbol;
            arbol = (struct nodo*)malloc(sizeof(struct nodo));
            arbol->letra = simbolos[i];
            arbol->frecuencia = frecuencias[i];
            arbol->sig = tmp;
            arbol->cero = NULL;
            arbol->uno = NULL;
        }
        printf("%p-%c(%.2f)->%p\n",arbol,arbol->letra,arbol->frecuencia,arbol->sig);
    }
    *codigoGenerado = 1;
    return arbol;
}

void mostrarArbol(struct nodo *arbol, int contador){
    if (arbol == NULL)
    {
        return;
    }
    else
    {
        mostrarArbol(arbol->uno, contador+1);
        for (int i = 0; i < contador; i++)
        {
            printf("    ");
        }
        printf("%.2f",arbol->frecuencia);
        mostrarArbol(arbol->cero, contador+1);
    }
    
}

void mostrarLista(struct nodo *arbol){
    if(arbol == NULL){
        return;
    }
    if (arbol->sig)
    {
        mostrarLista(arbol->sig);
        printf("(%.2f)",arbol->frecuencia);
    }
    else{
        printf("(%.2f)",arbol->frecuencia);
    }
    
}