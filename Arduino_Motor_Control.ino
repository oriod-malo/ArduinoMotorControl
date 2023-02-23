#include <IRremote.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define IR_RECEIVE_PIN 8
#include <Servo.h>
#include <Keypad.h>

// LCD Control Section
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Keyboard Control Section
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'+','0','-','D'}
};
byte rowPins[ROWS] = {10, 11, 12, 13}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 5, 6, 7}; //connect to the column pinouts of the keypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

// Servo Control Section
Servo myservo;
int pos = 0;
bool Clockwise, counterClockwise;
int delayValue = 5;
int maxcounts = 0;


void setup() {

  // SETUP LCD
  lcd.init();
  
  // SETUP SERIAL PORT
  Serial.begin(9600);

  // CONFIGURE LCD
  lcd.begin(16,2);
  lcd.backlight();
  lcd.clear();
  lcd.setCursor (0,0);
  lcd.print("Lights On");
  
  // SETUP SERVO MOTOR
  myservo.attach(9);
  
}


void loop() {
  char customKey = customKeypad.getKey();
  
  if (customKey){
    Serial.println(customKey);
  }


  KeypadControl(customKey);

  if (Clockwise && (pos != 0))  {
    pos--;
  }
  if (counterClockwise && (pos != 180))  {
    pos++;
  }

  myservo.write(pos);
  delay(delayValue);
}

void KeypadControl(char pressedKey){
  // Makes the Servo sweep in one direction
      if (pressedKey == 'A'){
      Clockwise = !Clockwise;
      counterClockwise = false;
      lcd.clear();
      lcd.setCursor (0,0);
      lcd.print("Direction:");
      lcd.setCursor (0,1);
      lcd.print("Clock");
    }
    
  // makes the Servo sweep in the opposite direction
    if (pressedKey == 'B'){
      counterClockwise = !counterClockwise;
      Clockwise = false;
      lcd.clear();
      lcd.setCursor (0,0);
      lcd.print("Direction:");
      lcd.setCursor (0,1);
      lcd.print("Anti-Clock");
    }
    
    // Change servo rotation speed
    if ((pressedKey == '1')||(pressedKey == '2')||(pressedKey == '3')||(pressedKey == '4')||(pressedKey == '5')||(pressedKey == '6')||(pressedKey == '7')||(pressedKey == '8')||(pressedKey == '9')){
      int temp;
      temp=pressedKey-'0';
      delayValue = temp*5;
      lcd.clear();
      lcd.setCursor (0,0);
      lcd.print("New Delay Value:");
      lcd.setCursor (0,1);
      lcd.print(delayValue);
    }

    // increase number of automatic swipes
    if ((pressedKey == '+')){
      maxcounts++;
      if(12<maxcounts){
        maxcounts=0;
      }
      lcd.clear();
      lcd.setCursor (0,0);
      lcd.print("Will Do:");
      lcd.setCursor (0,1);
      lcd.print(maxcounts);
      lcd.setCursor (3,1);
      lcd.print("sweeps");
    }

    // Set number of swipes to zero
    if ((pressedKey == '0')){
      maxcounts=0;
      lcd.clear();
      lcd.setCursor (0,0);
      lcd.print("Will Do:");
      lcd.setCursor (0,1);
      lcd.print(maxcounts);
      lcd.setCursor (3,1);
      lcd.print("sweeps");
    }

    // Decrease number of automatic Sweeps
    if((pressedKey=='-')){
      if(maxcounts>0){
        maxcounts--;
      }
      lcd.clear();
      lcd.setCursor (0,0);
      lcd.print("Will Do:");
      lcd.setCursor (0,1);
      lcd.print(maxcounts);
      lcd.setCursor (3,1);
      lcd.print("sweeps");
    }

    // perform automatic Sweeps
    if((pressedKey == 'C')&&(maxcounts>0)){
    servoAutomatic();
    }
    if((pressedKey == 'D')){
      lcd.clear();
      lcd.setCursor (0,0);
      lcd.print("Servo Angle:");
      lcd.setCursor (0,1);
      lcd.print(pos);
      lcd.setCursor (4,1);
      lcd.print("degrees");
    }
    
}

void servoAutomatic() {
int counts = 0;
do{
  lcd.clear();
  lcd.setCursor (0,0);
  lcd.print(counts+1);
  lcd.setCursor (3,0);
  lcd.print("sweep");
  lcd.setCursor (0,1);
  lcd.print(maxcounts-counts-1);
  lcd.setCursor (3,1);
  lcd.print("sweeps left");
  
  for (pos = 0; pos <= 180; pos += 1) {
    // in steps of 1 degree
    myservo.write(pos);
    delay(delayValue);
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(delayValue);
  }
  
  counts++;
}
while(counts<maxcounts);
}
