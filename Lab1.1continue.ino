void setup() {
 Serial.begin(9600);
 while(!Serial);

  // put your setup code here, to run once:
}
void loop() {
 int raw=analogRead(A1);
 float voltage = raw*(3.3/4095.0);

 Serial.print("Analog value:");
 Serial.print(raw);
 Serial.print("->Voltage:");
 Serial.print(voltage,3);
 Serial.println("V");

 delay(1000);

}
