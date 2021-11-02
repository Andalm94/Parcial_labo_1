#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "eCliente.h"
#include "Inputs.h"
#include "eLocalidad.h"
#include "ePedido.h"
#include "Relaciones.h"

#define EMPTY 0
#define FULL 1

int CalcularPedidosPorCliente (eCliente cliente, ePedido* listaPedidos, int tamPedidos, int orden){
	int pedidosDelCliente;
	int i;
	pedidosDelCliente = 0;

	switch(orden){
		case -1: //Contabiliza solo los pedidos pendientes
			for (i=0; i<tamPedidos; i++){
				if (listaPedidos[i].isEmpty == FULL && strcmp(listaPedidos[i].estado,"PENDIENTE")==0 && listaPedidos[i].idClientes == cliente.idCliente){
					pedidosDelCliente++;
				}
			}
			break;
		case 0: //Contabiliza todos los pedidos
			for (i=0; i<tamPedidos; i++){
				if (listaPedidos[i].isEmpty == FULL && listaPedidos[i].idClientes == cliente.idCliente){
					pedidosDelCliente++;
				}
			}
			break;
		case 1: //Contabiliza solo los pedidos completados
			for (i=0; i<tamPedidos; i++){
				if (listaPedidos[i].isEmpty == FULL && strcmp(listaPedidos[i].estado,"COMPLETADO")==0 && listaPedidos[i].idClientes == cliente.idCliente){
					pedidosDelCliente++;
				}
			}
			break;
	}

	return pedidosDelCliente;
}

int ImprimirClientesConPedidosPendientes (eCliente* listaClientes, int tamClientes, ePedido* listaPedidos, int tamPedidos, int orden){
	int i;
	int succes;
	int pedidosPendientes;
	succes = -1;
	printf("ID\t||\tEMPRESA \t||\tCUIT \t||\tDIRECCION \t||\tLOCALIDAD \t||\tPEDIDOS PENDIENTES \t\n");

	for (i=0; i<tamClientes; i++){
		if (listaClientes[i].isEmpty == FULL){
			pedidosPendientes = CalcularPedidosPorCliente(listaClientes[i], listaPedidos, tamPedidos, orden);
			printf("%4d %20s %16d %20s %20d %16d\n", listaClientes[i].idCliente, listaClientes[i].empresa, listaClientes[i].cuit, listaClientes[i].direccion, listaClientes[i].idLocalidad, pedidosPendientes);
			succes = 0;
		}
	}



	return succes;
}

