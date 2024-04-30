#include <stdio.h>
#include <stdlib.h>

typedef struct{
int TareaID;//Numérico autoincremental comenzando en 1000
char *Descripcion; //
int Duracion; // entre 10 – 100
} Tarea;

struct Tnodo
{
  Tarea T;
  struct Tnodo *siguiente;
};


int main(){
  printf("Hola mundo");
    return 0;
}