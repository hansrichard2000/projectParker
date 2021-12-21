#include <Wire.h>

#include <Servo.h>
#include <LCD_I2C.h>

LCD_I2C lcd(0x27);

Servo myservo;
const int in = 7;
const int out = 6;
int count = 0;
int valin = 0;
int valout = 0;
int pos =0;
int cnt;
int IR = 3;
int IR2 = 2;
int IR3 = 4;
int IR4 = 5;
int IR5 = 6;
//int IRgate = 4;
int LED = 12;
int LED2 = 11;
int LED3 = 10;
int LED4 = 9;
bool apply = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.println("Tepar");
  lcd.setCursor(0, 1);
  lcd.print("P-L:");
  myservo.attach(8);
  myservo.write(117);
  pinMode(IR, INPUT);
  pinMode(IR2,INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);  
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int readIR = digitalRead(IR);
  int readIR2 = digitalRead(IR2);
  int readIR3 = digitalRead(IR3);
  int readIR4 = digitalRead(IR4);
  int readIR5 = digitalRead(IR5);
  if(readIR == LOW && readIR3 == LOW && readIR4 == LOW){
    apply = false;
  }else{
    lcd.setCursor(0, 0);
    lcd.println("Tepar");
    lcd.setCursor(0, 1);
    lcd.print("P-L:");
    apply = true;
  }
  if(apply == true){
    if(readIR == LOW){
      digitalWrite(LED, HIGH);
      lcd.setCursor(6, 1);
      lcd.print("1");
//      apply = false;
      delay(1000);
    }
    else{
      digitalWrite(LED, LOW);
      lcd.setCursor(6, 1);
      lcd.print(" ");
      delay(1000);
    }

    if((readIR2 == LOW && readIR5 == HIGH) || (readIR2 == HIGH && readIR5 == LOW)){
      digitalWrite(LED2, HIGH);
      lcd.setCursor(7, 0);
      lcd.print("Open");
      myservo.write(20);
    
      delay(1000);
    }
    else if(readIR2 == HIGH){
      digitalWrite(LED2, LOW);
      myservo.write(117);
      lcd.setCursor(7, 0);
      lcd.print("Close");
      delay(1000);
    }
    if((readIR5 == LOW && readIR2 == HIGH) || (readIR5 == HIGH && readIR2 == LOW)){
      digitalWrite(LED2, HIGH);
      myservo.write(20);
    
      delay(1000);
    }
    else if(readIR5 == HIGH){
      digitalWrite(LED2, LOW);
      myservo.write(117);
      lcd.setCursor(1, 1);
      delay(1000);
    }
    if(readIR3 == LOW){
      digitalWrite(LED3, HIGH);
      lcd.setCursor(7, 1);
      lcd.print("2");
//      apply = false;
      delay(1000);
    }
    else{
      digitalWrite(LED3, LOW);
      lcd.setCursor(7, 1);
      lcd.print(" ");
      delay(1000);
    }
    if(readIR4 == LOW){
      digitalWrite(LED4, HIGH);
      lcd.setCursor(8, 1);
      lcd.print("3");
//      apply = false;
      delay(1000);
    }
    else{
      digitalWrite(LED4, LOW);
      lcd.setCursor(8, 1);
      lcd.print(" ");
      delay(1000);
    }
  }else{
    if(readIR == LOW){
      digitalWrite(LED, HIGH);
      lcd.setCursor(6, 1);
      lcd.print("1");
      delay(1000);
    }
    else{
      digitalWrite(LED, LOW);
      lcd.println(" ");
      lcd.setCursor(6, 1);
      delay(1000);
    }

    if(readIR2 == LOW){
      digitalWrite(LED2, HIGH);
      lcd.setCursor(0, 0);
      lcd.println("Parking full");
      myservo.write(117);
    
      delay(1000);
    }
    else if(readIR2 == HIGH){
      digitalWrite(LED2, LOW);
      myservo.write(117);
      delay(1000);
    }
    if(readIR5 == LOW){
      digitalWrite(LED2, HIGH);
      myservo.write(20);
    
      delay(1000);
    }
    else if(readIR5 == HIGH){
      digitalWrite(LED2, LOW);
      myservo.write(117);
      delay(1000);
    }
    if(readIR3 == LOW){
      digitalWrite(LED3, HIGH);
      lcd.setCursor(7, 1);
      lcd.println("2");
//      apply = false;
      delay(1000);
    }
    else{
      digitalWrite(LED3, LOW);
      lcd.setCursor(7, 1);
      lcd.println(" ");
      delay(1000);
    }
    if(readIR4 == LOW){
      digitalWrite(LED4, HIGH);
      lcd.setCursor(8, 1);
      lcd.println("3");
//      apply = false;
      delay(1000);
    }
    else{
      digitalWrite(LED4, LOW);
      lcd.setCursor(8, 1);
      lcd.println(" ");
      delay(1000);
    }
  }
}
