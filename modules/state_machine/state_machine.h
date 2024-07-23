#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "mbed.h"

// Definición de estados
enum State {
    INIT,
    READ_USER,
    READ_BOOK,
    TRANSACTION,
};

// Función para manejar el estado
void state_machine_init();
void state_machine_update();

#endif // STATE_MACHINE_H
