#ifndef SERVO_H
#define SERVO_H
#include <stdint.h>

void servo_set_angle_timer1(uint8_t servo, uint8_t angle);
void pwm_init_timer1();
void setup_servo_d11();
void pulse_servo_d11(uint8_t angle);

#endif // SERVO_H
