#ifndef INGRESODEDATOS_H_
#define INGRESODEDATOS_H_

typedef struct{
	int idCliente; //PK
	char empresa[50];
	int cuit;
	int pedidosPendientes;
	eLocalidad listaLocalidad[50];
	int isEmpty;
}eCliente;

typedef struct{
	int idPedido; //PK
	int idCliente; //FK
	int idLocalidad;
	float kilosTotales;
	float kilosHDPE;
	float kilosLDPE;
	float kilosPP;
	int estado;
	int isEmpty;
}ePedido;

typedef struct{
	char localidad[50];
	char direccion[50];
}eLocalidad;

int GetInt(char mensaje[], int min, int max, char mensajeError[]);
float GetFloat(char mensaje[], int min, int max, char mensajeError[]);
int ValidarNumero(int numero);
void GetString (char mensaje[], char cadena[], int tam);


#endif
