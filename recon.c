//BITACORA:
//  11.01.2020 00:31H NO ALCANCE A PROGRAMAR NADA POR TERMINAR LO DE ESTADISTICA. AHORA JUGARE UNA PARTIDA DE HEROES OF THE STORM.
//  11.01.2020 15:31H TERMINE LA FUNCION QUE ABRE ARCHIVOS EN DISTINTAS FORMAS Y REALIZA LA COMPROBACION SI HUBO ERROR AL ABRIR CIERTO ARCHIVO.
//      FALTA POR TERMINAR LA FUNCION append() PARA PODER SEGIUR CON LA FUNCION get_data()

//IDEA:
//  LECTURA DE ARCHIVOS.
//  ESCRITURA DE ARCHIVOS.
//  RECONOCIMIENTO DE SECTORES ORDENADOS EN UNA LISTA.
//  NUMERACION DE SECTORES ORDENADOS.
//  ALGORITMO DE ORDENAMIENTO (BASICO).
//  IMPLEMENTACION DE RECONOCIMIENTO EN ALGORITMO DE ORDENAMIENTO (BASICO).
//  MENU
//  ALGORITMO DE ORDENAMIENTO (COMPLEJO).
//  IMPLEMENTACION DE RECONOCIMIENTO EN ALGORITMO DE ORDENAMIENTO (COMPLEJO).
//  INTENTAR HACER ANALISIS DE COMPLEJIDAD Y TIEMPOS DE EJECUCION.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "func.h"
#include "sorting.h"

#define false 0
#define true !(false)
#define has_next(T) (*T).next? true : false
#define ARRAY_LEN 100000
//ESTRUCTURAS(DEBIDO A LA CANTIDAD DE DATOS)

struct lista_l{
    double arrayA[ARRAY_LEN];
    double arrayB[ARRAY_LEN];
    struct lista_l *next;
}typedef lista_l;

//----------PROTOTIPADO----------//
FILE*open_file(const char*filename, const char*apertura);//----------------------COMPLETO
//void get_data(FILE*file, int arry[],const char* metodo="1by1");//----------------INCOMPLETO
void append(char cadena[],char at_end);//-----------------------------------------COMPLETO

void Insert_data(lista_l*head, FILE* file, int *counter_node, int*counter_data);
int data_counter(FILE* file);
lista_l* init_list( FILE* file, int *counter_data);
lista_l* clean_list(lista_l *head, int i);
void recorrer(lista_l *head);
//--------FIN PROTOTIPADO--------//
int main(int argc, char*argv[])
{
    /*printf("%s","init lista\n");
    double lista[16];
    for(int i = 0; i< 16; i++){
        lista[i] = (double)rand();
    }
    printf("%s","Merge\n");
    MergeSort_double(lista,0,short_arry_len(lista));
    for(int i = 0; i<short_arry_len(lista);i++){
        printf("%d\n",lista[i]);
    }*/
    printf("Abriendo archivo\n");
    FILE* num = fopen("ArchivoA.tex","r");
    rewind(num);
    double list[ARRAY_LEN];
    int peso = 1;
    int data = 0;
    //char *char_buff = (char*)malloc(sizeof(char_buff));
    double buffer;
    //fflush(stdout);
    printf("Contando elementos...\n");
    clock_t _count = clock();
    long int file_numbers = data_counter(num);
    double _time_count = ((double)clock()-_count)/CLOCKS_PER_SEC;
    printf("...OK. \n %li datos contados en el archivo (%f sec)", file_numbers, _time_count);
    rewind(num);
    lista_l * pointer;
    clock_t start = clock();
    pointer = init_list(num,&data);
    Insert_data(pointer, num,&peso,&data);
    double _time_in = ((double)clock() - start)/CLOCKS_PER_SEC;
    printf("\n|          Lista A          |          Lista B        |\n");
    /*for(int i = 0;i<ARRAY_LEN;i++){
        printf("|-------------------------------------------------------|\n");
        printf("|       %.7e       |       %.7e       |\n",(*pointer).arrayA[i],(*pointer).arrayB[i]);
        printf("|-------------------------------------------------------|\n");
    } */
    printf("...OK \n Tiempo transcurrido: %f \n Total de datos contados: %i \n Total de datos ordenados: %i \n Peso de la estructura(en bytes): %zu \n",_time_in,data,data,sizeof(lista_l));
    printf(" Numero de nodos enlazados: %d \n Peso total(en bytes): %zu (%f mb)\n",peso, sizeof(lista_l) * peso, (sizeof(lista_l) * peso)* 1e-6);
    printf("Liberando memoria...");
    clock_t free_mem = clock();
    recorrer(pointer);
    double final_freemem = ((double)clock()-free_mem)/CLOCKS_PER_SEC;
    printf("Memoria liberada con exito(%f s) \n Direccion: %u", final_freemem,pointer);
    pointer = clean_list(pointer, 1);
    printf("%zu", sizeof((*pointer)));
    //recorrer(pointer);
    //fclose(num);
}




