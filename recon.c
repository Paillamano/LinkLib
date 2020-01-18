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

/*
struct arbol{
    double data;
    arbol *padre;
    arbol * rd;
    arbol * ri;
}typedef arbol;
*/

struct lista_simple{
    double numero;
    struct lista_simple * next;
}typedef lista_simple;


struct lista_lista{
    lista_simple *raiz;
    lista_simple *fondo;
    struct lista_lista *next;
}typedef lista_lista;

//----------PROTOTIPADO----------//
FILE*open_file(const char*filename, const char*apertura);//----------------------COMPLETO
//void get_data(FILE*file, int arry[],const char* metodo="1by1");//----------------INCOMPLETO
void append(char cadena[],char at_end);//-----------------------------------------COMPLETO

void Insert_data(lista_l*head, FILE* file, int *counter_node, int*counter_data);
int data_counter(FILE* file);
lista_l* init_list( FILE* file, int *counter_data);
lista_l* clean_list(lista_l *head, int i);
void recorrer(lista_l *head);

int non_cero(double list[]);
void MERGE_LISTS (double list_1[], double list_2[], int len1, int len2, lista_simple ** raiz, lista_simple ** fondo);
void mostrar_sl(lista_simple *h);
lista_simple * init_sl(double dato);
void insertar_sl(double dato, lista_simple* raiz, lista_simple* fondo);
void MERGE_STRUCTURES(lista_simple *p, lista_simple *q, lista_simple **raiz_nueva, lista_simple ** fondo_nueva);

lista_lista * init_ll(lista_simple * raiz, lista_simple * fondo);
void insert_ll(lista_lista * head,lista_simple * raiz, lista_simple * fondo);

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
    int peso = 1;
    int data = 0;
    //char *char_buff = (char*)malloc(sizeof(char_buff));
    double buffer;
    //fflush(stdout);
    printf("Merge\n");
    printf("Contando elementos...\n");
    clock_t _count = clock();
    //long int file_numbers = data_counter(num);
    double _time_count = ((double)clock()-_count)/CLOCKS_PER_SEC;
    printf("...OK. \n %li datos contados en el archivo (%f sec)", 1, _time_count);
    rewind(num);
    lista_l * pointer;
    clock_t start = clock();
    pointer = init_list(num,&data);

    printf("Insertando\n"); 
    Insert_data(pointer, num,&peso,&data);
    lista_l *aux = pointer;
    lista_lista * head;
    lista_simple * raiz;
    lista_simple * fondo;
    raiz = NULL;
    fondo = NULL;
    while(aux){
        printf("%p\n", raiz);
        MERGE_LISTS(aux->arrayA,aux->arrayB,ARRAY_LEN,ARRAY_LEN,&raiz,&fondo);
        insert_ll(head,raiz,fondo);
        raiz = NULL;
        fondo = NULL;
        aux = aux->next;
    }
    lista_lista * aux_orden, *temp1,*temp2;
    lista_simple * raiz_o, *fondo_o;
    while(aux_orden){
        if(aux_orden->next != NULL){
            MERGE_STRUCTURES(aux_orden->raiz,aux_orden->next->raiz,&raiz_o,&fondo_o);
            temp1 = aux_orden;
            temp2 = temp1->next;
            aux_orden = (aux_orden->next)->next;
            free(temp1);
            free(temp2);
        }
        else{
            lista_simple *raiz_temp, *fondo_temp;
            raiz_temp = raiz;
            fondo_temp = fondo;
            MERGE_STRUCTURES(raiz_temp, aux_orden->raiz, &raiz_temp,&fondo_temp);
        }
    }

    printf("Mezclando listas\n");
    





    double _time_in = ((double)clock() - start)/CLOCKS_PER_SEC;
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



/*

arbol * init_tree(double dato, arbol* padre){
    arbol* nodo;
    nodo = (arbol*)malloc(sizeof(arbol));
    (*nodo).data = dato;
    (*nodo).rd = NULL;
    (*nodo).ri = NULL;
    (*nodo).padre = padre;
    return nodo;
}


void fix_nodes(arbol *root){
    fix_nodes(root->ri);
    if(root == NULL){

    }
    fix_nodes(root->rd);

    

}
*/

/*
void heap(double data, arbol *padre, int *c){
    if(padre == NULL){
        arbol * temp = init_tree(data,padre);
        padre = temp;
        *c = *c=1? 0: 1; 
    }else if(*c == 0){
        heap(data,padre->ri,&c);
    }else{
        heap(data,padre->rd,&c);
    }
}
*/







