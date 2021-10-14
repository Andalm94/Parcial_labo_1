#ifndef MANEJOSTRUCTS_H_
#define MANEJOSTRUCTS_H_

#include "Inputs.h"


void InicializarClientes(eCliente* list, int tam);
int MostrarClientes(eCliente* list, int tam);
void MostrarUnCliente(eCliente* list, int tam, int id);

void InicializarPedidos(ePedido* list, int tam);

int BuscarEspacioLibre(eCliente* list, int tam);
void IngresarDatos(char empresa[], int* cuit, char direccion[], char localidad[]);
int CargarNuevoCliente(eCliente* list, int tam, int* id);
int AsignarIdCliente(int* id);

int BuscarClientePorId(eCliente* list, int tam, int id);
int ModificarDireccion(eCliente* list, int tam, int id, char mensaje[]);
int ModificarLocalidad(eCliente* list, int tam, int id, char mensaje[]);

int EliminarCliente(eCliente* list, int tam, int id);

int CrearPedidoDeRecoleccion(eCliente* listaClientes, int tamClientes, ePedido* listaPedidos, int tamPedidos, int*idPedido);
int BuscarEspacioLibreParaPedido(ePedido* list, int tam);
int AsignarIdPedido(int* idPedido);

int ProcesarResiduos(ePedido* list, int tamPedidos, int id, eCliente* listaClientes, int tamClientes);
void RestarPedidoPendienteACliente(eCliente* listaCliente, int tamClientes, int id);


void MostrarPedidos(ePedido* listaPedidos, int tamPedidos, eCliente* listaClientes, int tamClientes);

void MostrarClientesConPedidosPendientes (eCliente* listaClientes, int tamClientes);

void MostrarPedidosPendientes(ePedido* listaPedidos, int tamPedidos, eCliente* listaClientes, int tamClientes);
void MostrarPedidosProcesados(ePedido* listaPedidos, int tamPedidos, eCliente* listaClientes, int tamClientes);

int BuscarPedidosPorLocalidad(char mensaje[], eCliente* listaClientes, int tamClientes);

float CalcularKilosPPPorCliente(eCliente* listaClientes, int tamClientes, ePedido* listaPedidos, int tamPedidos);

#endif /* MANEJOSTRUCTS_H_ */
