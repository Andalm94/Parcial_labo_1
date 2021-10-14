#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Inputs.h"
#include "ManejoStructs.h"
#include "Menus.h"

#define EMPTY 0
#define FULL 1

#define COMPLETADO 0
#define PENDIENTE 1




void InicializarClientes(eCliente* list, int tam){
	int i;

	for (i=0; i<tam; i++){
		list[i].isEmpty = EMPTY;
	}
}
void MostrarUnCliente(eCliente* list, int tam, int id){
	int i;

	for (i=0; i<tam; i++){
		if(list[i].idCliente == id && list[i].isEmpty == FULL){
			printf("ID\t||\tEMPRESA \t||\tCUIT \t||\tDIRECCION \t||\tLOCALIDAD \t\n");
			printf("%4d %20s %16d %20s %20s \n", list[i].idCliente, list[i].empresa, list[i].cuit, list[i].direccion, list[i].localidad);
		}

	}


}

void InicializarPedidos(ePedido* list, int tam){
	int i;

	for (i=0; i<tam; i++){
		list[i].isEmpty = EMPTY;
	}
}

int MostrarClientes(eCliente* list, int tam){
	int i;
	int succes;
	succes = 0;

	printf("ID\t||\tEMPRESA \t||\tCUIT \t||\tDIRECCION \t||\tLOCALIDAD \t\n");
	for(i=0; i<tam; i++){
		if(list[i].isEmpty == 1){
			printf("%4d %20s %16d %20s %20s \n", list[i].idCliente, list[i].empresa, list[i].cuit, list[i].direccion, list[i].localidad);
			printf("\n");

			succes = 1;
		}
	}

	return succes;
}

