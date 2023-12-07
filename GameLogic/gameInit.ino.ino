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
  
  free(snake);
  snake = (Snake*)malloc(sizeof(Snake));
  snake[0].x = 0;
  snake[0].y = 0;
  snake[0].z = 0;
  
  snake[0].dx = 0;
  snake[0].dy = 1;
  snake[0].dz = 0;

  
}

void loop() {       
  if (!gameStarted) {
       
    createApple(); 

    if (checkAppleCreated) {
          startGame(); 
        }     
    gameStarted = true;    
  }
}
