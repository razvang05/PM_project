#include <avr/io.h>
#include <util/delay.h>
#include "buzzer.h"


// ---------- Buzzer ----------
void generate_tone(uint16_t frequency, uint16_t duration_ms) {

  // calculăm timpul de întârziere pentru fiecare ciclu
  uint16_t delay_us = 1000000UL / (2 * frequency);
  // calculăm numărul total de cicluri necesare pentru durata specificată
  uint32_t total_cycles = (uint32_t)duration_ms * 1000UL / (2 * delay_us);


    for (uint32_t i = 0; i < total_cycles; i++) {
        // Toggle buzzer pin (D3)
        PORTD |= (1 << PD3);
        _delay_us(delay_us);
        // Set buzzer pin low
        PORTD &= ~(1 << PD3);
        _delay_us(delay_us);
    }
}