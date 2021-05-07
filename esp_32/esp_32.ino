/*
 * https://circuits4you.com
 * ESP32 LED Blink Example
 * Board ESP23 DEVKIT V1
 *
 * ON Board LED GPIO 2
 */

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <driver/adc.h>

#define LIGHT_STAGE_MODE 2
#define PHOTOGRAMMERTY_MODE 1 //Define mode of operation
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define LED 2
const int input_swich = 4;
const int trigger_pin = 19;


const int cam_1_pin = 32;
const int cam_2_pin = 33;
const int cam_3_pin = 25;
const int cam_4_pin = 26;
const int cam_5_pin = 27;
const int cam_6_pin = 14;
const int cam_7_pin = 12;
const int cam_8_pin = 13;
const int focus_pin =  13;
const int potPin = 34;
int external_delay_time = 30; // Time between cameras
int internal_delay_time = 60; // Time between cameras
int triggered = 0;
int swichState = 0;
int buttonState = 0;
int potValue = 0;
int mode_of_operation = 1;
  void setup() {

  pinMode(input_swich, INPUT);
  pinMode(cam_1_pin, OUTPUT);
  pinMode(cam_2_pin, OUTPUT);
  pinMode(cam_3_pin, OUTPUT);
  pinMode(cam_4_pin, OUTPUT);
  pinMode(cam_5_pin, OUTPUT);
  pinMode(cam_6_pin, OUTPUT);
  pinMode(cam_7_pin, OUTPUT);
  pinMode(cam_8_pin, OUTPUT);

  pinMode(input_swich, INPUT);


  Serial.begin(115200);
  pinMode(LED,OUTPUT);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(300);
  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,5);             // Start at top-left corner
  display.println("Light stage prot. ver. 0.1!");
  display.println("Ready to begin!");
  display.display();
  delay(1000);

   // Clear the buffer
  display.clearDisplay();

}

void loop() {
  swichState = digitalRead(input_swich);
  potValue = analogRead(potPin);
  if (digitalRead(trigger_pin) == HIGH){
    triggered = 1;
  }
  display.clearDisplay();
  display.setCursor(0,5);
  if (swichState == HIGH) {
  // =========  IF STATE == SET =================
    display.print("SET ");
    display.print("  ");
    //display.print(potValue);
    Serial.println("SET");
    //Serial.println(potValue);
    if (mode_of_operation == PHOTOGRAMMERTY_MODE){
      display.print("PHGR ");
      //Serial.println("PHGR");
    }
    if (mode_of_operation == LIGHT_STAGE_MODE){
      display.print("LGTSTG ");
      //Serial.println("LGTSTG");
    }
    if (triggered ==  1){
      switch (mode_of_operation) {
        case PHOTOGRAMMERTY_MODE:
        mode_of_operation = LIGHT_STAGE_MODE;
        break;
        case LIGHT_STAGE_MODE:
        mode_of_operation = PHOTOGRAMMERTY_MODE;
        break;
      }
    triggered = 0;

    delay(300);
    }
    display.display();
  }
  else{
  //========  IF STATE == ARM ===================
    display.print("ARM ");
    //Serial.println("ARM");

    if (mode_of_operation == PHOTOGRAMMERTY_MODE){
      display.print("PHGR ");
      //Serial.println("PHGR");
    }
    if (mode_of_operation == LIGHT_STAGE_MODE){
      display.print("LGTSTG ");
      //Serial.println("LGTSTG");
    }
    //if (triggered == 1){
      //display.print(" TRIGGERED");
      //Serial.println(" TRIGGERED");
    //}

  display.display();
  delay(1);


  if(triggered){
  /*

  */

    if (mode_of_operation == PHOTOGRAMMERTY_MODE){
      digitalWrite(LED, HIGH);
      digitalWrite(focus_pin, HIGH);
      delay(500);
      digitalWrite(focus_pin, HIGH);

      digitalWrite(cam_1_pin, HIGH);
      digitalWrite(cam_2_pin, HIGH);
      digitalWrite(cam_3_pin, HIGH);
      digitalWrite(cam_4_pin, HIGH);
      digitalWrite(cam_5_pin, HIGH);
      digitalWrite(cam_6_pin, HIGH);
      digitalWrite(cam_7_pin, HIGH);

      delay(10);

      digitalWrite(cam_1_pin, LOW);
      digitalWrite(cam_2_pin, LOW);
      digitalWrite(cam_3_pin, LOW);
      digitalWrite(cam_4_pin, LOW);
      digitalWrite(cam_5_pin, LOW);
      digitalWrite(cam_6_pin, LOW);
      digitalWrite(cam_7_pin, LOW);

      digitalWrite(LED, LOW);
      digitalWrite(focus_pin, LOW);
    }
    if (mode_of_operation == LIGHT_STAGE_MODE){
      digitalWrite(LED, HIGH);
      digitalWrite(focus_pin, HIGH);
      delay(200);


      blink(cam_1_pin,internal_delay_time,external_delay_time);
      blink(cam_2_pin,internal_delay_time,external_delay_time);
      blink(cam_3_pin,internal_delay_time,external_delay_time);
      blink(cam_4_pin,internal_delay_time,external_delay_time);
      blink(cam_5_pin,internal_delay_time,external_delay_time);
      blink(cam_6_pin,internal_delay_time,external_delay_time);
      delay(100);
      blink(cam_7_pin,internal_delay_time,external_delay_time);
      digitalWrite(LED, LOW);
      digitalWrite(focus_pin, LOW);

    }
    triggered=0;
    delay(200);
  }
  }
}


int blink(int pin,int int_delay,int ext_delay){
  digitalWrite(pin, HIGH);
  delay(int_delay);
  digitalWrite(pin, LOW);
  delay(ext_delay);
}
