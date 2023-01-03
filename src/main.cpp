#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <ESP32Servo.h>

// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLdNyiN2Jw"
#define BLYNK_DEVICE_NAME "IOTHOME"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial

#include "BlynkEdgent.h"

// Define PIN of external deives 
#define DEN_NHA_BEP          33 // 25 
#define DEN_PHONG_NGU        25 // 26 
#define DEN_PHONG_KHACH      26 // 33 
#define DEN_HANH_LANG         27 
#define QUAT_PHONG_NGU        14 
#define QUAT_PHONG_KHACH      4 

#define DHT11_HANH_LANG       18 
#define DHT11_PHONG_BEP       19 

#define KHI_GAS               32 
#define PIR                   13

#define BUTTON_CUA_CHINH      35 
#define BUTTON_PHONG_NGU      34 

#define SERVO_CUA_CHINH       16
#define SERVO_PHONG_NGU       17

Servo servo_cuachinh;
Servo servo_phongngu;
BlynkTimer timer;

// Define timer
#define timeSeconds          10  // Timer for LED off

// Temperature - DH11
DHT dht_hanh_lang(DHT11_HANH_LANG,DHT11);
DHT dht_phong_bep(DHT11_PHONG_BEP,DHT11);

// set LCD address, number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

unsigned long times = millis(); // set time to read temperature

int Khi_gas_value = 0;
int cuachinh_servo_value = 0;
int phongngu_servo_value = 0;

int  trangthai_cuachinh = 1;
int trangthai_phongngu = 1;
boolean btccState  = HIGH;
boolean btpnState  = HIGH;


unsigned long now = millis();
unsigned long lastTrigger = 0;
boolean startTimer = false;
// Checks if motion was detected
// Input Read PIR -> detect:OK 
// Output: Den hanh lang:ON
//         LCD: XIN CHAO BAN!
void IRAM_ATTR detectsMovement() {
  // lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("XIN CHAO");

  digitalWrite(DEN_HANH_LANG, HIGH);

  // Start timer to off Led
  // startTimer = true; 
  // lastTrigger = millis();
}

void dieukhien_cuachinh(int trangthai)
{
  if (trangthai == 1){
    servo_cuachinh.write(90);
    delay(150);
  }
  else if (trangthai == 0){
    servo_cuachinh.write(0);
    delay(150);
  }
  else{}
}

void dieukhien_phongngu(int trangthai)
{
  if (trangthai == 1){
    servo_phongngu.write(90);
    delay(150);
  }
  else if (trangthai == 0){
    servo_phongngu.write(0);
    delay(150);
  }
  else{}
}

void checkButton(){
  if(digitalRead(BUTTON_CUA_CHINH)==LOW){ 
    if (btccState == HIGH){
      if (trangthai_cuachinh == 1)
        trangthai_cuachinh = 0;
      else
        trangthai_cuachinh = 1;
      dieukhien_cuachinh(trangthai_cuachinh);
      Blynk.virtualWrite(V10,trangthai_cuachinh);
      // delay(100);
      btccState = LOW;
    }
  }
  else
  {
    btccState = HIGH;
  }
  if(digitalRead(BUTTON_PHONG_NGU)==LOW){ 
    if (btpnState == HIGH){
      if (trangthai_phongngu == 1)
        trangthai_phongngu = 0;
      else
        trangthai_phongngu = 1;
      dieukhien_phongngu(trangthai_phongngu);
      Blynk.virtualWrite(V11,trangthai_phongngu);
      // delay(100);
      btpnState = LOW;
    }
  }
  else
  {
    btpnState = HIGH;
  }
}

