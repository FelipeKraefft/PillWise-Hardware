#include <SoftwareSerial.h>

SoftwareSerial hc05(0, 1);  // RX, TX (Pines utilizados para la comunicación con el módulo HC-05)

// Reemplaza con los detalles de tu backend
const char* serverAddress = "10.4.13.54/api/hardware";
const int serverPort = 3000;

void setup() {
  Serial.begin(9600);
  hc05.begin(9600);  // Inicializar la comunicación con el módulo HC-05
  delay(10);

  Serial.println("Conexión Bluetooth establecida");
}

void loop() {
  if (hc05.available()) {
    String data = hc05.readStringUntil('\n');
    Serial.println("Datos recibidos por Bluetooth: " + data);

    // Enviar los datos al backend
    sendDataToBackend(data);
  }
}

void sendDataToBackend(const String& data) {
  // Conectar al servidor
  hc05.print("AT\r\n");
  delay(100);
  hc05.print("AT+CIPSTART=\"TCP\",\"");
  hc05.print(serverAddress);
  hc05.print("\",");
  hc05.print(serverPort);
  hc05.print("\r\n");
  delay(1000);

  // Enviar los datos al backend
  hc05.print("AT+CIPSEND=");
  hc05.print(data.length());
  hc05.print("\r\n");
  delay(100);
  hc05.print(data);
  delay(100);

  // Cerrar la conexión
  hc05.print("AT+CIPCLOSE\r\n");
  delay(100);

  Serial.println("Datos enviados al backend");
}
