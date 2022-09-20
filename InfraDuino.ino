#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>
#include <SNTPtime.h>

#include <EEPROM.h>
#include <ESP8266WebServer.h>

const uint8_t myPins[] = { D1, D2, D3, D5, D6, D7 };
const uint8_t releDefault = HIGH; // HIGH -> NC || LOW -> NO

SNTPtime NTPch("ch.pool.ntp.org");
strDateTime dateTime;

ESP8266WebServer server(80);
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
FirebaseData stream;

long myTimer = 1;

void setup() {
  
  Serial.begin(9600);
  pinMode(0, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  checkWifiServer();
  wifiClient();
  setFirebaseConfig();
  
}

void loop() {
  if( myTimer % 600000 == 0 ){
    releActions();
    myTimer = 1;
  }
  myTimer++;
  delay(1);
}
