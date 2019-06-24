#include <MsTimer2.h>
#include <LiquidCrystal_I2C.h>
#include <Q2HX711.h>
#include "config.h"
#include <SPI.h>
#include <SD.h>
#define uint unsigned int
#define SD_port 4
#define motor_port A1

Config cfg;
Q2HX711 main_cell1(A0,A0);
Q2HX711 main_cell2(A0,A0);
Q2HX711 water_cell(A0,A0);
Q2HX711 food_cell(A0,A0);
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

bool connected;
bool date_filled;
bool food_added;
int food_supply;
Data data;
Date date;
File file;

void setup(){
    Serial.begin(57600);
    while (!Serial);
    lcd.init();// initialize the lcd 
    lcd.backlight();

    while (!SD.begin(SD_port)) {
        print("SD Init Fail");
    }
    print("SD init done.");
    file = SD.open("weight.txt", FILE_WRITE);
    file.close();
    file = SD.open("food.txt", FILE_WRITE);
    file.close();
    file = SD.open("water.txt", FILE_WRITE);
    file.close();
    connected=false;
    date_filled=false;
    food_supply=0;
    pinMode(motor_port,OUTPUT);

    /* 
    char* new_cfg = send("cfgrequest");//"00:000" weight:food
    if(new_cfg=="no"){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("no config");
    }else{
        cfg[0]=1;
        cfg[2]=atoi(strtok(new_cfg,":"));
        cfg[3]=atoi(strtok(NULL,":"));
        delete[] new_cfg;
    }*/
    
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
    
    if (!SD.begin(SD_port)) {
        print("SD init fail");
        return;
    }
    if(date_filled){
        update_sdcard(data);
    }
    if(connected){
        send("connection check");//check connection
        delay(100);
        if(read()=="connecting"){//still connecting
            send("cfg");//check config update
            delay(100);
            if(read()=="new"){
                send("ready");
                delay(100);
                cfg.food=atoi(strtok(read(),":"));
                cfg.weight=atoi(strtok(NULL,":"));
            }
        }else{
            connected=false;//connection lost
        }
    }else{
        if(read()=="connecting request"){//new connection
            update_data();//update data from sd to client
            connected=true;
            if(!date_filled){
                send("date");
                delay(100);
                date=Date(atoi(strtok(read(),":")),atoi(strtok(NULL,":")),atoi(strtok(NULL,":")));
                MsTimer2::set(1000,time_up);
                MsTimer2::start();
                data=Data(date);
                send("weight");
                char* w=read();
                if(w!="no data") cfg.actual_weight=atoi(w);
            }
        }
    }


}