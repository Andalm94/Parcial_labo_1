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

void InicializarClientes(eCliente* list, int tam){
	int i;

	for (i=0; i<tam; i++){
		list[i].isEmpty = EMPTY;
	}
}
int BuscarClientePorId(eCliente* list, int tam, int id){
	int index;
	int i;
	index = -1;

	for(i=0; i<tam; i++){
		if(list[i].idCliente == id){
			index = i;
			break;
		}
	}

	return index;
}
int BuscarIndexLibreParaCliente(eCliente* list, int tam){
	int espacioLibre;
	int i;

	espacioLibre = -1;

	for (i=0; i<tam; i++){
		if (list[i].isEmpty == EMPTY){
			espacioLibre = i;
			break;
		}
	}
	return espacioLibre;
}
void MostrarUnCliente(eCliente* list, int tam, int id){
	//int i;
	int index;

	index = BuscarClientePorId(list, tam, id);

	printf("ID\t||\tEMPRESA \t||\tCUIT \t||\tDIRECCION \t||\tLOCALIDAD \t\n");
	printf("%4d %20s %16d %20s %20d \n", list[index].idCliente, list[index].empresa, list[index].cuit, list[index].direccion, list[index].idLocalidad);


}
int MostrarClientes(eCliente* list, int tam){
	int i;
	int succes;
	succes = -1;

	printf("ID\t||\tEMPRESA \t||\tCUIT \t||\tDIRECCION \t||\tLOCALIDAD \t\n");
	for(i=0; i<tam; i++){
		if(list[i].isEmpty == 1){
			printf("%4d %20s %16d %20s %20d \n", list[i].idCliente, list[i].empresa, list[i].cuit, list[i].direccion, list[i].idLocalidad);
			succes = 0;
		}
	}

	return succes;
}


/*--------------ABM--------------*/

int AltaNuevoCliente(eCliente* list, int tam, int* id){
	int index;
	int succes;

	char empresa[50];
	int cuit;
	char direccion[50];
	int localidad;

	succes = -1;

	index = BuscarIndexLibreParaCliente(list, tam);

	if (index != -1){
		GetString("Por favor, ingrese el nombre de la empresa: \n", empresa, 50);
		cuit = GetInt("Por favor, ingrese el cuit de la empresa: \n", 0, 900000000, "El numero ingresado es invalido, intente nuevamente");
		GetString("Por favor, ingrese la direccion de la empresa: \n", direccion, 50);
		localidad  = GetInt("Por favor, ingrese la localidad: \n", 1, 20, "Localidad invalida.");

		list[index].idCliente = *id;
		strcpy(list[index].empresa, empresa);
		list[index].cuit = cuit;
		strcpy(list[index].direccion, direccion);
		list[index].idLocalidad = localidad;
		list[index].isEmpty = FULL;

		*id = *id+1;
		succes = 0;
	}


	return succes;

}
int ModificarCliente(eCliente* listaClientes, int tam){
	int succes;
	int idSolicitado;
	int index;

	char nuevaDireccion[100];
	int nuevaLocalidad;
	succes = -1;


	if (MostrarClientes(listaClientes, tam) == 0){
		idSolicitado = GetInt("Por favor, ingrese el ID del usuario que desea modificar.\n", 0, 999999, "ID inexistente.");
		index = BuscarClientePorId(listaClientes, tam, idSolicitado);
		if (index != -1){
			GetString("Por favor, ingrese la nueva direccion\n", nuevaDireccion, 100);
			nuevaLocalidad = GetInt("Por favor, ingrese la nueva localidad: \n", 1, 20, "Localidad invalida.");

			listaClientes[index].idLocalidad = nuevaLocalidad;
			strcpy(listaClientes[index].direccion, nuevaDireccion);

			succes = 0;
		}
	}

	return succes;
}
int BajaCliente(eCliente* listaClientes, int tam){
	int succes;
	int idSolicitado;
	int index;
	succes = -1;

	if (MostrarClientes(listaClientes, tam) == 0){
		idSolicitado = GetInt("Por favor, ingrese el ID del usuario que desea dar de baja.\n", 0, 999999, "ID inexistente.");
		index = BuscarClientePorId(listaClientes, tam, idSolicitado);
		if (index != -1){

			listaClientes[index].isEmpty = EMPTY;
			succes = 0;
		}
	}

	return succes;
}
