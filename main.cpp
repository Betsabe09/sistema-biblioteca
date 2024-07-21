#include "mbed.h"
#include "Display_I2C.h"
#include "MFRC522.h"

// Configura los pines I2C y la dirección del LCD
Display_I2C lcd(PB_11, PB_10);

MFRC522 rfid(PA_7, PA_6, PA_5, PB_6, PB_7);

void displayRFIDId(const char* id) {
    lcd.clear(); // Limpiar la pantalla
    lcd.setCursor(0, 0); // Establecer el cursor en la primera línea
    lcd.print("ID: "); // Imprimir el texto "ID: "
    lcd.print(id); // Imprimir el ID de la tarjeta
}

int main() {
    // Inicializar el LCD
    lcd.initialize();
    lcd.setBacklight(true); // Encender el backlight del LCD
    
    // Inicializar el módulo RFID
    rfid.PCD_Init(); // Inicializa el módulo RFID
    
    lcd.print("Escanee tarjeta");

    while (true) {
        // Detectar si hay una tarjeta presente
        if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
            // Obtener el ID de la tarjeta
            char id[32]; // Asegúrate de que el tamaño del buffer sea suficiente para el ID
            snprintf(id, sizeof(id), "%02X%02X%02X%02X",
                     rfid.uid.uidByte[0], rfid.uid.uidByte[1],
                     rfid.uid.uidByte[2], rfid.uid.uidByte[3]);
            
            displayRFIDId(id); // Mostrar el ID en el LCD
            
            // Esperar un segundo antes de la próxima lectura
            ThisThread::sleep_for(1000ms);
        }
    }
}