#include <avr/io.h>
#include <avr/interrupt.h>

void setup() {
    // --- Configure PB5 (Arduino pin 13) as output ---
    DDRB |= (1 << DDB5);

    // --- Configure Timer1 in CTC mode ---
    TCCR1A = 0; // Normal port operation, WGM bits handled in TCCR1B
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // CTC mode, prescaler 1024

    OCR1A = 15625; // Compare match value for 1 Hz (1 second)

    TIMSK1 = (1 << OCIE1A); // Enable Timer1 Compare Match A interrupt

    sei(); // Enable global interrupts
}

void loop() {
    // Main loop does nothing, LED toggling handled in ISR
}

// --- Timer1 Compare Match A ISR ---
ISR(TIMER1_COMPA_vect) {
    PORTB ^= (1 << PORTB5); // Toggle LED on pin 13
}