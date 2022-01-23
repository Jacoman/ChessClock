/*
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

*/

// include the library code:
#include <LiquidCrystal.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // Change to (0x27,20,4) for 20x4 LCD.
  

  int pin7 = 10;
  int pin8 = 9;
  int buttonState = LOW;
  int buttonState2 = LOW;
  int state = 0;
  int Wstop = 0;
  int Bstop = 0;
  int w = 0;
  int b = 0;
  int counter = 0;
  long int timer, gameTime = 0;
  long int w1, b1 = 0;
void setup() {
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 2);

  while(w == 0 && b == 0)//while no time selected
  {
    timePreset();
    digitalWrite(6, HIGH);//lights
    digitalWrite(7, HIGH);
  }
  delay(500);
    buttonState = digitalRead(pin7); //pin 7 is white
    buttonState2 = digitalRead(pin8);//pin 8 is black  
  while(buttonState2 == LOW && buttonState == LOW)//while both buttons are not pressed
  {
    lcd.setCursor(0,0);
    lcd.print("Push To Start!");
    buttonState = digitalRead(pin7); //pin 7 is white
    buttonState2 = digitalRead(pin8);//pin 8 is black
  }
  gameTime = millis();
  timer = millis();
  int buttonState = 0;
  pinMode(pin7, INPUT);
  pinMode(pin8, INPUT);
  Serial.begin(9600);//debugging
}

void timePreset()
{
  lcd.setCursor(0,0);
  lcd.print("Pick a time!");
  int array1[] = {60, 180, 300, 600, 1800, 3600, 5400};
  int array2[] = {1 ,3, 5, 10, 30, 60, 90};
  buttonState = digitalRead(pin7); //pin 7 is white
  buttonState2 = digitalRead(pin8);//pin 8 is black
  delay(150);
  if(buttonState == HIGH)
  {
      lcd.setCursor(0,1);
      lcd.print("    ");
      counter++;
    
      if(counter >= 7)
      {
        counter = 0;
      }
  }
  lcd.setCursor(0,1);
  lcd.print(array2[counter]);

  if(buttonState2 == HIGH)//select time
  {
      delay(150);
      w = array1[counter];
      b = array1[counter];
  }
}

void loop() {
  
  w1 = ((w - (millis() - timer)/1000));
  b1 = (b - (millis() - timer)/1000);
  buttonState = digitalRead(pin7); //pin 7 is white
  buttonState2 = digitalRead(pin8);//pin 8 is black
  //delay(10);
  //Serial.println(buttonState);
 // Serial.println(buttonState2);
  lcd.setCursor(0, 1);

   if(buttonState == HIGH )
   {
      state = 1;
      b = b1;
      timer = millis();
   }
   if(buttonState2 == HIGH)
   {
      state = 2;
      
      w = w1;
      timer = millis();

   }

   if(state == 1 )
   {
      whiteTurn();
   }
   if(state == 2 )
   {
      blackTurn();
   }

   
   
}

void whiteTurn()
{
  lcd.setCursor(0,0);
  lcd.print("White Turn        ");
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  if(w1 > 0)
  {
      int m = minutes(w1);
      int s = seconds(w1);
      if(m < 10)
      {
        lcd.setCursor(0,1);
        lcd.print(" ");
        lcd.setCursor(1,1);
        lcd.print(m);
      }
      else
      {
        lcd.setCursor(0,1);
        lcd.print(m);
      }

      lcd.setCursor(2,1);
      lcd.print(":");

      if(s < 10)
      {
        lcd.setCursor(3,1);
        lcd.print("0");
        lcd.setCursor(4,1);
        lcd.print(s);
      }
      else
      {
        lcd.setCursor(3,1);
        lcd.print(s);  
      }

      int m2 = minutes(b);
      int s2 = seconds(b);

       if(m2 < 10)
      {
        lcd.setCursor(11,1);
        lcd.print(" ");
        lcd.setCursor(12,1);
        lcd.print(m2);
      }
      else
      {
        lcd.setCursor(11,1);
        lcd.print(m2);
      }
      lcd.setCursor(13,1);
      lcd.print(":");

      if(s2 < 10)
      {
        lcd.setCursor(14,1);
        lcd.print("0");
        lcd.setCursor(15,1);
        lcd.print(s2);
      }
      else
      {
        lcd.setCursor(14,1);
        lcd.print(s2);  
      }
  }
  else if(w1 <= 0)
  {
    int j =1 ;
    while(j = 1)
    {
      lcd.setCursor(0,0);
      lcd.print("Black Wins"); 
      digitalWrite(6, HIGH);//blinking lights
      digitalWrite(7, HIGH);
      delay(150);
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
      delay(150);
  }
}
}

void blackTurn()
{
  lcd.setCursor(0,0);
  lcd.print("Black Turn    ");
  digitalWrite(7, HIGH);
  digitalWrite(6, LOW);
   if(b1 > 0)
   {
      int m3 = minutes(w);
      int s3 = seconds(w);
       if(m3 < 10)
      {
        lcd.setCursor(0,1);
        lcd.print(" ");
        lcd.setCursor(1,1);
        lcd.print(m3);
      }
      else
      {
        lcd.setCursor(0,1);
        lcd.print(m3);
      }
      lcd.setCursor(2,1);
      lcd.print(":");

      if(s3 < 10)
      {
        lcd.setCursor(3,1);
        lcd.print("0");
        lcd.setCursor(4,1);
        lcd.print(s3);
      }
      else
      {
        lcd.setCursor(3,1);
        lcd.print(s3);  
      }
    
      int m4 = minutes(b1);
      int s4 = seconds(b1);
      if(m4 < 10)
      {
        lcd.setCursor(11,1);
        lcd.print(" ");
        lcd.setCursor(12,1);
        lcd.print(m4);
      }
      else
      {
        lcd.setCursor(11,1);
        lcd.print(m4);
      }
      lcd.setCursor(13,1);
      lcd.print(":");

      if(s4 < 10)
      {
        lcd.setCursor(14,1);
        lcd.print("0");
        lcd.setCursor(15,1);
        lcd.print(s4);
      }
      else
      {
        lcd.setCursor(14,1);
        lcd.print(s4);  
      }
   }
   else if(b1 <= 0)//if timer runs out
   {
    int j =1 ;
    while(j = 1)
    {
      lcd.setCursor(0,0);
      lcd.print("White Wins"); 
      digitalWrite(6, HIGH);//blinking lights
      digitalWrite(7, HIGH);
      delay(150);
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
      delay(150);
    }
   }
} 

int seconds(int var)
{
  return var % 60;
}

int minutes(int var2)
{
   return var2 / 60;
}

int hours(int var3)
{
  return var3 / 3600;
}
