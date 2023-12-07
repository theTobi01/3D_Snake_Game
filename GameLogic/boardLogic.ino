//bool isgameWon(){
//  if (bodySize >= 20){
//    Serial.println("Game WON");
//        bodySize = 0;
//    applesEaten = 0;
//    gameStarted = false;
//    
//  }
//}

bool gameOverBoard() {  //Verifi's if gameOver by end of the board

  if (snake[0].x == 7 || snake[0].y == 7 || snake[0].z == 7) {

    allLED_ON();
    
    bodySize = 0;
    applesEaten = 0;
    gameStarted = false;

    //Snake* snake = (Snake*)malloc(sizeof(Snake));
    //Snake* snakeHead = &snake[0];
    //Body delete;
    
    Serial.println("GAME OVER");
    free(snake);
    resetGameBoard();
    startGame();

    return true;
  } else {
    return false;
  }
}

void allLED_ON() {
  for (int x = 0; x <= 6; x++) {
    for (int y = 0; y <= 6; y++) {
      for (int z = 0; z <= 6; z++) {
        gameState[x][y][z] = 1;
        readVirtualMatrix();
      }
    }
  }
}


void printMatrix(){
  for(int y = 0 ; y < 6 ; y++) {
    for(int x = 0 ; x < 6 ; x++) {
        for(int z = 5 ; z >= 0 ; z--) {
            Serial.print(gameState[x][y][z]);
            Serial.print(" ");
        }
        Serial.println();
    }
    Serial.println();
    Serial.print("Layer y = ");
    Serial.println(y);
    Serial.println();
}
Serial.println(" new cycle ");
}

void resetGameBoard() { //Inicialize virtual LEDs state matrix with all 0 TUDO DESLIGADO
  int x, y, z;
  for (int x = 0; x < 6; x++) {
    for (int y = 0; y < 6; y++) {
      for (int z = 0; z < 1; z++) {
        gameState[x][y][z] = 0;
      }
    }
   }
  }


void readVirtualMatrix() {  //Lê Todas as posições da matriz uma a uma
  Serial.println("Reading Game State matrix:");
  for (int x = 0; x < 6; x++) {
    for (int y = 0; y < 6; y++) {
      for (int z = 0; z < 6; z++) {
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
