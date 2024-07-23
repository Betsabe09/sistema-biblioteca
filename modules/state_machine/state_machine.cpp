#include "mbed.h"

#include "state_machine.h"
#include "rfid_reader.h"
#include "lcd_control.h"
#include "database_serial_com.h"

static State currentState = INIT;

void state_machine_init() {
    currentState = INIT;
}

void state_machine_update() {
    switch (currentState) {
        case INIT:
            lcd_display_message("Initializing...");
            currentState = READ_USER; // Cambio de estado por ejemplo
            break;
        case READ_USER:
            if (rfid_read_card()) {
                db_query_user(rfid_get_card_id());
                currentState = READ_BOOK;
            }
            break;
        case READ_BOOK:
            // Lógica para leer el libro
            currentState = TRANSACTION;
            break;
        case TRANSACTION:
            // Lógica de transacción
            lcd_display_message("Transaction Complete");
            currentState = INIT;
            break;
    }
}