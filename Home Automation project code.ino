#include "DHT.h"
#include <LiquidCrystal.h>
const int rs =8, en =9, d4 =10, d5 =11, d6 =12, d7 =13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#define DHTPIN A0    
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE); 
const int pingPin =2; // Trigger Pin of Ultrasonic Sensor
const int echoPin =3; // Echo Pin of Ultrasonic Sensor
long duration;
int distance;
int ss=A1;
int buz=7;
int light=A3;
int fan=A4;
int f=2;
int ldr=A5;
int x;
void setup() {
Serial.begin(9600);
  pinMode(f,INPUT);
  pinMode(ldr,INPUT);
  pinMode(light,OUTPUT);
  pinMode(fan,OUTPUT);
  pinMode(ss,INPUT);
  pinMode(buz,OUTPUT);
  pinMode(pingPin, OUTPUT);
pinMode(echoPin, INPUT);
  digitalWrite(light,1);
  digitalWrite(fan,0);   
  lcd.begin(16, 2);
  lcd.print("WELCOME");
 // wifi_init();
  dht.begin();  
}
void loop() {
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  int sval=analogRead(ss);
  int fval=1-digitalRead(f);
  int lval=1023-analogRead(ldr);
  digitalWrite(pingPin, LOW);
delayMicroseconds(2);
digitalWrite(pingPin, HIGH);
delayMicroseconds(10);
digitalWrite(pingPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance= (duration/2)/29.1;
delay(200);
 //Serial.println("T:"+ String(t) + "  H:" +String(h) + "  S:" + String(sval));
 lcd.setCursor(0,0);
 lcd.print("T:" + String(t) + "  H:" +String(h)+ "  L:" +String(distance));
 lcd.setCursor(0,1);
 lcd.print("G:" + String(sval) + "  F:" + String(fval));

Serial.print("433137,354BA8AR8Y3IXJPT,433676,SWX1Q3Q505Z23765,SRC 24G,src@internet,"+String(t)+","+String(h) + ","+String(distance)+","+String(sval)+","+String(fval)+",\n");

 if(t>40||h>90 ||sval>200 ||fval==1)
 { 
  digitalWrite(buz,1);

 }
 else
 {
  digitalWrite(buz,0);
 }
  x=Serial.read();
  if(x=='1')
  {
    digitalWrite(light,1);
  }
    if(x=='2')
  {
    digitalWrite(light,0);
  }
    if(x=='3')
  {
    digitalWrite(fan,0);
  }
    if(x=='4')
  {
    digitalWrite(fan,1);
  }
}
