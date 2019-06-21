#include <SD.h>
#include <LiquidCrystal_I2C.h>
#include <Stepper.h>
#include <Q2HX711.h>
#include <SPI.h>

/* */
File myFile;
Q2HX711 scale1(3, 2);
Q2HX711 scale2(7, 6);
LiquidCrystal_I2C lcd(0x27,16,2);  
#define spr=200;
Stepper motor(200,A0,A1,A2,A3);

void setup() {
  lcd.init();
  lcd.backlight(); 
  Serial.begin(9600);
  motor.setSpeed(60);
  Serial.println("connected");
 
  /*
  while(1){
    if (!SD.begin()) {
      lcd.setCursor(0,0);                //设置显示指针
      lcd.print("SD Init Fail");
      continue;
    }
    lcd.setCursor(0,0);                //设置显示指针
    lcd.print("SD card detected");
    break;
  }
  myFile = SD.open("test.txt", FILE_WRITE);
  myFile.seek(myFile.size());
  myFile.write("this is my data");
  myFile.close();
 */
}

void loop() {
  if(!Serial.available()) return;
  String str="";
  while(Serial.available()) {
    char a=Serial.read();
    str+=a;
    delay(1);
  }
  

  Serial.println(str);
  if(str=="gg"){
    Serial.println("yes");
  }
  if(str=="aa"){
    Serial.println("no");
  }
  motor.setSpeed(100);
  //motor.step(40);
  //Serial.println("s1"+String(scale1.read()/100000-70));
  //Serial.println("s2"+String(scale2.read()/10000));
}
