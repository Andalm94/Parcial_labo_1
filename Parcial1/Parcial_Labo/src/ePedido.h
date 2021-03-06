#ifndef EPEDIDO_H_
#define EPEDIDO_H_

typedef struct {
	int idPedido;
	float cantidadKilosTotales;
	float HPPE;
	float LDPE;
	float PP;
	char estado[10];
	int isEmpty;
	int idClientes;
}ePedido;

/*---INICIALIZACION Y BUSQUEDA----*/

void InicializarPedidos(ePedido* list, int tam);
int BuscarPedidoPorId(ePedido* list, int tam, int id);
int BuscarIndexLibreParaPedido(ePedido* list, int tam);
void MostrarUnPedido(ePedido* list, int tam, int id);
int MostrarPedidos(ePedido* list, int tam);


/*--------------ABM--------------*/

int AltaNuevoPedido(ePedido* listaPedidos, int tamPedidos, int* id, eCliente* listaClientes, int tamClientes);
int ProcesarResiduos(ePedido* listaPedidos, int tamPedidos);

#endif
