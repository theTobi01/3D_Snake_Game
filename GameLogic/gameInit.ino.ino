#include <Wire.h> // library for I2C communication

int delayTime = 20;
int gameState[6][6][6];

bool gameStarted = false;

struct Apple{ 
  int x;
  int y;
  int z;
};

typedef struct{
  int x;
  int y;
  int z;
}Snake;

Apple apple;

Snake* snake = (Snake*)malloc(sizeof(Snake));
Snake* snakeHead = &snake[0];

int bodySize = 0;


bool isAppleCreated = false; //Para já não está em uso
int applesEaten;

void setup() {  //Leitura na consola
  Wire.begin();
  Serial.begin(9600);
  resetGameBoard();
}

void loop() {       
  if (!gameStarted) {
       
    createApple(); //Criação do objeto appl
    if (checkAppleCreated) {
          startGame(); 
        }     
    gameStarted = true;  //Jogo começou   
  }
}
