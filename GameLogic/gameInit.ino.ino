#include <Wire.h> // library for I2C communication

#define RIGHT "RIGHT";
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

int bodySize = 0;
int delayTime = 20;

int gameState[6][6][6];

bool gameStarted = true;
int buttonState = 0;
int lastButtonState = LOW;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

unsigned long gameStartTimer = 0;


void setup() {  //Leitura na consola 
  Wire.begin();
  Serial.begin(9600);

  pinMode(2, INPUT_PULLUP);
  resetGameBoard();

  snake = (Snake*)malloc(sizeof(Snake));
  snake[0].x = 0;
  snake[0].y = 0;
  snake[0].z = 0;

  snake[0].dx = 0;
  snake[0].dy = 1;
  snake[0].dz = 0;

  createApple();

}

void loop() {  

//  int reading = digitalRead(2);
//  if (reading != lastButtonState) {
//
//    lastDebounceTime = millis();
//    
//  }
//  if ((millis() - lastDebounceTime) > debounceDelay) {
//
//    if (reading != buttonState) {
//      buttonState = reading;
//
//      if (buttonState == HIGH) {
//        //gameStarted = true;
//        gameOver();
//      }
//    }
//  }
//  lastButtonState = reading;
 
  if (gameStarted) {
    
     // Serial.print("Apple Coordinates (x, y, z): ");
     // Serial.print(apple.x);
     // Serial.print(", ");
     // Serial.print(apple.y);
     // Serial.print(", ");
     // Serial.println(apple.z);

    //Serial.print("Current size of the snake = ");
    //Serial.println(sizeof(snake));

    // Prints the current position of the snake into the game board matrix
    for (int i = 0; i < sizeof(snake); i++) {
      gameState[snake[i].x][snake[i].y][snake[i].z] = 1;
    }

    // Checks if in the new position the snake eats the apple
    if (checkAppleCollision()) {
      gameState[apple.x][apple.y][apple.z] = 0;
     
      createApple(); // If the snake ate the apple, spawns a new apple
    }

    printMatrix(); // Print the current game state

    // Moves the snake to its next position, according to the current direction, and simultanously deletes the current position (now, outdated) from the game board
    for (int i = 0 ; i < sizeof(snake); i++) { // Deletes current positions
      gameState[snake[i].x][snake[i].y][snake[i].z] = 0;
    }

    moveSnake(snake); // Moves the snake to the new position
    changeDirection("RIGHT",snake);

    // Check user input condition to exit the game

  }
}
