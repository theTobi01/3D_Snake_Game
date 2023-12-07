void startGame() {
  while (gameOverBoard) {
    for (int x = 0; x < 6; x++) {
      for (int y = 0; y < 6; y++) {
        for (int z = 0; z < 6; z++) {


          //Create button logic

          Serial.println(sizeof(snake));

          for (int i = 0; i < sizeof(snake); i++) {
            Serial.print("Snake[");
            Serial.print(snake[i].x);
            Serial.print("][");
            Serial.print(snake[i].y);
            Serial.print("][");
            Serial.print(snake[i].z);
            Serial.println("]");

            gameState[snake[i].x][snake[i].y][snake[i].z] = 1;
          }

          if (checkAppleCollision()) {
            gameState[apple.x][apple.y][apple.z] = 0;
            //   checkGameWon();
            Serial.println("Apple eaten!");
            createApple();
          }
          printMatrix();
          for (int i = 0 ; i < sizeof(snake); i++) {
            gameState[snake[i].x][snake[i].y][snake[i].z] = 0;
          }
          //readVirtualMatrix();
    
          moveSnake(snake);
        }
      }
    }
  }
}
