void updateHead(int x, int y, int z) {
  snakeHead->x = x;
  snakeHead->y = y;
  snakeHead->z = z;
}

//void bodyFirstPiece(int prevHeadX, int prevHeadY, int prevHeadZ) {
//
//    snakeBody->x = prevHeadX;
//    snakeBody->y = prevHeadY;
//    snakeBody->z = prevHeadZ;
//}
//
//void addBodyPiece(int prevBodyX,int prevBodyY,int prevBodyZ){
//    
//    for (int i = bodySize; i>1;i--){
//    snakeBody[i].x = prevBodyX;
//    snakeBody[i].y = prevBodyY;
//    snakeBody[i].z = prevBodyZ;
//    }
//}

//void growBody() {
//  Snake* newBodyPiece = (Snake*)malloc(sizeof(Snake));
//
//  newBodyPiece->x = snake[sizeof(bodySize) - 1].x;
//  newBodyPiece->y = snake[sizeof(bodySize) - 1].y;
//  newBodyPiece->z = snake[sizeof(bodySize) - 1].z;
//
//  Snake* snakeBody = (Snake*)realloc(snakeBody, sizeof(Snake) * (bodySize + 1));
//  snake[bodySize] = *newBodyPiece;
//
//  bodySize++;
//
//  free(newBodyPiece);
//}
