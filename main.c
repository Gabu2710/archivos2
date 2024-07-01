#include <stdio.h>
#include <string.h>
#include "funciones.h"

int main() {
    int opcion;
    int numHabitacion;
    int habitacionSeleccionada = 0;
    char habitaciones[9][3][40] = {
        {"1", "simple", "Dan_Carlton"},
        {"2", "doble", "Dan_Carlton"},
        {"3", "triple", "Dan_Carlton"},
        {"4", "simple", "Swissotel"},
        {"5", "doble", "Swissotel"},
        {"6", "triple", "Swissotel"},
        {"7", "simple", "Sheraton"},
        {"8", "doble", "Sheraton"},
        {"9", "triple", "Sheraton"}
    };
    double precios[9] = {100.0, 150.0, 200.0, 120.0, 170.0, 220.0, 130.0, 180.0, 230.0};
    char clientes[10][2][40] = {0};
    int reservas[10][3] = {0};
    char cedula[20];
    int numReserva;

    do {
        printf("Menu:\n");
        printf("1. Buscar habitacion\n");
        printf("2. Realizar reserva\n");
        printf("3. Buscar reserva por cedula\n");
        printf("4. Pagar reserva\n");
        printf("5. Actualizar reserva\n");
        printf("6. Buscar reserva en archivo\n");
        printf("7. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("1. Buscar por tamano\n");
                printf("2. Buscar por hotel\n");
                printf("Seleccione una opcion: ");
                scanf("%d", &opcion);
                switch (opcion) {
                    case 1:
                        buscarPorTamano(&numHabitacion, habitaciones, precios);
                        habitacionSeleccionada = 1;
                        printf("Habitacion Guardada con exito,\n");
                        printf("Recuerde que si desea cambiar Habitacion, debe buscar Habitacion nuevamente, Gracias\n");
                        break;
                    case 2:
                        buscarHotel(&numHabitacion, habitaciones, precios);
                        habitacionSeleccionada = 1;
                        printf("Habitacion Guardada con exito,\n");
                        printf("Recuerde que si desea cambiar Habitacion, debe buscar Habitacion nuevamente, Gracias\n");
                        break;
                }
                break;
            case 2:
                if (habitacionSeleccionada) {
                    realizarReserva(numHabitacion, habitaciones, clientes, reservas, precios);
                } else {
                    printf("Primero debe buscar y seleccionar una habitacion antes de realizar una reserva.\n");
                }
                break;
            case 3:
                printf("Ingrese la cedula del cliente: ");
                scanf("%s", cedula);
                buscarReservaPorCedula(&numReserva, clientes, reservas, cedula);
                imprimirReserva(numReserva, reservas, habitaciones, precios);
                break;
            case 4:
                printf("Ingrese la cedula del cliente: ");
                scanf("%s", cedula);
                buscarReservaPorCedula(&numReserva, clientes, reservas, cedula);
                if (numReserva != -1) {
                    pagarReserva(numReserva, reservas, habitaciones, precios);
                } else {
                    printf("No se encontro ninguna reserva para la cedula ingresada.\n");
                }
                break;
            case 5:
                printf("Ingrese la cedula del cliente: ");
                scanf("%s", cedula);
                char nuevaHabitacion[40];
                char nuevoHotel[40];
                double nuevoPrecio;
                printf("Ingrese la nueva habitacion: ");
                scanf("%s", nuevaHabitacion);
                printf("Ingrese el nuevo hotel: ");
                scanf("%s", nuevoHotel);
                printf("Ingrese el nuevo precio: ");
                scanf("%lf", &nuevoPrecio);
                actualizarReservaEnArchivo(cedula, nuevaHabitacion, nuevoHotel, nuevoPrecio);
                break;
            case 6:
                printf("Ingrese la cedula del cliente: ");
                scanf("%s", cedula);
                buscarReservaEnArchivo(cedula);
                break;
        }
    } while (opcion != 7);

    return 0;
}