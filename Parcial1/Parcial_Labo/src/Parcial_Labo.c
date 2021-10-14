#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Inputs.h"
#include "ManejoStructs.h"
#include "Menus.h"

#define MAXClientes 100
#define MAXPedidos 100


int main(){
	setbuf(stdout, NULL);
	int opcionMenuPrincipal;
	eCliente listaClientes[MAXClientes];
	ePedido listaPedidos[MAXPedidos];

	int retornoFuncion;
	int idCliente;
	int idClienteSeleccionado;
	int idPedido;
	int idPedidoSeleccionado;

	int pedidosPorLocalidad;

	float promedioKilosPP;



	idCliente = 1000;
	idPedido = 100;
	pedidosPorLocalidad = 0;
	promedioKilosPP = 0;

	/*int prueba;
	while(1){
		prueba = GetInt("Ingrese numero\n", 0, 100, "ERROR\n");

	}*/


	InicializarClientes(listaClientes, MAXClientes);
	InicializarPedidos(listaPedidos, MAXPedidos);

	do{
		opcionMenuPrincipal = MostrarMenuPrincipal("", 1, 11, "La opcion ingresada no existe, intente nuevamente.\n");
		switch (opcionMenuPrincipal){
			case 1: //Alta Cliente
				retornoFuncion = BuscarEspacioLibre(listaClientes, MAXClientes);
				if(retornoFuncion != -1){
					CargarNuevoCliente(listaClientes, MAXClientes, &idCliente);
					MostrarUnCliente(listaClientes, MAXClientes, idCliente-1);
				}
				break;
			case 2: //Modificar Cliente
				retornoFuncion = MostrarClientes(listaClientes, MAXClientes);
				idClienteSeleccionado = GetInt("Por favor, ingrese el ID del cliente: \n", 0, 1000000, "El ID ingresado no existe.");
				if (BuscarClientePorId(listaClientes, MAXClientes, idClienteSeleccionado) != -1){
					retornoFuncion = ModificarDireccion(listaClientes, MAXClientes, idClienteSeleccionado, "Por favor, ingrese la nueva direccion: \n");
					retornoFuncion = ModificarLocalidad(listaClientes, MAXClientes, idClienteSeleccionado, "Por favor, ingrese la nueva localidad: \n");
				}
				else{
					printf("No se ha encontrado el usuario solicitado. Intente nuevamente: \n");
				}
				break;
			case 3: //Baja Cliente
				retornoFuncion = MostrarClientes(listaClientes, MAXClientes);
				idClienteSeleccionado = GetInt("Por favor, ingrese el ID del cliente: \n", 0, 1000000, "El ID ingresado no existe.");
				if (BuscarClientePorId(listaClientes, MAXClientes, idClienteSeleccionado) != -1){
					retornoFuncion = EliminarCliente(listaClientes, MAXClientes, idClienteSeleccionado);
					if(retornoFuncion != -1){
						printf("El cliente ha sido dado de baja exitosamente. \n");
					}
					else{
						printf("El cliente no ha sido encontrado, intente nuevamente. \n");
					}
				}
				break;
			case 4: // Alta Pedido de Recoleccion
				retornoFuncion = CrearPedidoDeRecoleccion(listaClientes, MAXClientes, listaPedidos, MAXPedidos, &idPedido);
				if(retornoFuncion == 0){
					printf("El pedido se ha cargado exitosamente\n");
				}
				else{
					printf("No se ha podido cargar el pedido. Intente nuevamente.\n");
				}
				break;
			case 5: // Procesamiento de residuos
				MostrarPedidos(listaPedidos, MAXPedidos, listaClientes, MAXClientes);
				idPedidoSeleccionado = GetInt("Por favor, ingrese el ID del pedido: \n", 0, 1000000, "El ID ingresado no existe.");
				retornoFuncion = ProcesarResiduos(listaPedidos, MAXPedidos, idPedidoSeleccionado, listaClientes, MAXClientes);
				if(retornoFuncion == 0){
					RestarPedidoPendienteACliente(listaClientes, MAXClientes, idPedidoSeleccionado);
					printf("El pedido ha sido completado exitosamente.\n");
				}
				else{
					printf("El pedido no ha sido completado. Revise que las cantidades de pl�stico ingresadas no superen los kilogramos totales del pedido.\n");
				}
				break;
			case 6:
				MostrarClientesConPedidosPendientes(listaClientes, MAXClientes);
				break;
			case 7:
				MostrarPedidosPendientes(listaPedidos, MAXPedidos, listaClientes, MAXClientes);
				break;
			case 8:
				MostrarPedidosProcesados(listaPedidos, MAXPedidos, listaClientes, MAXClientes);
				break;
			case 9:
				pedidosPorLocalidad = BuscarPedidosPorLocalidad("Por favor, ingrese la localidad:\n", listaClientes, MAXClientes);
				if(pedidosPorLocalidad > 0){
					printf("La localidad ingresada tiene %d pedidos pendientes.", pedidosPorLocalidad);
				}
				break;
			case 10:
				promedioKilosPP = CalcularKilosPPPorCliente(listaClientes, MAXClientes, listaPedidos, MAXPedidos);
				printf("El promedio de kilos de poliproppileno reciclado por cliente es %.2f kilogramos\n", promedioKilosPP);
				break;
			case 11:
				break;
		}


	}while(opcionMenuPrincipal != 11);

	return 0;
}