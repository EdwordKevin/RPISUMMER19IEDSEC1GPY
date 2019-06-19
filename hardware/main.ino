#include <LiquidCrystal_I2C.h>
#include <Q2HX711.h>
#include "config.h"
#include <Stepper.h>
#include <SPI.h>
#include <SD.h>


void setup(){
    Serial.begin(115200);
    while (!Serial)
    const int stepsPerRevolution = 200;
    myStepper.setSpeed(motorSpeed);//0-100
    lcd.init();// initialize the lcd 
    lcd.backlight();

    if (!SD.begin(4)) {
        Serial.println("initialization failed!");
        while (1);
    }
    Serial.println("initialization done.");
    
    connected=false;
    updated=false;
    date_set=false;
}
void loop(){
    /* 
    myStepper.step(stepsPerRevolution / 100);
    long hx711.read();
    lcd.setCursor(3,0);
    lcd.print("Hello, world!");
    SD.exists("test.txt");
    myFile = SD.open("test.txt", FILE_WRITE);
    if (myFile) {
        myFile.println("testing 1, 2, 3.");
        myFile.close();
    }
    myFile = SD.open("test.txt");
    if (myFile) {
        // read from the file until there's nothing else in it:
        while (myFile.available()) {
        Serial.write(myFile.read());
        }
        myFile.close();
    }*/
    if(!date_filled){
        int request=read_bt();
        if(request!="connecting request"){
            lcd.setCursor(0,0);
            lcd.print("Please initialize with client.");
            delay(1000);
            return;
        }else{
            Serial.write(0);//0 for first connect, 1 for continue
        }
    }
    if(connected && !updated){
        update_data();
        updated=true;
    }
    
    
}