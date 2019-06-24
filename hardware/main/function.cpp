#define uint unsigned int
#include <MsTimer2.h>
#include <LiquidCrystal_I2C.h>
#include <Q2HX711.h>
#include "config.h"
#include <SPI.h>
#include <SD.h>
#include <avr/pgmspace.h>
#define kweight 0.001
#define bweight (-10)
#define kwater 0.001
#define bwater (-10)
#define kfood 0.001
#define bfood (-10)
#define motor_port A1

Data::Data(Date d):new_food(false),new_water(false),new_weight(false){
    this->hsy_water=get_water();
    this->hsy_food=get_food();
}

void operator+=(Date &a, int const& b){
    a.minute+=b;
    a.hour+=a.minute/60;
    a.minute=a.minute%60;
    a.stamp+=60;
    if(a.hour==24) a.hour=0;
    return a;
}

void time_up(){
    static uint sec=0;
    sec++;
    if(sec%60==0) {
        date+=1;
    }
    if(sec%600==0) {
        measure_food(data);
        measure_water(data);
        sec=0;
    }
    measure_weight(data);
    if((date.hour==11 || date.hour==5) && !food_added){
        food_added=true;
        if(cfg.actual_weight>cfg.weight) food_supply+=cfg.actual_weight-20;
        else if(cfg.actual_weight<cfg.weight) food_supply+=cfg.actual_weight+20;
        else food_supply+=cfg.actual_weight;
    }
    if(date.hour!=11) food_added=false;
    if(date.hour==0) food_supply=0;
}

void measure_water(Data& data){
    int water=get_water();
    if(water-data.hsy_water>50){
        data.hsy_water=water;
    }
    if(data.hsy_water-water>50){
        if(water<200){
            print("no water");
        }else{
            data.water=data.hsy_water-water;
            data.hsy_water=water;
            data.new_water=true;
        }
    }
}

int get_water(){
    int temp=water_cell.read();
    return temp*kwater+bwater;
}

void measure_food(Data& data){
    int food=get_food();
    if(data.hsy_food-food>10){
        data.food=data.hsy_food-food;
        data.hsy_food=food;
        data.new_food=true;
    }
    if(food<50){//no food in bowl
        int time_out = 200;
        while(food_supply!=0 && get_food()<100 && time_out!=0){
            run_motor();
            delay(100);
            time_out-=1;
        }
        stop_motor();
        if(time_out==0){//out of food
            print("no_food");
        }else{
            data.hsy_food=get_food();
        }
    }  
}

int get_food(){
    int temp=food_cell.read();
    return temp*kfood+bfood;
}

void measure_weight(Data& data){
    int weight=get_weight();
    if(weight>5) {
        data.weight=weight;
        data.new_weight=true;
    }
}

int get_weight(){
    int temp=main_cell1.read();
    temp+=main_cell2.read();
    return temp*kfood+bfood;
}

void run_motor(){
    digitalWrite(motor_port,HIGH);
}

void stop_motor(){
    digitalWrite(motor_port,LOW);
}

void update_sdcard(Data& data){
    if(!SD.exists("food.txt")){
        file = SD.open("food.txt", FILE_WRITE);
        file.close();
    }
    if(data.new_food){
        file = SD.open("food.txt", FILE_WRITE);
        file.print(date.stamp);
        file.print(" ");
        file.print(data.food);
        file.println();
        file.close();
        data.new_food=false;
    }
    if(!SD.exists("food.txt")){
        file = SD.open("food.txt", FILE_WRITE);
        file.close();
    }
    if(data.new_water){
        file = SD.open("water.txt", FILE_WRITE);
        file.print(date.stamp);
        file.print(" ");
        file.print(data.water);
        file.println();
        file.close();
        data.new_water=false;
    }
    if(data.new_weight){
        file = SD.open("weight.txt", FILE_WRITE);
        file.print(date.stamp);
        file.print(" ");
        file.print(data.weight);
        file.println();
        file.close();
        data.new_weight=false;
    }
}

void print(char line[]){
    lcd.setCursor(0,0);
    lcd.print(line);
}

void send(char line[]){
    Serial.print("\n");
    Serial.print(line);
    Serial.println();
}

char* read(){
    static char* read_line="";
    char l;
    delay(100);
    while(Serial.available()){
        l=Serial.read();
        if(l=='\n') {
            break;
        }
        delay(5);
    }
    while(Serial.available()){
        l=Serial.read();
        if(l=='\n') {
            break;
        }
        read_line += l;
        delay(5);
    }
    return read_line;
}

void update_data(){
    send("update data");
    if(!read()=="ready") return;

    file=SD.open("food.txt");
    Serial.write('\n');
    while (file.available()) {
      Serial.write(file.read());
    }
    Serial.write('\n');
    file.close();
    SD.remove("food.txt");

    file=SD.open("water.txt");
    Serial.write('\n');
    while (file.available()) {
      Serial.write(file.read());
    }
    Serial.write('\n');
    file.close();
    SD.remove("water.txt");

    file=SD.open("weight.txt");
    Serial.write('\n');
    while (file.available()) {
      Serial.write(file.read());
    }
    Serial.write('\n');
    file.close();
    SD.remove("weight.txt");
}