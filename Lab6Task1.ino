#include <SPI.h>

// Define the Slave Select pin for the Micro
const int SS_PIN = 10; 

// Data to send
byte dataToSend = 0x55; 

void setup() {
  Serial.begin(9600);
  // Wait for Serial Monitor to open (useful for Micro)
  while (!Serial) {
    ; 
  }

  pinMode(SS_PIN, OUTPUT);
  digitalWrite(SS_PIN, HIGH); // Start with Slave deselected

  SPI.begin(); // Initializes SPI on Micro's specific MO/MI/SCK pins

  // Configure SPI: 1 MHz, MSB First, Mode 0
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

  Serial.println("SPI Master (Arduino Micro) Ready!");
}

void loop() {
  Serial.print("Sending: 0x");
  Serial.print(dataToSend, HEX);

  // Select the slave
  digitalWrite(SS_PIN, LOW);

  // Send data and receive response
  byte received = SPI.transfer(dataToSend);

  // Deselect the slave
  digitalWrite(SS_PIN, HIGH);

  Serial.print(" | Received: 0x");
  Serial.println(received, HEX);

  // Toggle data between 0x55 (01010101) and 0xAA (10101010)
  if (dataToSend == 0x55) {
    dataToSend = 0xAA;
  } else {
    dataToSend = 0x55;
  }

  delay(500); // Slow down to see on oscilloscope
}
