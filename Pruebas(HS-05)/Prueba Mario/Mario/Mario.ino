
#define ledPin 2
#define buzzerPin 23

void setup() {
  // Set pin 2 as an output.
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Initialize the serial port.
  Serial.begin(9600);
  Serial.println("Iniciando");
  sing(1, buzzerPin);
}

void loop() {
  // If the serial port receives the string "prender", turn on pin 2.
  while (Serial.available() == 0) {} 
  String line = Serial.readString();
  line.trim();    
  
  if (line == "prender") {
    digitalWrite(ledPin, HIGH);
  }  
  
  else if (line == "apagar") {
    digitalWrite(ledPin, LOW);
  }

  else if (line == "buzzer"){
    sing(1, buzzerPin);
    sing(2, buzzerPin);
    sing(3, buzzerPin);
  }
  else
  {
    Serial.print(line);
  }

  
}
