#include <Wire.h> // library for I2C communication
int delayTime = 200;
int clock = 1;
int signal = 0;
int wait = 20;
byte data[2] = {0};


void setup() {
  // configure Pins for switch register
  pinMode(0, OUTPUT); // D0
  pinMode(1, OUTPUT); // D1

  pinMode(LED_BUILTIN, OUTPUT);

  Wire.begin(); // join I2C bus as the master; no adress given, not necessary for master

  Serial.begin(9600);

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
  Wire.write(0x03); // set all of port A to outputs (0 = Output) 0000 0011
  Wire.endTransmission();
  Wire.beginTransmission(0x24);
  Wire.write(0x01); // IODIRB register
  Wire.write(0xC0); // set all of port B to outputs
  Wire.endTransmission();
  // Setting the internal Pull-ups
  Wire.beginTransmission(0x24);
  Wire.write(0x06); // GPPUA register
  Wire.write(0x03); // 0000 0011 (Pull-up on A0 and A1)
  Wire.endTransmission();
  Wire.beginTransmission(0x24);
  Wire.write(0x16); // IODIRA register
  Wire.write(0xC0); // 1100 0000 Pull-up on B6 and B7
  Wire.endTransmission();

  Wire.beginTransmission(0x26);
  Wire.write(0x00); // IODIRA register
  Wire.write(0x03); // set all of port A to outputs
  Wire.endTransmission();
  Wire.beginTransmission(0x26);
  Wire.write(0x01); // IODIRB register
  Wire.write(0xC0); // set all of port B to outputs
  Wire.endTransmission();
  // Setting the internal Pull-ups
  Wire.beginTransmission(0x26);
  Wire.write(0x06); // GPPUA register
  Wire.write(0x03); // 0000 0011 (Pull-up on A0 and A1)
  Wire.endTransmission();
  Wire.beginTransmission(0x26);
  Wire.write(0x16); // IODIRA register
  Wire.write(0xC0); // 1100 0000 Pull-up on B6 and B7
  Wire.endTransmission();

  Wire.beginTransmission(0x27);
  Wire.write(0x00); // IODIRA register
  Wire.write(0x03); // set all of port A to outputs
  Wire.endTransmission();
  Wire.beginTransmission(0x27);
  Wire.write(0x01); // IODIRB register
  Wire.write(0xC0); // set all of port B to outputs
  Wire.endTransmission();
  // Setting the internal Pull-ups
  Wire.beginTransmission(0x27);
  Wire.write(0x06); // GPPUA register
  Wire.write(0x03); // 0000 0011 (Pull-up on A0 and A1)
  Wire.endTransmission();
  Wire.beginTransmission(0x27);
  Wire.write(0x16); // IODIRA register
  Wire.write(0xC0); // 1100 0000 Pull-up on B6 and B7
  Wire.endTransmission();


  // setting GPA0 & GPB0 to 1 on each device
  Wire.beginTransmission(0x24);
  Wire.write(0x12); // GPIO A register
  Wire.write(0xFF); // set it to LLLLLLLH
  Wire.endTransmission();
  Wire.beginTransmission(0x24);
  Wire.write(0x13); // GPIO B register
  Wire.write(0xFF); // set it to 00000001
  Wire.endTransmission();

  Wire.beginTransmission(0x26);
  Wire.write(0x12); 
  Wire.write(0xFF); 
  Wire.endTransmission();
  Wire.beginTransmission(0x26);
  Wire.write(0x13); 
  Wire.write(0xFF); 
  Wire.endTransmission();

  Wire.beginTransmission(0x27);
  Wire.write(0x12); 
  Wire.write(0xFF); 
  Wire.endTransmission();
  Wire.beginTransmission(0x27);
  Wire.write(0x13); 
  Wire.write(0xFF); 
  Wire.endTransmission();

}

