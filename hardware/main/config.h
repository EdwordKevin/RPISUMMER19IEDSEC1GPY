#ifndef __CONFIG__
#define __CONFIG__

#include <MsTimer2.h>
#include <LiquidCrystal_I2C.h>
#include <Q2HX711.h>
#include <SPI.h>
#include <SD.h>
#define uint unsigned int


class Config{
    public:
        uint food;
        uint weight;
        uint actual_weight;
        Config():food(100),weight(50),actual_weight(50){}
};

class Date{
    public:
        Date(){}
        Date(int s,int h,int m):stamp(s),hour(h),minute(m){}
        friend void operator+=(Date &a, const int& b);//add 1 minute
        int stamp;
        int hour;
        int minute;
};

class Data{
    public:
        bool new_food;//g
        bool new_water;//g
        bool new_weight;//0.1kg
        uint food;
        uint water;
        uint weight;
        uint hsy_food;
        uint hsy_water;
        Data(Date d);
        Data(){}
};

extern Config cfg;
extern Q2HX711 main_cell1;
extern Q2HX711 main_cell2;
extern Q2HX711 water_cell;
extern Q2HX711 food_cell;
extern LiquidCrystal_I2C lcd;  // set the LCD address to 0x27 for a 16 chars and 2 line display

extern bool connected;
extern bool date_filled;
extern bool food_added;
extern int food_supply;
extern Data data;
extern Date date;
extern File file;

void print(char line[]);
void measure_weight(Data& data);
void measure_food(Data& data);
void measure_water(Data& data);
int get_weight();
int get_food();
int get_water();
void run_motor();
void stop_motor();
void update_sdcard(Data& data);
void send(char line[]);
char* read();
void update_data();
void time_up();



#endif