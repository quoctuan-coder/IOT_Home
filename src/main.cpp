#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <ESP32Servo.h>


#define SERVO_CUA_CHINH       16
#define SERVO_PHONG_NGU       17

Servo servo_cuachinh;
Servo servo_phongngu;

void setup(){
servo_cuachinh.attach(SERVO_CUA_CHINH);
servo_phongngu.attach(SERVO_PHONG_NGU);

}

void loop()
{
int pos;
  for (pos = 0; pos <= 180; pos += 10) {  // goes from 0 degrees to 180 degrees
  // in steps of 1 degree
  servo_cuachinh.write(pos);  // tell servo to go to position in variable 'pos'
  delay(10);           // waits 15ms for the servo to reach the position
 }
 int pos1;
  for (pos1 = 0; pos1 <= 180; pos1 += 10) {  // goes from 0 degrees to 180 degrees
  // in steps of 1 degree
  servo_phongngu.write(pos1);  // tell servo to go to position in variable 'pos'
  delay(10);           // waits 15ms for the servo to reach the position
 }
}