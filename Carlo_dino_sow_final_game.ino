/*
  File: Carlos_dino_sow_final_game.ino
  MIT License
  Copyright 2024 Carlos R.

  Permission is hereby granted, free of charge,
  to any person obtaining a copy of this software 
  and associated documentation files (the “Software”), 
  to deal in the Software without restriction, including 
  without limitation the rights to use, copy, modify, 
  merge, publish, distribute, sublicense, and/or sell copies
  of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND
  , EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM
  , OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define variables
bool buttonA;
bool buttonB;
int buzzPin = 6; // Unused variable
int score = 0;
int dinoY = 2;
int dinoX = 2;
int buzz = 6;
int c0X = 15;
int c0Y;
int c1X = 15;
int c1Y;
int c2X = 15;
int c2Y;
int dinoYLast;
bool isRunning;
String scoreLabel;
// Setup LCD
LiquidCrystal_I2C lcd(0x27,16,2); 

// Setup
void setup() {
  // Pins mode
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(6, OUTPUT);
  Serial.begin(9600);

  // game start
  lcd.init();
  lcd.setBacklight(HIGH); 
  lcd.begin(20, 4);

  Serial.begin(9600);
  Serial.println("A Random game Debug Output");
  Serial.println("Carlo486");

  lcd.print("Random Game");
  lcd.setCursor(0,1);
  lcd.print("(c) Carlo486");
  lcd.setCursor(0,2);
  lcd.print("BUTTON A TO START");
  lcd.setCursor(0,3);
  lcd.print("Wubbalubbadubdub!");
  while (digitalRead(11) == 0) {}
  isRunning = true;
  Serial.println("LETS GO!");
}

// function to get events
void pollInputs() {
  if (digitalRead(11) == 1) {
    buttonA = true;
  } else {
    buttonA = false;
  }

  if (digitalRead(10) == 1) {
    buttonB = true;
  } else {
    buttonB = false;
  }

  if (buttonA) {
    dinoY -= 1;
    tone(buzz, 500);
    if(dinoY == -1) {
      dinoY == 0;
    }
    noTone(buzz);
  } 
  if (buttonB) {
    dinoY += 1;
    tone(buzz, 500);
    if(dinoY == 4) {
      dinoY == 3;
    }
    noTone(buzz);
  }
}



// game
void loop() {
while(isRunning) {
  lcd.clear();
  lcd.setCursor(10, 0);
  lcd.print(score);
  lcd.setCursor(2, 3);
  lcd.print(buttonA);
  Serial.print(buttonA);
  Serial.print(" ");
  lcd.setCursor(4,3);
  lcd.print(buttonB);
  Serial.println(buttonB);

  lcd.setCursor(12,3);
  lcd.print(dinoY);
  dinoYLast = dinoY;
  lcd.setCursor(dinoX, dinoY);
  lcd.print("D"); 
  
  lcd.setCursor(c0X, c0Y);
  lcd.print("C");

  lcd.setCursor(c1X, c1Y);
  lcd.print("C");

  lcd.setCursor(c2X, c2Y);
  lcd.print("C");
  

  
  c0X -= 0.1;
  c1X -= 0.1;
  c2X -= 0.1;
  
  // Game Over for u
  if(c0Y == dinoY && c0X == dinoX || c1Y == dinoY && c1X == dinoX || c2Y == dinoY && c2X == dinoX){
    tone(buzz, 1000);
    isRunning = false;
    Serial.println("Game Over For U");
  }

  // WHAT IF THE CACTUS X IS 0?
  if (c0X == 0) {
    if(c0X != dinoX || c1X != dinoX || c2X != dinoX) {
      score += 1;
    }
    
    c0X = 20;
    c0Y = random(0, 3);
  } else if (c1X == 0) {
    c1X = 20;
    c1Y = random(0, 3);
  } else if (c2X == 0) {
    c2X = 20;
    c2Y = random(0, 3);
  }
  pollInputs(); // Call the function to get inputs
  
  delay(250);
  //lcd.setBacklight(LOW);
}
  delay(1000);
  noTone(buzz);
  scoreLabel = String(score);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("game over :(");
  lcd.setCursor(0,1);
  lcd.print("SCORE: " + scoreLabel);
  lcd.setCursor(0,2);
  lcd.print("Reset to Play Again!");
  lcd.setCursor(0, 3);
  lcd.print("Made for Science");
}