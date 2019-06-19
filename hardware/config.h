#ifndef __CONFIG__
#define __CONFIG__
#include <arduino.h>
#include <Stepper.h>
#include <LiquidCrystal_I2C.h>

Q2HX711 main_cell1(A0,A0);
Q2HX711 main_cell2(A0,A0);
Q2HX711 water_cell(A0,A0);
Q2HX711 food_cell(A0,A0);
Q2HX711 bluetooth[6];
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
int sd[4];
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
bool connected;
bool updated;
bool date_filled;
bool cfg_filled;

class date{
    public:
        date(int a);
        String get();
        friend date operator+=(date &a, int& b);
    private:
        int year;
        int month;
        int day;
};

String read_bt();
int measure_weight();
int measure_food();
int measure_water();
int run_motor(int step);
int update_sdcard(String data);
bool update_data();





#endif