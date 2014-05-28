/*
*  Project: Arduino Calculator.
*  Description: A one signed digit calculator with one input keypad, and 8*8 LED Matrix for display.
*  Developers: Ahmed Abdelmajied - Mohamed El-Houssainy
*  Date: 26-05-2014
*/

/********************* DECLERATIONS *********************/
/*********** CONSTANTS ************/
// Numbers of keyPad
const int ONE = 0;
const int TWO = 4;
const int THREE = 8;
const int ADD = 12;
const int FOUR = 1;
const int FIVE = 5;
const int SIX = 9;
const int SUB = 13;
const int SEVEN = 2;
const int EIGHT = 6;
const int NINE = 10;
const int MUL = 14;
const int DEV = 3;
const int ZERO = 7;
const int EQU = 15;

const int INF = -255;

// Numbers on Led Matrix
const byte minus[] = {0,0,0,0,192,0,0,0}; 
const byte left_one[] = {0,32,32,32,32,32,32,0};

const byte one[] = {0,2,2,2,2,2,2,0};
const byte two[] = {0,7,1,7,7,4,7,0};
const byte three[] = {0,7,5,3,3,5,7,0};
const byte four[] = {0,5,5,7,7,1,1,0};
const byte five[] = {0,7,4,7,7,1,7,0};
const byte six[] = {0,7,4,7,5,7,7,0};
const byte seven[] = {0,6,6,2,7,2,2,0};
const byte eight[] = {0,7,5,7,7,5,7,0};
const byte nine[] = {0,7,5,7,7,1,7,0};
const byte zero[] = {0,7,7,5,5,7,7,0};
const byte infinity[] = {0,0,102,153,153,102,0,0};

// Operations
const byte add[] = {0,8,8,28,28,8,8,0};
const byte sub[] = {0,0,0,28,28,0,0,0};
const byte mul[] = {0,20,20,8,8,20,20,0};
const byte dev[] = {0,4,4,8,8,16,16,0};

byte currentOutput[] = {256,256,256,256,256,256,256,256};

/************* STATES **************/
const int STATE_FIRST_DIGIT = 1;
const int STATE_OP = 2;
const int STATE_SECOND_DIGIT = 3;
const int STATE_EQUAL = 4;
int currentState;

/************* KEY PAD *************/
int inputKeyPad[] = {16,17,18,19}; // The four pins of the input keypad
int outputKeyPad[] ={0,1,2,3}; // The four shared output pins between keypad and LED matrix

/************* LED MATRIX *************/
int oneLedMatrix[] = {0,1,2,3,4,5,6,7};
int zeroLedMatrix[] = {8,9,10,11,12,13,14,15};

/**************** END OF DECLERATIONS ****************/

// Data
int first;
char op;
int second;

// the setup routine runs once when you press reset:
void setup() {
  // set the input pins for keypad
  for(int i = 0 ; i < 4 ; i ++)
    pinMode(inputKeyPad[i], INPUT);
    
  /** output pins **/
  // set the output pins for keypad
//  for(int i = 0 ; i < 4 ; i ++)
//    pinMode(outputKeyPad[i] , OUTPUT);

  // set the output pins for LedMatrix and keypad
  for(int i = 0 ; i < 8 ; i ++){
    pinMode(oneLedMatrix[i] , OUTPUT);
    pinMode(oneLedMatrix[i] , OUTPUT);  
  }
    
  currentState = STATE_FIRST_DIGIT;    
}

// the loop routine runs over and over again forever:
void loop() {
 int input = getKeyPadInput();
//  if( input != -1 ) // There is a Key pressed
//    checkInput(input);
  
 printNumOnLedMatrix();
  delay(250);
}

// Check the pressed input
void checkInput(int input){
  if( currentState == STATE_FIRST_DIGIT){
    first = getCurrentDigit(input);
    currentState = STATE_OP;
  } else if( currentState == STATE_OP ){
    setOperation(input);
    currentState = STATE_SECOND_DIGIT;
  } else if( currentState == STATE_SECOND_DIGIT ){
    second = getCurrentDigit(input);
    currentState = STATE_FIRST_DIGIT;
  }else if( currentState == STATE_EQUAL ){
    int result = getCurrentResult(); // Get the result of the operation
    setResult(result);

    currentState = STATE_FIRST_DIGIT;
  }
}

