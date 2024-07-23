#ifndef DATABASE_SERIAL_COM_H
#define DATABASE_SERIAL_COM_H

// Declaración de funciones
void db_init();
void db_query_user(const char* userID);
void db_query_book(const char* bookID);

#endif