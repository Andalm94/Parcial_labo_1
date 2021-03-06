#ifndef ECLIENTE_H_
#define ECLIENTE_H_

typedef struct {
	int idCliente;
	char empresa[100];
	int cuit;
	char direccion[100];
	int idLocalidad;
	int isEmpty;
}eCliente;

/*---INICIALIZACION Y BUSQUEDA----*/

void InicializarClientes(eCliente* list, int tam);
int BuscarClientePorId(eCliente* list, int tam, int id);
int BuscarIndexLibreParaCliente(eCliente* list, int tam);
void MostrarUnCliente(eCliente* list, int tam, int id);
int MostrarClientes(eCliente* list, int tam);

/*--------------ABM--------------*/

int AltaNuevoCliente(eCliente* list, int tam, int* id);
int ModificarCliente(eCliente* listaClientes, int tam);
int BajaCliente(eCliente* listaClientes, int tam);

#endif