void setup() {
  // Initialize serial
  Serial.begin(115200);
  delay(100);

  // Setup PIN output
  pinMode(DEN_NHA_BEP   ,OUTPUT);
  pinMode(DEN_PHONG_NGU ,OUTPUT);
  pinMode(DEN_PHONG_KHACH ,OUTPUT);
  pinMode(DEN_HANH_LANG ,OUTPUT);
  pinMode(QUAT_PHONG_NGU ,OUTPUT);
  pinMode(QUAT_PHONG_KHACH ,OUTPUT);

  // Setup PIN input
  pinMode(KHI_GAS,INPUT);

  // Initialize Output is low
  digitalWrite(DEN_NHA_BEP     ,0);
  digitalWrite(DEN_PHONG_NGU   ,0);
  digitalWrite(DEN_PHONG_KHACH ,0);
  digitalWrite(DEN_HANH_LANG   ,0);
  digitalWrite(QUAT_PHONG_NGU  ,0);
  digitalWrite(QUAT_PHONG_KHACH,0);

  // PIR motion sensor mode input_pullup
  pinMode(PIR,INPUT_PULLDOWN);
  // Set motionSensor pin as interrupt, assign interrupt function and set RISING mode
  attachInterrupt(digitalPinToInterrupt(PIR), detectsMovement, RISING);

  servo_cuachinh.attach(SERVO_CUA_CHINH);
  servo_phongngu.attach(SERVO_PHONG_NGU);

  dieukhien_cuachinh(trangthai_cuachinh);
  dieukhien_phongngu(trangthai_phongngu);

  Blynk.virtualWrite(V10,trangthai_cuachinh);
  Blynk.virtualWrite(V11,trangthai_phongngu);

  // Initialize LCD
  lcd.init();
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("TRAN THANH HAI");

  // Setup serial
  Serial.begin(115200);                                                   
  Serial.println();

  // dht init.
  dht_hanh_lang.begin();
  dht_phong_bep.begin();
  
  BlynkEdgent.begin();
  // timer.setInterval()
  delay(2000);
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

BLYNK_WRITE(V10){
  int p = param.asInt();
  if (p == 1)
  {
    trangthai_cuachinh = 1;
  }
  else if (p ==0 )
  {
    trangthai_cuachinh = 0;
  }
  else
  {}
  dieukhien_cuachinh(trangthai_cuachinh);
}

BLYNK_WRITE(V11){
  int p = param.asInt();
  if (p == 1)
  {
    trangthai_phongngu = 1;
  }
  else if (p ==0)
  {
    trangthai_phongngu = 0;
  }
  else
  {}
  dieukhien_cuachinh(trangthai_phongngu);
}

void loop() {
  BlynkEdgent.run();
  // timer.run();

  // set timer to off Led hanh Lang
  now = millis();
  // Turn off the LED after the number of seconds defined in the timeSeconds variable
  // if(startTimer && (now - lastTrigger > (timeSeconds*1000))) 
  // {
  //   digitalWrite(DEN_HANH_LANG, LOW);
  //   startTimer = false;
  // }

  // set timer to display temperature blynk
  lcd.clear();
  lcd.setCursor(0,0);        
  lcd.print("Nhiet do:");

  // if (millis() - times > 200) 
  // {
    float nhietdo_phongbep = dht_phong_bep.readTemperature();
    float doam_phongbep = dht_phong_bep.readHumidity();

    // if (isnan(nhietdo_phongbep) || isnan(doam_phongbep)) {
    //   Serial.println(F("Failed to read from DHT (phong bep) sensor!"));
    //   return;
    // }
    
    float nhietdo_hanhlang = dht_hanh_lang.readTemperature();
    float doam_hanhlang = dht_hanh_lang.readHumidity();

    // if (isnan(nhietdo_hanhlang) || isnan(doam_hanhlang)) {
    //   Serial.println(F("Failed to read from DHT (hanh lang) sensor!"));
    //   return;
    // }

    Khi_gas_value = analogRead(KHI_GAS);

    lcd.setCursor(9,0);
    lcd.print(String(nhietdo_hanhlang,1)); 
    lcd.write(0);
    lcd.print("C  ");

    Blynk.virtualWrite(V6,nhietdo_hanhlang);
    Blynk.virtualWrite(V7,nhietdo_phongbep);
    Blynk.virtualWrite(V9,Khi_gas_value);

    times = millis();
  // }

  checkButton();
}