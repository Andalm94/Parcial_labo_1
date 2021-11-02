#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "eCliente.h"
#include "Inputs.h"
#include "eLocalidad.h"

#define EMPTY 0
#define FULL 1


/*---INICIALIZACION Y BUSQUEDA----*/

void InicializarLocalidades(eLocalidad* list, int tam){
	int i;

	for (i=0; i<tam; i++){
		list[i].isEmpty = EMPTY;
	}
}
int BuscarLocalidadPorId(eLocalidad* list, int tam, int id){
	int index;
	int i;
	index = -1;

	for(i=0; i<tam; i++){
		if(list[i].idLocalidad == id){
			index = i;
			break;
		}
	}

	return index;
}
