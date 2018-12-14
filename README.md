# ESP8266_wemos_d1_r1-----firebase-----flot.js

[![Build Status](https://travis-ci.org/joemccann/dillinger.svg?branch=master)](https://github.com/mlesterdampios/wemos_d1_r1-firebase)

Upload data from ESP8266 Wemos D1 R1 with DHT11 Sensors (Temperature and Humidity) to Firebase, then read Firebase data from local HTML file. Create a real-time chart using Flot.JS.
Requirements:

  - ESP8266 Wemos D1 R1 and DHT11
  - Firebase
  - Flot.JS
  - Magic
  
# Installtion
> Patience is virtue.

## Firebase

  - Setup firebase then copy all credentials. You will need that later. 

## Schematics

  - Connect DHT11 signal (output) to D5 (equivalent to pin 14) input of esp8266
  - Supply vcc and gnd
  
## Sketch Setup

  - The project is divided into 2 solution. To setup sketch, install libraries in the boardSourceCode\libraries then load up boardSourceCode\esp8266_tempSensor
  - Change all credentials in the esp8266_tempSensor.ino
  - Browse to \libraries\firebase-arduino-0.3\src\FirebaseHttpClient.h line 40 and 41 then replace Fingerprints-
  ```c
  static const char kFirebaseFingerprint[] =
      "6F D0 9A 52 C0 E9 E4 CD A0 D3 02 A4 B7 A1 92 38 2D CA 2F 26";
  ```
  - -to your respective firebase url (ex. xxxx.firebaseio.com) via https://www.grc.com/fingerprints.htm
  - Upload the code to the board and your done.
  - //You may notice that firebase is now receiving data from the board accordingly.
  - //We doesn't setup spiffs now but you can use serial monitor to check the logs

## Local HTML File

  - Edit localFiles/esp8266_dht11_firebase.html. Replace all credentials and you are good to go.
  - //Everything in the localFiles are already done setting up. I personaly used AdminLTE with Flot.JS to display the data gathered from the firebase.
  - After replacing all credentials, open up localFiles/esp8266_dht11_firebase.html. AND TADAAA!!!


### Tech

This project uses a number of open source projects to work properly:

* [AdminLTE] - AdminLTE with Flot.JS
* [ArduinoJson] - As pre-requisite of firebase-arduino
* [DHT] - Library for DHT modules
* [firebase-arduino] - Library to connect arduino esp8266 to firebase

### Bonus1

If you dont have wemos d1 r1 on your board list, add this to your board manager:
  ```json
  http://arduino.esp8266.com/stable/package_esp8266com_index.json
  ```
or visit [Arduino-Core-for-ESP8266]

### Bonus2
![alt](https://4.bp.blogspot.com/-_w2jQDs-WpM/WqxJSkJulKI/AAAAAAAAGII/5Jza5ED32ec9DZfam5uQGkl54UjI-4BQwCLcBGAs/s1600/maxresdefault%2B%25285%2529.jpg)
![alt](https://raw.githubusercontent.com/mlesterdampios/wemos_d1_r1-firebase/master/screenshot1.jpg)

License
----
* MIT 
* [mlesterdampios-github]
* [mlesterdampios-fb]


   [AdminLTE]: <https://github.com/almasaeed2010/AdminLTE>
   [ArduinoJson]: <https://github.com/bblanchon/ArduinoJson>
   [DHT]: <https://playground.arduino.cc/Main/DHTLib>
   [firebase-arduino]: <https://github.com/FirebaseExtended/firebase-arduino>
   [Arduino-Core-for-ESP8266]: <https://github.com/esp8266/Arduino>
   [mlesterdampios-github]: <https://github.com/mlesterdampios>
   [mlesterdampios-fb]: <https://www.facebook.com/MarkLesterDampios101>
