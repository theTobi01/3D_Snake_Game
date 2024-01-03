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
    if (apple.x == snake[0].x && 
        apple.y == snake[0].y && 
        apple.z == snake[0].z) {
          
        apple.x = random(6);
        apple.y = random(6);
        apple.z = random(6);

        gameState[apple.x][apple.y][apple.z] = 1;
        
      return true;   
  }
  return false;
}

bool checkAppleCollision() { // Every 1 -> 0  verifys if the snake eats the apple
  Serial.print("apple = ");
  Serial.print(apple.x); Serial.print(apple.y); Serial.println(apple.z);
  Serial.print("snake = ");
  Serial.print(snake[0].x); Serial.print(snake[0].y); Serial.println(snake[0].z);
  if(apple.x == snake[0].x &&
     apple.y == snake[0].y &&
     apple.z == snake[0].z){
     
     applesEaten ++;
     gameState[apple.x][apple.y][apple.z] = 0;
    //  createApple();
     return true; 
     }else{
       return false; 
     }   
}

//bool checkAppleCreated() {  //Verify's if the Apple is created, if not game won't begin or will stop the game
//  return (apple.x != 0 || apple.y != 0 || apple.z != 0);
//}
