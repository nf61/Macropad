#include <Bounce.h>
#include <Encoder.h>

//Keycodes 
#define CTRL (0x01 | 0xE000)

//How many rows, columns, and LEDS have been wired
#define WIDTH 4
#define LED 4
#define ROTPINS 3

//how sensitive rotary encoder is higher the number the less sensitive
#define ROT 3 

//Pin numbers
byte const leds [LED] = {16,18,14,15}; 
byte const rowZero [WIDTH] = {21, 19, 10, 0};   //21,19,10,0
byte const rowOne [WIDTH] = {20, 12, 2, 1};     //20,12,2,1
byte const rotEnc [ROTPINS] = {6,7,8};

//Speed starting leds go for lower the faster
int ledSpeed = 400;

//How many times LEDS cycle
int cycles = 2;

//Bounce objects set how sensitive the buttons are higher the number the less sensitive
Bounce one = Bounce(rowZero[0], 10);
Bounce two = Bounce(rowZero[1], 10);
Bounce three = Bounce(rowZero[2], 10);
Bounce four = Bounce(rowZero[3], 10);
Bounce five = Bounce(rowOne[0], 10);
Bounce six = Bounce(rowOne[1], 10);
Bounce seven = Bounce(rowOne[2], 10);
Bounce eight = Bounce(rowOne[3], 10);

//rotary encoder
Bounce buton = Bounce(rotEnc[0], 10);
Encoder knob(rotEnc[1], rotEnc[2]);
long knobFormerState = knob.read();
bool knobLayer = true;

//number of layers
byte layer = 0;
byte pause = 0;

void setup() {

  //intialize led pins
for(byte i = 0; i < LED; i++){
  pinMode(leds[i], OUTPUT);
  }
  
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
  
  //initiate rotary encoder
for(byte i = 0; i < ROTPINS; i++){
  pinMode(rotEnc[i], INPUT_PULLUP);
  digitalWrite(rotEnc[i], HIGH);
  }
  
  //Cycle leds
for(int i = 0; i < cycles; i++){
  for(byte j = 0; j < LED; j++){
    digitalWrite(leds[j], HIGH);
    delay(ledSpeed);
    digitalWrite(leds[j],LOW);
    }
  }
  
   //initiate keyboard
Keyboard.begin();

}

void loop() {

digitalWrite(leds[layer], HIGH);
digitalWrite(leds[layer], LOW);

   
 // update buttons dont add long delays in loop
one.update();
two.update();
three.update();
four.update();
five.update();
six.update();
seven.update();
eight.update();
buton.update();

//initiate rotary encoder
long knobCurrentState = knob.read();

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
  
if(buton.fallingEdge()) {
  if(layer == 0){
    if(knobLayer == true){
      knobLayer = false;
      }
    else knobLayer = true;
  }

   if(layer == 1){
      Keyboard.press(KEY_MEDIA_PLAY_PAUSE);
      Keyboard.release(KEY_MEDIA_PLAY_PAUSE);
     }
}

if(knobFormerState + ROT < knobCurrentState) {
  if(layer == 0){
    if(knobLayer == true){
      Keyboard.press(KEY_UP);
      Keyboard.release(KEY_UP);
      knobFormerState = knobCurrentState;
    }
    else {
      Keyboard.press(KEY_RIGHT);
      Keyboard.release(KEY_RIGHT);
      knobFormerState = knobCurrentState;
    }
  }

  if(layer == 1){
    Keyboard.press(KEY_MEDIA_VOLUME_INC);
    Keyboard.release(KEY_MEDIA_VOLUME_INC);
    knobFormerState = knobCurrentState;   
  }
}
   
if(knobFormerState - ROT > knobCurrentState) {
  if(layer == 0){
    if(knobLayer == true){
      Keyboard.press(KEY_DOWN);
      Keyboard.release(KEY_DOWN);
      knobFormerState = knobCurrentState;
    }
    else {
      Keyboard.press(KEY_LEFT);
      Keyboard.release(KEY_LEFT);
      knobFormerState = knobCurrentState;
    }
  }

  if(layer == 1){
    Keyboard.press(KEY_MEDIA_VOLUME_DEC);
    Keyboard.release(KEY_MEDIA_VOLUME_DEC);
    knobFormerState = knobCurrentState;    
  }
  }
   
   
}
