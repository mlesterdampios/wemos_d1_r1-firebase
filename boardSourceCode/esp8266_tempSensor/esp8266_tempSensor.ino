#include <FirebaseArduino.h>
#include  <ESP8266WiFi.h>
#include <time.h>
#include "dht.h"

#define dht_apin 14 // Analog Pin sensor is connected to; d5 pin of wemos d1 r1

#define FIREBASE_HOST "xxxx.firebaseio.com"
#define FIREBASE_AUTH "xxxx"

#define WIFI_SSID "PLDTHOMEFIBR10095" // Change the name of your WIFI
#define WIFI_PASSWORD "PLDTWIFI30285" // Change the password of your WIFI

dht DHT;

int timezone = 8;
int dst = 0;

void setup() {
  Serial.begin(9600);
   WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println ("");
  Serial.println ("WiFi Connected!");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.status());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Serial.println ("Firebase setup done");

  configTime(timezone * 3600, dst, "pool.ntp.org", "time.nist.gov");
  Serial.println("Waiting for time");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
}

void loop() {
  DHT.read11(dht_apin);
  
  float h = DHT.humidity;
  float t = DHT.temperature;  // Reading temperature as Celsius (the default)
  
  time_t now = time(nullptr);
  
  Firebase.setFloat ("Temp",t);
  if(Firebase.success()){
    Serial.print ("Temp successfully pushed to Firebase");
  }else{
    Serial.print (" Temp Error : ");
    Serial.print (Firebase.error());
  }
  Serial.println ("");
  
  Firebase.setFloat ("Humidity",h);
  if(Firebase.success()){
    Serial.print ("Humidity successfully pushed to Firebase");
  }else{
    Serial.print (" Humidity Error : ");
    Serial.print (Firebase.error());
  }
  Serial.println ("");
  
  char *datePushed = ctime(&now);
  if (datePushed[strlen(datePushed)-1] == '\n') datePushed[strlen(datePushed)-1] = '\0';
  Firebase.set ("DatePushed",datePushed);
  if(Firebase.success()){
    Serial.print ("DatePushed successfully pushed to Firebase");
  }else{
    Serial.print (" DatePushed Error : ");
    Serial.print (Firebase.error());
  }
  //logs
  {
    String _datePushed = reinterpret_cast<const char*>(datePushed);
    String _t =  String(t);
    String _h = String(h);
    DynamicJsonBuffer jsonBuffer;
     String input =
      "{\"Temp\":"+ _t +
      ",\"Humidity\":"+ _h +
      ",\"DatePushed\":\""+ _datePushed +"\"}";
  JsonObject& root = jsonBuffer.parseObject(input);
    Firebase.push ("logs",root);
  }
  
  Serial.println ("");
  Serial.print (" Temp = ");
  Serial.print (t);
  Serial.println ("");
  Serial.print (" Humidity = ");
  Serial.print (h);
  Serial.println ("%");
  Serial.println ("==========");
  delay(5000);
}
