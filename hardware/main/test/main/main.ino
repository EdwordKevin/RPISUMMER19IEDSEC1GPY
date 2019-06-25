//#include <SD.h>
#include <LiquidCrystal_I2C.h>
//#include <Stepper.h>
#include <Q2HX711.h>
#include <SPI.h>
//#include <SoftwareSerial.h>


//File myFile;
Q2HX711 scale1(3, 2);
Q2HX711 scale2(7, 6);
/* 
#define spr=200;
Stepper motor(200,A0,A1,A2,A3);
*/
LiquidCrystal_I2C lcd(0x27,16,2); 

//SoftwareSerial s1(2,3);
void setup() {
  /*lcd.init();
  lcd.backlight(); 
  lcd.setCursor(0,0);
  lcd.print("SD Init Fail");
  Serial.begin(57600);
  //motor.setSpeed(60);
  Serial.println("connected");*/
  Serial.begin(9600);
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
 long a;
  a=scale1.read();
  long b;
  b=scale2.read();
   Serial.println(a+b);
 delay(2000);
  /*
  String a="";
  if(Serial.available()) delay(100);
  while(Serial.available()){
    a+=(char)Serial.read();
    delay(1);
  }
   //Serial.println("ms");
   if (a!="") Serial.println("get"+a);
  //delay(5000);*/
  /*
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
  */
}
