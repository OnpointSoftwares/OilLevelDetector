const int waterSensorPin = A0;
const int ledPin = 13;         

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int waterLevel = analogRead(waterSensorPin);

  Serial.print("Water level: ");
  Serial.println(waterLevel);
 if (waterLevel > 500) {
    Serial.println("Water level is high!");
    digitalWrite(ledPin, HIGH); 
  } else {
    Serial.println("Water level is low.");
    digitalWrite(ledPin, LOW);  
  }

  delay(1000);
}
