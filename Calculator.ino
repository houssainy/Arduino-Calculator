/*
*  Project: Arduino Calculator.
*  Description: A one signed digit calculator with one input keypad, and 8*8 LED Matrix for display.
*  Developers: Ahmed Abdelmajied - Mohamed El-Houssainy
*  Date: 26-05-2014
*/

/********************* DECLERATIONS *********************/
/*********** CONSTANTS ************/
// Numbers of keyPad
const int ONE = 11;
const int TWO = 15;
const int THREE = 7;
const int ADD = 3;
const int FOUR = 10;
const int FIVE = 14;
const int SIX = 6;
const int SUB = 2;
const int SEVEN = 9;
const int EIGHT = 13;
const int NINE = 5;
const int MUL = 1;
const int DEV = 8;
const int ZERO = 12;
const int EQU = 0;

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
const byte add[] = {0,24,24,126,126,24,24,0};
const byte sub[] = {0,0,0,28,28,0,0,0};
const byte mul[] = {0,20,20,8,8,20,20,0};
const byte dev[] = {0,4,4,8,8,16,16,0};

byte currentOutput[] = {0,223,173,175,175,141,141,0};

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
    pinMode(zeroLedMatrix[i] , OUTPUT);  
  }
  

  currentState = STATE_FIRST_DIGIT;    
}

// the loop routine runs over and over again forever:
void loop() {
 int input = getKeyPadInput();
 if( input != -1 ) // There is a Key pressed
   checkInput(input);

 printNumOnLedMatrix();
}

// Check the pressed input
void checkInput(int input){
  if( currentState == STATE_FIRST_DIGIT  ){
    first = getCurrentDigit(input);
    if(first != -1 )
      currentState = STATE_OP;
  } else if( currentState == STATE_OP ){
    if( setOperation(input) )
      currentState = STATE_SECOND_DIGIT;
  } else if( currentState == STATE_SECOND_DIGIT ){
    second = getCurrentDigit(input);
    if( second != -1 )
      currentState = STATE_EQUAL;
  }else if( currentState == STATE_EQUAL ){
    if( input == EQU ){
      int result = getCurrentResult(); // Get the result of the operation
      setResult(result);
     
      currentState = STATE_FIRST_DIGIT;
    }
  }
}

// get Digit
int getCurrentDigit(int input){
  switch(input){
       case ONE:
          for(int i = 0 ; i < 8 ; i++)
            currentOutput[i] = one[i];           
          return 1;
       case TWO:
          for(int i = 0 ; i < 8 ; i++)
            currentOutput[i] = two[i];           
          return 2;
       case THREE:
          for(int i = 0 ; i < 8 ; i++)
            currentOutput[i] = three[i];           
          return 3;
       case FOUR:
          for(int i = 0 ; i < 8 ; i++)
            currentOutput[i] = four[i];           
          return 4;
       case FIVE:
          for(int i = 0 ; i < 8 ; i++)
            currentOutput[i] = five[i];           
          return 5;
       case SIX:
          for(int i = 0 ; i < 8 ; i++)
            currentOutput[i] = six[i];           
          return 6;
       case SEVEN:
          for(int i = 0 ; i < 8 ; i++)
            currentOutput[i] = seven[i];           
          return 7;
       case EIGHT:
          for(int i = 0 ; i < 8 ; i++)
            currentOutput[i] = eight[i];           
          return 8;
       case NINE:
          for(int i = 0 ; i < 8 ; i++)
            currentOutput[i] = nine[i];                  
          return 9;
       case ZERO:
          for(int i = 0 ; i < 8 ; i++)
            currentOutput[i] = zero[i];           
          return 0;
  }
  return -1; // Not in number
}

// Set operation
boolean setOperation(int input){
  switch(input){
    case ADD:
      op = '+';
      for(int i = 0 ; i < 8 ; i++)
        currentOutput[i] = add[i];
      return true;
    case SUB:
      op = '-';
      for(int i = 0 ; i < 8 ; i++)
        currentOutput[i] = sub[i];
      return true;
    case MUL:
      op = '*';
      for(int i = 0 ; i < 8 ; i++)
        currentOutput[i] = mul[i];
      return true;
    case DEV:
      op = '/';
      for(int i = 0 ; i < 8 ; i++)
        currentOutput[i] = dev[i];
      return true; 
  }
  return false;
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
  
  // add negative sign
  if( result < 0 ){ 
      for(int i = 0 ; i < 8 ; i++)
         currentOutput[i] |= minus[i];
      result *= -1;
  }
  
  // First digit
  int tepmDigit = result %10;
  result /= 10;
  switch(tepmDigit){ // Set first digit
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
  
  // Set Second digit
  switch(result){
    case 1:
      for(int i = 0 ; i < 8 ; i++)
        currentOutput[i] |= (one[i] << 3);
      break;
    case 2:
      for(int i = 0 ; i < 8 ; i++)
        currentOutput[i] |= (two[i] << 3);
      break;
    case 3:
      for(int i = 0 ; i < 8 ; i++)
        currentOutput[i] |= (three[i] << 3);
      break;
    case 4:
      for(int i = 0 ; i < 8 ; i++)
        currentOutput[i] |= (four[i] << 3);
      break;
    case 5:
      for(int i = 0 ; i < 8 ; i++)
        currentOutput[i] |= (five[i] << 3);
      break;
    case 6:
      for(int i = 0 ; i < 8 ; i++)
        currentOutput[i] |= (six[i] << 3);    
      break;
    case 7:
      for(int i = 0 ; i < 8 ; i++)
        currentOutput[i] |= (seven[i] << 3);
      break;
    case 8:
      for(int i = 0 ; i < 8 ; i++)
        currentOutput[i] |= (eight[i] << 3);
      break;
    case 9:
      for(int i = 0 ; i < 8 ; i++)
        currentOutput[i] |= (nine[i] << 3);    
      break;
  }

}

// Check if there is a button pressed from the keypad
int getKeyPadInput(){
  
  // Reset all the output pins of keypad
  for(int i = 0; i < 4 ; i++)
     digitalWrite(outputKeyPad[i], LOW);  
     
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
  byte temp;
  for( int i = 0 ; i < 8 ; i++){ // Rows
    temp = currentOutput[i];
    for(int j = 0; j < 8 ; j++){ // Columns from byte
      if( (temp & 128) == 128 /*10000000*/ ){ //one
            digitalWrite(zeroLedMatrix[j] , LOW);
            digitalWrite(oneLedMatrix[i] , HIGH);       
            delay(1);
            digitalWrite(zeroLedMatrix[j] , HIGH);    
            digitalWrite(oneLedMatrix[i] , LOW);
      }else{//zero
            digitalWrite(zeroLedMatrix[j] , HIGH);    
            digitalWrite(oneLedMatrix[i] , LOW);     
      }
      temp = (temp << 1);
    }    
  }
}


