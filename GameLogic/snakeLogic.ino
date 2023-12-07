void moveSnake(Snake* snake) {
  int x_prev = -1;
  int y_prev = -1;
  int z_prev = -1;
  int x_curr, y_curr, z_curr;

  //Serial.println(sizeof(snake));
  for (int i = 0; i < sizeof(snake) ; i++) {
     x_curr = snake[i].x;
    y_curr = snake[i].y;
    z_curr = snake[i].z;

    if (i == 0) { // If it's the head
      snake[i].x += snake[i].dx;
      snake[i].y += snake[i].dy;
      snake[i].z += snake[i].dz;

    } else { // If it's not the head
      snake[i].x = x_prev;
      snake[i].y = y_prev;
      snake[i].z = z_prev;
    }
    x_prev = x_curr;
    y_prev = y_curr;
    z_prev = z_curr;
    }
}


//bool changeDirection(const char *direction, Snake* snake) {
//
//  if (strcmp(direction, "LEFT") == 0) {
//    snake[0].dx = -1;
//    snake[0].dy = 0;
//    snake[0].dz = 0;
//  } else if (strcmp(direction, "RIGHT") == 0) {
//    snake[0].dx = 1;
//    snake[0].dy = 0;
//    snake[0].dz = 0;
//  } else if (strcmp(direction, "DOWN") == 0) {
//    snake[0].dx = 0;
//    snake[0].dy = 0;
//    snake[0].dz = -1;
//  } else if (strcmp(direction, "UP") == 0) {
//    snake[0].dx = 0;
//    snake[0].dy = 0;
//    snake[0].dz = 1;
//  } else if (strcmp(direction, "FRONT") == 0) {
//    snake[0].dx = 0;
//    snake[0].dy = 1;
//    snake[0].dz = 0;
//  } else if (strcmp(direction, "BACK") == 0) {
//    snake[0].dx = 0;
//    snake[0].dy = -1;
//    snake[0].dz = 0;
//  } else {
//    return false;       
//  }
//}
//
////void bodyFirstPiece(int prevHeadX, int prevHeadY, int prevHeadZ) {
////
////    snakeBody->x = prevHeadX;
////    snakeBody->y = prevHeadY;
////    snakeBody->z = prevHeadZ;
////}
////
////void addBodyPiece(int prevBodyX,int prevBodyY,int prevBodyZ){
////
////    for (int i = bodySize; i>1;i--){
////    snakeBody[i].x = prevBodyX;
////    snakeBody[i].y = prevBodyY;
////    snakeBody[i].z = prevBodyZ;
////    }
////}
//
//void growBody(Snake* snake) {
//  Snake new_tail;
//
//  // Gets the current position of the final segment (i.e. tail) of the snake and of the segment just before that (punultimate)
//  Snake tail = snake[sizeof(snake) - 1]; // Current position of the tail
//  Snake tail_prev = snake[sizeof(snake) - 2]; // Current position of the segment that comes just before the tail
//
//  // Checks if the tail is at a game zone boundary
//  if ( (tail.x == 0 || tail.x == 6) || (tail.y == 0 || tail.y == 6) || (tail.z == 0 || tail.z == 6) ) { // If the game IS at a game zone boundary
//    // Check in which line (i.e. intersection of 2 planes) both the tail and the tail_prev segments are contained
//    if ((tail.x == tail_prev.x) && (tail.y == tail_prev.y)) { // If they are contained in the same x and y axis
//      if (tail.y == 0) {
//        new_tail.x = tail.x;
//        new_tail.z = tail.z;
//        new_tail.y = tail.y + 1;
//      } else if (tail.y == 6) {
//        new_tail.x = tail.x;
//        new_tail.z = tail.z;
//        new_tail.y = tail.y - 1;
//      } else if (tail.x == 0) {
//        new_tail.y = tail.y;
//        new_tail.z = tail.z;
//        new_tail.x = tail.x + 1;
//      } else if (tail.x == 6) {
//        new_tail.y = tail.y;
//        new_tail.z = tail.z;
//        new_tail.x = tail.x - 1;
//      }
//    } else if ((tail.y == tail_prev.y) && (tail.z == tail_prev.z)) { // If they are contained in the same y and z axis
//      if (tail.y == 0) {
//        new_tail.x = tail.x;
//        new_tail.z = tail.z;
//        new_tail.y = tail.y + 1;
//      } else if (tail.y == 6) {
//        new_tail.x = tail.x;
//        new_tail.z = tail.z;
//        new_tail.y = tail.y - 1;
//      } else if (tail.z == 0) {
//        new_tail.x = tail.x;
//        new_tail.y = tail.y;
//        new_tail.z = tail.z + 1;
//      } else if (tail.z == 6) {
//        new_tail.x = tail.x;
//        new_tail.y = tail.y;
//        new_tail.z = tail.z - 1;
//      }
//    } else if ((tail.x == tail_prev.x) && (tail.z == tail_prev.z)) { // If they are contained in the same x and z axis
//      if (tail.x == 0) {
//        new_tail.y = tail.y;
//        new_tail.z = tail.z;
//        new_tail.x = tail.x + 1;
//      } else if (tail.x == 6) {
//        new_tail.y = tail.y;
//        new_tail.z = tail.z;
//        new_tail.x = tail.x - 1;
//      } else if (tail.z == 0) {
//        new_tail.x = tail.x;
//        new_tail.y = tail.y;
//        new_tail.z = tail.z + 1;
//      } else if (tail.z == 6) {
//        new_tail.x = tail.x;
//        new_tail.y = tail.y;
//        new_tail.z = tail.z - 1;
//      }
//    }
//  } else { // If the tail IS NOT at a game zone boundary
//    // Check in which line (i.e. intersection of 2 planes) both the tail and the tail_prev segments are contained
//    if ((tail.x == tail_prev.x) && (tail.y == tail_prev.y)) { // If they are contained in the same x and y axis
//      new_tail.x = tail.x;
//      new_tail.y = tail.y;
//      if (tail.z < tail_prev.z)
//        new_tail.z = tail.z - 1;
//      else
//        new_tail.z = tail.z + 1;
//    } else if ((tail.y == tail_prev.y) && (tail.z == tail_prev.z)) { // If they are contained in the same y and z axis
//      new_tail.y = tail.y;
//      new_tail.z = tail.z;
//      if (tail.x < tail_prev.x)
//        new_tail.x = tail.x - 1;
//      else
//        new_tail.x = tail.x + 1;
//    } else if ((tail.x == tail_prev.x) && (tail.z == tail_prev.z)) { // If they are contained in the same x and z axis
//      new_tail.x = tail.x;
//      new_tail.z = tail.z;
//      if (tail.y < tail_prev.y)
//        new_tail.y = tail.y - 1;
//      else
//        new_tail.y = tail.y + 1;
//    }
//  }
//
//  // Add the new segment to the snake's body
//  snake = (Snake *)realloc(snake, (sizeof(snake) + 1) * sizeof(Snake*));
//  snake[sizeof(snake) - 1].x = new_tail.x;
//  snake[sizeof(snake) - 1].y = new_tail.y;
//  snake[sizeof(snake) - 1].z = new_tail.z;
//}
