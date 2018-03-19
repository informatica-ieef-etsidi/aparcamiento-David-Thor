//David Thomas
//Este programa gestiona cuatro plazas de aparcamiento: controla si las plazas estan libres o ocupadas y, en ese caso, que vehiculo
//esta aparcado y lo que tiene que pagar basandose en el tiempo que lleva

#include<stdio.h>
#include<time.h>
#include<windows.h>
#include<string.h>

#define NUMPLAZAS 4

struct TPlaza {
	int vehiculo; //0 - coche, 1 - moto
	int ocupado; //1 si la plaza esta ocupada
	char matricula[9];
};

void main() {        

	struct TPlaza plaza[NUMPLAZAS] = { {0,0}, {0,0}, {1,0}, {1,0} };
	char opcion, otraOpcion, opcionPlaza, otraMatricula[9];
	int i, z;
	float dinero, tiempoTotal;

	while (1) {

		//Pedir datos por pantalla   
		time_t start[4], end[4];  //Creacion de objetos para calcular el tiempo que un coche esta aparcado
		SYSTEMTIME str_t;
		GetSystemTime(&str_t);

		printf("Son las %d:%d:% d\n", str_t.wHour, str_t.wMinute, str_t.wSecond);
		printf("Seleccione una de estas opciones : \n");
		printf("R - Reservar plaza \n");
		printf("A - Abandonar plaza \n");
		printf("E - Estado del aparcamiento \n");
		printf("S - Salir del programa \n");
		printf("B - Buscar un vehiculo \n");
		scanf_s("%c", &opcion, 1); getchar();

		switch (opcion) {
			case 'r':
			case 'R':
				printf("Tienes coche(introduce c) o moto(m) \n");
				scanf_s("%c", &otraOpcion, 1);
				switch (otraOpcion)				{
				case'c':
				case'C':
					if (plaza[0].ocupado * plaza[1].ocupado == 0) {
						for (int j = 0; j < 2; j++) {
							if (plaza[j].ocupado == 0) {
								plaza[j].ocupado = 1;
								printf("Introduce tu matricula: \n"); getchar();
								gets(plaza[j].matricula);
								time(&start[j]);
								printf("Tu coche ha sido aparcado en la plaza %d", j + 1);
								break;
							}
						}
					}
					else printf("No quedan plazas libres de este tipo");
					break;
				case'm':
				case'M':
					if (plaza[2].ocupado * plaza[3].ocupado == 0) {
						for (int j = 2; j < 4; j++) {
							if (plaza[j].ocupado == 0) {
								plaza[j].ocupado = 1;
								printf("Introduce tu matricula: \n"); getchar();
								gets(plaza[j].matricula);
								time(&start[j]);
								printf("Tu moto ha sido aparcada en la plaza %d", j + 1);
								break;
							}
						}
					}
					else printf("No quedan plazas libres de este tipo");
					break;
				default:
					printf("Opcion no valida"); break;
				}break;

			case 'a':
			case 'A':
				printf("En que plaza esta tu coche? \n");
				scanf_s("%d", &opcionPlaza);
				if (1 <= opcionPlaza && opcionPlaza <= 4) {
					if (plaza[opcionPlaza - 1].ocupado == 1) {
						printf("Por seguridad, introduce tu matricula: \n"); getchar();
						gets(otraMatricula);
						if (strcmp(otraMatricula, plaza[opcionPlaza - 1].matricula) == 0) {   //Si la matricula coincide
							plaza[opcionPlaza - 1].ocupado = 0;
							time(&end[opcionPlaza - 1]);
							tiempoTotal = difftime(end[opcionPlaza - 1], start[opcionPlaza - 1]);
							dinero = 0.01 * tiempoTotal;               //Por cada segundo se paga 1 cent.
							printf("Has tenido tu vehiculo aparcado %f minutos, vas a tener que pagar %f euros \n", tiempoTotal / 60, dinero);							
						}
						else{          //Si la matricula no coincide 
							printf("ERROR: Las matriculas no coinciden");
						}
					}
				}
				else printf("Numero de plaza incorrecto");

				break;

			case 'e':
			case 'E':
				printf("plaza 1 -- ");
				if (plaza[0].ocupado == 0) printf("Libre \n"); 
				else {
					printf("Ocupada, matricula: ");
					printf("%s", plaza[0].matricula); printf("\n");
				}
				printf("plaza 2 -- ");
				if (plaza[1].ocupado == 0) printf("Libre \n");
				else {
					printf("Ocupada, matricula: ");
					printf("%s", plaza[1].matricula); printf("\n");
				}	
				printf("plaza 3 -- ");
				if (plaza[2].ocupado == 0) printf("Libre \n");
				else {
					printf("Ocupada, matricula: ");
					printf("%s", plaza[2].matricula); printf("\n");
				}
				printf("plaza 4 -- ");
				if (plaza[3].ocupado == 0) printf("Libre \n");
				else {
					printf("Ocupada, matricula: ");
					printf("%s", plaza[3].matricula); printf("\n");
				}
				break;

			case 's':
			case 'S':
				return;

			case 'b':
			case 'B':
				printf("Introduce la matricula del vehiculo que quieres buscar");
				gets(otraMatricula); getchar();
				z = 0;
				for (int i = 0; i < NUMPLAZAS; i++) {
					if (strcmp(otraMatricula, plaza[i].matricula) == 0) {
						printf("Tu vehiculo esta en la plaza %d", i + 1);
						z = 1;
					}
				}
				if (z == 0) printf("Esa matricula no se corresponde con la de ningun vehiculo estacionado");
				break;				

			default:
				printf("Opcion no valida"); break;
		}
		getchar();
		printf(" \n Pulsa un boton para volver al menu");
		scanf_s("%c", &opcion);           //Este comando lo unico que hace es mantener la pantalla quieta para el usuario
		system("cls");                    //pueda leerla comodamente. Al darle a un boton, se limpia y el codigo vuelve a empezar
	}
		
}
