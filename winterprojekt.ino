#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>

#define OLED_RESET 0  
Adafruit_SSD1306 display(OLED_RESET);
//Schnittstelle zur OpenWeatherMap

String APIKEY = "xxxxxxxxxxxxxxx";
String CityID = "2857458"; //ID von Oldenburg

WiFiManager wifi;
WiFiClient client;
unsigned long timeCheck = 0;
int weatherID = 0;
int weatherID_sum = 0;
String weatherReport = " ";
int temperatureCelsiusInt = 0;

void setup() {
  delay(3000);
  Serial.begin(9600);
  getWeather();
  ledInit();
  ledWhite();
  delay(30); //kurz warten
  wifi.autoConnect("Wemos_D1");
  delay(3000);
 
}

void loop() {
  if(millis() - timeCheck >= 1800000) { //hiermit wird nur alle 30 min das Wetter abgefragt
    getWeather();                       //millis gibt die Zeit, seit dem Start des Arduinos, an
    timeCheck = millis();
  }
  Serial.print("Its ");
  Serial.println(weatherReport);
  switch(weatherID_sum){ 
    case 2: ledThun();
    break;
    case 3: ledDrizzle();
    break;
    case 5: ledRain();
    break;
    case 6: ledSnow();
    break;
    case 7: ledFog();
    break;
  }
}

void getWeather() {  //diese Methode aktualliesiert die Wetterlage 
  Serial.println("Connecting to ");
  Serial.println("api.openweathermap.org");
  if(client.connect("api.openweathermap.org", 80)){
    client.println("GET /data/2.5/weather?id= "+ CityID + "&units=metric&APPID=" + APIKEY);
    client.println("Host: api.openweathermap.org");
    client.println("Connection: close");
    client.println();
  }
  else {
    Serial.println("No connection to Server");
    Serial.println();
  }
  const size_t capacity = JSON_ARRAY_SIZE(2) + 2 * JSON_OBJECT_SIZE(1) + 2 * JSON_OBJECT_SIZE(2) + 2 * JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(14) + 360;
  DynamicJsonDocument doc(capacity);
  deserializeJson(doc, client);
  client.stop();

  weatherID = doc["weather"][0]["id"];
  int temperatureCelsius = doc["main"]["temp"];
  temperatureCelsiusInt = (int)temperatureCelsius;

  weatherID_sum = (int)(weatherID / 100); //die weatherID ist eine dreistellige Zahl. Die letzten 2 Stellen sind jedoch unbedeutend, also teilen wir durch 100
  switch (weatherID_sum) {
    
    case 2: weatherReport = "Thunder"; 
    break;
    case 3: weatherReport = "Dizzle"; 
    break;
    case 5: weatherReport = "Rain"; 
    break;
    case 6: weatherReport = "Snow"; 
    break;
    case 7: weatherReport = "Foggy"; 
    break;
    default: weatherReport = ""; 
    break;      
                                                                     
  } 
  
  
}
