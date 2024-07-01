void buscarPorTamano(int *numHabitacion, char habitaciones[][3][40], double precios[]);
void buscarHotel(int *numHabitacion, char habitaciones[][3][40], double precios[]);
void realizarReserva(int numHabitacion, char habitaciones[][3][40], char clientes[][2][40], int reservas[][3], double precios[]);
void buscarReservaPorCedula(int *numReserva, char clientes[][2][40], int reservas[][3], char *cedula);
void imprimirReserva(int numReserva, int reservas[][3], char habitaciones[][3][40], double precios[]);
void pagarReserva(int numReserva, int reservas[][3], char habitaciones[][3][40], double precios[]);
void guardarReservaEnArchivo(int numHabitacion, char habitaciones[][3][40], char cliente[], char cedula[], double precios[]);
void actualizarReservaEnArchivo(char cedula[], char nuevaHabitacion[], char nuevoHotel[], double nuevoPrecio);
void buscarReservaEnArchivo(char cedula[]);