#ifndef BUZZER_H
#define BUZZER_H

#include <stdint.h>

void generate_tone(uint16_t frequency, uint16_t duration_ms);

#endif // BUZZER_H