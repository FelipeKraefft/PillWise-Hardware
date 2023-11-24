#include <HTTPClient.h>
#include <WiFi.h>

const char* ssid = "IoTB";
const char* password =  "inventaronelVAR";

String lat = "10";
String lon = "10";

int inicio;
int antTiempo;

void setup() {
  inicio = millis();
  antTiempo = millis();
  delay(10);
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Conectando...");
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(500);
    Serial.print(".");
  }
  Serial.print("Conectado con éxito, mi IP es: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  if((antTiempo + 5000) > inicio){
    sendLatLon("{\"sensor\":\"GPS\",\"Lon\":\"24.25\",\"Lat\":\"49.54\"}", "http://10.8.8.13:3000/api/hardware");
    inicio = antTiempo;
  }
  
  antTiempo += millis();
}


void sendLatLon(String datos_a_enviar, String url){
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status

    HTTPClient http;

    http.begin(url);        //Indicamos el destino
    http.addHeader("Content-Type", "application/json"); //Preparamos el header text/plain si solo vamos a enviar texto plano sin un paradigma llave:valor.

    int codigo_respuesta = http.POST(datos_a_enviar);   //Enviamos el post pasándole, los datos que queremos enviar. (esta función nos devuelve un código que guardamos en un int)

    if(codigo_respuesta>0){
      Serial.println("Código HTTP ► " + String(codigo_respuesta));   //Print return code

      if(codigo_respuesta == 200){
        String cuerpo_respuesta = http.getString();
        Serial.println("El servidor respondió ▼ ");
        Serial.println(cuerpo_respuesta);

      }
    }
    else{
     Serial.print("Error enviando POST, código: ");
     Serial.println(codigo_respuesta);
    }
    http.end();  //libero recursos

  }
  else{
     Serial.println("Error en la conexión WIFI");
  }
  
}
