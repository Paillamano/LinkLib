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
#include "func.h"
#include "sorting.h"


//ESTRUCTURAS(DEBIDO A LA CANTIDAD DE DATOS)

struct nodo{
    int n;
    char x;
}typedef nodo;

//----------PROTOTIPADO----------//
FILE*open_file(const char*filename, const char*apertura);//----------------------COMPLETO
//void get_data(FILE*file, int arry[],const char* metodo="1by1");//----------------INCOMPLETO
void append(char cadena[],char at_end);//-----------------------------------------COMPLETO
void mostrar(node h);
node Insertar(node h,double value);

//--------FIN PROTOTIPADO--------//
int main(int argc, char*argv[])
{
    nodo *a;
    ArrayList(nodo) *Datos = new_ArrayList(nodo,{ .n=7, .x='A'});//FUNCIONA
    LinkedList(int) *lista = new_LinkedList(int,1,2,3,4,5,6);
    printf("%i%c",lista->data,'\n');
    Show_LinkedList(int,lista);
    printf("%i  %c",(*Datos).data[0].n,(*Datos).data[0].x);
    //print_f(); //arboles con reduccion de memoria
    printf("Abriendo archivo\n");
    //FILE* num = open_file("numeros.txt","r");
    FILE* num = fopen("ArchivoA.tex","r");
    node h = NULL;
    rewind(num);
    double list[10];
    printf("Iniciando buffer char\n");
    char *char_buff = (char*)malloc(sizeof(char_buff));
    printf("iniciando buffer float\n");
    double buffer;
    printf("Iniciando ciclo\n");
    for(unsigned int i = 0; i<10; i++)
    {
        fscanf(num,"%le",&buffer);
        list[i] = buffer;
        //h = Insertar(h,*buffer);
        printf("%i ) %.7e \n",i,list[i]);
    }
    int aux = short_arry_len(list);
    quicksort_double(list,0,aux-1);
    printf("%.7e%c",list[0],'\n');
    for(unsigned int e = 0; e<10; e++)
    {
        printf("%.7e%c",list[e],'\n');
    }
    fclose(num);
}




void mostrar(node h)
{
    node aux;
    aux = h;
    while(aux != NULL){
        printf("%.7e%c",(*aux).n,'\n');
        aux = (*aux).next;
    }
}

node init_node()
{
    node temp;
    temp = (node)malloc(sizeof(struct LinkedList));
    (*temp).next = NULL;
    return temp;
}

node Insertar(node h,double value)
{
    node temp,p;
    temp = init_node();
    (*temp).n = value;
    if(h==NULL)
    {
        h = temp;
    }
    else
    {
        p = h;
        while((*p).next !=NULL)
        {
            p = (*p).next;
        }
        (*p).next = temp;
    }
    return h;
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

