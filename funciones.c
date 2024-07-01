#include <stdio.h>
#include <string.h>
#include "funciones.h"

void buscarPorTamano(int *numHabitacion, char habitaciones[][3][40], double precios[]) {
    char tamano[20];
    int opcionValida = 0;
    int selec = 0;

    while (!opcionValida) {
        printf("Ingrese el tamano de la habitacion (simple, doble, triple): ");
        scanf("%s", tamano);
        for (int i = 0; i < 9; i++) {
            if (strcmp(habitaciones[i][1], tamano) == 0) {
                printf("Habitacion %s, Hotel %s, Precio %.2f\n", habitaciones[i][0], habitaciones[i][2], precios[i]);
                opcionValida = 1;
            }
        }
        if (!opcionValida) {
            printf("Opcion no valida. Intente de nuevo.\n");
        }
    }
    do {
        printf("Ingrese el numero de la habitacion que desea: ");
        scanf("%d", numHabitacion);
        *numHabitacion -= 1;
        printf("Desea guardar la habitacion?(1=Si,2=No): ");
        scanf("%d", &selec);
    } while (selec != 1);
}

void buscarHotel(int *numHabitacion, char habitaciones[][3][40], double precios[]) {
    char hotel[40];
    int opcionValida = 0;
    int selec = 0;

    while (!opcionValida) {
        printf("Ingrese el nombre del hotel(Dan_Carlton, Swissotel, Sheraton): ");
        scanf("%s", hotel);
        for (int i = 0; i < 9; i++) {
            if (strcmp(habitaciones[i][2], hotel) == 0) {
                printf("Habitacion %s, Tipo %s, Precio %.2f\n", habitaciones[i][0], habitaciones[i][1], precios[i]);
                opcionValida = 1;
            }
        }
        if (!opcionValida) {
            printf("Opcion no valida. Intente de nuevo.\n");
        }
    }
    do {
        printf("Ingrese el numero de la habitacion que desea: ");
        scanf("%d", numHabitacion);
        *numHabitacion -= 1;
        printf("Desea guardar la habitacion?(1=Si,2=No): ");
        scanf("%d", &selec);
    } while (selec != 1);
}

void guardarReservaEnArchivo(int numHabitacion, char habitaciones[][3][40], char cliente[], char cedula[], double precios[]) {
    FILE *archivo = fopen("C:/uni/reservas.txt", "a+");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para guardar la reserva.\n");
        return;
    }
    fprintf(archivo, "Cedula: %s\nCliente: %s\nHabitacion: %s\nHotel: %s\nPrecio: %.2f\n",
            cedula, cliente, habitaciones[numHabitacion][0], habitaciones[numHabitacion][2], precios[numHabitacion]);
    fclose(archivo);
}

void realizarReserva(int numHabitacion, char habitaciones[][3][40], char clientes[][2][40], int reservas[][3], double precios[]) {
    char cliente[40];
    char cedula[20];
    int i = 0;

    while (clientes[i][0][0] != '\0' && i < 10) {
        i++;
    }
    
    if (i == 10) {
        printf("No se pueden realizar mas reservas. Limite alcanzado.\n");
        return;
    }
    
    printf("Ingrese el nombre del cliente: ");
    scanf("%s", cliente);
    printf("Ingrese la cedula del cliente: ");
    scanf("%s", cedula);

    strcpy(clientes[i][0], cliente);
    strcpy(clientes[i][1], cedula);

    reservas[i][0] = i;
    reservas[i][1] = numHabitacion;
    reservas[i][2] = 0; // 0 = no pagada, 1 = pagada

    printf("Reserva realizada para %s en la habitacion %s del hotel %s.\n", cliente, habitaciones[numHabitacion][0], habitaciones[numHabitacion][2]);

    guardarReservaEnArchivo(numHabitacion, habitaciones, cliente, cedula, precios);
}

void buscarReservaPorCedula(int *numReserva, char clientes[][2][40], int reservas[][3], char *cedula) {
    *numReserva = -1;
    for (int i = 0; i < 10; i++) {
        if (strcmp(clientes[i][1], cedula) == 0) {
            *numReserva = reservas[i][0];
            return;
        }
    }
    if (*numReserva == -1) {
        printf("No se encontro ninguna reserva para la cedula ingresada.\n");
    }
}

void imprimirReserva(int numReserva, int reservas[][3], char habitaciones[][3][40], double precios[]) {
    if (numReserva == -1) {
        printf("No hay reserva para imprimir.\n");
        return;
    }
    
    printf("Reserva #%d\n", numReserva);
    printf("Habitacion: %s\n", habitaciones[reservas[numReserva][1]][0]);
    printf("Hotel: %s\n", habitaciones[reservas[numReserva][1]][2]);
    printf("Precio: %.2f\n", precios[reservas[numReserva][1]]);
    printf("Estado: %s\n", reservas[numReserva][2] == 0 ? "No pagada" : "Pagada");
}

void pagarReserva(int numReserva, int reservas[][3], char habitaciones[][3][40], double precios[]) {
    if (numReserva == -1) {
        printf("No hay reserva para pagar.\n");
        return;
    }
    
    printf("Pagando la reserva #%d\n", numReserva);
    printf("Habitacion: %s\n", habitaciones[reservas[numReserva][1]][0]);
    printf("Hotel: %s\n", habitaciones[reservas[numReserva][1]][2]);
    printf("Precio: %.2f\n", precios[reservas[numReserva][1]]);
    
    reservas[numReserva][2] = 1; // Cambiar estado a pagada
    printf("Reserva pagada con exito.\n");
}

void actualizarReservaEnArchivo(char cedula[], char nuevaHabitacion[], char nuevoHotel[], double nuevoPrecio) {
    FILE *archivo = fopen("C:/uni/reservas.txt", "a+");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para actualizar la reserva.\n");
        return;
    }

    char line[256];
    long int pos;
    int found = 0;
    while (fgets(line, sizeof(line), archivo)) {
        if (strstr(line, cedula)) {
            found = 1;
            pos = ftell(archivo);
            fseek(archivo, pos, SEEK_SET);
            fprintf(archivo, "Habitacion: %s\nHotel: %s\nPrecio: %.2f\n\n",
                    nuevaHabitacion, nuevoHotel, nuevoPrecio);
            break;
        }
    }

    if (!found) {
        printf("No se encontró la reserva con la cedula %s.\n", cedula);
    }

    fclose(archivo);
}

void buscarReservaEnArchivo(char cedula[]) {
    FILE *archivo = fopen("C:/uni/reservas.txt", "a+");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para buscar la reserva.\n");
        return;
    }

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), archivo)) {
        if (strstr(line, cedula)) {
            found = 1;
            printf("Reserva encontrada:\n");
            printf("%s", line);
            for (int i = 0; i < 4; i++) {
                if (fgets(line, sizeof(line), archivo)) {
                    printf("%s", line);
                }
            }
            break;
        }
    }

    if (!found) {
        printf("No se encontró la reserva con la cedula %s.\n", cedula);
    }

    fclose(archivo);
}