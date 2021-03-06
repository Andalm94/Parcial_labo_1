#ifndef RELACIONES_H_
#define RELACIONES_H_


int CalcularPedidosPendientesPorCliente (eCliente cliente, ePedido* listaPedidos, int tamPedidos);
int CalcularPedidosCompletadosPorCliente (eCliente cliente, ePedido* listaPedidos, int tamPedidos);
int CalcularPedidosTotalesPorCliente (eCliente cliente, ePedido* listaPedidos, int tamPedidos);
int ImprimirClientesConPedidosPendientes (eCliente* listaClientes, int tamClientes, ePedido* listaPedidos, int tamPedidos, int orden);
int CalcularPedidosPorCliente (eCliente cliente, ePedido* listaPedidos, int tamPedidos, int orden);

int ImprimirPedidosPendientes (eCliente* listaClientes, int tamClientes, ePedido* listaPedidos, int tamPedidos);
int ImprimirPedidosProcesados (eCliente* listaClientes, int tamClientes, ePedido* listaPedidos, int tamPedidos);
int ImprimirPedidosPendientesPorLocalidad (eCliente* listaClientes, int tamClientes, ePedido* listaPedidos, int tamPedidos);
float CalcularPromedioKilosPPPorCliente(eCliente* listaClientes, int tamClientes, ePedido* listaPedidos, int tamPedidos);
int InformarClienteConMasPedidosPendientes(eCliente* listaClientes, int tamClientes, ePedido* listaPedidos, int tamPedidos);
int InformarClienteConMasPedidosCompletados(eCliente* listaClientes, int tamClientes, ePedido* listaPedidos, int tamPedidos);

int BuscarIdClienteConMasPedidos(eCliente* listaClientes, int tamClientes, ePedido* listaPedidos, int tamPedidos, int orden);

#endif
