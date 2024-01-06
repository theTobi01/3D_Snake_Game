bool isgameWon(){
  if (applesEaten > 2){

    allLED_ON();   
    resetGameBoard();   
    destroySnake(snake);
    applesEaten = 0;
    gameStarted = false;
   return true;
  }else
  return false;
}

bool gameOver() {  //Verifi's if gameOver by end of the board
  SnakeSegment* current = snake->head;

  if (snake->head->x == 6 || snake->head->y == 6 || snake->head->z == 6 || snake->head->x == -1 || snake->head->y == -1 || snake->head->z == -1) {
   // allLED_ON();    
    resetGameBoard();   
    destroySnake(snake);
    applesEaten = 0;
    gameStarted = false;
    return true;
  }else{  
    current = current->next;   
    while (current->next != NULL) {
            
      if(snake->head->x == current->x && 
        snake->head->y == current->y && 
        snake->head->z == current->z){
          
        resetGameBoard();   
        destroySnake(snake);
        applesEaten = 0;
        gameStarted = false;
        return true;            
      } 
      current = current->next;
    }
  } 
  return false;
}

bool gameOverButton(){   
  // moves snake head out of the game board so game over is caused on the next game cycle
  snake->head->x = 6;
  snake->head->y = 6;
  snake->head->z = 6;

  return true;
}



void allLED_ON() {
  for (int x = -1; x <= 5; x++) {
    for (int y = -1; y <= 5; y++) {
      for (int z = -1; z <= 5; z++) {
        gameState[x][y][z] = 1;
        //printMatrix();
      }
    }
  }
}
void resetGameBoard() { //Inicialize virtual LEDs state matrix with all 0 TUDO DESLIGADO
  for (int x = 0; x < 6; x++) {
    for (int y = 0; y < 6; y++) {
      for (int z = 0; z < 6; z++) {
        gameState[x][y][z] = 0;
      }
    }
  }
}


void printMatrix() {
  for (int y = 0 ; y < 6 ; y++) {
    for (int x = 0 ; x < 6 ; x++) {
      for (int z = 5 ; z >= 0 ; z--) {
        Serial.print(gameState[x][y][z]);
        Serial.print(" ");
      }
      Serial.println();
    }
    Serial.print("Layer y = ");
    Serial.println(y);
    Serial.println();
  }
  Serial.println(" new cycle ");
}
void readVirtualMatrix() {  //Lê Todas as posições da matriz uma a uma
  Serial.println("Reading Game State matrix:");
  for (int x = 0; x < 1; x++) {
    for (int y = 0; y < 5; y++) {
      for (int z = 0; z < 1; z++) {

        //isAppleColision();

        Serial.print("Position[");
        Serial.print(x);
        Serial.print("][");
        Serial.print(y);
        Serial.print("][");
        Serial.print(z);
        Serial.print("]: ");
        Serial.println(gameState[x][y][z]);
      }
    }
  }
}


void startGame(){

  gameStarted = true;

  resetGameBoard();

  createApple();

  snake = initializeSnake();
}