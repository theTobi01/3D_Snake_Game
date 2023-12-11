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

void readAllButtons(){
  unsigned long startTime = micros();

  byte dataA, dataB;
  uint16_t result;
  
  // read from IOEx1
  Wire.beginTransmission(IOEx1);
  Wire.write(GPIOA); // not sure why -> test if necessary
  Wire.endTransmission();

  Wire.requestFrom(IOEx1, 1);
  dataA = Wire.read();

  Wire.requestFrom(IOEx1, 1);
  dataB = Wire.read();

  Wire.endTransmission();

  dataA &= 0x03; // setting bits 2 to 7 to 0
  dataB &= 0xC0; // setting bits 0 to 5 to 0

  // Serial.print("Data 1A: ");
  // Serial.println(dataA, BIN);

  // Serial.print("Data 1B: ");
  // Serial.println(dataB, BIN);

  if ((dataA & 0x01) != 0) { // checking if bit 0 is 1
    button10 = false;
  } 
  else{
    button10 = true;
    buttonPressed10 = true;
  }
  if ((dataA & 0x02) != 0) { // checking if bit 1 in 1
    button7 = false;
  } 
  else{
    button7 = true;
    buttonPressed7 = true;
  }
  if ((dataB & 0x70) != 0) {  // checking if bit 6 is 1
    button1 = false;
  } 
  else{
    button1 = true;
    buttonPressed1 = true;
  }
  if ((dataB & 0x80) != 0) { // checking of bit 7 is 1
    button4 = false;
  } 
  else{
    button4 = true;
    buttonPressed4 = true;
  }


  // read from IOEx2
  Wire.beginTransmission(IOEx2);
  Wire.write(GPIOA); // not sure why -> test if necessary
  Wire.endTransmission();

  Wire.requestFrom(IOEx2, 1);
  dataA = Wire.read();

  Wire.requestFrom(IOEx2, 1);
  dataB = Wire.read();

  Wire.endTransmission();

  dataA &= 0x03; // setting bits 2 to 7 to 0
  dataB &= 0xC0; // setting bits 0 to 5 to 0

  // Serial.print("Data 2A: ");
  // Serial.println(dataA, BIN);

  // Serial.print("Data 2B: ");
  // Serial.println(dataB, BIN);

  if ((dataA & 0x01) != 0) {
    button11 = false;
  } 
  else{
    button11 = true;
    buttonPressed11 = true;
  }
  if ((dataA & 0x02) != 0) {
    button8 = false;
  } 
  else{
    button8 = true;
    buttonPressed8 = true;
  }
  if ((dataB & 0x70) != 0) {
    button2 = false;
  } 
  else{
    button2 = true;
    buttonPressed2 = true;
  }
  if ((dataB & 0x80) != 0) {
    button5 = false;
  } 
  else{
    button5 = true;
    buttonPressed5 = true;
  }


  // read from IOEx3
  Wire.beginTransmission(IOEx3);
  Wire.write(GPIOA); // not sure why -> test if necessary
  Wire.endTransmission();

  Wire.requestFrom(IOEx3, 1);
  dataA = Wire.read();

  Wire.requestFrom(IOEx3, 1);
  dataB = Wire.read();

  Wire.endTransmission();

  dataA &= 0x03; // setting bits 2 to 7 to 0
  dataB &= 0xC0; // setting bits 0 to 5 to 0

  // Serial.print("Data 3A: ");
  // Serial.println(dataA, BIN);

  // Serial.print("Data 3B: ");
  // Serial.println(dataB, BIN);

  if ((dataA & 0x01) != 0) {
    button12 = false;
  } 
  else{
    button12 = true;
    buttonPressed12 = true;
  }
  if ((dataA & 0x02) != 0) {
    button9 = false;
  } 
  else{
    button9 = true;
    buttonPressed9 = true;
  }
  if ((dataB & 0x70) != 0) {
    button3 = false;
  } 
  else{
    button3 = true;
    buttonPressed3 = true;
  }
  if ((dataB & 0x80) != 0) {
    button6 = false;
  } 
  else{
    button6 = true;
    buttonPressed6 = true;
  }

  unsigned long endTime = micros();
  unsigned long executionTime = endTime - startTime;

  Serial.print("Execution time readAllButtons: ");
  Serial.print(executionTime);
  Serial.println(" microseconds");
}

void clearButtonsPressed(){
  buttonPressed1 = buttonPressed2 = buttonPressed3 = buttonPressed4 = buttonPressed5 = buttonPressed6 = buttonPressed7 = buttonPressed8
   = buttonPressed9 = buttonPressed10 = buttonPressed11 = buttonPressed12 = false;
}

void clearAllLEDs(){
  Wire.beginTransmission(IOEx1);
  Wire.write(GPIOA);
  Wire.write(0xFF);
  Wire.endTransmission();
  Wire.beginTransmission(IOEx1);
  Wire.write(GPIOB);
  Wire.write(0xFF);
  Wire.endTransmission();

  Wire.beginTransmission(IOEx2);
  Wire.write(GPIOA);
  Wire.write(0xFF);
  Wire.endTransmission();
  Wire.beginTransmission(IOEx2);
  Wire.write(GPIOB);
  Wire.write(0xFF);
  Wire.endTransmission();
  
  Wire.beginTransmission(IOEx3);
  Wire.write(GPIOA);
  Wire.write(0xFF);
  Wire.endTransmission();
  Wire.beginTransmission(IOEx3);
  Wire.write(GPIOB);
  Wire.write(0xFF);
  Wire.endTransmission();
}