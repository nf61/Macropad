#include <Bounce.h>
#include <Encoder.h>

//Keycodes 
#define CTRL (0x01 | 0xE000)

//How many rows, columns, and LEDS have been wired
#define WIDTH 4

//Pin numbers

byte const rowZero [WIDTH] = {21, 19, 10, 0};   //21,19,10,0
byte const rowOne [WIDTH] = {20, 12, 2, 1};     //20,12,2,1

//Bounce objects set how sensitive the buttons are higher the number the less sensitive
Bounce one = Bounce(rowZero[0], 10);
Bounce two = Bounce(rowZero[1], 10);
Bounce three = Bounce(rowZero[2], 10);
Bounce four = Bounce(rowZero[3], 10);
Bounce five = Bounce(rowOne[0], 10);
Bounce six = Bounce(rowOne[1], 10);
Bounce seven = Bounce(rowOne[2], 10);
Bounce eight = Bounce(rowOne[3], 10);

//number of layers
byte layer = 0;
byte pause = 0;

void setup() {

 
  //intialize row pins
for(byte i = 0; i < WIDTH; i++){
  pinMode(rowZero[i], INPUT_PULLUP);
  digitalWrite(rowZero[i], HIGH);
  }
  
  //initiate col pins
for(byte i = 0; i < WIDTH; i++){
  pinMode(rowOne[i], INPUT_PULLUP);
  digitalWrite(rowOne[i], HIGH);
  }  
  
   //initiate keyboard
Keyboard.begin();

}

void loop() {
   
 // update buttons dont add long delays in loop
one.update();
two.update();
three.update();
four.update();
five.update();
six.update();
seven.update();
eight.update();

// keycodes at https://www.pjrc.com/teensy/td_keyboard.html
// if one doesn't work check to see if the error message gives the hex code like crtl above. 
// it looks like those use bitwise or to function correctly

//copy macro
//button 5 (I know its messed up change the keys or variables if you want)
if(one.fallingEdge()) {
  if(layer == 0){
    Keyboard.press(CTRL);
    Keyboard.press('c');
    delay(100);
    Keyboard.release(CTRL);
    Keyboard.release('c');
  }
  
  if(layer == 1){
    //    
  }
 }
   
  //paste macro
  //button 6
if(two.fallingEdge()) {
  if(layer == 0){
    Keyboard.press(CTRL);
    Keyboard.press('v');
    delay(100);
    Keyboard.release(CTRL);
    Keyboard.release('v');
  }
  
  if(layer == 1){
    //    
  }
}

   //cut macro
   //button 7
if(three.fallingEdge()) {
  if(layer == 0){
    Keyboard.press(CTRL);
    Keyboard.press('x');
    delay(100);
    Keyboard.release(CTRL);
    Keyboard.release('x');
  }
  
  if(layer == 1){
    //    
  }
 }

   //opens stack overflow on chrome, only works on windows
   //button 8
if(four.fallingEdge()) {
  if(layer == 0){
    Keyboard.set_modifier(MODIFIERKEY_RIGHT_GUI);
    Keyboard.press('r');
    delay(100);
    Keyboard.set_modifier(0); 
    Keyboard.release('r');
    Keyboard.send_now();
    delay(100);
    Keyboard.print("chrome stackoverflow.com");
    Keyboard.send_now();
    Keyboard.press(KEY_ENTER);
    Keyboard.release(KEY_ENTER);  
  }
  if(layer == 1){
    //    
  }
  }

  //button 1 
  //enter key
if(five.fallingEdge()) {
  if(layer == 0){
    Keyboard.press(KEY_ENTER);
    Keyboard.release(KEY_ENTER);
  }
  if(layer == 1){
    //    
  }
 }
  
  //Changes Layer on every layer
  //button 2
if(six.fallingEdge()) {
  if(layer < LED - 1) {
    layer++;
  }
  else layer = 0;
 }
  
  //
  //button 3
if(seven.fallingEdge()) {
  if(layer == 0){
    Keyboard.press(KEY_TAB);
    Keyboard.release(KEY_TAB);
    
  }
  if(layer == 1){
    //    
  }
 }

 //holds down shift click a second time to stop
 //button 4
if(eight.fallingEdge()) {
  if(layer == 0){
    Keyboard.set_modifier(MODIFIERKEY_SHIFT);
    if(eight.fallingEdge()) {
      Keyboard.set_modifier(0);
    }
  }
  
  if(layer == 1){
    Keyboard.press('r');
    Keyboard.release('r');   
  }
 }
  

