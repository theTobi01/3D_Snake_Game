#include <Wire.h> // library for I2C communication

#define scl A4
#define sda A5
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
button1 = button2 = button3 = button4 = button5 = button6 = button7 = button8 = button9 = button10 = button11 = button12 = false;



void setDirection(int address){
  Wire.beginTransmission(address);
  Wire.write(IODIRB);
  Wire.write(0xC0); // B6 & B7 input, rest output
  Wire.endTransmission();

  Wire.beginTransmission(address);
  Wire.write(IODIRA);
  Wire.write(0x03); // A0 & A1 input, rest output
  Wire.endTransmission();
  
}

void setPullUps(int address){
  Wire.beginTransmission(address);
  Wire.write(GPPUA);
  Wire.write(0x03);
  Wire.endTransmission();

  Wire.beginTransmission(address);
  Wire.write(GPPUB);
  Wire.write(0xC0);
  Wire.endTransmission();
}

void configureIoExtenders() {
  setDirection(IOEx1);
  setPullUps(IOEx1);

  setDirection(IOEx2);
  setPullUps(IOEx2);

  setDirection(IOEx3);
  setPullUps(IOEx3);
}

void configurePins(){
  
  pinMode(init,OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

}

void readAllButtons(){
  byte dataA, dataB;
  
  // read from IOEx1
  Wire.beginTransmission(IOEx1);
  Wire.write(GPIOA); // not sure why -> test if necessary
  Wire.endTransmission();
  Wire.requestFrom(IOEx1, 2);

  dataA = Wire.read();
  dataB = Wire.read();

  Wire.endTransmission();

  dataA &= 0x03; // setting bits 2 to 7 to 0
  dataB &= 0xC0; // setting bits 0 to 5 to 0

  if ((inA & 0x01) != 0) { // checking if bit 0 is 1
    button7 = true;
  } 
  else{
    button7 = false;
  }
  if ((inA & 0x02) != 0) { // checking if bit 1 in 1
    button10 = true;
  } 
  else{
    button10 = false;
  }
  if ((inB & 0x07) != 0) {  // checking if bit 6 is 1
    button1 = true;
  } 
  else{
    button1 = false;
  }
  if ((inB & 0x08) != 0) { // checking of bit 7 is 1
    button4 = true;
  } 
  else{
    button4 = false;
  }


  // read from IOEx2
  Wire.beginTransmission(IOEx2);
  Wire.write(GPIOA); // not sure why -> test if necessary
  Wire.endTransmission();
  Wire.requestFrom(IOEx2, 2);

  dataA = Wire.read();
  dataB = Wire.read();

  Wire.endTransmission();

  dataA &= 0x03; // setting bits 2 to 7 to 0
  dataB &= 0xC0; // setting bits 0 to 5 to 0

  if ((inA & 0x01) != 0) {
    button8 = true;
  } 
  else{
    button8 = false;
  }
  if ((inA & 0x02) != 0) {
    button11 = true;
  } 
  else{
    button11 = false;
  }
  if ((inB & 0x07) != 0) {
    button2 = true;
  } 
  else{
    button2 = false;
  }
  if ((inB & 0x08) != 0) {
    button5 = true;
  } 
  else{
    button5 = false;
  }


  // read from IOEx3
  Wire.beginTransmission(IOEx3);
  Wire.write(GPIOA); // not sure why -> test if necessary
  Wire.endTransmission();
  Wire.requestFrom(IOEx3, 2);

  dataA = Wire.read();
  dataB = Wire.read();

  Wire.endTransmission();

  dataA &= 0x03; // setting bits 2 to 7 to 0
  dataB &= 0xC0; // setting bits 0 to 5 to 0

  if ((inA & 0x01) != 0) {
    button9 = true;
  } 
  else{
    button9 = false;
  }
  if ((inA & 0x02) != 0) {
    button12 = true;
  } 
  else{
    button12 = false;
  }
  if ((inB & 0x07) != 0) {
    button3 = true;
  } 
  else{
    button3 = false;
  }
  if ((inB & 0x08) != 0) {
    button6 = true;
  } 
  else{
    button6 = false;
  }
}




void setup() {

  Wire.begin(); // join I2C bus as the master; no adress given, not necessary for master
  Serial.begin(9600); // Serial connection for output to PC

  ConfigurePins();
  ConfigureIoExtenders();

}

void loop() {
  // put your main code here, to run repeatedly:

}
