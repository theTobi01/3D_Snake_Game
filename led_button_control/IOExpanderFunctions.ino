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

  if ((dataA & 0x01) != 0) { // checking if bit 0 is 1
    button7 = true;
  } 
  else{
    button7 = false;
  }
  if ((dataA & 0x02) != 0) { // checking if bit 1 in 1
    button10 = true;
  } 
  else{
    button10 = false;
  }
  if ((dataB & 0x07) != 0) {  // checking if bit 6 is 1
    button1 = true;
  } 
  else{
    button1 = false;
  }
  if ((dataB & 0x08) != 0) { // checking of bit 7 is 1
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

  if ((dataA & 0x01) != 0) {
    button8 = true;
  } 
  else{
    button8 = false;
  }
  if ((dataA & 0x02) != 0) {
    button11 = true;
  } 
  else{
    button11 = false;
  }
  if ((dataB & 0x07) != 0) {
    button2 = true;
  } 
  else{
    button2 = false;
  }
  if ((dataB & 0x08) != 0) {
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

  if ((dataA & 0x01) != 0) {
    button9 = true;
  } 
  else{
    button9 = false;
  }
  if ((dataA & 0x02) != 0) {
    button12 = true;
  } 
  else{
    button12 = false;
  }
  if ((dataB & 0x07) != 0) {
    button3 = true;
  } 
  else{
    button3 = false;
  }
  if ((dataB & 0x08) != 0) {
    button6 = true;
  } 
  else{
    button6 = false;
  }
}