// get Digit
int getCurrentDigit(int input){
  switch(input){
       case ONE:
          return 1;
       case TWO:
          return 2;
       case THREE:
          return 3;
       case FOUR:
          return 4;
       case FIVE:
          return 5;
       case SIX:
          return 6;
       case SEVEN:
          return 7;
       case EIGHT:
          return 8;
       case NINE:
          return 9;
       case ZERO:
          return 0;
  }
}

// Set operation
void setOperation(int input){
  switch(input){
    case ADD:
      op = '+';
      for(int i = 0 ; i < 8 ; i++)
        currentOutput[i] = add[i];
      break;
    case SUB:
      op = '-';
      for(int i = 0 ; i < 8 ; i++)
        currentOutput[i] = sub[i];
      break;
    case MUL:
      op = '*';
      for(int i = 0 ; i < 8 ; i++)
        currentOutput[i] = mul[i];
      break;
    case DEV:
      op = '/';
      for(int i = 0 ; i < 8 ; i++)
        currentOutput[i] = dev[i];
      break;   
  }
}

// Set result
int getCurrentResult(){
  switch(op){
   case '+':
     return first + second;
   case '-':
     return first - second;
     break;
   case '*':
     return first * second;
     break;
   case '/':
     if( second == 0 ) // Undifined operation
       return INF;
       
     return first / second;    
  }
}

void setResult(int result){
  if( result == INF ){
    for(int i = 0 ; i < 8 ; i++)
      currentOutput[i] = infinity[i];
    return;
  }
  
  // Reset 
  for(int i = 0 ; i < 8 ; i++)
     currentOutput[i] = 0;
  
  if( result < 0 ){ // Set number to negative
      for(int i = 0 ; i < 8 ; i++)
         currentOutput[i] |= minus[i];
      result *= -1;
  }
  
  if( result > 10 ){ // Set second Digit = 1
    for(int i = 0 ; i < 8 ; i++)
      currentOutput[i] |= left_one[i];
    result -= 10;
  }
  
  switch(result){ // Set first digit
    case 0:
      for(int i = 0 ; i < 8 ; i++)
        currentOutput[i] |= zero[i];
      break;
    case 1:
      for(int i = 0 ; i < 8 ; i++)
        currentOutput[i] |= one[i];
      break;
    case 2:
      for(int i = 0 ; i < 8 ; i++)
        currentOutput[i] |= two[i];
      break;
    case 3:
      for(int i = 0 ; i < 8 ; i++)
        currentOutput[i] |= three[i];
      break;
    case 4:
      for(int i = 0 ; i < 8 ; i++)
        currentOutput[i] |= four[i];
      break;
    case 5:
      for(int i = 0 ; i < 8 ; i++)
        currentOutput[i] |= five[i];
      break;
    case 6:
      for(int i = 0 ; i < 8 ; i++)
        currentOutput[i] |= six[i];    
      break;
    case 7:
      for(int i = 0 ; i < 8 ; i++)
        currentOutput[i] |= seven[i];
      break;
    case 8:
      for(int i = 0 ; i < 8 ; i++)
        currentOutput[i] |= eight[i];
      break;
    case 9:
      for(int i = 0 ; i < 8 ; i++)
        currentOutput[i] |= nine[i];    
      break;
  }
  
}

// Check if there is a button pressed from the keypad
int getKeyPadInput(){
  int num = -1;
  for( int i = 0 ; i < 4; i++){
     digitalWrite(outputKeyPad[i], HIGH);
     for(int j = 0 ; j < 4 ; j++ ){
       if( digitalRead(inputKeyPad[j]) == 1 ){
          num = i*4 + j;
          break;
       }
     }
     digitalWrite(outputKeyPad[i], LOW);   
  }
  return num;
}

void printNumOnLedMatrix(){
  //Reset
  for( int i = 0 ; i < 8 ; i++)
    digitalWrite(oneLedMatrix[i] , HIGH);
    
  for( int i = 0 ; i < 8 ; i++)
    digitalWrite(zeroLedMatrix[i] , LOW);    
}


