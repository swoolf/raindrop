#include "softAP.h"
#include "application.h"
#include "sparse.h"
#include <SparkJson.h>
#include <neopixel.h>

PRODUCT_ID(7863);
PRODUCT_VERSION(4);

SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(SEMI_AUTOMATIC);

#define npix 23
#define PIXEL_PIN D6
#define PIXEL_TYPE WS2812B
#define PEACH 200,50,5
#define CYAN 10,150,70
#define PURPLE 180,3,180
#define BLUE 5,5,190
#define LIGHTBLUE 160,160,240
#define WHITE 150,150,150
#define GREEN 10,180,10
#define RED 180,10,10
#define YELLOW 180,180,10
#define OFF 0,0,0

unsigned long upTime = 20000;
int eepromZipAddress = 0;
int j;
int counter = 0;
int probability[65];
int wifiState = false;
String zipCodeStr ="";

Adafruit_NeoPixel strip = Adafruit_NeoPixel(npix, PIXEL_PIN, PIXEL_TYPE);

void setup() {
    Serial.begin(9600);
    ///////////////////////////////////////////////////////////SetUP WIFI
    Particle.connect(); //try to connect to wifi
    unsigned long start = millis();
    
    strip.begin();
    
    while(! Particle.connected() && start+upTime>millis()){ //Wait for upTime to look for connection, ~20secs
      breathe(GREEN);
    }
    
    if (! Particle.connected()){// if not connected, engage user setup
    //   breathe(BLUE);
      wifiState=1;
      WiFi.listen();
      while(! Particle.connected()){breathe(BLUE);}
      }
    ///////////////////////////////////////////////////////////
    strip.setBrightness(50);
    int i =12345; //Check EEPROM for stored Zip Code
    int j = 0;
    int zipCode = EEPROM.get(0, i);
    zipCodeStr=String(zipCode);
    int sendInfo = EEPROM.get(10,j);
 
    if(sendInfo==1){
        Particle.subscribe("particle/device/name", dnameHandler);
        Particle.publish("particle/device/name");
        EEPROM.put(10,0);
        }
    
    if(System.updatesPending()){
        delay(10*1000);
    }
    
    Serial.println("zipfromMem: "+zipCodeStr);
    
    //Get handler name from Azure
    String rainHandler = getName(zipCode);
    Serial.println("Handler: " + rainHandler + "rainDial");
    Particle.subscribe(rainHandler + "rainDial", myHandler, MY_DEVICES);

    
    //Start up Disco
    startUpDisco();

}


void loop() {
}//nothing here...

//handles weather event pulled from MS Azure Cloud script + DarkSky API
void myHandler(const char *event, const char *data) {
    eParse(probability, data); //parse event data to arrays
    weather2LEDs(probability,0);
    counter=1;
}

void dnameHandler(const char *topic, const char *data) {
    // Serial.println("received " + String(topic) + ": " + String(data));
    String deviceName = String(data);
    Particle.publish("sendDeviceInfo", String(zipCodeStr) +", "+ deviceName, PRIVATE);
}
          

//update LEDs with weather info.
void weather2LEDs(int probability[], int offset) {
    for (int i=0; i<60; i++){
        int j = round(i* npix/60.0);
        if (probability[i]>0){strip.setPixelColor(j, BLUE);}
        else{strip.setPixelColor(j, OFF);}
        }
    strip.show();
}


//Spin LEDs on neopixel strip
void spin(int R, int G, int B) {
    for(int i=0; i < npix; i++) {
        strip.setPixelColor(i, R,G,B);
        strip.show();
        delay(40);
    }
}

void breathe(int R, int G, int B) {
    for (int j=255; j>0; j=j-10){
        strip.setBrightness(j);
        for(int i=0; i < npix; i++) {
            strip.setPixelColor(i, R,G,B);
        }
        strip.show();
        delay(30);
    }
    delay(50);
    for (int j=0; j<255; j=j+10){
        strip.setBrightness(j);
        for(int i=0; i < npix; i++) {
            strip.setPixelColor(i, R,G,B);
        }
        strip.show();
        delay(30);
    }
}

void startUpDisco(){
    int halfpix= round(npix/2);
    for (int i=0; i<npix;i++){strip.setPixelColor(i, OFF);}
    
    meltDownUp(LIGHTBLUE, BLUE);
    meltDownUp(PURPLE, BLUE);
    meltDownUp(CYAN, BLUE);
    
    for(int i=0; i<halfpix+1; i++){
        strip.setPixelColor(i, OFF);
        strip.setPixelColor(( npix-1)-i, OFF);
        strip.show();
        delay(100);
    }
    
}

void meltDownUp(int R1, int G1, int B1, int R2, int G2, int B2){
    int halfpix= round(npix/2);
    for(int i=0; i<halfpix+1; i++){
        strip.setPixelColor(i, R1, G1, B1);
        strip.setPixelColor(( npix-1)-i, R1, G1, B1);
        strip.show();
        delay(100);
    }
    for(int i=0; i<halfpix+1; i++){
        strip.setPixelColor(i+halfpix, R2, G2, B2);
        strip.setPixelColor( ( halfpix)-i, R2, G2, B2);
        strip.show();
        delay(75);
    }
}