int BuscarEspacioLibre(eCliente* list, int tam){
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
void IngresarDatos(char empresa[], int* cuit, char direccion[], char localidad[]){
	GetString("Por favor, ingrese el nombre de la empresa: \n", empresa, 50);
	*cuit = GetInt("Por favor, ingrese el cuit de la empresa: \n", 0, 900000000, "El numero ingresado es invalido, intente nuevamente");
	GetString("Por favor, ingrese la direccion de la empresa: \n", direccion, 50);
	GetString("Por favor, ingrese la localidad: \n", localidad, 20);
}
int CargarNuevoCliente(eCliente* list, int tam, int* id){
	int index;
	int succes;

	char empresa[50];
	int cuit;
	char direccion[50];
	char localidad[20];

	succes = -1;

	index = BuscarEspacioLibre(list, tam);

	if (index != -1){
		IngresarDatos(empresa, &cuit, direccion, localidad);

		list[index].idCliente = AsignarIdCliente(id);
		strcpy(list[index].empresa, empresa);
		list[index].cuit = cuit;
		strcpy(list[index].direccion, direccion);
		strcpy(list[index].localidad, localidad);
		list[index].pedidosPendientes = 0;
		list[index].isEmpty = FULL;
		succes = 0;
	}


	return succes;

}
int AsignarIdCliente(int* id){
	int idAsignado;

	idAsignado = *id;
	*id = idAsignado + 1;

	return idAsignado;
}


int BuscarClientePorId(eCliente* list, int tam, int id){
	int index;
	int i;
	index = -1;


	for(i=0; i<tam; i++){
		if(list[i].idCliente == id){
			index = i;
		}
	}


	return index;
}
int ModificarDireccion(eCliente* list, int tam, int id, char mensaje[]){
	int i;
	int succes;
	char nuevaDireccion[50];
	succes = -1;

	for (i=0; i<tam; i++){
		if(list[i].idCliente == id && list[i].isEmpty == FULL){
			GetString(mensaje, nuevaDireccion, 50);
			strcpy(list[i].direccion, nuevaDireccion);
			succes = 0;
		}

	}

	return succes;
}
int ModificarLocalidad(eCliente* list, int tam, int id, char mensaje[]){
	int i;
	int succes;
	char nuevaLocalidad[50];
	succes = -1;

	for (i=0; i<tam; i++){
		if(list[i].idCliente == id && list[i].isEmpty == FULL){
			GetString(mensaje, nuevaLocalidad, 50);
			strcpy(list[i].localidad, nuevaLocalidad);
			succes = 0;
		}

	}

	return succes;
}

int EliminarCliente(eCliente* list, int tam, int id){
	int i;
	int succes;
	succes = -1;

	for (i=0; i<tam; i++){
		if(list[i].idCliente == id && list[i].isEmpty == FULL){
			list[i].isEmpty = EMPTY;
			succes = 0;
		}

	}

	return succes;
}

//4
int CrearPedidoDeRecoleccion(eCliente* listaClientes, int tamClientes, ePedido* listaPedidos, int tamPedidos, int*idPedido){
	int succes;
	int idIngresado;
	int index;
	int i;

	float kilosTotales;

	succes = -1;


	if(MostrarClientes(listaClientes, tamClientes) != -1){
		idIngresado = GetInt("Por favor, ingrese el ID del cliente: \n", 0, 1000000, "El ID no existe. Intente nuevamente. \n");
		if(BuscarClientePorId(listaClientes, tamClientes, idIngresado) != -1){
			index = BuscarEspacioLibreParaPedido(listaPedidos, tamPedidos);
			if (index != -1){
				kilosTotales = GetFloat("Por favor, ingrese la cantidad de kilogramos que desea recolectar.\n", 0, 1000000, "La cantidad ingresada es invalida");
				listaPedidos[index].kilosTotales = kilosTotales;
				listaPedidos[index].idCliente = idIngresado;
				listaPedidos[index].idPedido = AsignarIdPedido(&idPedido);
				listaPedidos[index].isEmpty = FULL;
				succes = 0;
				for(i=0; i<tamClientes; i++){
					if (listaClientes[i].idCliente == idIngresado){
						listaClientes[i].pedidosPendientes++;
						break;
					}
				}
			}
		}
	}

	return succes;
}
int BuscarEspacioLibreParaPedido(ePedido* list, int tam){
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
int AsignarIdPedido(int* idPedido){
	int idAsignado;

	idAsignado = *idPedido;
	*idPedido = idAsignado + 1;

	return idAsignado;
}


int ProcesarResiduos(ePedido* list, int tamPedidos, int id, eCliente* listaClientes, int tamClientes){ //ROMPE
	int succes;
	int i;
	//int j;
	int index;

	succes = 0;

	for(i=0; i<tamPedidos; i++){
		if(list[i].idPedido == id){
			index = i;
			break;
		}
	}

	printf("El pedido seleccionado es de %.2f kilos totales.\n", list[index].kilosTotales);


	list[index].kilosHDPE = GetFloat("Ingrese cuantos kilogramos de HDPE se recolectaron:\n", 0, list[index].kilosTotales, "La cantidad esta fuera de los parametros. Intente nuevamente.\n");
	list[index].kilosLDPE = GetFloat("Ingrese cuantos kilogramos de LDPE se recolectaron:\n", 0, list[index].kilosTotales, "La cantidad esta fuera de los parametros. Intente nuevamente.\n");
	list[index].kilosPP = GetFloat("Ingrese cuantos kilogramos de PP se recolectaron:\n", 0, list[index].kilosTotales, "La cantidad esta fuera de los parametros. Intente nuevamente.\n");

	if((list[index].kilosHDPE + list[index].kilosLDPE + list[index].kilosPP) > list[index].kilosTotales){
		//Si entra en este if, es debido a que excedio el limite de kilogramos totales.
		list[index].kilosHDPE = 0;
		list[index].kilosLDPE = 0;
		list[index].kilosPP = 	0;
		succes = -1;
	}
	else{
		//Si entra en este else, ha ingresado las cantidades correctamente.
		//El pedido se marca como completado y se resta un pedido pendiente al cliente.
		list[index].estado = COMPLETADO;
		/*for(i=0; i<tamClientes; i++){
			for(j=0; j < tamPedidos; i++){
				if(listaClientes[i].idCliente == list[j].idCliente){
					printf("4\n");
					listaClientes[i].pedidosPendientes--;
					printf("La cantidad de pedidos pendientes es %d", listaClientes[i].pedidosPendientes); //prueba
					break;
				}

			}
		}*/
	}



	return succes;
}

void RestarPedidoPendienteACliente(eCliente* listaCliente, int tamClientes, int id){
	int i;

	for(i=0; i<tamClientes; i++){
		if(listaCliente[i].idCliente == id){
			listaCliente[i].pedidosPendientes--;
			break;
		}
	}
}


void MostrarPedidos(ePedido* listaPedidos, int tamPedidos, eCliente* listaClientes, int tamClientes){
	int i;
	int j;

	printf("ID-Pedido\tEmpresa\tKilos\n");
	for (i=0; i<tamPedidos; i++){
		if(listaPedidos[i].isEmpty == FULL){
			for(j=0; j<tamClientes; j++){
				if(listaPedidos[j].idCliente == listaClientes[i].idCliente){
					printf("%d\t%s\t%f\n", listaPedidos[i].idPedido, listaClientes[j].empresa, listaPedidos[i].kilosTotales);
				}
			}

		}
	}
}

void MostrarClientesConPedidosPendientes (eCliente* listaClientes, int tamClientes){
	int i;

	printf("ID\t||EMPRESA\t||CUIT\t||DIRECCION\t||LOCALIDAD\t||PEDIDOS PENDIENTES\t\n");
	for(i=0; i<tamClientes; i++){
		if(listaClientes[i].isEmpty == FULL && listaClientes[i].pedidosPendientes > 0){
			printf("%4d %20s %8d %20s %20s %4d \n", listaClientes[i].idCliente, listaClientes[i].empresa, listaClientes[i].cuit, listaClientes[i].direccion, listaClientes[i].localidad, listaClientes[i].pedidosPendientes);
		}
	}
}


void MostrarPedidosPendientes(ePedido* listaPedidos, int tamPedidos, eCliente* listaClientes, int tamClientes){
	int i;
	int j;

	printf("CUIT\t||DIRECCION\t||KILOGRAMOS\t\n");
	for (i=0; i<tamPedidos; i++){
		if(listaPedidos[i].isEmpty == FULL && listaPedidos[i].estado == PENDIENTE){
			for(j=0 ; j < tamClientes; j++){
				if (listaPedidos[i].idCliente == listaClientes[j].idCliente){
					printf("%d\t %s\t %.2f\n", listaClientes[j].cuit, listaClientes[j].direccion, listaPedidos[i].kilosTotales);
				}
			}
		}
	}

}

void MostrarPedidosProcesados(ePedido* listaPedidos, int tamPedidos, eCliente* listaClientes, int tamClientes){
	int i;
	int j;

	printf("CUIT\t||DIRECCION\t||KG: HDPE\t||KG: LDPE\t||KG: PP\t||\n");
	for (i=0; i<tamPedidos; i++){
		if(listaPedidos[i].isEmpty == FULL && listaPedidos[i].estado == COMPLETADO){
			for(j=0 ; j < tamClientes; j++){
				if (listaPedidos[i].idCliente == listaClientes[j].idCliente){
					printf("%d\t %s\t %.2f\t %.2f\t %.2f\n", listaClientes[j].cuit, listaClientes[j].direccion, listaPedidos[i].kilosHDPE, listaPedidos[i].kilosLDPE, listaPedidos[i].kilosPP);
				}
			}
		}
	}

}


int BuscarPedidosPorLocalidad(char mensaje[], eCliente* listaClientes, int tamClientes){
	int i;
	int pedidosPendientesEnLaLocalidad;

	pedidosPendientesEnLaLocalidad = 0;

	char localidadIngresada[20];

	GetString(mensaje, localidadIngresada, 20);

	for(i=0; i<tamClientes; i++){
		if(listaClientes[i].localidad == localidadIngresada && listaClientes[i].pedidosPendientes > 0){
			pedidosPendientesEnLaLocalidad += listaClientes[i].pedidosPendientes;
		}
	}


	return pedidosPendientesEnLaLocalidad;
}

float CalcularKilosPPPorCliente(eCliente* listaClientes, int tamClientes, ePedido* listaPedidos, int tamPedidos){ //revisar
	int i;
	int j;

	float acumuladorKilosPP;
	int clientesTotales;
	float promedio;

	printf("Entre en la funcion");

	for (i=0; i<tamClientes; i++){
		if (listaClientes[i].isEmpty == FULL){
			clientesTotales++;
			for (j=0; i<tamPedidos; j++){
				if(listaPedidos[j].idCliente == listaClientes[i].idCliente){
					acumuladorKilosPP += listaPedidos[j].kilosPP;
				}
			}
		}
	}

	printf("Sali del for y calculare el promedio");
	promedio = acumuladorKilosPP/clientesTotales;
	printf("Calcule el promedio");

	return promedio;
}