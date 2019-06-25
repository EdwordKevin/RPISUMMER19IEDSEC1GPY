#define uint unsigned int
#include <MsTimer2.h>
#include <LiquidCrystal_I2C.h>
#include <Q2HX711.h>
#include "config.h"
#include <SPI.h>
#include <SD.h>
#include <avr/pgmspace.h>
#define kweight 0.0000458
#define bweight (-789)
#define kwater 0.00268
#define bwater (-24022)
#define kfood 0.000872
#define bfood (-7618)
#define motor_port A1

Data::Data(Date& d):new_food(false),new_water(false),new_weight(false){
    print("init data");
    hsy_water=get_water();
    hsy_food=get_food();
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
    print("time check");
    static int sec=0;
    sec++;
    if(sec%60==0) {
        m_up=true;
    }
    if(sec%600==0) {
        m10_up=true;
        sec=0;
    }
    s_up=true;

}

void measure_water(Data& data){
    print("measure water");
    int water=get_water();
    print(String(water));
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
    //return 100;
    print("get water");
    long temp=water_cell.read();
    return temp*kwater+bwater;
}

void measure_food(Data& data){
    print("measure_food");
    int food=get_food();
    print(String(food));
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
    //return 100;
    
    long temp=food_cell.read();
    //print("get food");
    return temp*kfood+bfood;
}

void measure_weight(Data& data){
    print("measure weight");
    int weight=get_weight();
    print(String(weight));
    if(weight>5) {
        data.weight=weight;
        data.new_weight=true;
    }
    
}

int get_weight(){
    print("get weight");
    long temp=main_cell1.read();
    temp+=main_cell2.read();
    return temp*kweight+bweight;
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

void print(String line){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(line);
}

void print(char c){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(c);
}

void send(String line){
    print(line);
    Serial.print('%');
    Serial.print(line);
    Serial.println('%');
}

String read(){
    String read_line="";
    char l;
    Serial.println("read");
    int s=0;
    while(!Serial.available()){
        delay(1000);
        print(String(s));
        s++;
        if(s==5) return "";
    }
    
    while(Serial.available()){
        l=Serial.read();
        if(l=='%') {
            break;
        }
        delay(10);
    }
    delay(10);
    while(Serial.available()){
        l=Serial.read();
        if(l=='%') {
            break;
        }
        read_line += l;
        delay(50);
    }
    Serial.print(read_line);
    print(read_line);
    return read_line;
}

void update_data(){
    send("update data");
    if(!read()=="ready") return;

    file=SD.open("food.txt");
    Serial.write('%');
    while (file.available()) {
      Serial.write(file.read());
    }
    Serial.write('%');
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

String* split(String a, char b,int& len){
    print("enter");
    len=0;
    for(int i=0;i<a.length();++i){
        if(a[i]==b) len++;
    }
    print("c");
    String* save=new String[len+1];
    for(int i=0;i<len+1;i++){
        save[i]="";
    }

    len=0;
    for(int i=0;i<a.length();++i){
        if (a[i]==b){
            len++;
            Serial.println(a[i]);
            continue;
        }else{
            save[len]+=a[i];
        }
    }
    print("end");
    return save;
}