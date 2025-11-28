// Arduino code with potentiometer control
const int fanPin = 9;       // PWM pin connected to Darlington transistor base
const int potPin = A0;      // Potentiometer connected to analog pin
unsigned long lastOnTime = 0;
unsigned long currentTime = 0;
bool fanState = false;

void setup() {
    pinMode(fanPin, OUTPUT);
    pinMode(potPin, INPUT);
}

void loop() {
    currentTime = millis();
    
    // Every 15 seconds cycle
    if (currentTime - lastOnTime >= 15000) {
        fanState = true;
        lastOnTime = currentTime;
    }
    
    if (fanState && (currentTime - lastOnTime < 5000)) {
        // Fan is on for 5 seconds, speed controlled by potentiometer
        int potValue = analogRead(potPin);              // Read 0-1023
        int pwmValue = map(potValue, 0, 1023, 0, 255);  // Map to PWM 0-255
        analogWrite(fanPin, pwmValue);
    } else {
        // Fan is off
        analogWrite(fanPin, 0);
        fanState = false;
    }
    
    delay(10);  // Small delay for stability
}
