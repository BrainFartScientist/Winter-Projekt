#define FASTLED_ALLOW INTERRUPTS 0
#define FASTLED_ESP8266_RAW_PIN_ORDER

#include <FastLED.h>
#define DATA_PIN D5
#define NUM_LEDS 8
#define FRAMES_PER_SECOND 120


CRGB leds[NUM_LEDS];

void ledInit(){
  //Init
  FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //Helligkeit einstellen in %
  FastLED.setBrightness(50);
  //damit die Stromstärke nicht überschritten wird
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 400);
}

void ledWhite() 
{
  for(int i = 0; i < 255; i++){
    leds[7] = CRGB(i,i,i);
    delay(10);
    FastLED.show();
  }
}
void ledDrizzle(){ //hellblau
  for(int i = 0; i < 255; i++){
    leds[7] = CRGB(0,i,i);
    delay(10);
    FastLED.show();
  }  
  delay(1);
  for(int i = 255; i > 0; i--){
    leds[7] = CRGB(0,i,i);
    delay(10);
    FastLED.show();
  }
}
void ledFog(){
  for(int i = 0; i < 255; i++){
    leds[7] = CRGB(i,0,i);
    delay(10);
    FastLED.show();
  }  
  delay(1);
  for(int i = 255; i > 0; i--){
    leds[7] = CRGB(i,0,i);
    delay(10);
    FastLED.show();
  }
}
void ledRain(){
  for(int i = 0; i < 255; i++){
    leds[7] = CRGB(0,0,i);
    delay(10);
    FastLED.show();
  }  
  delay(1);
  for(int i = 255; i > 0; i--){
    leds[7] = CRGB(0,0,i);
    delay(10);
    FastLED.show();
  }
}
void ledThun(){
  for(int i = 0; i < 5; i++) {
    leds[7] = CRGB(200, 200, 0);
    delay(200);
    FastLED.show();
    leds[7] = CRGB(0, 0, 0);
    delay(100);
    FastLED.show();
  }
  delay(2000);
}
void ledSnow(){
  for(int i = 0; i < 255; i++){
    leds[7] = CRGB(i,i,i);
    delay(10);
    FastLED.show();
  }  
  delay(500);
  for(int i = 255; i > 0; i--){
    leds[7] = CRGB(i,i,i);
    delay(10);
    FastLED.show();
  }
}
