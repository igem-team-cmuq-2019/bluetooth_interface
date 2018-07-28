/*     VR Rifle Sensors, Augmea Simulation Technologies
 *
 *  by Kaan Aksoy,
 *
 */

#include <SoftwareSerial.h>

const int txPin = 10;
const int rxPin = 11;
const int signalLed = 13;


const int topEncoderInput_A = 6;
const int topEncoderInput_B = 5;
const int topEncoderButton = 4;

const int btmEncoderInput_A = 9;
const int btmEncoderInput_B = 8;
const int btmEncoderButton = 7;

const int triggerButton = 2;
const int reloadButton = 3;

char inSerial[15];

int topEncoderButtonState = 0;
int btmEncoderButtonState = 0;

int triggerState = 0;
int reloadState = 0;
int lastReloadState = 0;


int topCounter = 0;
int topAState;
int topALastState;

int btmCounter = 0;
int btmAState;
int btmALastState;

SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);
int mySerialState = 0;

void setup() {
  pinMode (triggerButton, INPUT_PULLUP);
  pinMode (reloadButton, INPUT_PULLUP);
  pinMode (signalLed, OUTPUT);
  
  
  pinMode (btmEncoderButton, INPUT_PULLUP);
  pinMode (btmEncoderInput_A, INPUT_PULLUP);
  pinMode (btmEncoderInput_B, INPUT_PULLUP); 
  
  pinMode (topEncoderButton, INPUT_PULLUP);
  pinMode (topEncoderInput_A,INPUT_PULLUP);
  pinMode (topEncoderInput_B,INPUT_PULLUP);
  
  pinMode (txPin, OUTPUT);
  pinMode (rxPin, INPUT);
  
  mySerial.begin (9600);
  signal();
  signal();
  signal();
  mySerial.println("Connected to Rifle.");
  // Reads the initial state of the outputA
  topALastState = digitalRead(topEncoderInput_A);
  btmALastState = digitalRead(btmEncoderInput_A);
}
void loop() {
  
  topEncoderButtonState = digitalRead(topEncoderButton);
  if (topEncoderButtonState == LOW) {
    topCounter = 0;
    mySerial.print("Top Position: ");
    mySerial.println(topCounter);
    signal();
    delay(250);
  }
  
  btmEncoderButtonState = digitalRead(btmEncoderButton);
  if (btmEncoderButtonState == LOW) {
    btmCounter = 0;
    mySerial.print("Bottom Position: ");
    mySerial.println(btmCounter);
    signal();
    delay(250);
  }
  
  triggerState = digitalRead(triggerButton);
  if (triggerState == LOW) {
    mySerial.println("Fire");
    signal();
    delay(50);
  }
  
  reloadState = digitalRead(reloadButton);
  if (reloadState == LOW) {
    if (lastReloadState == HIGH){
      mySerial.println("Reload");
      lastReloadState = reloadState;
      delay(250);
    }
  }
  else{
    lastReloadState = HIGH;
  }

  
   topAState = digitalRead(topEncoderInput_A); // Reads the "current" state of the outputA
  // If the previous and the current state of the outputA are different, that means a Pulse has occured
  if (topAState != topALastState){
    // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
    if (digitalRead(topEncoderInput_B) != topAState) {
      topCounter ++;
    } 
    else {
      topCounter --;
    }
    mySerial.print("Top Position: ");
    mySerial.println(topCounter);
    signal();
  }
  topALastState = topAState; // Updates the previous state of the outputA with the current state

   btmAState = digitalRead(btmEncoderInput_A); // Reads the "current" state of the outputA
  // If the previous and the current state of the outputA are different, that means a Pulse has occured
  if (btmAState != btmALastState){
    // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
    if (digitalRead(btmEncoderInput_B) != btmAState) {
      btmCounter ++;
    } 
    else {
      btmCounter --;
    }
    mySerial.print("Bottom Position: ");
    mySerial.println(btmCounter);
    signal();
  }
  btmALastState = btmAState; // Updates the previous state of the outputA with the current state
}

void signal(){
  digitalWrite(signalLed, HIGH);
  delay(100);
  digitalWrite(signalLed, LOW);
}
