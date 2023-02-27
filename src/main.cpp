#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h> 


#define redlight 23
#define greenlight 22
#define yellowlight 21

const char * WIFI_SSID = "Wokwi-GUEST";
const char * WIFI_PASS = "";
char * endpoint = "https://ecse-three-led-api.onrender.com/api/state";



void setup() {
  
  pinMode(redlight, OUTPUT);
  pinMode(greenlight, OUTPUT);
  pinMode(yellowlight, OUTPUT);

  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
 

  if (WiFi.status()==WL_CONNECTED){
    HTTPClient http;
    String http_response;
    http.begin(endpoint);
    http.addHeader("X-API-KEY","Edwin#5368");
   

    int httpResponseCode = http.GET();

    if (httpResponseCode>0){
        Serial.print("HTTP Response Code: ");
        Serial.println(httpResponseCode);

        Serial.print("Response from server: ");
        http_response = http.getString();
        Serial.print(http_response);
    }
  else{
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    
  }
  http.end();

  StaticJsonDocument<1024> doc;

  DeserializationError error = deserializeJson(doc, http_response);
  if (error){
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
      }

    const char* user = doc["user"];
    const char* id = doc["_id"];
    bool switch1 = doc["light_switch_1"];
    bool switch2 = doc["light_switch_2"];
    bool switch3 = doc["light_switch_3"];
   

    Serial.println("");

    Serial.print("Red Light STOP!: ");
    Serial.println(switch1);

    Serial.print("Green Light GO!: ");
    Serial.println(switch2);

    Serial.print("Yellow Light PAUSE: ");
    Serial.println(switch3);
    Serial.println("");

    if (switch1==1)
    {
      digitalWrite(redlight,HIGH);}  else {

      digitalWrite(redlight,LOW);
    }
        if (switch2==1){
      digitalWrite(greenlight,HIGH);}else {
      digitalWrite(greenlight,LOW);
    }

        if (switch3==1){
      digitalWrite(yellowlight,HIGH);
    }
      else{
      digitalWrite(yellowlight,LOW);
    }

  }
 
}