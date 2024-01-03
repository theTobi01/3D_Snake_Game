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

// BUG: doesn't work at all -> creates competly messed up coorinates
bool growSnake() {
  int snakeSize = sizeof(snake) + 1;
  Snake* newSnake = (Snake*)malloc((sizeof(snake)+1) * sizeof(Snake)); // Create new array for the new snake body

  if (newSnake != NULL) {
    // 1 - MAKES EVERY SEGMENT OF THE NEW SKIN EQUAL TO THE RESPECTIVE SEGMENT OF THE NEW SKIN (EXCEPT NEW TAIL)
    for (int i = 0; i < sizeof(snake); i++) {
      newSnake[i + 1] = snake[i];
    }

    // 2 - DETERMINE BEST POSITION FOR NEW TAIL

    Snake* new_tail = &newSnake[sizeof(newSnake)-1];
    bool valid_position = false;

    // Randomizes the new tail's position until it chooses a spot that is free (no other body segment + no apple + within game zone boundaries)
    while(!valid_position) {
      new_tail->x = random(6);
      new_tail->y = random(6);
      new_tail->z = random(6);
      if(gameState[new_tail->x][new_tail->y][new_tail->z] == 0)
        valid_position = true;
    }
    
    // 3 - GIVE NEW SKIN TO SNAKE AND DELETE OLD SKIN

    free(snake); // Free memory of the old snake body
    snake = newSnake; // Update snake pointer to point to new body
    return true;
  } else {
    Serial.println("Failed in growning snake");
    return false;
  }
}

// BUG: direction is reset to FRONT after one cycle
bool changeDirection(Snake* snake) {
    if (buttonPressedLEFT){
        snake[0].dx = -1;
        snake[0].dy = 0;
        snake[0].dz = 0;
    } else if (buttonPressedRIGHT){
        snake[0].dx = 1;
        snake[0].dy = 0;
        snake[0].dz = 0;
    } else if (buttonPressedDOWN){
        snake[0].dx = 0;
        snake[0].dy = 0;
        snake[0].dz = -1;
    } else if (buttonPressedUP){
        snake[0].dx = 0;
        snake[0].dy = 0;
        snake[0].dz = 1;
    } else if (buttonPressedFRONT){
        snake[0].dx = 0;
        snake[0].dy = 1;
        snake[0].dz = 0;
    } else if (buttonPressedBACK){
        snake[0].dx = 0;
        snake[0].dy = -1;
        snake[0].dz = 0;
    } else {
        return false;
    }
    return true; // Indicate successful direction change
}