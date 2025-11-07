#include <avr/io.h>
#include <avr/interrupt.h>

void setup() {
    // --- Configure PB0 (Arduino pin 8) as input with pull-up ---
    DDRB &= ~(1 << DDB0);     // PB0 as input
    PORTB |= (1 << PORTB0);   // Enable internal pull-up resistor

    // --- Configure PB5 (Arduino pin 13) as output for testing ---
    DDRB |= (1 << DDB5);

    // --- Enable Pin Change Interrupt for PB0 ---
    PCICR |= (1 << PCIE0);    // Enable pin change interrupt for PCINT[7:0] (Port B)
    PCMSK0 |= (1 << PCINT0);  // Enable interrupt for PB0 (PCINT0)

    sei(); // Enable global interrupts
}

void loop() {
    // Main loop - do nothing, waiting for interrupt
}

// --- Interrupt Service Routine for Port B Pin Change ---
ISR(PCINT0_vect) {
    // Check if PB0 is LOW (falling edge)
    if (!(PINB & (1 << PINB0))) {
        // Example: toggle LED on PB5 (Arduino pin 13)
        PORTB ^= (1 << PORTB5);
    }
}
