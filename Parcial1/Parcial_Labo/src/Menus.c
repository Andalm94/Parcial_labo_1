#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Inputs.h"
#include "ManejoStructs.h"
#include "Menus.h"

int MostrarMenuPrincipal(char mensaje[], int min, int max, char mensajeError[]){
	int opcionElegida;

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
	printf("11) Salir\n");



	opcionElegida = GetInt(mensaje, min, max, mensajeError);


	return opcionElegida;
}

int MostrarMenuInformes(char mensaje[], char mensajeError[]){
	int opcionElegida;

	printf("------------INFORMES------------\n");
	printf("1) Listado de empleados ordenados por apellido y sector\n");
	printf("2) Total y promedio de salarios. Numero de empleados que superan el salario promedio.\n");
	printf("3) Volver al Menu Principal\n");

	opcionElegida = GetInt(mensaje, 1, 3, mensajeError);
	return opcionElegida;
}