lista_l* init_list( FILE* file, int *counter_data){
    lista_l *head = (lista_l*)malloc(sizeof(lista_l));
    (*head).next = NULL;
    int index;
    double buffer;
    //printf("Lista_A => init\n");
    for(index = 0; index<ARRAY_LEN;index++){
         fscanf(file,"%le",&buffer);
         (*head).arrayA[index] = buffer;
         *counter_data+=1;
    }
    //printf("Lista_B => init\n");
    for(index = 0; index<ARRAY_LEN;index++){
         fscanf(file,"%le",&buffer);
         (*head).arrayB[index] = buffer;
         *counter_data+=1;
    }
    //printf("Iniciando quicksort con: %li datos",short_arry_len((*head).arrayA)+short_arry_len((*head).arrayB));
    quicksort_double((*head).arrayA,0,ARRAY_LEN-1);
    quicksort_double((*head).arrayB,0,ARRAY_LEN-1);
    return head;
}

void recorrer(lista_l *head){
    printf("if head != null\n");
    if(head!=NULL){
        lista_l *aux;
        aux = head;
        int i = 1;
        while(aux){
            printf("NODO (%i)\n size next %zu\n", i,sizeof((*(*aux).next)));
            i++;
            aux=(*aux).next;
        }
    }
}

lista_l* clean_list(lista_l *head, int i){
    lista_l *aux;
    while(head){
        if(head){
            aux = head;
            printf("LIMPIANDO NODO (%i); PESO INICIAL: %zu; PESO DEL SIGUENTE NODO: %zu ",i,sizeof(*aux),sizeof((*(*aux).next)));
            if(has_next(head)){
                head = (*head).next;
            }
            fflush(stdout);
            free(aux);
            aux=NULL;
            printf("PESO FINAL: %zu\n",sizeof(*aux));
            i++;
        }
    }
    return NULL;
}
void Insert_data(lista_l*head, FILE* file, int *counter_node, int *counter_data){
    if(!file){
        printf("ERROR.");
    }else{
        lista_l *aux;
        aux = head;
        int index;
        double buffer;
        do{
            lista_l *temp = (lista_l*)malloc(sizeof(lista_l));
            //printf("Lista_A => body\n");
            for(index = 0; index<ARRAY_LEN; index++){
                if(!feof(file)){
                    fscanf(file,"%le",&buffer);
                    (*temp).arrayA[index] = buffer;
                    *counter_data+=1;
                }
            }
            //printf("Lista_B => body\n");
            for(index = 0; index<ARRAY_LEN; index++){
                if(!feof(file)){
                    fscanf(file,"%le",&buffer);
                    (*temp).arrayB[index] = buffer;
                    *counter_data+=1;
                }
            }
            (*temp).next = NULL;
            (*aux).next = temp;
            aux = temp;
            temp = NULL;
            quicksort_double((*aux).arrayA,0,ARRAY_LEN-1);
            quicksort_double((*aux).arrayB,0,ARRAY_LEN-1);
            *counter_node+=1;
            //free(temp);
        }while(!feof(file));
    }
}

int data_counter(FILE* file){
    if(!file){
        printf("ERROR, el archivo debe estar abierto\n");
        return 0;
    }else{
        double buffer;
        long int counter = 0;
        while(!feof(file)){
            fscanf(file,"%le",&buffer);
            counter++;
        }
        return counter;
    }
}


FILE*open_file(const char*filename, const char*apertura)
{
    //TIPOS DE APERTURA DE ARCHIVOS DISPONIBLES PARA C EN STDIO
    //
    //EXISTE UN TIPO ADICIONAL DENOTADO "b" PARA ARCHIVOS BINARIOS
    //PERO SOLO ES UTILIZADO EN SISTEMAS OPERATIVOS NO PERTENECIENTES
    //A LA FAMILIA DE UNIX

    FILE* file;
    //ARCHIVO DE LECTURA, EL ARCHIVO DEBE EXISTIR
    if(apertura == "read" || apertura == "r")
        file = fopen(filename,"r");
    //ARCHIVO DE ESCRITURA, SE CREA SI NO EXISTE O SE SOBREESCRIBE SI EXISTE
    else if(apertura == "overwrite" || apertura == "w")
        file = fopen(filename,"w");
    //ARCHIVO DE ESCRITURA AL FINAL DE LOS DATOS, SE CREA SI NO EXISTE
    else if(apertura == "append_write" || apertura == "a")
        file = fopen(filename,"a");
    //ARCHIVO DE LECTURA Y ESCRITURA, EL ARCHIVO DEBE EXISTIR
    else if(apertura == "rw_file" || apertura == "r+")
        file = fopen(filename,"r+");
    //ARCHIVO DE LECTURA Y ESCRITURA, SI NO EXISTE SE CREA Y SI EXISTE, SE SOBREESCRIBE
    else if(apertura == "rw_overwrite" || apertura == "w+")
        file = fopen(filename, "w+");
    //ARCHIVO BINARIO PARA ACTUALIZACION
    else if(apertura == "bin_update" || apertura == "r+b" || apertura == "rb+")
        file = fopen(filename, "rb+");
    //ARCHIVO DE LECTURA BINARIO
    else if(apertura == "bin_read" || apertura == "rb")
        file = fopen(filename,"rb");
    else
    {
        printf("Tipo de apertura desconocido");
    }
    //EN EL CASO DE NO PODER ABRIR EL ARCHIVO, file RETORNA NULL
    if(file == NULL){
        fputs("Hubo un error inesperado",stderr);
        exit(1);
    }
    return file;
}

