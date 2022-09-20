#include <WiFi.h>
#include <PubSubClient.h>
#include "time.h"

char* ssid = "Bruno";
char* pwd = "123456789";
char* mqttServer = "test.mosquitto.org";

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

#define LED 2

void setup() {
 pinMode(LED, OUTPUT);
 digitalWrite(LED, LOW); 
 Serial.begin(115200);
 WiFi.begin(ssid, pwd);
  connectWifi();
  mqttClient.setServer(mqttServer, 1883);
  mqttClient.setCallback(callback);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!mqttClient.connected()){
    connectMqtt();
  }
  mqttClient.loop();
}

void connectWifi(){
  Serial.println("Conectando...");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado ao WiFi com o IP: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length){
  Serial.print(topic);
  Serial.print("");
  String msg;
  for(int i=0; i < length; i++){
    msg +=(char)message[i];
  }
  Serial.println(msg);

  // on, off
  if(msg[1] == 'n'){
    digitalWrite(LED, HIGH);  
  } else {
    digitalWrite(LED, LOW);  
  }
}

void connectMqtt(){
  if(!mqttClient.connected()){
    if(mqttClient.connect("Maby21")) {
      Serial.println("Conectou!");
      mqttClient.subscribe("iot/maby/");
    } else {
      Serial.println("Sem conexão...");
      delay(5000);
    }
  }
}