int ImprimirPedidosPendientes (eCliente* listaClientes, int tamClientes, ePedido* listaPedidos, int tamPedidos){
	int succes;
	int i;
	int indexCliente;
	succes = -1;

	printf("--------PEDIDOS PENDIENTES--------\n");
	printf("ID-PEDIDO \t||\tCUIT DEL CLIENTE \t||\tDIRECCION \t||\tKILOS A RECOLECTAR\n");
	for (i=0; i<tamPedidos; i++){
		if(listaPedidos[i].isEmpty == FULL && strcmp(listaPedidos[i].estado, "PENDIENTE") == 0){
			indexCliente = BuscarClientePorId(listaClientes, tamClientes, listaPedidos[i].idClientes);
			printf("%10d %20d %30s %20.2f\n", listaPedidos[i].idPedido, listaClientes[indexCliente].cuit, listaClientes[indexCliente].direccion, listaPedidos[i].cantidadKilosTotales);
			succes = 0;
		}
	}

	return succes;
}
int ImprimirPedidosProcesados (eCliente* listaClientes, int tamClientes, ePedido* listaPedidos, int tamPedidos){
	int succes;
	int i;
	int indexCliente;
	succes = -1;

	printf("--------PEDIDOS PROCESADOS--------\n");
	printf("ID-PEDIDO \t||\tCUIT DEL CLIENTE \t||\tDIRECCION \t||\tKILOS HDPE||\tKILOS LDPE||\tKILOS PP\n");
	for (i=0; i<tamPedidos; i++){
		if(listaPedidos[i].isEmpty == FULL && strcmp(listaPedidos[i].estado, "COMPLETADO") == 0){
			indexCliente = BuscarClientePorId(listaClientes, tamClientes, listaPedidos[i].idClientes);
			printf("%10d %20d %30s %20.2f %20.2f %20.2f\n", listaPedidos[i].idPedido, listaClientes[indexCliente].cuit, listaClientes[indexCliente].direccion, listaPedidos[i].HPPE, listaPedidos[i].LDPE, listaPedidos[i].PP);
			succes = 0;
		}
	}

	return succes;
}
int ImprimirPedidosPendientesPorLocalidad (eCliente* listaClientes, int tamClientes, ePedido* listaPedidos, int tamPedidos){
	int succes;
	int i;
	int j;
	int idLocalidadSeleccionada;
	int contadorPedidosPendientes;

	contadorPedidosPendientes = 0;
	succes = -1;


	idLocalidadSeleccionada = GetInt("Por favor, seleccione una localidad\n", 1, 20, "No existe esa localidad\n");

	for (i=0; i<tamClientes; i++){
		if (listaClientes[i].idLocalidad == idLocalidadSeleccionada){
			for (j=0; j<tamPedidos; j++){
				if(listaClientes[i].idCliente == listaPedidos[j].idClientes && listaPedidos[j].isEmpty == FULL && strcmp(listaPedidos[j].estado,"PENDIENTE")==0){
					contadorPedidosPendientes ++;
					succes = 0;
				}
			}
		}
	}

	printf("La cantidad de pedidos pendientes en la localidad seleccionada es de %d\n", contadorPedidosPendientes);

	return succes;
}
float CalcularPromedioKilosPPPorCliente(eCliente* listaClientes, int tamClientes, ePedido* listaPedidos, int tamPedidos){
	float promedio;
	int contadorClientes;
	float kilosTotalesPP;
	int i;

	promedio = 0;
	contadorClientes = 0;
	kilosTotalesPP = 0;

	for (i=0; i<tamClientes; i++){
		if (listaClientes[i].isEmpty == FULL){
			contadorClientes++;
		}
	}

	for (i=0; i<tamPedidos; i++){
		if (listaPedidos[i].isEmpty == FULL && strcmp(listaPedidos[i].estado, "COMPLETADO") == 0){
			kilosTotalesPP += listaPedidos[i].PP;
		}
	}

	promedio = kilosTotalesPP/contadorClientes;
	return promedio;
}
int InformarClienteConMasPedidosPendientes(eCliente* listaClientes, int tamClientes, ePedido* listaPedidos, int tamPedidos){
	int succes;
	int idClienteConMasPedidosPendientes;
	int pedidosPendientes;
	int pedidosPendientesMAX;

	int i;

	pedidosPendientesMAX = 0;
	succes = -1;

	for (i=0; i<tamClientes; i++){
		pedidosPendientes = CalcularPedidosPorCliente(listaClientes[i], listaPedidos, tamPedidos, -1);
		if (pedidosPendientes > pedidosPendientesMAX){
			pedidosPendientesMAX = pedidosPendientes;
			idClienteConMasPedidosPendientes = listaClientes[i].idCliente;
			succes = 0;
		}
	}

	printf("El cliente con mas cantidad de pedidos pendientes es:\n");
	MostrarUnCliente(listaClientes, tamClientes, idClienteConMasPedidosPendientes);
	printf("Cantidad de pedidos pendientes: %d \n", pedidosPendientesMAX);

	return succes;
}
int InformarClienteConMasPedidosCompletados(eCliente* listaClientes, int tamClientes, ePedido* listaPedidos, int tamPedidos){
	int succes;
	int idClienteConMasPedidosCompletados;
	int pedidosCompletados;
	int pedidosCompletadosMAX;

	int i;

	pedidosCompletadosMAX = 0;
	succes = -1;

	for (i=0; i<tamClientes; i++){
		pedidosCompletados = CalcularPedidosPorCliente(listaClientes[i], listaPedidos, tamPedidos, 1);
		if (pedidosCompletados > pedidosCompletadosMAX){
			pedidosCompletadosMAX = pedidosCompletados;
			idClienteConMasPedidosCompletados = listaClientes[i].idCliente;
			succes = 0;
		}
	}

	printf("El cliente con mas cantidad de pedidos pendientes es:\n");
	MostrarUnCliente(listaClientes, tamClientes, idClienteConMasPedidosCompletados);
	printf("Cantidad de pedidos pendientes: %d \n", pedidosCompletadosMAX);

	return succes;
}