lista_lista * init_ll(lista_simple * raiz, lista_simple * fondo){
    lista_lista * temp = (lista_lista*)malloc(sizeof(lista_lista));
    temp->raiz = raiz;
    temp->fondo = fondo;
    temp->next = NULL;
    return temp;
}

void insert_ll(lista_lista * head,lista_simple * raiz, lista_simple * fondo){
    lista_lista *aux = init_ll(raiz,fondo);
    aux->next = head;
    head = aux;
}







int non_cero(double list[]){
    long int i = 0;
    while(i< short_arry_len(list)){
        if(list[i]!= 0){
            i++;
        }else{
            return i;
        }
    }
}



















void MERGE_STRUCTURES(lista_simple *p, lista_simple *q, lista_simple **raiz_nueva, lista_simple ** fondo_nueva){
    lista_simple *auxP, *auxQ, *intercambio;
    auxP = p;
    auxQ = q;
    while(auxP || auxQ){
        if(auxQ && auxP){
            if((*auxP).numero >= (*auxQ).numero){
                insertar_sl(auxQ->numero,*raiz_nueva,*fondo_nueva);
                auxQ = (*auxQ).next;
            }else{
                insertar_sl(auxP->numero,*raiz_nueva,*fondo_nueva);
                auxP = (*auxP).next;
            }
        }else if(!auxP){
            insertar_sl((*auxQ).numero,*raiz_nueva,*fondo_nueva);
            auxQ = (*auxQ).next;
        }else{
            insertar_sl((*auxP).numero,*raiz_nueva,*fondo_nueva);
            auxP = (*auxP).next;
        }
    }
}



void MERGE_LISTS (double list_1[], double list_2[], int len1, int len2, lista_simple ** raiz, lista_simple ** fondo){
    int largo_L1 = len1;
    int largo_L2 = len2;
    int _MIN = largo_L1 <= largo_L2? largo_L1 : largo_L2;
    int _MAX = largo_L1 > largo_L2? largo_L1 : largo_L2;
    int i_1 = 0;
    int j_2 = 0;
    printf("Largo lista 1: %i; Largo lista 2: %i\n", largo_L1, largo_L2);
    printf("Largo maximo: %i; Largo minimo: %i\n",_MAX,_MIN);
    printf("While i < min or j < min\n");
    while(i_1 < _MIN || j_2 < _MIN){
        if(list_1[i_1] < list_2[j_2]){
            insertar_sl(list_1[i_1],*raiz,*fondo);
            //printf("i: %i => %.7e   |   j: %i => %.7e\n", i_1,list_1[i_1] ,j_2, list_2[j_2]);
            i_1++;
        }else{
            insertar_sl(list_2[j_2],*raiz,*fondo);
            //printf("i: %i => %.7e   |   j: %i => %.7e\n", i_1,list_1[i_1] ,j_2, list_2[j_2]);
            j_2++;
        }
    }
    printf("for\n");
    for(int R = i_1>j_2? j_2:i_1; R<_MAX; R++){
        if(largo_L1 >  largo_L2){
            insertar_sl(list_1[R],*raiz,*fondo);
        }else{
            insertar_sl(list_2[R],*raiz,*fondo);
        }
    }
}


lista_simple * init_sl(double dato){
    lista_simple * head = (lista_simple*)malloc(sizeof(lista_simple));
    (*head).next = NULL;
    (*head).numero = dato;
    return head;
}

void insertar_sl(double dato, lista_simple * raiz, lista_simple * fondo){
    lista_simple* nuevo = malloc(sizeof(lista_simple));
    nuevo->numero = dato;
    nuevo->next = NULL;
    if(raiz == NULL){
        raiz = nuevo;
        fondo = nuevo;
    }else{
        fondo->next = nuevo;
        fondo = nuevo;
    }
}

void mostrar_sl(lista_simple *h){
    lista_simple *aux;
    aux = h;
    while(aux){
        printf("%f\n",(*aux).numero);
        aux=(*aux).next;
    }
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
    quicksort_double((*head).arrayA,0,ARRAY_LEN);
    quicksort_double((*head).arrayB,0,ARRAY_LEN);
    return head;
}

void recorrer(lista_l *head){
    printf("if head != null\n");
    if(head!=NULL){
        lista_l *aux;
        aux = head;
        int i = 1;
        while(aux){
            printf("NODO (%li)\n size next %zu; A_size: %i;  B_size: %li", i,sizeof((*(*aux).next)),non_cero((*aux).arrayA),non_cero((*aux).arrayB));
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
            head = (*head).next;
            free(aux);
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

