//#include <TinyGPS++.h>
#include <Wire.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <Arduino_JSON.h>

//#define RXD2 16
//#define TXD2 17
//HardwareSerial neogps(1);
//char   datoCmd = 0;

//TinyGPSPlus gps;

const char* ssid = "IoTB";
const char* password =  "inventaronelVAR";

const char* serverNameSoundGet = "http://10.8.17.90:3000/api/sound/1";

const char* serverNameSoundPost = "https://pillwise-medicine.vercel.app/api/check";

//String lat = "-58.454213";
//String lon = "-34.549659";

int inicio;
int antTiempo;

//------------------------------------------------------------------------------------------------------------------------------------------

void setup() 
{ 
  inicio = millis();
  antTiempo = millis();
  delay(10);
  Serial.begin(115200);
  //neogps.begin(9600, SERIAL_8N1, RXD2, TXD2);
  delay(2000);
  WiFi.begin(ssid, password);

  Serial.print("Conectando...");
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(500);
    Serial.print(".");
  }
  Serial.print("Conectado con éxito, mi IP es: ");
  Serial.println(WiFi.localIP());
}

//------------------------------------------------------------------------------------------------------------------------------------------

void loop(){
 if (WiFi.status()== WL_CONNECTED){
    sendReieved(serverNameSoundPost);

  }
  else {
    Serial.println("WiFi Disconnected");
  }



/* //GPS no funciona
  if((antTiempo + 5000) > inicio){
    Visualizacion_Serial();
    sendLatLon("{\"sensor\":\"GPS\",\"Lon\":\"" + String(lat) + "\",\"Lat\":\"" + String(lon) + "\"}", "http://10.8.8.13:3000/api/hardware");
    inicio = antTiempo;
  }
  
  antTiempo += millis();

  */
}




void Visualizacion_Serial(void){ 
   
  if (gps.location.isValid()){  
    Serial.print("Lat: ");
    Serial.println(gps.location.lat(),6);
    Serial.print("Lng: ");
    Serial.println(gps.location.lng(),6);  
    Serial.print("Speed: ");
    Serial.println(gps.speed.kmph());    
    Serial.print("SAT:");
    Serial.println(gps.satellites.value());
    Serial.print("ALT:");   
    Serial.println(gps.altitude.meters(), 0);     

    Serial.print("Date: ");
    Serial.print(gps.date.day()); Serial.print("/");
    Serial.print(gps.date.month()); Serial.print("/");
    Serial.println(gps.date.year());

    Serial.print("Hour: ");
    Serial.print(gps.time.hour()); Serial.print(":");
    Serial.print(gps.time.minute()); Serial.print(":");
    Serial.println(gps.time.second());
    Serial.println("---------------------------");
  }
  else
  {
    Serial.println("Sin señal gps");  
  }  

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

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);
  
  // If you need Node-RED/server authentication, insert user and password below
  //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}


void sendReieved(String url){
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status

    String datos_a_enviar = "{\"message\":\"recibido\"}";
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

bool Sonar(){
  sensorReadings = httpGETRequest(serverNameSouondGet);
  JSONVar myObject = JSON.parse(sensorReadings);

  // JSON.typeof(jsonVar) can be used to get the type of the var
  if (JSON.typeof(myObject) == "undefined") {
    Serial.println("Parsing input failed!");
    return false;
  }
  Serial.println(myObject);
  return myObject["sonando"];
}