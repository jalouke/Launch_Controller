/* @file HelloKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates the simplest use of the matrix Keypad library.
|| #
*/
#include <Keypad.h>
#include <ArduinoRS485.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//keypad on pins PC0-5, PB1-2 [Arduino A0-5,D9-10]
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {10,9,7,8}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A3,A2,A1,A0}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
  RS485.begin(9600);
  Serial.println("start");
}
  
void loop(){
  char key = keypad.getKey();
  
  if (key){
    RS485.beginTransmission();
    //Serial.println(key);
    RS485.println(key);
    RS485.endTransmission();
  }
}
