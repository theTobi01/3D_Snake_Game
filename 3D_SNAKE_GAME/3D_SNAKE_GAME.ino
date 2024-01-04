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

// typedef struct {
//   int x;
//   int y;
//   int z;

//   int dx;
//   int dy;
//   int dz;
// } Snake;

typedef struct SnakeSegment {
  int x;
  int y;
  int z;
  int dx;
  int dy;
  int dz;
  struct SnakeSegment* next;
} SnakeSegment;

typedef struct {
  SnakeSegment* head;
} Snake;

Apple apple;

// Snake* snake;
Snake* snake;

bool button1, button2, button3, button4, button5, button6, button7, button8, button9, button10, button11, button12;
bool buttonPressedLEFT, buttonPressedUP, buttonPressed3, buttonPressedRIGHT, buttonPressedDOWN, buttonPressed6, buttonPressedBACK, 
     buttonPressed8, buttonPressed9, buttonPressedFRONT, buttonPressed11, buttonPressed12;
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
  buttonPressedLEFT = buttonPressedUP = buttonPressed3 = buttonPressedRIGHT = buttonPressedDOWN = buttonPressed6 = buttonPressedBACK = 
     buttonPressed8 = buttonPressed9 = buttonPressedFRONT = buttonPressed11 = buttonPressed12 = false;

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

  // snake = (Snake*)malloc(sizeof(Snake));
  // snake[0].x = 0;
  // snake[0].y = 0;
  // snake[0].z = 0;

  // snake[0].dx = 0;
  // snake[0].dy = 1;
  // snake[0].dz = 0;

  snake = initializeSnake();
  
  createApple();
  
  // clearAllLEDs();// turn all LEDs off at the IO Expanders

}

void gameLogic(){
  unsigned long startTime = micros();
  // gameStarted = true;

  if(gameStarted){
    
    // deleting old position of the snake:
    SnakeSegment* current = snake->head;
    while (current != NULL) {
      gameState[current->x][current->y][current->z] = 0;

      current = current->next;
    }

    // if (checkAppleCollision()) {
    //   Serial.println("Apple Collision");
    //   createApple(); // Spawns a new apple
    //   growSnake(snake); // Adds new segment to the snake's body
    // }
    

    // change direction if button was pressed
    changeDirection(snake);
    
    moveSnake(snake); // Moves the snake to the new position

    if (checkAppleCollision()) {
      Serial.println("Apple Collision");
      createApple(); // Spawns a new apple
      growSnake(snake); // Adds new segment to the snake's body
    }

    bool over = gameOver();
    bool won = isgameWon(); 

    // Update the LEDs
    if(!over && !won){
      current = snake->head;
      while (current != NULL) {
        gameState[current->x][current->y][current->z] = 1;

        current = current->next;
      }
    }
  }




  clearButtonsPressed();

  unsigned long endTime = micros();
  unsigned long executionTime = endTime - startTime;

  Serial.print("Execution time GameLogic: ");
  Serial.print(executionTime);
  Serial.println(" microseconds");
}

// setLEDs ~ 15ms, readAllButtons ~ 3ms
// GameLogic ~ 30ms
// for now run 5 micro cycles
void micro0(){ // -> 18ms
  setLEDs();
  readAllButtons();
}

void micro1(){ // -> 48ms
  setLEDs();
  readAllButtons();
  gameLogic();
}


void loop() {
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
  micro0(); sync();
  micro0(); sync();
  micro0(); sync();
  micro0(); sync();
  micro0(); sync();
  micro0(); sync();
  micro0(); sync();
  micro0(); sync();
  micro0(); sync();
  micro0(); sync();
  micro0(); sync();
  micro0(); sync();
  micro0(); sync();
  micro0(); sync();

}