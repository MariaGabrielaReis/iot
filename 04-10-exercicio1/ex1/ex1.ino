#include <WiFi.h>
#include <HTTPClient.h>
#include <time.h>

const char* ssid = "rede";
const char* pwd = "senha";

// configurações para mexer com dada/hora
char* ntpServer = "pool.ntp.org";
long gmtOffset_sec = 0;
int daylightOffset_sec = 0;

struct tm timeInfo;

String serverName = "http://postman-echo.com/"; // URL do servidor

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pwd);
  Serial.print("Conectando...");

  // enquanto a conexão não estabelece...  
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.print("\n Conectado ao WiFi com o IP: ");
  Serial.println(WiFi.localIP());

  // configurando data/hora
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  if(!getLocalTime(&timeInfo)){
    Serial.println("Acesso ao ntp falhou");
  }
}

void loop(){
  bool isFiveMultipleTime = timeInfo.tm_min % 5 == 0;
  if(WiFi.status() == WL_CONNECTED && isFiveMultipleTime) {   
    if(!getLocalTime(&timeInfo)){
      Serial.println("Acesso ao ntp falhou");
    }
      
    // GET
    HTTPClient http;
    String tmp = serverName + "get?temp=21.0&minutes=" + timeInfo.tm_min;
    http.begin(tmp.c_str());
    int httpCode = http.GET();

    if(httpCode > 0) {
      Serial.print("Status code: ");
      Serial.println(httpCode);
      String payload = http.getString();
      Serial.print("Response: ");
      Serial.println(payload);
    } else {
      Serial.println("Erro! Sem conexão...");  
    }

    delay(30000);
  }  
}
