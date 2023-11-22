#include <Wire.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define initial 3
#define clk 2
#define sda 18
#define scl 19

#define freq 1
#define delayinit 70

#define IODIRB 0x01
#define IODIRA 0x00
#define GPIOA 0x12
#define GPIOB 0x13
#define GPPUA 0x0C
#define GPPUB 0x0D

#define latchLeft 0x27
#define latchCenter 0x26
#define latchRight 0x24
#define minCycles 50
int maxCycles = 400;


int num0[15] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0};
int num1[15] = {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1};
int num2[15] = {0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0};
int num3[15] = {0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0};
int num4[15] = {1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0};
int num5[15] = {0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0};
int num6[15] = {0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0};
int num7[15] = {1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0};
int num8[15] = {0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0};
int num9[15] = {0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0};

int setInitLow = 1;
int floorNum = 0;
int cycles = 0;
int gameOver = 0;
int gameOverSetup = 1;
boolean refresh = false;
int gameState[6][6][6];
int createNewPiece = 1;

boolean downM = false;
boolean leftM = false;
boolean rightM = false;
boolean backM = false;
boolean frontM = false;

boolean slideRightR = false;
boolean slideLeftR = false;
boolean rightR = false;
boolean leftR = false;
boolean frontR = false;
boolean backR = false;

int score = 14;



typedef enum {
  I, O, T, S, Z, J, L
} PieceType;

typedef enum{
  left, right, down, front, back, slideRight, slideLeft
} Direction;

typedef struct{
  int line;
  int col;
  int height;
} Block;

typedef struct{
	PieceType type;
	Block blocks[4];

} Piece;


typedef struct{
  int line;
  int col;
  int height;
} NumBlock;



typedef struct{
  NumBlock blocks[15];
  int values[15];

} Number;

Piece currentPiece;
Number leftNum;
Number rightNum;

