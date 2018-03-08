//David Thomas
//Este programa gestiona dos plazas de aparcamiento: controla si las plazas estan libres o ocupadas y, en ese caso, que coche 
//esta aparcado y lo que tiene que pagar basandose en el tiempo que lleva
//El unico problema es que no comprueba si la matricula que se ha introducido es valida, pues tras mucho intentarlo, no lo he logrado

#include<stdio.h>
#include<time.h>
#include <windows.h>

void main() {        

	//Declaracion de variables
	int plazaAparcamiento[2] = { 0,0 };        //Las usaré como variables booleanas, 1 si estan ocupadas y 0 si están libres
	char opcion;
	char matricula[2][9];
	int i;
	float dinero, tiempoTotal;

	while (1) {

		//Pedir datos por pantalla   
		time_t start_1, start_2, end_1, end_2;  //Creacion de objetos para calcular el tiempo que un coche esta aparcado
		SYSTEMTIME str_t;
		GetSystemTime(&str_t);

		printf("Son las %d:%d:% d\n", str_t.wHour, str_t.wMinute, str_t.wSecond);
		printf("Seleccione una de estas opciones : \n");
		printf("R - Reservar plaza \n");
		printf("A - Abandonar plaza \n");
		printf("E - Estado del aparcamiento \n");
		scanf_s("%c", &opcion, 1); getchar();

		switch (opcion) {
			case 'r':
			case 'R':

				if (plazaAparcamiento[0] == 0) {
					plazaAparcamiento[0] = 1;
					printf("\n Introduce la matricula de tu coche: \n");
					scanf_s("%s", matricula[0], 8); getchar();
					printf("Tu coche esta aparcado en la plaza 1");
					time(&start_1);
				}
				else if (plazaAparcamiento[1] == 0) {
					plazaAparcamiento[1] = 1;
					printf("\n Introduce la matricula de tu coche: \n");
					scanf_s("%s", matricula[1], 8); getchar();
					printf("Tu coche esta aparcado en la plaza 2");
					time(&start_2);
				}
				else printf("\n No hay ninguna plaza libre \n");
				break;

			case 'a':
			case 'A':

				do {
					i = 1;
					printf("\n Introduce la plaza de tu coche (1 o 2) --- pulsa '0' para salir \n");
					scanf_s("%c", &opcion); getchar();
					if (opcion == '1') {
						if (plazaAparcamiento[0] == 1) {
							plazaAparcamiento[0] = 0;
							time(&end_1);
							tiempoTotal = difftime(end_1, start_1);
							dinero = 0.01 * tiempoTotal;               //Por cada segundo se paga 1 cent.
							printf("Has tenido el coche aparcado %f minutos, vas a tener que pagar %f euros \n", tiempoTotal/60, dinero);
							scanf_s("%c", &opcion);
						}
						else {
							printf("Esta plaza ya estaba vacia!!, vuelve a intentarlo \n");
							i = 2;
						}
					}
					else if (opcion == '2') {
						if (plazaAparcamiento[1] == 1) {
							plazaAparcamiento[1] = 0;
							time(&end_2);
							tiempoTotal = difftime(end_2, start_2);
							dinero = 0.01 * tiempoTotal;
							printf("Has tenido el coche aparcado %f minutos, vas a tener que pagar %f euros \n", tiempoTotal / 60, dinero);
							scanf_s("%c", &opcion);
						}
						else {
							printf("Esta plaza ya estaba vacia!!, vuelve a intentarlo \n");
							i = 2;
						}
					}
					else if (opcion == '0') break;
					else {
						i = 2;
						printf("Opcion no valida, vuelve a intentarlo \n");
					}
				} while (i == 2);
				break;

			case 'e':
			case 'E':
				printf("plaza 1 -- ");
				if (plazaAparcamiento[0] == 0) printf("Libre \n"); 
				else {
					printf("Ocupada, matricula: ");
					printf("%s", matricula[0]); printf("\n");
				}
				printf("plaza 2 -- ");
				if (plazaAparcamiento[1] == 0) printf("Libre \n");
				else {
					printf("Ocupada, matricula: ");
					printf("%s", matricula[1]); printf("\n");
				}				
				break;

		}
		printf(" \n Pulsa un boton para volver al menu");
		scanf_s("%c", &opcion);           //Este comando lo unico que hace es mantener la pantalla quieta para el usuario
		system("cls");                    //pueda leerla comodamente. Al darle a un boton, se limpia y el codigo vuelve a empezar
	}
		
}
