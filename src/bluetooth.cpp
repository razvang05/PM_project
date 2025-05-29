#include <avr/io.h>
#include "bluetooth.h"
#include "servo.h"
#include <util/delay.h>


#define BT_STATE_PIN PB5  // D13
#define BAUD 9600
#define MYUBRR ((F_CPU / 16 / BAUD) - 1)

void uart_init() {
  uint16_t ubrr = MYUBRR;
  UBRR0H = (uint8_t)(ubrr >> 8);
  UBRR0L = (uint8_t)ubrr;
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);           // Enable RX, TX
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);         // 8 data bits, 1 stop bit
}

uint8_t uart_available() {
  return (UCSR0A & (1 << RXC0)); // Returnează 1 dacă datele au sosit
}

char uart_read() {
  while (!(UCSR0A & (1 << RXC0))); // Așteaptă date
  return UDR0;
}

bool is_bluetooth_connected() {
  return (PINB & (1 << BT_STATE_PIN));  // HIGH = conectat
}

void control_bluetooth() {
  if (uart_available()) {
    
    char cmd = uart_read();

    switch (cmd) {
      case 'A': servo_set_angle_timer1(2,10);_delay_ms(100); break;
      case 'B': servo_set_angle_timer1(2,0);_delay_ms(100); break;
      case 'C': servo_set_angle_timer1(1, 90); break;
      case 'D': servo_set_angle_timer1(1, 0); break;
      case 'E': pulse_servo_d11(90); break;
      case 'F': pulse_servo_d11(40); break;
      case 'G': PORTB |= (1 << PB4); break;
      case 'H': PORTB &= ~(1 << PB4); break;
    }
  }
}
