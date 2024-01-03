Apple createApple() { //Creates Apple
  apple.x = random(6);
  apple.y = random(6);
  apple.z = random(6);
  
  isApplePositionInSnake();

  gameState[apple.x][apple.y][apple.z] = 1;
  return apple;
}

bool isApplePositionInSnake() {
    if (apple.x == snake[0].x && 
        apple.y == snake[0].y && 
        apple.z == snake[0].z) {
          
        apple.x = random(6);
        apple.y = random(6);
        apple.z = random(6);
        
      return true;   
  }
  return false;
}

bool checkAppleCollision() { // Every 1 -> 0  verifys if the snake eats the apple
  if(apple.x == snake[0].x &&
     apple.y == snake[0].y &&
     apple.z == snake[0].z){
     
     applesEaten ++;
     gameState[apple.x][apple.y][apple.z] = 0;
     return true; 
     }else{
       return false; 
     }   
}

//bool checkAppleCreated() {  //Verify's if the Apple is created, if not game won't begin or will stop the game
//  return (apple.x != 0 || apple.y != 0 || apple.z != 0);
//}
