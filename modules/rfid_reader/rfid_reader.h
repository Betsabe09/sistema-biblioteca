#ifndef RFID_READER_H
#define RFID_READER_H

#include "mbed.h"

// Definir pines
#define RFID_RST_PIN     PC_7
#define RFID_CS_PIN      PA_4
#define RFID_SPI_MOSI    PA_7
#define RFID_SPI_MISO    PA_6
#define RFID_SPI_SCK     PA_5

// Inicializar el SPI y el pin de reset
extern SPI rfid_spi;
extern DigitalOut rfid_rst;
extern DigitalOut rfid_cs;

// Funciones
void rfid_init();
void rfid_reset();
void rfid_write(uint8_t reg, uint8_t value);
uint8_t rfid_read(uint8_t reg);
void rfid_request(uint8_t mode, uint8_t *response);
void rfid_read_card(uint8_t *data, uint8_t *size);

#endif
