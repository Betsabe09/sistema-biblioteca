#include "database_serial_com.h"
#include "mbed.h"
#include <cstring>

static UnbufferedSerial serial(PA_2, PA_3, 9600); // TX, RX, baud rate

void db_init() {
    serial.format(8, SerialBase::None, 1);
}

void db_query_user(const char* userID) {
    serial.write("QUERY_USER ", 11);
    serial.write(userID, strlen(userID));
    serial.write("\n", 1);
    // Espera la respuesta y maneja la lógica
}

void db_query_book(const char* bookID) {
    serial.write("QUERY_BOOK ", 11);
    serial.write(bookID, strlen(bookID));
    serial.write("\n", 1);
    // Espera la respuesta y maneja la lógica
}