//FUNCIONES PARA TRATADO DE ARREGLOS
//
#include <stdlib.h>
#include <stdio.h>

//-----------PROTOTIPADO-----------//

    //PSEUDO SOBRECARGA
void swap_int(int list[], int i, int j);
void swap_double(double list[], int i, int j);
void swap_float(float list[], int i, int j);
void swap_bool(_Bool list[], int i, int j);
void swap_char(char list[], int i, int j);

void print_f();
    //FIN PSEUDO SOBRECARGA

//---------FIN PROTOTIPADO---------//



#define LinkedList(T)   \
            struct LinkedList_##T{\
                link_base;\
                T data; \
                struct LinkedList_##T *next;\
            }   
#define link_base       \
            struct{\
                size_t cap,len;\
            }



#define new_LinkedList(T, xs...)        \
                    ({              \
                        const size_t init_size = 16;\
                        const T _xs[] = {xs};\
                        struct LinkedList_##T *list = malloc(sizeof(LinkedList(T)) + sizeof(T));\
                        struct LinkedList_##T *temp;\
                        struct LinkedList_##T *aux;\
                        list->data = _xs[0];\
                        list->next = NULL;\
                        aux = list;\
                        for(int i = 1; i<LIST_ALEN(_xs);i++){\
                            temp = malloc(sizeof(LinkedList(T))+sizeof(T));\
                            temp->data = _xs[i];\
                            temp->next = NULL;\
                            aux->next = temp;\
                            aux = temp;\
                        }\
                        list;\
                    })

#define Show_LinkedList(T,pointer)\
                    ({\
                        struct LinkedList_##T *aux;\
                        aux = pointer;\
                        while(aux){\
                            printf(GET_FORMAT(aux->data),aux->data);\
                            aux = aux->next;\
                        }\
                    })


#define GET_FORMAT(x) _Generic((x), int: "%i", float: "%f", char*: "%s")
//-----------------------------------------------------ARRAYLIST-------------------------------------------------------------
#define ArrayList(T)                   \
            struct ArrayList_##T {      \
                array_base;       \
                T data[];               \
            }
#define array_base       \
            struct{ \
                size_t cap, len;\
            }


    //ALOCACION DE MEMORIA
#define new_ArrayList(T, xs...)             \
                    ({                 \
                        const size_t init_size = 16;   \
                        const T _xs[] = {xs};   \
                        struct ArrayList_##T *list = malloc(sizeof(ArrayList(T)) + sizeof(T) * LIST_ALEN(_xs));\
                        list->cap = init_size;\
                        list->len = LIST_ALEN(_xs);         \
                        for(int i =0; i< list->len;i++)\
                            list->data[i] = _xs[i];\
                        list;\
                    })
#define push_Node(list, xs...)({     \
                        const typeof(*list->data) _xs[] = {xs};\
                        if(list->len + LIST_ALEN(_xs) >= list->cap){ \
                            while(list->cap <= list->len + LIST_ALEN(_xs)){  \
                                list->cap *=2;\
                            }\
                            list = realloc(list,sizeof(array_base) + list->cap*sizeof(*list->data));\
                        }\
                        for(int i = 0; i<LIST_ALEN(_xs);i++){       \
                            list->data[list->len++] = _xs[i];\
                        }\
                        list;\
                        })

    //FUNCIONES VARIAS
#define pop_Node(list) (list->data[--list->len])
#define link_ref(list,index)(&list->data[index])
#define at_Node(list, index)(*(link_ref(list,index)))
#define free_ArrayList(list) free(list)
#define LIST_ALEN(a) (sizeof(a)/sizeof(*a))

//MACROS PARA UNIFICAR FUNCIONES
#define swap(list, i, j) _Generic((list),                        \
                                int*: swap_int,         \
                                char*: swap_char,      \
                                double*: swap_double,   \
                                float*: swap_float,     \
                                _Bool*: swap_bool,      \
                                default: NULL)((list), (i),(j))

//FORMA DE GENERICIDAD POR MEDIO DE PARAMETRIZACION
#define short_arry_len(x) (sizeof(x)/sizeof(x[0]))



//ESTRUCTURAS

struct LinkedList{
    double n;
    struct LinkedList * next;
}typedef *node;

//PARA ARBOLES BINARIOS
struct NODE { 
    _Bool is_leaf; 
    union { 
        struct
        { 
            struct NODE* left; 
            struct NODE* right; 
        } internal; 
        double data; 
    } info; 
}typedef tree; 



void print_f(){
    tree* a,*b;
    (*a).info.internal.left = NULL;
    printf("%p%c",a,'\n');
    printf("%p%c",b,'\n');
    (*a).info.internal.left = b;
    printf("%p%c",a,'\n');
    printf("%p%c",b,'\n');
    printf("Entero");
}




//COLECCION DE SWAP
void swap_int(int list[], int i, int j)//i->j; j->i
{
    int temp = list[i];
    list[i] = list[j];
    list[j] = temp;
}
void swap_double(double list[], int i, int j)//i->j; j->i
{
    double temp = list[i];
    list[i] = list[j];
    list[j] = temp;
}
void swap_float(float list[], int i, int j)//i->j; j->i
{
    float temp = list[i];
    list[i] = list[j];
    list[j] = temp;
}
void swap_bool(_Bool list[], int i, int j)//i->j; j->i
{
    _Bool temp = list[i];
    list[i] = list[j];
    list[j] = temp;
}
void swap_char(char list[], int i, int j)//i->j; j->i
{
    char temp = list[i];
    list[i] = list[j];
    list[j] = temp;
}
