// Function to initialize the snake with a single segment
Snake* initializeSnake() {
  Snake* snake = (Snake*)malloc(sizeof(Snake));
  if (snake != NULL) {
    snake->head = (SnakeSegment*)malloc(sizeof(SnakeSegment));
    if (snake->head != NULL) {
      snake->head->x = 0;
      snake->head->y = 0;
      snake->head->z = 0;
      snake->head->dx = 0;
      snake->head->dy = 1;
      snake->head->dz = 0;
      snake->head->next = NULL;
      return snake;
    } else {
      free(snake);
      return NULL;
    }
  } else {
    return NULL;
  }
}

// Function to move the snake
void moveSnake(Snake* snake) {
  SnakeSegment* current = snake->head;
  int x_prev, y_prev, z_prev;
  while (current != NULL) {
    int x_curr = current->x;
    int y_curr = current->y;
    int z_curr = current->z;

    if (current == snake->head) {
      current->x += current->dx;
      current->y += current->dy;
      current->z += current->dz;
    } else {
      current->x = x_prev;
      current->y = y_prev;
      current->z = z_prev;
    }

    x_prev = x_curr;
    y_prev = y_curr;
    z_prev = z_curr;

    current = current->next;
  }
}

void growSnake(Snake* snake) {
    SnakeSegment* newSegment = (SnakeSegment*)malloc(sizeof(SnakeSegment));
    SnakeSegment* current = snake->head;
    
    newSegment->x = 0;
    newSegment->y = 0;
    newSegment->z = 0;
    newSegment->next = NULL;
    
    // if (current == NULL) {
    //     snake->head = newSegment;
    //     return;
    // }

    while (current->next != NULL) {
        current = current->next;
    }
        
    newSegment->x = current->x;
    newSegment->y = current->y;
    newSegment->z = current->z;

    current->next = newSegment;
  
}


// Function to change the direction of the snake
void changeDirection(Snake* snake, int dx, int dy, int dz) {
  if (snake->head != NULL) {
    snake->head->dx = dx;
    snake->head->dy = dy;
    snake->head->dz = dz;
  }
}

bool changeDirection(Snake* snake) {
  if (snake->head != NULL) {
    if (buttonPressedLEFT){
        snake->head->dx = -1;
        snake->head->dy = 0;
        snake->head->dz = 0;
    } else if (buttonPressedRIGHT){
        snake->head->dx = 1;
        snake->head->dy = 0;
        snake->head->dz = 0;
    } else if (buttonPressedDOWN){
        snake->head->dx = 0;
        snake->head->dy = 0;
        snake->head->dz = -1;
    } else if (buttonPressedUP){
        snake->head->dx = 0;
        snake->head->dy = 0;
        snake->head->dz = 1;
    } else if (buttonPressedFRONT){
        snake->head->dx = 0;
        snake->head->dy = 1;
        snake->head->dz = 0;
    } else if (buttonPressedBACK){
        snake->head->dx = 0;
        snake->head->dy = -1;
        snake->head->dz = 0;
    } else {
      return false;
    }
    return true;
  }
}

// Function to free the memory occupied by the snake
void destroySnake(Snake* snake) {
  SnakeSegment* current = snake->head;
  while (current != NULL) {
    SnakeSegment* temp = current;
    current = current->next;
    free(temp);
  }
  free(snake);
}
