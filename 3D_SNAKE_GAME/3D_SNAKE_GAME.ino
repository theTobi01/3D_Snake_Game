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

struct Apple {
  int x;
  int y;
  int z;
};

typedef struct {
  int x;
  int y;
  int z;

  int dx;
  int dy;
  int dz;
} Snake;

Apple apple;

Snake* snake;

bool button1, button2, button3, button4, button5, button6, button7, button8, button9, button10, button11, button12;
bool buttonPressed1, buttonPressed2, buttonPressed3, buttonPressed4, buttonPressed5, buttonPressed6, buttonPressed7, 
     buttonPressed8, buttonPressed9, buttonPressed10, buttonPressed11, buttonPressed12;
int delayTimeShort = 1;
int delayTimeLong = 1500;

int applesEaten = 0;
bool gameStarted = true;

int counter = 0;

volatile int go = 0;

int gameState[6][6][6] = {};
// first dimension left -> right
// second dimension back -> front
// third dimension layer


void configurePins(){
  
  pinMode(init,OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

}

void sync(){
  while(!go) {}; //wait
  go = 0; // reset Flag
}

ISR(TIMER1_COMPA_vect){//timer1 interrupt
  go = 1;
  // Sched_Schedule();
  // Sched_Dispatch(); // needed for preemtable
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
  OCR1A = 3125; // 20Hz -> Freq = 16MHz/256/compare value => compare Value = 16MHz/256/Freq
  TCCR1B |= (1 << WGM12); // CTC mode
  TCCR1B |= (1 << CS12); // 256 prescaler
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
  interrupts(); // enable all interrupts

  resetGameBoard();

  snake = (Snake*)malloc(sizeof(Snake));
  snake[0].x = 0;
  snake[0].y = 0;
  snake[0].z = 0;

  snake[0].dx = 0;
  snake[0].dy = 1;
  snake[0].dz = 0;
  
  createApple();
  
  clearAllLEDs();// turn all LEDs off at the IO Expanders

}

void gameLogic(){

  if (gameStarted) {
    // Prints the current position of the snake into the game board matrix
    for (int x = 0; x <7 ; x++) {
      for (int y = 0; y < 7; y++) {
        for (int z = 0; z < 7; z++) {

          // 1 - PRINT CURRENT POSITION OF THE SNAKE INTO THE GAMEBOARD
          for (int i = 0; i < sizeof(snake); i++) {
            gameState[snake[i].x][snake[i].y][snake[i].z] = 1;
          }

          // 2 - CHECKS IF IN THE NEW POSITION THE SNAKE EATS THE APPLE
          //     IF SNAKE EATS APPLE -> 1) SPAWNS NEW APPLE IN THE GAMEBOARD + 2) GROW SNAKE
          if (checkAppleCollision()) {
            createApple(); // Spawns a new apple
            growSnake(); // Adds new segment to the snake's body
          }
          
          // 3 - PRINT CURRENT GAMEBOARD
          /*
          printMatrix(); // Print the current game state
          readVirtualMatrix();
          */

          // 4 - MOVES THE SNAKE ACCORDING TO ITS CURRENT DIRECTION
          for (int i = 0 ; i < sizeof(snake); i++) { // Deletes previous snake position
            gameState[snake[i].x][snake[i].y][snake[i].z] = 0;
          }
          moveSnake(snake); // Moves the snake to the new position

          gameOver();
          isgameWon();           
        }
      }
    }

  }

  
  clearButtonsPressed();
}

// setLEDs ~ 15ms, readAllButtons ~ 3ms
// assume GameLogic takes half a second -> divided into parts
// for now run 5 micro cycles
void micro0(){
  setLEDs();
  readAllButtons();
}

void micro1(){
  setLEDs();
  readAllButtons();
  gameLogic();
}


void loop() {

  micro0(); sync();
  micro0(); sync();
  micro0(); sync();
  micro0(); sync();
  micro0(); sync();
  micro0(); sync();
  micro0(); sync();
  micro0(); sync();
  micro0(); sync();
  micro1(); sync();
  micro0(); sync();
  micro0(); sync();
  micro0(); sync();
  micro0(); sync();
  micro0(); sync();
  micro0(); sync();
  micro0(); sync();
  micro0(); sync();
  micro0(); sync();
  micro1(); sync();
}