void loop() {
  // creating a clock and input signal to the Switch Register to switch between the layers
  // data inputs are logicialls ANDed, A is set to high in hardware -> we set input with B (Pin D0 of adruino)
  // CLK signal to push bits in register (Pin D1 of adruino)

  //Wire.beginTransmission(0x24);

  Wire.requestFrom(0x24, 2);

  // Check if data is available
  if (Wire.available() >= 2) {
    // Read data from the I2C device
    for (int i = 0; i < 2; i++) {
      data[i] = Wire.read();
    }
  }


  if(data[0] == 1){
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else{
    digitalWrite(LED_BUILTIN, LOW);
  }

  // Print the received data to the Serial monitor
  Serial.print("Received data: ");
  for (int i = 0; i < 2; i++) {
    Serial.print(data[i]);
    Serial.print(" ");
  }
  Serial.println();
  







  // CLK signal
  // digitalWrite(clock, HIGH);
  // delay(delayTime);
  // digitalWrite(clock, LOW);
  // digitalWrite(signal, HIGH);
  // delay(delayTime);
  // digitalWrite(clock, HIGH);
  // delay(delayTime);
  // digitalWrite(clock, LOW);
  // //sigitalWrite(signal, LOW);
  // for (int i = 0; i < wait; i++){
  //   digitalWrite(clock, HIGH);
  //   delay(delayTime);
  //   digitalWrite(clock, LOW);
  //   delay(delayTime);
  // }

  // Wire.beginTransmission(0x27);
  // Wire.write(0x13); // GPIO A register
  // Wire.write(0xFD); // set it to LLLLLLHL
  // Wire.endTransmission();

  // for (int i = 0; i < wait; i++){
  //   digitalWrite(clock, HIGH);
  //   delay(delayTime);
  //   digitalWrite(clock, LOW);
  //   delay(delayTime);
  // }

  // Wire.beginTransmission(0x27);
  // Wire.write(0x13); // GPIO A register
  // Wire.write(0xFB); // set it to LLLLLHLL
  // Wire.endTransmission();

  // for (int i = 0; i < wait; i++){
  //   digitalWrite(clock, HIGH);
  //   delay(delayTime);
  //   digitalWrite(clock, LOW);
  //   delay(delayTime);
  // }

  // Wire.beginTransmission(0x27);
  // Wire.write(0x13); // GPIO A register
  // Wire.write(0xF7); // set it to LLLLHLLL
  // Wire.endTransmission();

  // for (int i = 0; i < wait; i++){
  //   digitalWrite(clock, HIGH);
  //   delay(delayTime);
  //   digitalWrite(clock, LOW);
  //   delay(delayTime);
  // }

  // Wire.beginTransmission(0x27);
  // Wire.write(0x13); // GPIO A register
  // Wire.write(0xEF); // set it to LLLHLLLL
  // Wire.endTransmission();

  // for (int i = 0; i < wait; i++){
  //   digitalWrite(clock, HIGH);
  //   delay(delayTime);
  //   digitalWrite(clock, LOW);
  //   delay(delayTime);
  // }

  // Wire.beginTransmission(0x27);
  // Wire.write(0x13); // GPIO A register
  // Wire.write(0xDF); // set it to LLHLLLLL
  // Wire.endTransmission();

  // for (int i = 0; i < wait; i++){
  //   digitalWrite(clock, HIGH);
  //   delay(delayTime);
  //   digitalWrite(clock, LOW);
  //   delay(delayTime);
  // }

  // Wire.beginTransmission(0x27);
  // Wire.write(0x13); // GPIO A register
  // Wire.write(0xBF); // set it to LHLLLLLL
  // Wire.endTransmission();

  // for (int i = 0; i < wait; i++){
  //   digitalWrite(clock, HIGH);
  //   delay(delayTime);
  //   digitalWrite(clock, LOW);
  //   delay(delayTime);
  // }

  // Wire.beginTransmission(0x27);
  // Wire.write(0x13); // GPIO A register
  // Wire.write(0x7F); // set it to HLLLLLLL
  // Wire.endTransmission();

}
