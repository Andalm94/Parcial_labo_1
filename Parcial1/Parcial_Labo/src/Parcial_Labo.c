#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "eCliente.h"
#include "Inputs.h"
#include "eLocalidad.h"
#include "ePedido.h"
#include "Relaciones.h"

#define MAXClientes 100
#define MAXPedidos 1000


int main(){
	setbuf(stdout, NULL);

	int opcionMenu;
	int auxiliar;

	eCliente listaClientes[MAXClientes];
	ePedido listaPedidos[MAXPedidos];
	int idCliente = 1000;
	int idPedido = 100;

	InicializarClientes(listaClientes, MAXClientes);
	InicializarPedidos(listaPedidos, MAXPedidos);

do{
		printf("-----------------MENU PRINCIPAL-----------------\n");
		printf("1) Alta de cliente\n");
		printf("2) Modificacion de cliente\n");
		printf("3) Baja de cliente\n");
		printf("4) Crear pedido de recoleccion\n");
		printf("5) Procesar residuos\n");
		printf("6) Imprimir clientes\n");
		printf("7) Imprimir pedidos pendientes\n");
		printf("8) Imprimir pedidos procesados\n");
		printf("9) Informar pedidos pendientes por localidad\n");
		printf("10) Informar promedio de kilos de polipropileno reciclado por cliente\n");
		printf("11) Informar cliente con mas pedidos pendientes\n");
		printf("12) Informar cliente con mas pedidos completados\n");
		printf("13) Informar cliente con mas pedidos\n");
		printf("14) Salir\n");
		opcionMenu = GetInt("", 1, 14, "Opcion incorecta. Intente nuevamente.");

		switch(opcionMenu){
			case 1:
				if (AltaNuevoCliente(listaClientes, MAXClientes, &idCliente) == 0){
					MostrarUnCliente(listaClientes, MAXClientes, idCliente-1);
				}
				else{
					printf("No se ha podido cargar el cliente. Intente nuevamente.\n");
				}
				break;
			case 2:
				if (ModificarCliente(listaClientes, MAXClientes) == 0){
					printf("Se han realizado los cambios exitosamente\n");
				}
				else{
					printf("No se ha cargado ningun cliente.\n");
				}
				break;
			case 3:
				if (BajaCliente(listaClientes, MAXClientes) == 0){
					printf("El cliente ha sido dado de baja exitosamente\n");
				}
				else{
					printf("ERROR. Intente nuevamente\n");
				}
				break;
			case 4:
				if(AltaNuevoPedido(listaPedidos, MAXPedidos, &idPedido, listaClientes, MAXClientes) == 0){
					MostrarUnPedido(listaPedidos, MAXPedidos, idPedido-1);
					printf("El pedido ha sido cargado exitosamente\n");
				}
				else{
					printf("No ha sido posible cargar el pedido. Intente nuvemente.\n");
				}
				break;
			case 5:
				if (ProcesarResiduos(listaPedidos, MAXPedidos) == 0){
					printf("El pedido ha sido procesado exitosamente.\n");
				}
				else{
					printf("Ha habido un error, intente nuevamente.\n");
				}
				break;
			case 6:
				if (ImprimirClientesConPedidosPendientes(listaClientes, MAXClientes, listaPedidos, MAXPedidos, -1) == -1){
					printf("No hay ningun cliente con pedidos pendientes.\n");
				}
				break;
			case 7:
				if (ImprimirPedidosPendientes (listaClientes, MAXClientes, listaPedidos, MAXPedidos) == -1){
					printf("No hay ningun pedidos pendientes.\n");
				}
				break;
			case 8:
				if (ImprimirPedidosProcesados (listaClientes, MAXClientes, listaPedidos, MAXPedidos) == -1){
					printf("No se ha procesado ningun pedido.\n");
				}
				break;
			case 9:
				if (ImprimirPedidosPendientesPorLocalidad (listaClientes, MAXClientes, listaPedidos, MAXPedidos) == -1){
					printf("No hay pedidos en la localidad seleccionada");
				}
				break;
			case 10:
				printf("El promedio de kilos PP reciclado por cliente es de %.2f\n", CalcularPromedioKilosPPPorCliente(listaClientes, MAXClientes, listaPedidos, MAXPedidos));
				break;
			case 11:
				auxiliar = BuscarIdClienteConMasPedidos(listaClientes, MAXClientes, listaPedidos, MAXPedidos, -1);
				if (auxiliar != -1){
					printf("El cliente con mas pedidos pendientes es: \n");
					MostrarUnCliente(listaClientes, MAXClientes, auxiliar);
				}
				break;
			case 12:
				auxiliar = BuscarIdClienteConMasPedidos(listaClientes, MAXClientes, listaPedidos, MAXPedidos, 1);
				if (auxiliar != -1){
					printf("El cliente con mas pedidos completados es: \n");
					MostrarUnCliente(listaClientes, MAXClientes, auxiliar);
				}
				break;
			case 13:
				auxiliar = BuscarIdClienteConMasPedidos(listaClientes, MAXClientes, listaPedidos, MAXPedidos, 0);
				if (auxiliar != -1){
					printf("El cliente con mas pedidos es: \n");
					MostrarUnCliente(listaClientes, MAXClientes, auxiliar);
				}
			break;
			case 14:
				break;

		}



	}while (opcionMenu != 14);


	return 0;
}
