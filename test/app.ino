//#include<Q2HX711.h>
//const int stepsPerRevolution = 200;
//Q2HX711 hx711(7, 8);
void setup() {
  /*
  Stepper myStepper(stepsPerRevolution, 14, 15, 16, 17);
  myStepper.setSpeed(motorSpeed);//0-100
  */
  Serial.begin(57600);
}

void loop() {
  /*
  myStepper.step(stepsPerRevolution / 100);*/
  Serial.print("gg");
  delay(5000);
  
}