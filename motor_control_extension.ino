#define enB 10
#define in3 8
#define in4 9
#define button 4
#define ledPin 13 // LED for direction indication

int rotDirection = 0;
int pressed = false;

void setup() {
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(button, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

  // Set initial rotation direction
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(ledPin, LOW);
}

void loop() {
  int potValue = analogRead(A0); // Read potentiometer value
  int pwmOutput = map(potValue, 0, 1023, 0 , 255); // Map the potentiometer value from 0 to 255
  analogWrite(enB, pwmOutput); // Send PWM signal to L298N Enable pin

  // Read button - Debounce
  if (digitalRead(button) == HIGH) {
    pressed = !pressed;
    delay(200); // Debounce delay
    while (digitalRead(button) == HIGH); // Wait for button release
  }

  // If button is pressed - change rotation direction
  if (pressed == true && rotDirection == 0) {
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    digitalWrite(ledPin, HIGH); // LED ON
    rotDirection = 1;
  }
  // If button is not pressed - change rotation direction
  if (pressed == false && rotDirection == 1) {
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    digitalWrite(ledPin, LOW); // LED OFF
    rotDirection = 0;
  }

  // Serial monitoring
  Serial.print("Potentiometer: ");
  Serial.print(potValue);
  Serial.print(" | PWM: ");
  Serial.print(pwmOutput);
  Serial.print(" | Direction: ");
  Serial.println(rotDirection ? "Reverse" : "Forward");

  delay(50);
}