void setup() {
  // put your setup code here, to run once:
  Wire.begin(); // Start I2C Bus as Master
  pinMode(initial, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(sda, OUTPUT);
  pinMode(scl, OUTPUT);
  Serial.begin(9600);

  randomSeed(analogRead(0));
  
  digitalWrite(initial, HIGH);

  setAsOutput(latchLeft);
  setAsOutput(latchRight);
  setAsOutput(latchCenter);
  setAsPullUp(latchLeft);
 setAsPullUp(latchCenter);
 setAsPullUp(latchRight);

  int i, j, k;


createEmptyArray();
for(i = 0; i < 6; i++)
for(j = 0; j < 5; j++)
gameState[i][j][0] = 0;

gameState[5][5][0] = 0;
gameState[0][5][0] = 0;




  clear();

}

void loop() {

  displayLeds();


  if(gameOver && gameOverSetup)  
  {
      setupScore();
      gameOverSetup = 0;
  }
  else
      gameCycle();

    
}

Number createNumber(int number, int isLeft){

  Number num;

  int i;
  int line;

  if(isLeft)
    line = 5;
  else
    line = 2;


  int valuesArray[15] = {0};
  
  switch(number){
      case 0:
        memcpy(num.values, num0, sizeof(int) * 15);
        break;
      case 1:
        memcpy(num.values, num1, sizeof(int) * 15);
        break;
      case 2:
        memcpy(num.values, num2, sizeof(int) * 15);
        break;
      case 3:
        memcpy(num.values, num3, sizeof(int) * 15);
        break;
      case 4:
        memcpy(num.values, num4, sizeof(int) * 15);
        break;
      case 5:
        memcpy(num.values, num5, sizeof(int) * 15);
        break;
      case 6:
        memcpy(num.values, num6, sizeof(int) * 15);
        break;
      case 7:
        memcpy(num.values, num7, sizeof(int) * 15);
        break;
      case 8:
        memcpy(num.values, num8, sizeof(int) * 15);
        break;
      case 9:
        memcpy(num.values, num9, sizeof(int) * 15);
        break;
        
       
  }


    for(int i = 0; i < 15; ++i){
      num.blocks[i].col = 5;
    if(i < 5){
      num.blocks[i].line = line;
      num.blocks[i].height = i;
    }
    else if(i < 10){
      num.blocks[i].line = line - 1;
      num.blocks[i].height = i -5 ;
    }
    else{
      num.blocks[i].line = line - 2;
      num.blocks[i].height = i - 10;
    }
  }

  return num;
}

void setupScore(){

    int leftDigit = score / 10;
    int rightDigit = score % 10;

    leftNum = createNumber(leftDigit, 1);
    rightNum = createNumber(rightDigit, 0);
    clear();

 
}

void displayLeds(){

    if(floorNum > 11)
    floorNum = 0;

  if(floorNum % 2 != 40){
    if(!gameOver)
      writeFloor();
    else
      writeFloorNum();
  }
  digitalWrite(clk, HIGH);
  

  digitalWrite(clk, LOW);
  
  
  if(setInitLow == 1){
    digitalWrite(initial, LOW);
  }

  setInitLow++;
  if(setInitLow > 12){
    digitalWrite(initial, HIGH);
    setInitLow = 1;
  }

    ++floorNum;
}

void gameCycle(){
  
    ++cycles;

  if(createNewPiece){

      int pieceRand = random(7);
      PieceType type;
      switch(pieceRand){
        case 0:
          type = I;
          break;
        case 1:
          type = O;
          break;
        case 2:
          type = J;
          break;
        case 3:
          type = L;
          break;
        case 4:
          type = S;
          break;
        case 5:
          type = Z;
          break;
        case 6:
          type = T;
          break;
      }
    
      currentPiece = createPiece(type);
      createNewPiece = 0;
    }

    if(cycles >= maxCycles){
      cycles = 0;
      invokeMovePiece(down);
    }

    if(cycles % 15 == 0)
    readButton();

  if(downM){
    invokeMovePiece(down);
    downM = false;
  }
    if(frontM){
    invokeMovePiece(front);
    frontM = false;
  }
    if(backM){
    invokeMovePiece(back);
    backM = false;
  }  
  if(leftM){
    invokeMovePiece(left);
    leftM = false;
  }  
  if(rightM){
    invokeMovePiece(right);
    rightM = false;
  }
/*ROTATE*/
    if(slideRightR){
    invokeRotatePiece(slideRight);
    slideRightR = false;
  }
    if(slideLeftR){
    invokeRotatePiece(slideLeft);
    slideLeftR = false;
  }
    if(frontR){
    invokeRotatePiece(front);
    frontR = false;
  }
    if(backR){
    invokeRotatePiece(back);
    backR = false;
  }  
  if(leftR){
    invokeRotatePiece(left);
    leftR = false;
  }  
  if(rightR){
    invokeRotatePiece(right);
    rightR = false;
  }
    


}

void readButton(){

  byte inA, inB, inC, inD, inE, inF;
  
  Wire.beginTransmission(latchLeft);
  Wire.write(GPIOA);
  Wire.endTransmission();
  Wire.requestFrom(latchLeft, 2);

  inA = Wire.read();
  inB = Wire.read();

  inA &= 0x03;
  inB &= 0xC0;

  if(inA == 1)
    if(maxCycles > minCycles)
      maxCycles -= 50;
  if(inA == 2)
    rightM = true;
   if(inB == 64)
    backM = true;
  if(inB == 128)
    frontM = true;

  Wire.endTransmission();

  Wire.beginTransmission(latchCenter);
  Wire.write(GPIOA);
  Wire.endTransmission();
  Wire.requestFrom(latchCenter, 2);

  inC = Wire.read();
  inD = Wire.read();

  inC &= 0x03;
  inD &= 0xC0;

  if(inC == 1)
    downM = true;
  if(inC == 2)
    leftM = true;
   if(inD == 64)
    rightR = true;
  if(inD == 128)
    slideRightR = true;

  Wire.endTransmission();

  Wire.beginTransmission(latchRight);
  Wire.write(GPIOA);
  Wire.endTransmission();
  Wire.requestFrom(latchRight, 2);

  inE = Wire.read();
  inF = Wire.read();

  inE &= 0x03;
  inF &= 0xC0;

  if(inE == 1)
    frontR = true;
  if(inE == 2)
    backR = true;
   if(inF == 64)
    leftR = true;
  if(inF == 128)
    slideLeftR = true;

  Wire.endTransmission();

}

void setAsOutput(int address){
  Wire.beginTransmission(address);
  Wire.write(IODIRB);
  Wire.write(0xC0); // set all of port B to outputs
  Wire.endTransmission();

  Wire.beginTransmission(address);
  Wire.write(IODIRA);
  Wire.write(0x03); // set all of port A to outputs
  Wire.endTransmission();
  
}

void setAsPullUp(int address){
  Wire.beginTransmission(address);
  Wire.write(GPPUA);
  Wire.write(0x03);
  Wire.endTransmission();

  Wire.beginTransmission(address);
  Wire.write(GPPUB);
  Wire.write(0xC0);
  Wire.endTransmission();
}


void clear(){

  writeToLed(latchLeft, GPIOA, 0xFF);
  writeToLed(latchLeft, GPIOB, 0xFF);
  writeToLed(latchCenter, GPIOA, 0xFF);
  writeToLed(latchCenter, GPIOB, 0xFF);
  writeToLed(latchRight, GPIOA, 0xFF);
  writeToLed(latchRight, GPIOB, 0xFF); 
}

int convertArray(int array[]){

  float value = 0;
  int i;

  for(i = 5; i >= 0; --i){

    value += (array[i] * pow(2, i+2));
  
  }

  return (int)ceil(value);     
}

int convertArrayB(int array[]){


  float value = 0;
  int i;

  for(i = 0; i < 6; ++i){

    value += (array[i] * pow(2, i));
  
  }


  return (int)ceil(value);     
}

boolean checkChanges(){
  return true;
}

void writeFloorNum(){
    int floorArray[6][6];

  int i, j;

  for(i = 0; i < 6; i++)
    for(j = 0; j < 6; j++)
        floorArray[i][j] = 1;
 

  for(int i = 0; i < 15; ++i)
    if(leftNum.blocks[i].height == floorNum/2)
      floorArray[leftNum.blocks[i].line][leftNum.blocks[i].col] = leftNum.values[i];
  for(int i = 0; i < 15; ++i)
    if(rightNum.blocks[i].height == floorNum/2)
      floorArray[rightNum.blocks[i].line][rightNum.blocks[i].col] = rightNum.values[i];                
 
  writeToLed(latchLeft, GPIOA, convertArray(floorArray[0]));
  writeToLed(latchLeft, GPIOB, convertArrayB(floorArray[1]));
  writeToLed(latchCenter, GPIOA, convertArray(floorArray[2]));
  writeToLed(latchCenter, GPIOB, convertArrayB(floorArray[3]));
  writeToLed(latchRight, GPIOA, convertArray(floorArray[4]));
  writeToLed(latchRight, GPIOB, convertArrayB(floorArray[5]));
}

void writeFloor(){
  int floorArray[6][6];

  int i, j;
 

  for(i = 0; i < 6; ++i)
    for(int j = 0; j < 6; ++j)
      floorArray[i][j] = gameState[i][j][floorNum/2];

    for(int i = 0; i < 4; ++i)
      if(currentPiece.blocks[i].height == floorNum/2)
        floorArray[currentPiece.blocks[i].line][currentPiece.blocks[i].col] = 0;      
  

  writeToLed(latchLeft, GPIOA, convertArray(floorArray[0]));
  writeToLed(latchLeft, GPIOB, convertArrayB(floorArray[1]));
  writeToLed(latchCenter, GPIOA, convertArray(floorArray[2]));
  writeToLed(latchCenter, GPIOB, convertArrayB(floorArray[3]));
  writeToLed(latchRight, GPIOA, convertArray(floorArray[4]));
  writeToLed(latchRight, GPIOB, convertArrayB(floorArray[5]));

}

void writeToLed(int latch, int port, int value) {


 Wire.beginTransmission(latch);
 Wire.write(port);
 Wire.write(value);
 Wire.endTransmission();
}


/*********************************************************************************************************************************************************************/


Piece createPiece(PieceType type){
	Piece piece;

	piece.type = type;

	switch(type)
	{
	case I:
		piece.blocks[0] = createBlock(1, 3, 5);
		piece.blocks[1] = createBlock(2, 3, 5);
		piece.blocks[2] = createBlock(3, 3, 5);
		piece.blocks[3] = createBlock(4, 3, 5);
		break;
	case O:
		piece.blocks[0] = createBlock(2, 2, 5);
		piece.blocks[1] = createBlock(2, 3, 5);
		piece.blocks[2] = createBlock(3, 2, 5);
		piece.blocks[3] = createBlock(3, 3, 5);
		break;
	case T:
		piece.blocks[0] = createBlock(2, 2, 5);
		piece.blocks[1] = createBlock(2, 3, 5);
		piece.blocks[2] = createBlock(3, 3, 5);
		piece.blocks[3] = createBlock(2, 4, 5);
		break;
	case S:
		piece.blocks[0] = createBlock(2, 2, 5);
		piece.blocks[1] = createBlock(2, 3, 5);
		piece.blocks[2] = createBlock(3, 3, 5);
		piece.blocks[3] = createBlock(3, 4, 5);
		break;
	case Z:
		piece.blocks[0] = createBlock(3, 2, 5);
		piece.blocks[1] = createBlock(3, 3, 5);
		piece.blocks[2] = createBlock(2, 3, 5);
		piece.blocks[3] = createBlock(2, 4, 5);
		break;
	case J:
		piece.blocks[0] = createBlock(3, 2, 5);
		piece.blocks[1] = createBlock(3, 3, 5);
		piece.blocks[2] = createBlock(3, 4, 5);
		piece.blocks[3] = createBlock(2, 4, 5);
		break;
	case L:
		piece.blocks[0] = createBlock(2, 2, 5);
		piece.blocks[1] = createBlock(2, 3, 5);
		piece.blocks[2] = createBlock(2, 4, 5);
		piece.blocks[3] = createBlock(3, 4, 5);
		break;
	}

	return piece;

}

int movePiece(Piece *piece, Direction dir){

	int i;

	for(i = 0; i < 4; ++i)
		if(!moveBlock(&(piece->blocks[i]), dir))
			return 0;

	//TODO - Revert to old gamestate if unsuccessful

	return 1;
}

int rotatePiece(Piece *piece, Direction dir){
  int i;
  int pivotLine = piece->blocks[1].line;
    int pivotCol = piece->blocks[1].col;
  int pivotHeight = piece->blocks[1].height;

  switch(dir){
    case right:
    for(i=0; i < 4; i++){
      int line = piece->blocks[i].line;
      int height = piece->blocks[i].height;
      piece->blocks[i].line = pivotLine + pivotHeight - height;
      piece->blocks[i].height = pivotHeight - pivotLine + line;
    }
    break;
    case left:
    for(i=0; i < 4; i++){
      int line = piece->blocks[i].line;
      int height = piece->blocks[i].height;
      piece->blocks[i].line = pivotLine - pivotHeight + height;
      piece->blocks[i].height = pivotHeight + pivotLine - line;
    }
    break;
    case front:
      for(i=0; i < 4; i++){
      int height = piece->blocks[i].height;
      int col = piece->blocks[i].col;
      piece->blocks[i].height = pivotHeight - pivotCol + col;
      piece->blocks[i].col = pivotCol + pivotHeight - height;
    }
    break;
    case back:
    for(i=0; i < 4; i++){
      int height = piece->blocks[i].height;
      int col = piece->blocks[i].col;
      piece->blocks[i].height = pivotHeight + pivotCol - col;
      piece->blocks[i].col = pivotCol - pivotHeight + height;
    }
    break;
    case slideRight:
    for(i=0; i < 4; i++){
      int line = piece->blocks[i].line;
      int col = piece->blocks[i].col;
      piece->blocks[i].line = pivotLine - pivotCol + col;
      piece->blocks[i].col = pivotCol + pivotLine - line;
    }
    break;
    case slideLeft:
    for(i=0; i < 4; i++){
      int line = piece->blocks[i].line;
      int col = piece->blocks[i].col;
      piece->blocks[i].line = pivotLine + pivotCol - col;
      piece->blocks[i].col = pivotCol - pivotLine + line;
    }
    break;
  }

  for(i = 0; i < 4; ++i){

    int line = piece->blocks[i].line;
    int col = piece->blocks[i].col;
    int height = piece->blocks[i].height;
    
    if(line > 5 || line < 0 || col > 5 || col < 0 || height > 5 || height < 0)
      return 0;

    if(gameState[line][col][height] == 0)
      return 0;
  }
  
  return 1;
}

int rotateI(Piece *piece, Direction dir){

 /* switch(dir){
    case right:
    break;
    case left:
    break;
    case front:
    break;
    case back:
    break;
    case slideRight:
    break;
    break;
    case slideLeft:
    break;
  }

  Serial.println(
          piece->blocks[0].line);
Serial.println(
          piece->blocks[0].col);
            Serial.println(
          piece->blocks[1].line);
Serial.println(
          piece->blocks[1].col);
            Serial.println(
          piece->blocks[2].line);
Serial.println(
          piece->blocks[2].col);
            Serial.println(
          piece->blocks[3].line);
Serial.println(
          piece->blocks[3].col);
  return 1;*/
}


/*********************************************************************************************************************************************************************/


Block createBlock(int line, int col, int height){
	Block block;

	block.line = line;
	block.col = col;
	block.height = height;

	return block;
}

int moveBlock(Block *block, Direction dir){


	switch(dir){
	case front:
		if(!gameState[block->line][block->col - 1][block->height] || block->col == 0)
			return 0;
		--block->col;
		break;
	case back:
		if(!gameState[block->line][block->col + 1][block->height] || block->col == 5)
			return 0;
		++block->col;
		break;
	case right:
		if(!gameState[block->line - 1][block->col][block->height] || block->line  == 0)
			return 0;
		--block->line;
		break;
	case left:
		if(!gameState[block->line + 1][block->col][block->height] || block->line  == 5)
			return 0;
		++block->line;
		break;
	case down:
		if(!gameState[block->line][block->col][block->height - 1] || block->height  == 0)
			return 0;
		--block->height;
		break;
	default:
		printf("Invalid movement");
		exit(-1);
	}

	return 1;

}


/*********************************************************************************************************************************************************************/


void removeFloor(int testFloor){

	int i, j, k;

	//Drops all lines down
	for(i = 0; i < 6; ++i)
		for(j = 0; j < 6; ++j)
			for(k = testFloor; k < 5; ++k)
				gameState[i][j][k] = gameState[i][j][k+1];


	//Fills the top line with '1's

	for(i = 0; i < 6; ++i)
		for(j = 0; j < 6; ++j)
			gameState[i][j][5] = 1;

  score++;
}

void removeCompletedFloors(){
  int i;

  for(i = 5; i >= 0; --i)
    if(floorComplete(i))
      removeFloor(i); 
}

int floorComplete(int testFloor){

	int i, j;

	for(i = 0; i < 6; ++i)
		for(j = 0; j < 6; ++j)
			if(gameState[i][j][testFloor] == 1)
				return 0;

	//After running through the whole line, if no '1' is found, return 'true'
	return 1;
}
void solidifyPiece(){
	int i;
	for(i = 0; i < 4; ++i){
		gameState[currentPiece.blocks[i].line][currentPiece.blocks[i].col][currentPiece.blocks[i].height] = 0;
    if(currentPiece.blocks[i].height == 5)
        gameOver = 1;
    }
  

	//Removes last last if it is complete
	removeCompletedFloors();
}

void createEmptyArray(){

int i, j, z;
  for(i = 0; i < 6; i++)
    for(j = 0; j < 6; j++)
      for(z = 0; z < 6; z++)
        gameState[i][j][z] = 1;
}


/*******************MAIN***************************/


void invokeMovePiece(Direction dir){

  //Creates copy of piece to test if it can move
  Piece pieceCopy = currentPiece;


  //if it can't move the piece, don't update the piece values
  if(!movePiece(&pieceCopy, dir)){
    //if the direction is down, then "solidify" piece
    if(dir == down){
      solidifyPiece();
      createNewPiece = 1;
    }

    return;
  }

  currentPiece = pieceCopy;
}

void invokeRotatePiece(Direction dir){
  //Creates copy of piece to test if it can move
  Piece pieceCopy = currentPiece;

  if(!rotatePiece(&pieceCopy, dir)){
    return;
  }

  currentPiece = pieceCopy;
  
}





