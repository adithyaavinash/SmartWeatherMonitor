#define trigPin D8
#include <Servo.h>
#define echoPin D7
int a=0;
int b=0;
Servo myservo; 
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define SSD1306_LCDHEIGHT 64

// OLED display TWI address
#define OLED_ADDR   0x3C

Adafruit_SSD1306 display(-1);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
void setup() {
   display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
  myservo.attach(D4);
// display a line of text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.print("Tollgate working");
  display.display(); // update display with all of the above graphics
  

  

}

void loop() {
  // put your main code here, to run repeatedly:
int duration, distance;
digitalWrite(trigPin, HIGH);
delay(100);
digitalWrite(trigPin, LOW);
duration=pulseIn(echoPin, HIGH);
distance= (duration/2)*0.0343;
int v,pos;
if (distance<=20)
{
  v=1;
  b=0;
  }
  else 
  {
    v=0;
    a=0;
    }
if (v== 1)
{
  a=a+1;
  if(a==1) {
     Serial.println("The gate is opening please wait ");
  for (pos = 0; pos <= 90; pos += 15) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);   // tell servo to go to position in variable 'pos'
    delay(100);   
    // waits 15ms for the servo to reach the position
   
  }
    Serial.println("The gate is opened ");
    display.clearDisplay();
    gateopen();
    
   
  }
                      // waits 15ms for the servo to reach the position
  }
  else if(v==0)
  {
    b=b+1;
    if(b==1) {
      
    for (pos = 90; pos >= 0; pos -= 15) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(100);   
    // waits 15ms for the servo to reach the position
    }
    Serial.println("The gate is closed ");
      display.clearDisplay();
          gateclose();
    }
}
}
void gateopen()
{
    display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,1);
  display.print("GATE \nOPENED");
  display.display();
  }
  void gateclose()
{
    display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,1);
  display.print("GATE \nCLOSED");
  display.display();
  }
  
