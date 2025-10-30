#include "sam.h"

#define LED_PIN   10   // PB10
#define PORT_GROUP 1   // Group[1] = PORTB

void setup() {
  // Enable the APB clock for the PORT module (covers both A and B)
  PM->APBBMASK.reg |= PM_APBBMASK_PORT;

  // Configure PB10 as output
  PORT->Group[PORT_GROUP].DIRSET.reg = (1 << LED_PIN);
}

void loop() {
  // LED ON
  PORT->Group[PORT_GROUP].OUTSET.reg = (1 << LED_PIN);
  delay(500);

  // LED OFF
  PORT->Group[PORT_GROUP].OUTCLR.reg = (1 << LED_PIN);
  delay(500);
}
