bool gameOverBoard() {  //Verifi's if gameOver by end of the board

  if (snakeHead->x == 7 || snakeHead->y == 7 || snakeHead->z == 7) {

    allLED_ON();
    
    bodySize = 0;
    applesEaten = 0;
    gameStarted = false;

    //Snake* snake = (Snake*)malloc(sizeof(Snake));
    //Snake* snakeHead = &snake[0];
    //Body delete;
    
    Serial.println("GAME OVER");
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
