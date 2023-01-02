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

#define DEN_NHA_BEP           13 // Led 12V
#define DEN_PHONG_NGU         32 // Led 12V
#define DEN_PHONG_KHACH       33 // Led 5V
#define DEN_HANH_LANG         33 // Led 5V
#define QUAT_PHONG_NGU        33 // Led 5V
#define QUAT_PHONG_KHACH      33 // Led 5V

#define DHT11_HANH_LANG       11 //
#define DHT11_PHONG_BEP       11 //

#define KHI_GAS               15 //
#define PIR                   96 //

// Temperature - DH11
DHT dht_hanh_lang(DHT11_HANH_LANG,DHT11);
DHT dht_phong_bep(DHT11_PHONG_BEP,DHT11);

// set LCD address, number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

// Checks if motion was detected
// Input Read PIR -> detect:OK 
// Output: Den hanh lang:ON
//         LCD: XIN CHAO BAN!

void IRAM_ATTR detectsMovement() {
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("XIN CHAO");

  digitalWrite(DEN_HANH_LANG, HIGH);
  // startTimer = true;
  // lastTrigger = millis();
}

void setup() {
  // Initialize serial
  Serial.begin(115200);
  delay(100);

  // Setup output
  pinMode(DEN_NHA_BEP   ,OUTPUT);
  pinMode(DEN_PHONG_NGU ,OUTPUT);
  pinMode(DEN_PHONG_KHACH ,OUTPUT);
  pinMode(DEN_HANH_LANG ,OUTPUT);
  pinMode(QUAT_PHONG_NGU ,OUTPUT);
  pinMode(QUAT_PHONG_KHACH ,OUTPUT);
  
  // Initialize Output is low
  digitalWrite(DEN_NHA_BEP     ,0);
  digitalWrite(DEN_PHONG_NGU   ,0);
  digitalWrite(DEN_PHONG_KHACH ,0);
  digitalWrite(DEN_HANH_LANG   ,0);
  digitalWrite(QUAT_PHONG_NGU  ,0);
  digitalWrite(QUAT_PHONG_KHACH,0);

  // PIR motion sensor mode input_pullup
  pinMode(PIR,INPUT_PULLUP);
  // Set motionSensor pin as interrupt, assign interrupt function and set RISING mode
  attachInterrupt(digitalPinToInterrupt(PIR), detectsMovement, RISING);

  // Initialize LCD
  lcd.init();
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("TRAN THANH HAI");

  // Setup serial
  Serial.begin(115200);                                                   
  Serial.println();
  Serial.println("Erisim Noktasi (AP)konfigure ediliyor...");

  
  BlynkEdgent.begin();

}


// Define virtual Pin
BLYNK_WRITE(V0){
  int p = param.asInt();
  digitalWrite(DEN_NHA_BEP,p);
}

BLYNK_WRITE(V1){
  int p = param.asInt();
  digitalWrite(DEN_PHONG_NGU,p);
}

BLYNK_WRITE(V2){
  int p = param.asInt();
  digitalWrite(DEN_PHONG_KHACH,p);
}

BLYNK_WRITE(V3){
  int p = param.asInt();
  digitalWrite(DEN_HANH_LANG,p);
}

BLYNK_WRITE(V4){
  int p = param.asInt();
  digitalWrite(QUAT_PHONG_NGU,p);
}

BLYNK_WRITE(V5){
  int p = param.asInt();
  digitalWrite(QUAT_PHONG_KHACH,p);
}

void loop() {
  BlynkEdgent.run();

}