#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "eCliente.h"
#include "Inputs.h"
#include "eLocalidad.h"
#include "ePedido.h"

#define EMPTY 0
#define FULL 1

/*---INICIALIZACION Y BUSQUEDA----*/

void InicializarPedidos(ePedido* list, int tam){
	int i;

	for (i=0; i<tam; i++){
		list[i].isEmpty = EMPTY;
		list[i].cantidadKilosTotales = 0;
		list[i].HPPE = 0;
		list[i].LDPE = 0;
		list[i].PP = 0;
	}
}
int BuscarPedidoPorId(ePedido* list, int tam, int id){
	int index;
	int i;
	index = -1;

	for(i=0; i<tam; i++){
		if(list[i].idPedido == id){
			index = i;
			break;
		}
	}

	return index;
}
int BuscarIndexLibreParaPedido(ePedido* list, int tam){
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
void MostrarUnPedido(ePedido* list, int tam, int id){
	int index;

	index = BuscarPedidoPorId(list, tam, id);

	printf("ID-Pedido\tEmpresa\tKilos\n");
	printf("%4d %4d %4f\n", list[index].idPedido, list[index].idClientes, list[index].cantidadKilosTotales);


}
int MostrarPedidos(ePedido* list, int tam){
	int i;
	int succes;
	succes = -1;

	printf("ID-Pedido\tEmpresa\tKilos\n");
	for(i=0; i<tam; i++){
		if(list[i].isEmpty == 1){
			printf("%4d %4d %4f\n", list[i].idPedido, list[i].idClientes, list[i].cantidadKilosTotales);
			printf("\n");

			succes = 0;
		}
	}

	return succes;
}
int MostrarPedidosPendientes(ePedido* list, int tam){
	int i;
	int succes;
	succes = -1;

	printf("ID-Pedido\tEmpresa\tKilos\n");
	for(i=0; i<tam; i++){
		if(list[i].isEmpty == 1 && strcmp(list[i].estado,"PENDIENTE") == 0){
			printf("%4d %4d %4f\n", list[i].idPedido, list[i].idClientes, list[i].cantidadKilosTotales);
			printf("\n");

			succes = 0;
		}
	}

	return succes;
}


/*--------------ABM--------------*/

int AltaNuevoPedido(ePedido* listaPedidos, int tamPedidos, int* id, eCliente* listaClientes, int tamClientes){
	int indexPedido;
	int idClienteSolicitado;
	float kilosSolicitados;
	int succes;

	succes = -1;

	indexPedido = BuscarIndexLibreParaPedido(listaPedidos, tamPedidos);

	if (indexPedido != -1){
		if(MostrarClientes(listaClientes, tamClientes) != 1){

			idClienteSolicitado = GetInt("Por favor, ingrese el ID del cliente.\n", 1000, 999999, "El ID ingresado no existe\n");
			kilosSolicitados = GetFloat("Por favor, ingrese la cantidad de kilos totales.\n", 1, 999999, "Numero invalido, intente nuevamente \n");

			listaPedidos[indexPedido].cantidadKilosTotales = kilosSolicitados;
			listaPedidos[indexPedido].idClientes = idClienteSolicitado;
			strcpy(listaPedidos[indexPedido].estado, "PENDIENTE");
			listaPedidos[indexPedido].idPedido = *id;
			listaPedidos[indexPedido].isEmpty = FULL;

			*id = *id+1;
			succes = 0;
		}

	}


	return succes;

}
int ProcesarResiduos(ePedido* listaPedidos, int tamPedidos){
	int succes;
	int idPedidoSeleccionado;
	int indexPedido;

	succes = -1;

	if(MostrarPedidosPendientes(listaPedidos, tamPedidos) == 0){
		idPedidoSeleccionado = GetInt("Por favor, seleccione el ID de un pedido:\n", 100, 999999, "El ID ingresado no existe.\n");
		indexPedido = BuscarPedidoPorId(listaPedidos, tamPedidos, idPedidoSeleccionado);
		if(indexPedido != -1){

			printf("El pedido seleccionado es de %.2f kilos totales\n", listaPedidos[indexPedido].cantidadKilosTotales);
			listaPedidos[indexPedido].HPPE = GetFloat("Por favor, indique cuantos kilos de HPPE se recolectaron.\n", 0 , listaPedidos[indexPedido].cantidadKilosTotales, "La cantidad de kilos ingresados supera el total. Ingrese la cantidad nuevamente\n");
			listaPedidos[indexPedido].LDPE = GetFloat("Por favor, indique cuantos kilos de LDPE se recolectaron.\n", 0 , listaPedidos[indexPedido].cantidadKilosTotales, "La cantidad de kilos ingresados supera el total. Ingrese la cantidad nuevamente\n");
			listaPedidos[indexPedido].PP = GetFloat("Por favor, indique cuantos kilos de PP se recolectaron.\n", 0 , listaPedidos[indexPedido].cantidadKilosTotales, "La cantidad de kilos ingresados supera el total. Ingrese la cantidad nuevamente\n");

			if (listaPedidos[indexPedido].HPPE + listaPedidos[indexPedido].LDPE + listaPedidos[indexPedido].PP <= listaPedidos[indexPedido].cantidadKilosTotales){
				strcpy(listaPedidos[indexPedido].estado, "COMPLETADO");
				succes = 0;
			}
		}
	}


	return succes;
}
