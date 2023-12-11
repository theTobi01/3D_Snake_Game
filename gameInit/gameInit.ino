#include <Wire.h> // library for I2C communication
struct Apple{ 
  int x;
  int y;
  int z;
};

typedef struct{
  int x;
  int y;
  int z;
  
  int dx;
  int dy;
  int dz;
}Snake;

Apple apple;

Snake* snake;

int bodySize = 0;
int delayTime = 20;
int gameState[6][6][6];

bool gameStarted = false;


bool isAppleCreated = false; //Para já não está em uso
int applesEaten;

void setup() {  //Leitura na consola
  Wire.begin();
  Serial.begin(9600);
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
  unsigned long startTime = micros();
  if (checkAppleCreated) {
    Serial.print("Current size of the snake = "); Serial.println(sizeof(snake));
    // Prints the current position of the snake into the game board matrix
    for (int i = 0; i < sizeof(snake); i++) {
      gameState[snake[i].x][snake[i].y][snake[i].z] = 1;
    }

    // Checks if in the new position the snake eats the apple
    if (checkAppleCollision()) {
      gameState[apple.x][apple.y][apple.z] = 0;
      //checkGameWon();
      Serial.println("Apple eaten!");
      createApple(); // If the snake ate the apple, spawns a new apple
    }
    printMatrix(); // Print the current game state

    // Moves the snake to its next position, according to the current direction, and simultanously deletes the current position (now, outdated) from the game board
    for (int i = 0 ; i < sizeof(snake); i++) { // Deletes current positions
      gameState[snake[i].x][snake[i].y][snake[i].z] = 0;
    }
    moveSnake(snake); // Moves the snake to the new position

    // Check user input condition to exit the game
    char c = Serial.read();
    if (c == 'q') {
      free(snake);
      // break;
    }
  }

  unsigned long endTime = micros();
  unsigned long executionTime = endTime - startTime;

  Serial.print("Execution time Game: ");
  Serial.print(executionTime);
  Serial.println(" microseconds");
}
