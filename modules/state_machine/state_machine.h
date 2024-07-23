#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "RFIDReader.h"
#include "LCDDisplay.h"
#include "Database.h"
#include "TransactionManager.h"

class StateMachine {
public:
    StateMachine();
    void run();
private:
    enum State {
        INICIO,
        LECTURA_USUARIO,
        LECTURA_LIBRO,
        PROCESAR_TRANSACCION,
        ACTUALIZAR_BASE_DATOS,
        FIN
    };

    State currentState;
    RFIDReader rfidReader;
    LCDDisplay lcd;
    Database db;
    TransactionManager transactionManager;

    void handleInicio();
    void handleLecturaUsuario();
    void handleLecturaLibro();
    void handleProcesarTransaccion();
    void handleActualizarBaseDatos();
    void handleFin();
};

#endif

