#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tarea Tarea;
typedef struct Nodo Nodo;

struct Tarea{
int TareaID;//Numérico autoincremental comenzando en 1000
char *Descripcion; //Debo reservar memoria dinamica para poder almacenar una descripcion
int Duracion; // entre 10 – 100
};

struct Nodo
{
  Tarea T;
  struct Nodo *siguiente;
};

Nodo **crearListaVacia()
{
    Nodo **lista = (Nodo **)malloc(sizeof(Nodo *));
    *lista = NULL;
    return lista;
}


//Si tarea fuese un puntero tarea deberia reservar memoria para el
//En este caso solo reservamos memoria para nodo, ya que noto tiene un tarea dentro


//tendre una listaTareasPendientes y listaTareasRealizadas;
//hora 1.02
//hora 1.18 expliocacion insertar nodo **
//hora 1.29
//hora 2.08 Explicacion de listas
//hora 2.37 punto 2 avanzado

int generadorNumRandom(int min, int max){
    return (min+rand()%(max-min+1));
}

void mostrarTareas(Nodo **start){
  Nodo *aux=*start;
  if(aux){
    while (aux){
      printf("\n\n[Tarea]");
      printf("\nID de la tarea: %d",aux->T.TareaID);
      printf("\nDescripcion:%s",aux->T.Descripcion);
      printf("\nDuracion: %d",aux->T.Duracion);
      aux=aux->siguiente;
    }
  } else{
    printf("\nNo hay tareas");
  }
}

Tarea crearTarea(int id){
  Tarea tarea;
  char buffer[100];
  printf("\nDescripcion de tarea: ");
  gets(buffer);
  fflush(stdin);
  tarea.Descripcion=(char*)malloc(strlen(buffer)+1);
  strcpy(tarea.Descripcion, buffer);
  tarea.Duracion=generadorNumRandom(10,100);
  tarea.TareaID=id;
  return tarea;
}

Nodo *crearNodo(int id){
  Nodo *nuevo=(Nodo*)malloc(sizeof(Nodo));
  nuevo->siguiente=NULL;
  nuevo->T=crearTarea(id);
  return nuevo;
}

Nodo insertarNodoAlFinal(Nodo **start, Nodo *nuevo){
  Nodo *aux=*start;
  if(aux){
      while (aux->siguiente){
      aux=aux->siguiente;
    }
    aux->siguiente=nuevo;
  } else{
    *start=nuevo;
  }
}

Nodo insertarNodoAlComienzo(Nodo **start, Nodo *nuevo){
  nuevo->siguiente=*start;
  *start=nuevo;
}

int main(){
  int opcion;
  Nodo **listaTareasPendientes=crearListaVacia();
  Nodo **listaTareasRealizadas=crearListaVacia();
  mostrarTareas(listaTareasPendientes);
  insertarNodoAlFinal(listaTareasPendientes, crearNodo(3));
  insertarNodoAlComienzo(listaTareasPendientes, crearNodo(4));
  mostrarTareas(listaTareasPendientes);

  do
  {
        printf("\n\nIngrese la operacion a trabajar, presone 0 para salir\n");
        printf("1. Agregar tarea a pendientes\n");              //
        printf("2. Cambiar tarea de pendiente a realizada\n");
        printf("3. Mostrar tareas pendientes\n");               //
        printf("4. Mostrar tareas realizadas\n");               //
        printf("5. Buscar tarea por ID\n");
        printf("6. Buscar tarea por palabra\n");
        printf("Presone 0 para salir\n");
        scanf("%d", &opcion);
        fflush(stdin);
        switch (opcion)
        {
        case 0: //Salir
          break;
        case 1: 
          insertarNodoAlComienzo(listaTareasPendientes, crearNodo(4));
          break;
        case 3: 
          mostrarTareas(listaTareasPendientes);
          break;
        case 4: 
          mostrarTareas(listaTareasRealizadas);
          break;
        
        default:
          printf("\nIngrese una opcion valida");
          break;
        }
  } while (opcion!=0);
  

  return 0;
}