int BuscarIdClienteConMasPedidos(eCliente* listaClientes, int tamClientes, ePedido* listaPedidos, int tamPedidos, int orden){
	int idClienteConMasPedidos;
	int pedidos;
	int pedidosMAX;

	int i;

	pedidosMAX = 0;
	idClienteConMasPedidos = -1;

	switch (orden){
		case -1: //Busca el id del usuario con mas pedidos pendientes
			for (i=0; i<tamClientes; i++){
				pedidos = CalcularPedidosPorCliente(listaClientes[i], listaPedidos, tamPedidos, orden);
				if (pedidos > pedidosMAX){
					pedidosMAX = pedidos;
					idClienteConMasPedidos = listaClientes[i].idCliente;
				}
			}
			break;
		case 0: //Busca el id del usuario con mas pedidos totales
			for (i=0; i<tamClientes; i++){
				pedidos = CalcularPedidosPorCliente(listaClientes[i], listaPedidos, tamPedidos, orden);
				if (pedidos > pedidosMAX){
					pedidosMAX = pedidos;
					idClienteConMasPedidos = listaClientes[i].idCliente;
				}
			}
			break;
		case 1: //Busca el id del usuario con mas pedidos completados
			for (i=0; i<tamClientes; i++){
				pedidos = CalcularPedidosPorCliente(listaClientes[i], listaPedidos, tamPedidos, orden);
				if (pedidos > pedidosMAX){
					pedidosMAX = pedidos;
					idClienteConMasPedidos = listaClientes[i].idCliente;
				}
			}
			break;
	}

	return idClienteConMasPedidos;
}




// El codigo comentado aqui debajo fue sintetizado en la funcion "CalcularPedidosPorCliente"
/*
int CalcularPedidosPendientesPorCliente (eCliente cliente, ePedido* listaPedidos, int tamPedidos){
	int pedidosDelCliente;
	int i;
	pedidosDelCliente = 0;

	for (i=0; i<tamPedidos; i++){
		if (listaPedidos[i].isEmpty == FULL && strcmp(listaPedidos[i].estado,"PENDIENTE")==0 && listaPedidos[i].idClientes == cliente.idCliente){
			pedidosDelCliente++;
		}
	}


	return pedidosDelCliente;
}
int CalcularPedidosCompletadosPorCliente (eCliente cliente, ePedido* listaPedidos, int tamPedidos){
	int pedidosDelCliente;
	int i;
	pedidosDelCliente = 0;

	for (i=0; i<tamPedidos; i++){
		if (listaPedidos[i].isEmpty == FULL && strcmp(listaPedidos[i].estado,"COMPLETADO")==0 && listaPedidos[i].idClientes == cliente.idCliente){
			pedidosDelCliente++;
		}
	}


	return pedidosDelCliente;
}
int CalcularPedidosTotalesPorCliente (eCliente cliente, ePedido* listaPedidos, int tamPedidos){
	int pedidosDelCliente;
	int i;
	pedidosDelCliente = 0;

	for (i=0; i<tamPedidos; i++){
		if (listaPedidos[i].isEmpty == FULL && listaPedidos[i].idClientes == cliente.idCliente){
			pedidosDelCliente++;
		}
	}


	return pedidosDelCliente;
}
*/

