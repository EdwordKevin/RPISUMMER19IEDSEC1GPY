#include <LiquidCrystal_I2C.h>
#include <MsTimer2.h>
#include <Q2HX711.h>
#include "config.h"
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#define uint unsigned int
#define SD_port 10
#define motor_port A1

Config cfg;
Q2HX711 main_cell1(5,4);
Q2HX711 main_cell2(3,2);
Q2HX711 water_cell(7,6);
Q2HX711 food_cell(9,8);
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int up;
bool s_up;
bool m_up;
bool m10_up;
bool connected;
bool date_filled;
bool food_added;
int food_supply;
Data data;
Date date;
File file;

void setup(){
    pinMode(10,OUTPUT);
    Serial.begin(9600);
    while (!Serial);
   // Serial.println("sys init");
    lcd.init();// initialize the lcd
    delay(100); 
    lcd.backlight();
      lcd.setCursor(0,0);
        lcd.print("on");
    delay(100);
    /*
    if(!SD.begin(SD_port)) print("SD Init Fail");
    while (!SD.begin(SD_port)) {
        //println("sdfail");
        delay(500);
    }*/
    print("SD init done.");
   // Serial.println("sd init");
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
    s_up=false;
    m10_up=false;
    m_up=false;
    print("init end");
    up=0;
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
    print("start loop");
    /*
    if (!SD.begin(SD_port)) {
        print("SD init fail");
        return;
    }*/
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
                send("cfg init");
                delay(100);
                int len;
                String* a= split(read(),':',len);
                cfg.food=a[0].toInt();
                cfg.weight=a[1].toInt();
                delete[] a;
            }
        }else{
            connected=false;//connection lost
            print("disconnected");
        }
    }else{
        send("new connection");
        if(read()=="connecting request"){//new connection
            print("connecting");
            //Serial.println("new connect");
            //update_data();//update data from sd to client
            connected=true;
            if(!date_filled){
                send("date");
                delay(100);
                //int len;
                String buffer[3];
                buffer[0]=read();
                buffer[1]=read();
                buffer[2]=read();
                date=Date(buffer[0].toInt(),buffer[1].toInt(),buffer[2].toInt());
                //delete[] a;
                
                print(String(date.stamp)+"-"+String(date.hour)+"-"+String(date.minute));
                //MsTimer2::set(1000,time_up);
                //MsTimer2::start();
                print("count start");
                data=Data(date);
                print("date");
                send("weight");
                String w=read();
                if(w!="no data"){
                    cfg.actual_weight=w.toInt();
                    print("weight "+w);
                }
                else print("no weight data");
                date_filled=true;
            }
        }
        
    }

    /*
    measure_weight(data);
    if((date.hour==11 || date.hour==17) && !food_added){
        food_added=true;
        if(cfg.actual_weight>cfg.weight) food_supply+=cfg.actual_weight-20;
        else if(cfg.actual_weight<cfg.weight) food_supply+=cfg.actual_weight+20;
        else food_supply+=cfg.actual_weight;
    }
    if(date.hour!=11) food_added=false;
    if(date.hour==0) food_supply=0;*/
    while(get_food()<cfg.food){
        print("motor on" + String(get_food()));
        run_motor();
    }
    stop_motor();

    send("data");
    
    send(String(get_water()));
    send(String(get_food()));
    send(String(get_weight()));

    if(up%600==0  && date_filled){
        up=0;

        //measure_food(data);
        //measure_water(data);
        print("10m");
      
    }
    print("loop end");
    delay(1000);
    up++;

}