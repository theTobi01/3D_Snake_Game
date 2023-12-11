#include <Wire.h> // library for I2C communication

#define scl A5
#define sda A4
#define init 2     //IO0
#define clk 3      //IO1

#define IODIRA 0x00 //Define reading Register 
#define IODIRB 0x01 //Define reading Register  

#define GPIOA 0x12 //Define writing Register  
#define GPIOB 0x13 //Define writing Register 

#define GPPUA 0x0C //Define input Register  
#define GPPUB 0x0D //Define input Register 

#define IOEx1 0x24  //IC on the left
#define IOEx2 0x26  //IC in the center
#define IOEx3 0x27  //IC on the right

// For Scheduler:
typedef struct {
 /* period in ticks */
 int period;
 /* ticks until next activation */
 int delay;
 /* function pointer */
 void (*func)(void);
 /* activation counter */
 int exec;
} Sched_Task_t;

#define NT 20 // number of tasks
Sched_Task_t Tasks[NT];
int cur_task = NT;

bool button1, button2, button3, button4, button5, button6, button7, button8, button9, button10, button11, button12;
bool buttonPressed1, buttonPressed2, buttonPressed3, buttonPressed4, buttonPressed5, buttonPressed6, buttonPressed7, 
     buttonPressed8, buttonPressed9, buttonPressed10, buttonPressed11, buttonPressed12;
int delayTime = 100;

int counter = 0;

volatile int go = 0;

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
  buttonPressed1 = buttonPressed2 = buttonPressed3 = buttonPressed4 = buttonPressed5 = buttonPressed6 = buttonPressed7 = buttonPressed8
   = buttonPressed9 = buttonPressed10 = buttonPressed11 = buttonPressed12 = false;

  digitalWrite(init, LOW);
  digitalWrite(clk, LOW);

  // Timer Configuration
  noInterrupts(); // disable all interrupts
  TCCR1A = 0; // reset registers
  TCCR1B = 0;
  TCNT1 = 0; // preload avlue set to 0
  OCR1A = 12500; // 5Hz -> Freq = 16MHz/256/compare value => compare Value = 16MHz/256/Freq
  TCCR1B |= (1 << WGM12); // CTC mode
  TCCR1B |= (1 << CS12); // 256 prescaler
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
  interrupts(); // enable all interrupts
  
  clearAllLEDs();
  clearLEDMatrix();

  // Add all the tasks
  // Parameter: function, delay (in timer ticks), period (in timer ticks), prio (0 = highest)
  // Sched_Add(setLEDs, 0, 1, 0); //13000us (with delay 1us) 15000us (with delay 100us)
  // Sched_Add(readAllButtons, 1, 1, 1); //2600us
  // Sched_Add(gameLogic, 0, 5, 2);

}

void gameLogic(){

  clearLEDMatrix();

  // LEDMatrix[0][0][0] = buttonPressed1;
  // LEDMatrix[0][1][1] = buttonPressed2;
  // LEDMatrix[0][2][2] = buttonPressed3; 
  // LEDMatrix[0][3][3] = buttonPressed4; 
  // LEDMatrix[0][4][4] = buttonPressed5; 
  // LEDMatrix[0][5][5] = buttonPressed6; 

  // LEDMatrix[1][0][0] = buttonPressed7;
  // LEDMatrix[1][1][1] = buttonPressed8;
  // LEDMatrix[1][2][2] = buttonPressed9; 
  // LEDMatrix[1][3][3] = buttonPressed10; 
  // LEDMatrix[1][4][4] = buttonPressed11; 
  // LEDMatrix[1][5][5] = buttonPressed12;

  if(buttonPressed1){
  LEDMatrix[0][0][0] = 1;
  LEDMatrix[1][1][1] = 1;
  LEDMatrix[2][2][2] = 1; 
  LEDMatrix[3][3][3] = 1; 
  LEDMatrix[4][4][4] = 1; 
  LEDMatrix[5][5][5] = 1; 
  }


  clearButtonsPressed();
}

// setLEDs ~ 15ms, readAllButtons ~ 3ms
// assume GameLogic takes half a second -> divided into parts
// for now run 5 micro cycles
void micro0(){
  setLEDs();
  readButtons();
}

void micro1(){
  setLEDs();
  readButtons();
  gameLogic();
}


void loop() {
  // Sched_Dispatch(); // needed for non preemtable

  micro0(); sync();
  micro0(); sync();
  micro0(); sync();
  micro0(); sync();
  micro1(); sync();
}