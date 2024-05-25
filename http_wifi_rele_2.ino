//gerencia o sinal de Wifi
#include <WiFi.h>
#include <WiFiClient.h>
//gera servico http no esp32
#include <WebServer.h>
#include <string.h>
//definição nome, senha e canal do wifi
//#define WIFI_SSID "devsenai"
//#define WIFI_PASSWORD "sesisenai"
//#define WIFI_CHANNEL 6
const char *ssid = "seu-nomettt";
const char *password = "987654321";
IPAddress local_IP(192, 168, 4, 22);
IPAddress gateway(192, 168, 4, 9);
IPAddress subnet(255, 255, 255, 0);

//variaveis para controle do acendimento
int acende =0;
int acendeT =0;
int tempAcende =0;
int pisca =0;
//instância da biblioteca WebServer e passo a porta
WebServer server(80);
//pino de acionamento rele
const int pinRele = 33;

void setup() {
  Serial.begin(115200);
  pinMode(pinRele, OUTPUT);
  //inicio o sistema de wifi, e imprimi ponto ate conectar
  //WiFi.begin(WIFI_SSID, WIFI_PASSWORD, WIFI_CHANNEL);
  //Serial.print("Connecting to WiFi ");
  //Serial.print(WIFI_SSID);
  //while (WiFi.status() != WL_CONNECTED) {
  //  delay(100);
  //  Serial.print(".");
  //}
  Serial.print("Setting soft-AP configuration ... ");
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");
  Serial.print("Setting soft-AP ... ");
  Serial.println(WiFi.softAP(ssid, password) ? "Ready" : "Failed!");
  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());

  //Configuro as chamadas de função conforme as paginas.
  server.on("/", handleIndex);
  server.on("/acendeTime", acendeLuzTime);
  server.on("/acende", acendeLuz);
  server.on("/acendeP", acendePisca);
  //inicio o servidor http
  server.begin();

}

void loop() { 
  //fica escutando as solicitações dos clientes
   server.handleClient();
   acendeMaster();
}
void acendeLuz(){
  if(acende == 0){
    acende = 1;
  }
  else
  {
    acende =0;
  }
  server.sendHeader("Location", "/");
  server.send(302, "text/plain", "");
}

void acendePisca(){
  if(pisca == 0){
    pisca = 1;
  }
  else
  {
    pisca =0;
  }
  server.sendHeader("Location", "/");
  server.send(302, "text/plain", "");
}

void acendeLuzTime(){
 tempAcende = atoi(server.arg("txtTime").c_str())*1000;
  Serial.println(tempAcende);
 if(acendeT == 0){
    acendeT =1;
 }
 else
  {
    acendeT =0;
 }
  server.sendHeader("Location", "/");
 server.send(302, "text/plain", "");
}

void acendeMaster(){

   if(acende ==1)
   {
    digitalWrite(pinRele, LOW);
    
   }
   else if(acendeT ==1){
    digitalWrite(pinRele, LOW);
    
    delay(tempAcende);
    digitalWrite(pinRele, HIGH);
    acendeT =0;
   }else if(pisca == 1){
    digitalWrite(pinRele, LOW); 
    delay(1000);
    digitalWrite(pinRele, HIGH);
    delay(1000);
   }
   else{
    digitalWrite(pinRele, HIGH);
    
   }
}