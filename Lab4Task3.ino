// Exercise 3: MOSFET with Potentiometer Speed Control
const int fanPin = 9;       // PWM pin connected to MOSFET gate (via resistor)
const int potPin = A0;      // Potentiometer output connected to A0
unsigned long previousMillis = 0;
bool fanOn = false;

void setup() {
    pinMode(fanPin, OUTPUT);
    pinMode(potPin, INPUT);
}

void loop() {
    unsigned long currentMillis = millis();
    
    // Timing: Fan on for 6 seconds, off for 10 seconds (16 second cycle)
    if (fanOn) {
        // Fan is ON for 6 seconds
        if (currentMillis - previousMillis >= 6000) {
            fanOn = false;
            previousMillis = currentMillis;
            analogWrite(fanPin, 0);  // Turn off fan
        } else {
            // Read potentiometer and control speed
            int potValue = analogRead(potPin);              // 0-1023
            int pwmValue = map(potValue, 0, 1023, 0, 255);  // Map to PWM 0-255
            analogWrite(fanPin, pwmValue);
        }
    } else {
        // Fan is OFF for 10 seconds
        if (currentMillis - previousMillis >= 10000) {
            fanOn = true;
            previousMillis = currentMillis;
        }
    }
    
    delay(10);  // Small delay for stability
}
