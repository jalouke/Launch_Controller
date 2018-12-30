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
#include <Wire.h>
#define DISPLAY_ADDRESS1 0x72 //This is the default address of the LCD display

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
  Wire.begin(); // LCD begin
  RS485.begin(9600);
  Serial.println("start");

  //LCD initialization and color selection
  Wire.begin(DISPLAY_ADDRESS1);
  Wire.write('|');
  Wire.write('-');
  delay(20);
  Wire.write('|'); //Put LCD into setting mode
  Wire.write(128+29); //red
  delay(20);
  Wire.write('|');
  Wire.write(158+29); //green
  delay(20);
  Wire.write('|');
  Wire.write(188+29); //blue
  delay(20);
  Wire.end();
  delay(5000);
  //write initialized text
  Wire.begin(DISPLAY_ADDRESS1);
  Wire.write('|');
  Wire.write('-');
  Wire.print("Range:"); //number starts at pos 7
  delay(50);
  Wire.write(254); //Send cursor command 
  Wire.write(128 + 64 + 0); //cursor position (128), Line 2 (64), begin of line (0)
  Wire.print("Launch Pad:"); //number starts at pos 12
  delay(50);
  Wire.write(254); //Send cursor command 
  Wire.write(128 + 84 + 0); //cursor position (128), Line 4 (84), begin of line (0)
  Wire.print("ARM?:"); //number starts at pos 5
  delay(50);
  Wire.end();
}
  
void loop(){
  char key = keypad.getKey();
  
  
  
  if (key){
    RS485.beginTransmission();
    RS485.println(key);
    RS485.endTransmission();
    Wire.write(254); //Send cursor command 
    Wire.write(128 + 64 + 12); //cursor position (128), Line 4 (84), begin of line (0)
    Wire.print(key);
    
  }
}
