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


int external_delay_time = 300; // Time between cameras
int internal_delay_time = 300; // Time between cameras
int triggered = 0;
int swichState = 0;
int buttonState = 0;

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
  if (digitalRead(trigger_pin) == HIGH){
    triggered = 1;
  }
  display.clearDisplay();
  display.setCursor(0,5);
  if (swichState == HIGH) {
    triggered = 0;
    display.print("SET");
    Serial.println("SET");
  }
  else{
    display.print("ARM");
    Serial.println("ARM");
    if (triggered == 1){
      display.print(" TRIGGERED");
      Serial.println(" TRIGGERED");
    }
  }
  display.display();
  delay(1);


  if(triggered){
  digitalWrite(LED, HIGH);

  blink(cam_1_pin,internal_delay_time,external_delay_time);
  blink(cam_2_pin,internal_delay_time,external_delay_time);
  digitalWrite(LED, LOW);
  
  }
  triggered=0;
  
} 


int blink(int pin,int int_delay,int ext_delay){
  digitalWrite(pin, HIGH);
  delay(int_delay);
  digitalWrite(pin, LOW);
  delay(ext_delay);
}
