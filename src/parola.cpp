#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "lcd.h"
#include "servo.h"
#include "parola.h"
#include <Arduino.h>


#define BUTON_ROSU PD5
#define BUTON_VERDE PD4

bool usaDeschisa = false;
String parola = "";
const String parolaCorecta = ".--.";

//---------- Afișează parola pe LCD ----------
void afiseazaParola() {

    lcd_clear();
    lcd_set_cursor(0, 0);
    lcd_print("   Smart Home");
    lcd_set_cursor(0, 1);
    lcd_print("Parola: ");
    for (uint8_t i = 0; i < parola.length(); i++) {
        lcd_write(parola[i]);
    }

}

void ParolaMorse() {
    bool rosu = !(PIND & (1 << PD5));
    bool verde = !(PIND & (1 << PD4));
    int timp = 0;

    if (rosu && !verde) {
        _delay_ms(100);
        while (!(PIND & (1 << PD5))) {
        timp++;
        _delay_ms(10);
        }
        parola += (timp < 5) ? "." : "-";
        afiseazaParola();

    }

    if (verde && !rosu) {

    _delay_ms(100);

    if (!usaDeschisa && parola == parolaCorecta) {

        lcd_clear();
        lcd_set_cursor(0, 0);
        lcd_print("Parola corecta");
        servo_set_angle_timer1(1, 90);
        usaDeschisa = true;
    } else if (!usaDeschisa) {

        lcd_clear();
        lcd_set_cursor(0, 0);
        lcd_print("Parola gresita");
        _delay_ms(1000);
        afiseazaParola();

    } else {

        servo_set_angle_timer1(1,0);
        lcd_clear();
        lcd_set_cursor(0, 0);
        lcd_print("   Smart Home");
        usaDeschisa = false;
    }

    parola = "";
    }
}