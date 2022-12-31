#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLdNyiN2Jw"
#define BLYNK_DEVICE_NAME "IOTHOME"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial

#include "BlynkEdgent.h"

// Define PIN of external deives 
#define DHT11   11 
#define PIR     12
#define MQ2     14
#define SERVO_1 15
#define SERVO_2 16
#define FAN     13

#define LED_1   13 // Led 12V
#define LED_2   32 // Led 12V
#define LED_3   33 // Led 5V

// set LCD address, number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  
                                                
void setup() {
  // Initialize serial
  Serial.begin(115200);
  delay(100);

  // Setup output
  pinMode(FAN   ,OUTPUT);
  pinMode(LED_1 ,OUTPUT);
  pinMode(LED_2 ,OUTPUT);
  pinMode(LED_3 ,OUTPUT);

  // Initialize LCD
  lcd.init();
  lcd.backlight();

  // Setup serial
  Serial.begin(115200);                                                   
  Serial.println();
  Serial.println("Erisim Noktasi (AP)konfigure ediliyor...");      

  BlynkEdgent.begin();
}

BLYNK_WRITE(V1){
  int p = param.asInt();
  digitalWrite(LED_1,p);
}
BLYNK_WRITE(V2){
  int p = param.asInt();
  digitalWrite(LED_2,p);
}
BLYNK_WRITE(V3){
  int p = param.asInt();
  digitalWrite(LED_3,p);
}


void loop() {
  BlynkEdgent.run();

  lcd.setCursor(4,0);
  lcd.print("XIN CHAO");

}