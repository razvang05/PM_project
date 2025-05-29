#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <stdint.h>

void uart_init();
uint8_t uart_available();
char uart_read();
bool is_bluetooth_connected();
void control_bluetooth();

#endif
