#include <Wire.h> // library for I2C communication

void setup() {
  // configure Pins for switch register
  pinMode(0, OUTPUT); // D0
  pinMode(1, OUTPUT); // D1

  int delayTime = 10;
  int clock = 1;
  int signal = 0;

  Wire.begin(); // join I2C bus as the master; no adress given, not necessary for master

  // configuring the 3 IO Expanders -> for now all pins to output -> easier (later set GPA0 & GPA1 to input for buttons)
  /*
  Adresses of the ICs
    U1: A0. A1 -> GND & A2 -> Vcc   => 0x24
    U2: A0 -> GND & A1, A2 -> Vcc   => 0x26
    U3: A0, A1, A2 -> Vcc           => 0x27

    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    We need to set the SDA and SCL line with a Pullup to high (4.7kOhm)

  */
  Wire.beginTransmission(0x24);
  Wire.write(0x00); // IODIRA register
  Wire.write(0x00); // set all of port A to outputs (0 = Output)
  Wire.endTransmission();
  Wire.beginTransmission(0x24);
  Wire.write(0x01); // IODIRB register
  Wire.write(0x00); // set all of port B to outputs
  Wire.endTransmission();

  Wire.beginTransmission(0x26);
  Wire.write(0x00); // IODIRA register
  Wire.write(0x00); // set all of port A to outputs
  Wire.endTransmission();
  Wire.beginTransmission(0x26);
  Wire.write(0x01); // IODIRB register
  Wire.write(0x00); // set all of port B to outputs
  Wire.endTransmission();

  Wire.beginTransmission(0x27);
  Wire.write(0x00); // IODIRA register
  Wire.write(0x00); // set all of port A to outputs
  Wire.endTransmission();
  Wire.beginTransmission(0x27);
  Wire.write(0x01); // IODIRB register
  Wire.write(0x00); // set all of port B to outputs
  Wire.endTransmission();


  // setting GPA0 & GPB0 to 1 on each device
  Wire.beginTransmission(0x24);
  Wire.write(0x12); // GPIO A register
  Wire.write(0x01); // set it to 00000001
  Wire.endTransmission();
  Wire.beginTransmission(0x24);
  Wire.write(0x13); // GPIO B register
  Wire.write(0x00); // set it to 00000001
  Wire.endTransmission();

  Wire.beginTransmission(0x26);
  Wire.write(0x12); 
  Wire.write(0x00); 
  Wire.endTransmission();
  Wire.beginTransmission(0x26);
  Wire.write(0x13); 
  Wire.write(0x00); 
  Wire.endTransmission();

  Wire.beginTransmission(0x27);
  Wire.write(0x12); 
  Wire.write(0x00); 
  Wire.endTransmission();
  Wire.beginTransmission(0x27);
  Wire.write(0x13); 
  Wire.write(0x00); 
  Wire.endTransmission();

}

void loop() {
  // creating a clock and input signal to the Switch Register to switch between the layers
  // data inputs are logicialls ANDed, A is set to high in hardware -> we set input with B (Pin D0 of adruino)
  // CLK signal to push bits in register (Pin D1 of adruino)

  // CLK signal
  digitalWrite(clock, HIGH);
  delay(delayTime);
  digitalWrite(clock, LOW);
  digitalWrite(signal, HIGH);
  delay(delayTime);
  digitalWrite(clock, HIGH);
  delay(delayTime);
  digitalWrite(clock, LOW);
  digitalWrite(signal, LOW);
  delay(delayTime);
  digitalWrite(clock, HIGH);
  delay(delayTime);
  digitalWrite(clock, LOW);
  delay(delayTime);
  digitalWrite(clock, HIGH);
  delay(delayTime);
  digitalWrite(clock, LOW);

}
