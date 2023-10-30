
#define ledPin 2
#define buzzerPin 9

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

  else if (line == "mario"){
    sing(1, buzzerPin);
  }
  else if (line == "buzzer"){
    tone(buzzerPin, 1000);
    delay(3000);
    noTone(buzzerPin);
  }
  
  else
  {
    Serial.print(line);
  }

  
}
