#ifndef INGRESODEDATOS_H_
#define INGRESODEDATOS_H_

typedef struct{
	int idCliente; //PK
	char empresa[50];
	int cuit;
	char direccion[50];
	char localidad[20];
	int pedidosPendientes;
	int isEmpty;
}eCliente;

typedef struct{
	int idPedido; //PK
	int idCliente; //FK
	float kilosTotales;
	float kilosHDPE;
	float kilosLDPE;
	float kilosPP;
	int estado;
	int isEmpty;
}ePedido;

int GetInt(char mensaje[], int min, int max, char mensajeError[]);
float GetFloat(char mensaje[], int min, int max, char mensajeError[]);
int ValidarNumero(int numero);
void GetString (char mensaje[], char cadena[], int tam);


#endif