void setup() {
  Serial.begin(9600);
  while(!serial);  // giving time to Serial Monitor to open
  Serial.println(" Simple Calculator ");
}
float readFloat() {
  while (Serial.available() == 0);     // Wait for input
  float value = Serial.parseFloat();   // getting floating-point number by user
  while (Serial.available()) Serial.read(); // I removed any stored char
  return value;
}
char readOperator() {
  while (Serial.available() == 0);   // Wait for input
  char op = Serial.read();           // Read one character  by user (+, -, *, /)
  while (Serial.available()) Serial.read(); // Clear character such as newline
  return op;
}
void loop() {
  Serial.println("\nEnter first number:");
  float num1 = readFloat();
  Serial.println("Enter operator (+, -, *, /):");
  char op = readOperator();
  Serial.println("Enter second number:");
  float num2 = readFloat();
  Serial.print("Result: ");
  switch (op) {
    case '+':
      Serial.println(num1 + num2);
      break;
    case '-':
      Serial.println(num1 - num2);
      break;
    case '*':
      Serial.println(num1 * num2);
      break;
    case '/':
      if (num2 != 0)
        Serial.println(num1 / num2);
      else
        Serial.println("Error! Division by zero");
      break;
    default:
      Serial.println("Invalid operator!");
      break;
  }
  Serial.println("------------------------------");
}