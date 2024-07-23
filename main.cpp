#include "mbed.h"
#include "rfid_reader.h"

UnbufferedSerial pc(PA_3, PA_2, 9600); // Para depuración

int main() {
    uint8_t card_data[16];
    uint8_t data_size;
    
    // Inicializa el módulo RFID
    rfid_init();
    
    // Imprime un mensaje de inicio
    pc.write("RFID Reader Initialized\n", 25);
    
    while (true) {
        // Lee la tarjeta RFID
        rfid_read_card(card_data, &data_size);
        
        // Si se detecta una tarjeta
        if (data_size > 0) {
            pc.write("Card ID: ", 9);
            
            // Envia el ID de la tarjeta
            for (int i = 0; i < data_size; i++) {
                char buf[4];
                int len = sprintf(buf, "%02X ", card_data[i]);
                pc.write(buf, len);
            }
            
            pc.write("\n", 1);
        }
        
        ThisThread::sleep_for(1s);
    }
}