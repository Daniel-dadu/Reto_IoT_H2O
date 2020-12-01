#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ArduinoHttpClient.h>

const char* ssid = "INFINITUM5967_2.4"; //"TP-Link_E24A"; // nombre de la red a la que se va a conectar
const char* password =  "MR17KeGGAa";//password de la red
const char* device_secret_key = "d_sk_z2fGfe7ZSxcATXSbnfTBp5Nx"; //contraseña que se obtiene de la pagina de wia

char server[] = "api.wia.io"; // sitio web al que se enlaza
char path[] = "/v1/events"; // trayectoria de los eventos a almacenar
int port = 80; // puerto que atiende el servicio MQTT
int cont = 0;
 String inputString = "";
bool stringComplete = false;
float data1;

/*******************************
 * Inicialización
 */
WiFiClient client;
int status = WL_IDLE_STATUS;
HttpClient httpClient = HttpClient(client, server, port);

StaticJsonDocument<200> jsonBuffer;
JsonObject root = jsonBuffer.to<JsonObject>();
/*******************************
 * Inicialización
 */
void setup() {
  Serial.begin(9600); // Se habilita el puerto serial para detectar errores
  while (!Serial) {
    ; 
  }
  WiFi.begin(ssid, password);
  Serial.print("Attempting to connect to SSID: ");
  Serial.print(ssid);
  // attempt to connect to WiFi network:
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    // Connect to WPA/WPA2 network. Change this line if using open or WEP  network:
    // wait 5 seconds for connection:
    delay(5000);
  }
  /*******************************
 * Datos de la conección que serán impresos en la terminal
 */
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Connected");
 /*******************************
 * Datos de la conección que serán impresos en la terminal
 */ 
}


void loop() {
 char inChar;
 String data;
 //data = "";
 if (Serial.available()>0){
     inChar = (char)Serial.read();
    if (inChar != '*' || inChar != ' '){
      inputString += inChar;
    }
    
    if (inChar == '*' || inChar == ' '){
      stringComplete = true;
      cont++;
    }
  }
  if (stringComplete){
    data = inputString;
    stringComplete = false;
    inputString = "";
    data1 = data.toFloat();
    if (cont == 1){
      root["name"] = "hello-luz"; // nombre del evento a reportar
      root["data"] = data1; // valor a entregar
      postToWia(root);
    }
    if (cont == 2){
      root["name"] = "hello-luz2"; // nombre del evento a reportar
      root["data"] = data1; // valor a entregar
      postToWia(root);
    }
    if (cont == 3){
      root["name"] = "hello-pie"; // nombre del evento a reportar
      root["data"] = data1; // valor a entregar
      postToWia(root);
    }
    if (cont == 4){
      root["name"] = "hello-hum"; // nombre del evento a reportar
      root["data"] = data1; // valor a entregar
      postToWia(root);
    }
    if (cont == 5){
      root["name"] = "hello-temp"; // nombre del evento a reportar
      root["data"] = data1; // valor a entregar
      postToWia(root); // llamado a función que hace la cadena de información con la especificación de JSON
      cont = 0;
    }
 
  }
  
  //Serial.println(data1);
  
  delay(100);
  data = "";
  
}

/*******************************
 * Función que crea las cadenas para que Wia defina los elementos a guardar y mostrar
 */
void postToWia(JsonObject& data) {
  String dataStr = "";
  serializeJson(data, dataStr);
  httpClient.beginRequest();
  httpClient.post(path);
  httpClient.sendHeader("Content-Type", "application/json");
  httpClient.sendHeader("Content-Length", dataStr.length());
  httpClient.sendHeader("Authorization", "Bearer "  + String(device_secret_key));
  httpClient.beginBody();
  httpClient.print(dataStr);
  httpClient.endRequest();
}
