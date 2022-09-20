#include <WiFi.h>
// #include <HTTPClient.h>

const char* ssid = "Maby phone";
const char* pwd = "head7132";

void setup(){
  Serial.begin(115200);

  WiFi.begin(ssid, pwd);
  Serial.println("Conectando... \n");

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n Conectando ao wifi com o IP: ");
  Serial.print(WiFi.localIP());
}

void loop(){
  
}
