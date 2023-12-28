#include <Wire.h> // library for I2C communication
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

int delayTime = 20;
int applesEaten;
int gameState[6][6][6];

bool gameStarted = true;
int buttonState = 0;

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
  
  applesEaten = 0;
  createApple();

}

void loop() {
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
}