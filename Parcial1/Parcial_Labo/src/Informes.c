#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Inputs.h"
#include "ManejoStructs.h"
#include "Menus.h"

int ClienteConMasPedidosPendientes(eCliente* listaClientes, int tamClientes){
	int i;
	int idClienteConMasPedidos;
	int maxPedidos;

	maxPedidos = 0;
	idClienteConMasPedidos = -1;

	for (i=0; i<tamClientes; i++){
		if(listaClientes[i].pedidosPendientes > maxPedidos){
			idClienteConMasPedidos = listaClientes[i].idCliente;
			maxPedidos = listaClientes[i].pedidosPendientes;
		}
	}

	return idClienteConMasPedidos;
}




