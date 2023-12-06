void clearLEDMatrix(){
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      for (int k = 0; k < 6; k++) {
        LEDMatrix[i][j][k] = 0;
      }
    }
  }
}

// void printLEDMatrix(){
//   Serial.println("Current State of the Matrix: ");
//   for (int i = 0; i < 6; i++) {
//     for (int j = 0; j < 6; j++) {
//       for (int k = 0; k < 6; k++) {
//         Serial.print(LEDMatrix[i][j][k]);
//         if (i == 0) {
//         Serial.print("  ");
//       } else if (i == 1) {
//         Serial.print("* ");
//       } else if (i == 2) {
//         Serial.print("** ");
//       } else if (i == 3) {
//         Serial.print("*** ");
//       } else if (i == 4) {
//         Serial.print("**** ");
//       } else if (i == 5) {
//         Serial.print("***** ");
//       }
//       }
//       Serial.println();
//     }
//   }
// }


void setLEDs(){
  // shift register switches on rising flank
  // set LEDS for layer -> switch Layer on -> switch layer off 

  

  // Layer 0
  setIOExpanders(0);
  // set init becasue layer 0
  digitalWrite(init, HIGH);
  // switching on the layer
  digitalWrite(clk, HIGH);
  digitalWrite(init, LOW);
  delayMicroseconds(delayTime);
  digitalWrite(clk, LOW);
  delayMicroseconds(delayTime);

  // switching off the layer
  digitalWrite(clk, HIGH);
  delayMicroseconds(delayTime);
  digitalWrite(clk, LOW);
  // Layer 1
  setIOExpanders(1);
  delayMicroseconds(delayTime);
  // switching on the layer
  digitalWrite(clk, HIGH);
  delayMicroseconds(delayTime);
  digitalWrite(clk, LOW);
  delayMicroseconds(delayTime);

  // switching off the layer
  digitalWrite(clk, HIGH);
  delayMicroseconds(delayTime);
  digitalWrite(clk, LOW);
  // Layer 2
  setIOExpanders(2);
  delayMicroseconds(delayTime);
  // switching on the layer
  digitalWrite(clk, HIGH);
  delayMicroseconds(delayTime);
  digitalWrite(clk, LOW);
  delayMicroseconds(delayTime);

  // switching off the layer
  digitalWrite(clk, HIGH);
  delayMicroseconds(delayTime);
  digitalWrite(clk, LOW);
  // Layer 3
  setIOExpanders(3);
  delayMicroseconds(delayTime);
  // switching on the layer
  digitalWrite(clk, HIGH);
  delayMicroseconds(delayTime);
  digitalWrite(clk, LOW);
  delayMicroseconds(delayTime);

  // switching off the layer
  digitalWrite(clk, HIGH);
  delayMicroseconds(delayTime);
  digitalWrite(clk, LOW);
  // Layer 4
  setIOExpanders(4);
  delayMicroseconds(delayTime);
  // switching on the layer
  digitalWrite(clk, HIGH);
  delayMicroseconds(delayTime);
  digitalWrite(clk, LOW);
  delayMicroseconds(delayTime);

  // switching off the layer
  digitalWrite(clk, HIGH);
  delayMicroseconds(delayTime);
  digitalWrite(clk, LOW);
  // Layer 5
  setIOExpanders(5);
  delayMicroseconds(delayTime);
  // switching on the layer
  digitalWrite(clk, HIGH);
  delayMicroseconds(delayTime);
  digitalWrite(clk, LOW);
  delayMicroseconds(delayTime);

  unsigned long endTime = micros();
  unsigned long executionTime = endTime - startTime;

  Serial.print("Execution time setLEDs: ");
  Serial.print(executionTime);
  Serial.println(" microseconds");

}

void setIOExpanders (int layer){
  byte buffer = 0;
  // 1A
  // invert Matrix becasue LEDs are low active
  for (int i = 0; i < 6; i++){
    buffer |= (!LEDMatrix[1][i][layer] << i+2);
  }
  // send to IO Expander
  Wire.beginTransmission(IOEx1);
  Wire.write(GPIOA);
  Wire.write(buffer);
  Wire.endTransmission();

  // reset buffer
  buffer = 0;

  // 1B
  for (int i = 0; i < 6; i++){
    buffer |= (!LEDMatrix[0][i][layer] << i);
  }
  Wire.beginTransmission(IOEx1);
  Wire.write(GPIOB);
  Wire.write(buffer);
  Wire.endTransmission();
  buffer = 0;

  // 2A
  for (int i = 0; i < 6; i++){
    buffer |= (!LEDMatrix[3][i][layer] << i+2);
  }
  Wire.beginTransmission(IOEx2);
  Wire.write(GPIOA);
  Wire.write(buffer);
  Wire.endTransmission();
  buffer = 0;

  // 2B
  for (int i = 0; i < 6; i++){
    buffer |= (!LEDMatrix[2][i][layer] << i);
  }
  Wire.beginTransmission(IOEx2);
  Wire.write(GPIOB);
  Wire.write(buffer);
  Wire.endTransmission();
  buffer = 0;

  // 3A
  for (int i = 0; i < 6; i++){
    buffer |= (!LEDMatrix[5][i][layer] << i+2);
  }
  Wire.beginTransmission(IOEx3);
  Wire.write(GPIOA);
  Wire.write(buffer);
  Wire.endTransmission();
  buffer = 0;

  // 3B
  for (int i = 0; i < 6; i++){
    buffer |= (!LEDMatrix[4][i][layer] << i);
  }
  Wire.beginTransmission(IOEx3);
  Wire.write(GPIOB);
  Wire.write(buffer);
  Wire.endTransmission();
  //buffer = 0;
}
