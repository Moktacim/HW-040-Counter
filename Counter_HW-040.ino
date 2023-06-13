#define CLK 2
#define DT 3
#define SW 4

int counter = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir = "";
unsigned long lastButtonPress = 0;

void setup () {

//  Set the encoder pins as inputs
pinMode (CLK, INPUT);
pinMode (DT, INPUT);
pinMode (SW, INPUT_PULLUP);

//  Setup Serial Monitor
Serial.begin (9600);

// Reak the initial state of CLK

lastStateCLK = digitalRead (CLK);
}

void loop () {
// Read the current state of CLK
currentStateCLK = digitalRead (CLK);

//  If last and current state of CLK are different, then pulse on
//  React to only 1 state change to avoid double count
if (currentStateCLK != lastStateCLK ){
//  IF the DT state is different than the CLK state then
// the encoder is rotating CW so incecrement
  if (digitalRead(DT) != currentStateCLK) 
  {
    counter ++;
    currentDir = "CW";

  }
  
  if (digitalRead(DT) == currentStateCLK)
  {
    // Encoder is rotating CCW so decrement
    // counter = 0;
    counter --;
    currentDir = "CCW";
  }

  Serial.print("Direction: ");
  Serial.print(currentDir);
  Serial.print(" | Counter:");
  Serial.print(counter);
  Serial.println();

}
// Remember last CLK state
lastStateCLK = currentStateCLK;

// Read the button state
int btnState = digitalRead(SW);

// If we detect LOW sognal, button is pressed
if (btnState == LOW) {
// if 50 ms have passed sonce last LOW pulse, it means that the 
// button has been pressed, released and pressed again
  if (millis() -lastButtonPress < 50) {
  Serial.println("Buttoon Pressed!");
  }

// Remember last button press event
lastButtonPress = millis();

}
// Put in a slight delay to help debounce the reading
delay(1);
}




