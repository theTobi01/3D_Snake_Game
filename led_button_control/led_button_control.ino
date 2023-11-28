#include <Wire.h> // library for I2C communication

#define scl A5
#define sda A4
#define init 0     //IO0
#define clk 1      //IO1

#define IODIRA 0x00 //Define reading Register 
#define IODIRB 0x01 //Define reading Register  

#define GPIOA 0x12 //Define writing Register  
#define GPIOB 0x13 //Define writing Register 

#define GPPUA 0x0C //Define input Register  
#define GPPUB 0x0D //Define input Register 

// U1: A0. A1 -> GND & A2 -> Vcc   => 0x24
// U2: A0 -> GND & A1, A2 -> Vcc   => 0x26
// U3: A0, A1, A2 -> Vcc           => 0x27
#define IOEx1 0x24  //IC on the left
#define IOEx2 0x26  //IC in the center
#define IOEx3 0x27  //IC on the right

bool button1, button2, button3, button4, button5, button6, button7, button8, button9, button10, button11, button12;
int delayTime = 200;

int counter = 0;

int LEDMatrix[6][6][6] = {};
// first dimension left -> right
// second dimension back -> front
// third dimension layer


void configurePins(){
  
  pinMode(init,OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

}

void setup() {

  Wire.begin(); // join I2C bus as the master; no adress given, not necessary for master
  Serial.begin(9600); // Serial connection for output to PC

  configurePins();
  configureIoExtenders();
  button1 = button2 = button3 = button4 = button5 = button6 = button7 = button8 = button9 = button10 = button11 = button12 = false;

  // Test program for buttons:
  // just write something in the shift register to make some LEDs light up
  digitalWrite(init, LOW);
  // digitalWrite(clk, HIGH);
  // delay(delayTime/10);
  // digitalWrite(clk, LOW);
  // delay(delayTime/10);
  // digitalWrite(clk, HIGH);
  // delay(delayTime/10);
  // digitalWrite(clk, LOW);
  // delay(delayTime/10);
  // digitalWrite(clk, HIGH);
  // delay(delayTime/10);
  // digitalWrite(clk, LOW);
  // delay(delayTime/10);
  // digitalWrite(clk, HIGH);
  // delay(delayTime/10);
  // digitalWrite(clk, LOW);

  clearAllLEDs();
  clearLEDMatrix();
  LEDMatrix[0][0][0] = 1;
  LEDMatrix[1][1][1] = 1;
  LEDMatrix[2][2][2] = 1;
  LEDMatrix[3][3][3] = 1;
  LEDMatrix[4][4][4] = 1;
  LEDMatrix[5][5][5] = 1;

}

void loop() {
  // Test program for buttons:

  // readAllButtons();

  // byte leftRow = 0;
  // byte secondLeftRow = 0;

  // // save button status in bytes (B6&7 stay empty)
  // leftRow |= (button1 << 0);
  // leftRow |= (button2 << 1);
  // leftRow |= (button3 << 2);
  // leftRow |= (button4 << 3);
  // leftRow |= (button5 << 4);
  // leftRow |= (button6 << 5);

  // // A0&1 stay empty
  // secondLeftRow |= (button7 << 2);
  // secondLeftRow |= (button8 << 3);
  // secondLeftRow |= (button9 << 4);
  // secondLeftRow |= (button10 << 5);
  // secondLeftRow |= (button11 << 6);
  // secondLeftRow |= (button12 << 7);


  // // send Buttons status to LEDs
  // Wire.beginTransmission(IOEx1);
  // Wire.write(GPIOB);
  // Wire.write(leftRow);
  // Wire.endTransmission();

  // Wire.beginTransmission(IOEx1);
  // Wire.write(GPIOA);
  // Wire.write(secondLeftRow);
  // Wire.endTransmission();

  //delay(1000);

  setLEDs();


}
