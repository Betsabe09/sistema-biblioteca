#include "rfid_reader.h"

// Inicializar SPI y pines
SPI rfid_spi(RFID_SPI_MOSI, RFID_SPI_MISO, RFID_SPI_SCK);
DigitalOut rfid_rst(RFID_RST_PIN, 1);
DigitalOut rfid_cs(RFID_CS_PIN, 1);

// Función para inicializar el módulo RFID
void rfid_init() {
    rfid_spi.format(8, 3); // Configuración SPI: 8 bits, modo 3
    rfid_spi.frequency(1000000); // Frecuencia SPI: 1 MHz
    rfid_rst = 0;
    wait_us(1000); // Esperar 1 ms
    rfid_rst = 1;
    wait_us(1000); // Esperar 1 ms
    rfid_reset();
}

// Función para resetear el módulo RFID
void rfid_reset() {
    rfid_write(0x01, 0x0F); // Resetear el módulo
    wait_us(1000);
}

// Función para escribir en un registro
void rfid_write(uint8_t reg, uint8_t value) {
    rfid_cs = 0;
    rfid_spi.write(reg);
    rfid_spi.write(value);
    rfid_cs = 1;
}

// Función para leer de un registro
uint8_t rfid_read(uint8_t reg) {
    uint8_t value;
    rfid_cs = 0;
    rfid_spi.write(reg);
    value = rfid_spi.write(0x00);
    rfid_cs = 1;
    return value;
}

// Función para solicitar información
void rfid_request(uint8_t mode, uint8_t *response) {
    rfid_write(0x0C, mode); // Enviar el comando de solicitud
    wait_us(1000);
    *response = rfid_read(0x0A); // Leer la respuesta
}

// Función para leer la tarjeta RFID
void rfid_read_card(uint8_t *data, uint8_t *size) {
    uint8_t status;
    uint8_t i;
    uint8_t len;
    
    // Solicitar la tarjeta
    rfid_request(0x26, &status);
    
    if (status == 0x00) {
        // Leer los datos de la tarjeta
        for (i = 0; i < 16; i++) {
            data[i] = rfid_read(0x09 + i);
        }
        *size = 16;
    } else {
        *size = 0;
    }
}
