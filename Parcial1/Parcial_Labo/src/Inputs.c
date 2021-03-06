#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Inputs.h"

int GetInt(char mensaje[], int min, int max, char mensajeError[]){
	int number;

	printf("%s", mensaje);
	fflush(stdin);
	scanf("%d", &number);

	while(number<min || number>max){
		printf("%s", mensajeError);
		fflush(stdin);
		scanf("%d", &number);
	}

	return number;
}
float GetFloat(char mensaje[], int min, int max, char mensajeError[]){
	float number;

	printf("%s", mensaje);
	fflush(stdin);
	scanf("%f", &number);

	while(number<min || number>max){
		printf("%s", mensajeError);
		fflush(stdin);
		scanf("%f", &number);
	}

	return number;
}
void GetString (char mensaje[], char cadena[], int tam){
	printf("%s", mensaje);
	fflush(stdin);
	if (fgets(cadena, tam, stdin)){
		cadena[strcspn(cadena, "\n")] = 0;
	}
}
