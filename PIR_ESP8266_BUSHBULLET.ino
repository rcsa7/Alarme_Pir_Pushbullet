/*
 * SENSOR_PIR_BUZZER_ESP8266_BUSHBULLET_Portão_GARAGEM_ABERTO
 * PIR SENSOR 
 * VCC----VCC
 * GND----GNC
 * OUT-----D5
 */



#include "ESP8266WiFi.h"
const char WEBSITE[] = "api.pushingbox.com";    //pushingbox API server
const String devid1 = "v75142156D6087CD";       //Sensor PIR alarme Portão GARAGEM Aberto


const char* ssid = "XXXXXXXXXXXX";
const char* password =  "XXXXXXXXXXXXX";

void Janela();
int pinLed = 15;// GPIO15------D8
int pinBuzzer = 13;// GPIO13----D7
int pirSensor = 14;// GPIO14----D5
int relayInput = 12;//GPIO12---D6

void setup() {
   Serial.begin(115200);
     pinMode(pinBuzzer,OUTPUT);
      pinMode(pinLed,OUTPUT);
  pinMode(pirSensor, INPUT);
  pinMode(relayInput, OUTPUT); 
  Serial.print("Connecting to SSID: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) //not connected,..waiting to connect
    {
      delay(1000);
      Serial.print(".");
    }

   
}
void loop() {
  int sensorValue = digitalRead(pirSensor);
  if (sensorValue == 1) {
     Janela();
     ligarAlarme();
    digitalWrite(relayInput, HIGH); // The Relay Input works Inversly
     delay(2800);
      digitalWrite(relayInput, LOW); // The Relay Input works Inversly
  }
   else 
   {
    desligarAlarme();
  }    
}


void Janela(){
  WiFiClient client;  //------Instantiate WiFi object

    //-------Start or API service using our WiFi Client through PushingBox
    if (client.connect(WEBSITE, 80))
      { 
         client.print("GET /pushingbox?devid=" + devid1
         );

      client.println(" HTTP/1.1"); 
      client.print("Host: ");
      client.println(WEBSITE);
      client.println("User-Agent: ESP8266/1.0");
      client.println("Connection: close");
      client.println();
      }
      Serial.println("Janela");  
}

void ligarAlarme() {
  //Ligando o led
  digitalWrite(pinLed, HIGH);
   
  //Ligando o buzzer com uma frequencia de 1500 hz.
  tone(pinBuzzer,1500);
   
  delay(4000); //tempo que o led fica acesso e o buzzer toca
   
  desligarAlarme();
}
 
void desligarAlarme() {
  //Desligando o led
  digitalWrite(pinLed, LOW);
   
  //Desligando o buzzer
  noTone(pinBuzzer);
}
