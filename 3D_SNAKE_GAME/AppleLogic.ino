Apple createApple() { //Creates Apple
  apple.x = random(6);
  apple.y = random(6);
  apple.z = random(6);
  
  isApplePositionInSnake();

  gameState[apple.x][apple.y][apple.z] = 1;
  Serial.println("Apple Created");
  return apple;
}

bool isApplePositionInSnake() {
    if (apple.x == snake->head->x && 
        apple.y == snake->head->y && 
        apple.z == snake->head->z) {
          
        apple.x = random(6);
        apple.y = random(6);
        apple.z = random(6);

        gameState[apple.x][apple.y][apple.z] = 1;
        
      return true;   
  }
  return false;
}

bool checkAppleCollision() { // Every 1 -> 0  verifys if the snake eats the apple
  if(apple.x == snake->head->x && 
     apple.y == snake->head->y && 
     apple.z == snake->head->z){
     
     applesEaten ++;
     gameState[apple.x][apple.y][apple.z] = 0;
    //  createApple();
     return true; 
     }else{
       return false; 
     }   
}

