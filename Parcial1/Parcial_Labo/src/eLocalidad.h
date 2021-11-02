#ifndef ELOCALIDAD_H_
#define ELOCALIDAD_H_

typedef struct {
	int idLocalidad;
	char localidad[100];
	int isEmpty;
}eLocalidad;

void InicializarLocalidades(eLocalidad* list, int tam);
int BuscarLocalidadPorId(eLocalidad* list, int tam, int id);


#endif
