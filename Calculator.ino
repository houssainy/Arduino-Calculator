// CONSTANTS
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
const int DIV = 3;
const int ZERO = 7;
const int EQU = 15;

/*
*
*/

/************* KEY PAD *************/
int inputKeyPad[] = {16,17,18,19}; // The four pins of the input keypad
int outputKeyPad[] ={0,1,2,3}; // The four shared output pins between keypad and LED matrix
/***********************************/

/************* LED MATRIX *************/
int ledMatrix[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13};
/***********************************/ 

// the setup routine runs once when you press reset:
void setup() {
  // set the input pins for keypad
  for(int i = 0 ; i < 4 ; i ++)
    pinMode(inputKeyPad[i], INPUT);
    
  /** output pins **/
  // set the output pins for keypad
  for(int i = 0 ; i < 4 ; i ++)
    pinMode(outputKeyPad[i] , OUTPUT);

  // set the output pins for LedMatrix
  for(int i = 4 ; i < 14 ; i ++)
    pinMode(ledMatrix[i] , OUTPUT);    
}

// the loop routine runs over and over again forever:
void loop() {

}

int checkState(){
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
