#include <WiFi.h>
#include <ThingSpeak.h>
#include "DHT.h"

#define DHTPIN  33      

#define DHTTYPE DHT11// DHT 11

DHT dht(DHTPIN, DHTTYPE);

int PulseSensorPurplePin = 34;


int Signal, BPM;
int Threshold = 300;  

const char* ssid="kv27";
const char* password="87023279605";

unsigned long channelID = 1748891;
const char* WriteAPIKey ="Q9ES40BF2VP3OOLZ";

WiFiClient person;


void setup() {
  
  Serial.begin(115200);
  delay(1000);

  Serial.println("Sensors are connected");
  dht.begin();

  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected at WiFi");
  ThingSpeak.begin(person);
  delay(5000);
}


void loop() {

  delay(5000);
  download();

  ThingSpeak.writeFields(channelID,WriteAPIKey);

  Serial.println("indicators are downloaded at ThingSpeak!");
  delay(10000);
}

void download(){

  float temperatura= dht.readTemperature();
  Signal = analogRead(PulseSensorPurplePin);
  
  BPM = Signal / 30;
  Serial.print("BPM: ");
  Serial.println(BPM);
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println("°C");
  Serial.println("-----------------------------------------");

  ThingSpeak.setField(1,temperatura);
  ThingSpeak.setField(2,BPM);
}
