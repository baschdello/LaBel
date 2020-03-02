#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
  DDRB   |=  (1 << PB0);														// MOTOR_EN für Polygon-Motor-Einheit
  DDRB   |=  (1 << PB2);														// PWM-Takt Ausgang
  DDRD   &= ~(1 << PB1);														// MOTOR_ON als Start-Anforderung von CONTROLLER1


  TCCR0A = (1 << COM0A0)|									// Set OC0B on Compare Match (OCR0B), clear on TOP (OCR0A)
    (1 << WGM00 ) | (1 << WGM01 ) ;									// Fast PWM mit OCR0A = TOP
  TCCR0B = (1 << WGM02 );

  OCR0A  = 0x2;																// TOP = 17 (zählt von 0 bis 17 = 18 Takte)
  OCR0B  = 0x00;																// Ab 0 wird das Ausgabe-Bit gesetzt

  TCCR0B |= (1<<CS02)|(1 << CS00);														// Takt = CLK/1 (kein Prescaler), start PWM
}

void loop() {
  // put your main code here, to run repeatedly:
  if( !(PINB & (1 << PB1)) )
  {
    //Polygon-Motor laufen lassen
    PORTB &= ~(1 << PB0);
  }
  else
  {
    //Polygon-Motor stoppen
    PORTB |= (1 << PB0);
  }
}
