void startGame() {
  bodySize = 0;
  applesEaten = 0;
  
  while (gameOverBoard) {
    for (int x = 0; x <= 6; x++) {
      for (int y = 0; y <= 6; y++) {
        for (int z = 0; z <= 6; z++) {

          int prevHeadX = snakeHead->x;
          int prevHeadY = snakeHead->y;
          int prevHeadZ = snakeHead->z;

//          int prevBodyX = snakeBody->x;
//          int prevBodyY = snakeBody->y;
//          int prevBodyZ = snakeBody->z;

//          if (applesEaten == 1) {
//            bodyFirstPiece(prevHeadX, prevHeadY, prevHeadZ);
//
//            gameState[snakeBody->x][snakeBody->y][snakeBody->z] = 1;
//
//          } else if (applesEaten > 1) {
//
//            bodyFirstPiece(prevHeadX, prevHeadY, prevHeadZ);
//
//            addBodyPiece(prevBodyX, prevBodyY, prevBodyZ);
//
//            gameState[snakeBody->x][snakeBody->y][snakeBody->z] = 1;
//          }

          updateHead(x, y, z);

          gameState[snakeHead->x][snakeHead->y][snakeHead->z] = 1;

          if (checkAppleCollision()) {
            gameState[apple.x][apple.y][apple.z] = 0;
        //    growBody();

            Serial.println("Apple eaten!");
            createApple();
          }
          readVirtualMatrix();
          gameState[snakeHead -> x][snakeHead -> y][snakeHead -> z] = 0;
        }
      }
    }
  }
}
