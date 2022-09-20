#include <WiFi.h>
#include <HTTPClient.h>
#include "time.h"

const char* ssid = ""; // nome da conexão
const char* pwd = ""; //senha da conexão

// configurações para mexer com dada/hora
char* ntpServer = "pol.ntp.org";
long gmtOffset_sec = 0;
int daylightOffset_sec = 0;
int horaBrasil = -10800;

String serverName = "http://postman-echo.com/get?"; // URL do servidor

// simulação de coleta de temperatura e umidade
float TEMPERATURA = 12.0;
float UMIDADE = 27.0;

void setup() {
  Serial.begin();
  WiFi.begin(ssid, pwd);
  Serial.println("Conectando...");

  // enquanto a conexão não estabelece...  
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n Conectado ao WiFi com o IP: ");
  Serial.print(WiFi.localIP());

  // configurando data/hora
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  // para usar horas do Brasil
  // configTime(gmtOffset_sec, horaBrasil, ntpServer);
  
  struct tm timeInfo;
  if(!gmtLocalTime(&timeInfo)){
    Serial.println("Acesso ao ntp falhou");
  }
  Serial.println(&timeInfo, "%A %B %d %Y %H:%M:%S")
}


void loop(){
  if(WiFi.status() != WL_CONNECTED) {
    HTTPClient http;
    
    String tmp = serverName + "temp=" + TEMPERATURA + "&umidade=" + UMIDADE;
    
    http.begin(tmp.c_str());
    int httpCode = http.GET();

    if(httpCode > 0) {
      Serial.println(TEMP);
      Serial.println("Status code: ");
      Serial.print(httpCode);
      String payload = http.getString();
      Serial.print("Response: ");
      Serial.println(payload);
    } else {
      Serial.println("Erro! Sem conexão...");  
    }

    // incremento das coletas
    TEMPERATURA = TEMPERATURA + 0.25;
    UMIDADE = UMIDADE + 0.11;
    delay(10000);
  }  
}
