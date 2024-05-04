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

int generadorNumRandom(int min, int max);
void mostrarTareas(Nodo **start);
Tarea crearTarea(int id);
Nodo *crearNodo(int id);
void insertarNodoAlFinal(Nodo **start, Nodo *nuevo);
void insertarNodoAlComienzo(Nodo **start, Nodo *nuevo);
void buscarPorId(Nodo **startPendiente,Nodo **startRealizada, int id);
void buscarPorPalabra(Nodo **startPendiente, Nodo **startRealizada, char *palabra);
void mover_pendiente_a_realizada(Nodo **startPendiente, Nodo **startRealizada, int id);

int main()
{
  int opcion, id;
  char palabra[100];
  Nodo **listaTareasPendientes=crearListaVacia();
  Nodo **listaTareasRealizadas=crearListaVacia();
  do
  {
        printf("\n\nIngrese la operacion a trabajar, presone 0 para salir\n");
        printf("1. Agregar tarea a pendientes\n");              //
        printf("2. Cambiar tarea de pendiente a realizada\n");  //
        printf("3. Mostrar tareas pendientes\n");               //
        printf("4. Mostrar tareas realizadas\n");               //
        printf("5. Buscar tarea por ID\n");                     //
        printf("6. Buscar tarea por palabra\n");
        printf("0. Para salir\n");
        printf("Operacion elegida: ");
        scanf("%d", &opcion);
        fflush(stdin);
        switch (opcion)
        {
        case 0: //Salir
          break;
        case 1: 
          printf("\nIngrese ID de la tarea pendiente: ");
          scanf("%d", &id);
          fflush(stdin);
          insertarNodoAlFinal(listaTareasPendientes, crearNodo(id));
          break;
        case 2: 
          printf("\nIngrese ID de la tarea que realizo: ");
          scanf("%d", &id);
          fflush(stdin);
          mover_pendiente_a_realizada(listaTareasPendientes, listaTareasRealizadas, id);
          break;
        case 3: 
          mostrarTareas(listaTareasPendientes);
          break;
        case 4: 
          mostrarTareas(listaTareasRealizadas);
          break;
        case 5: 
          printf("\nIngrese el ID de la tarea a buscar: ");
          scanf("%d", &id);
          fflush(stdin);
          buscarPorId(listaTareasPendientes, listaTareasRealizadas, id);
          break;
        case 6: 
          printf("\nPalabra clave para buscar tarea: ");
          gets(palabra);
          buscarPorPalabra(listaTareasPendientes, listaTareasRealizadas, palabra);
          break;
        default:
          printf("\nIngrese una opcion valida");
          break;
        }
  } while (opcion!=0);
  return 0;
}


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

void insertarNodoAlFinal(Nodo **start, Nodo *nuevo){
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

void insertarNodoAlComienzo(Nodo **start, Nodo *nuevo){
  nuevo->siguiente=*start;
  *start=nuevo;
}

void buscarPorId(Nodo **startPendiente,Nodo **startRealizada, int id){
  Nodo *aux=*startPendiente;
  Nodo *aux2=*startRealizada;
  if(aux){
    while (aux && aux->T.TareaID!=id){
      aux=aux->siguiente;
    }
    if(aux==NULL){
      //printf("\nTarea de id: %d - NO encontrada", id);
    } else{
      printf("\n[Tarea Pendiente]");
      printf("\nID de la tarea: %d",aux->T.TareaID);
      printf("\nDescripcion:%s",aux->T.Descripcion);
      printf("\nDuracion: %d",aux->T.Duracion);
    }
  } else{
    //printf("\nLista pendiente vacia");
  }
  if(aux2){
    while (aux2 && aux2->T.TareaID!=id){
      aux2=aux2->siguiente;
    }
    if(aux2==NULL){
      //printf("\nTarea de id: %d - NO encontrada", id);
    } else{
      printf("\n[Tarea Realizada]");
      printf("\nID de la tarea: %d",aux2->T.TareaID);
      printf("\nDescripcion:%s",aux2->T.Descripcion);
      printf("\nDuracion: %d",aux2->T.Duracion);
    }
  } else{
    //printf("\nLista Realizada vacia");
  }
}

void mover_pendiente_a_realizada(Nodo **startPendiente, Nodo **startRealizada, int id){
  Nodo *aux=*startPendiente;
  Nodo *anterior=*startPendiente;

  if(aux){
    while (aux && aux->T.TareaID!=id){
      anterior=aux;
      aux=aux->siguiente;
    }
    if(aux==NULL){
      printf("\nTarea de id: %d - NO encontrado", id);
    } else{
      printf("\n[Tarea Encontrada]");
      if(aux==anterior){//primero de la lista
        printf("\n[1ra posicion]");
        *startPendiente=aux->siguiente;
      } else{
        if(aux->siguiente==NULL){
          printf("\n[Ultima posicion]");
          anterior->siguiente=NULL;
        } else{
          anterior->siguiente=aux->siguiente;
        }
      }
      aux->siguiente=NULL;
      aux->siguiente=*startRealizada;
      *startRealizada=aux;
    }
  } else{
    printf("\nLista vacia");
  }
}



void buscarPorPalabra(Nodo **startPendiente, Nodo **startRealizada, char *palabra)
{
  Nodo *aux=*startPendiente;
  Nodo *aux2=*startRealizada;
  if(aux){
    while (aux){
      if(strstr(aux->T.Descripcion, palabra)){
        printf("\n[Tarea Pendiente]");
        printf("\nID de la tarea: %d",aux->T.TareaID);
        printf("\nDescripcion:%s",aux->T.Descripcion);
        printf("\nDuracion: %d",aux->T.Duracion);
      }
      aux=aux->siguiente;
    }
  if(aux2){
    while (aux2){
      if(strstr(aux2->T.Descripcion, palabra)){
        printf("\n[Tarea Realizada]");
        printf("\nID de la tarea: %d",aux2->T.TareaID);
        printf("\nDescripcion:%s",aux2->T.Descripcion);
        printf("\nDuracion: %d",aux2->T.Duracion);
      }
      aux2=aux2->siguiente;
      }
    }
  }
}
