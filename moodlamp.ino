#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "LiquidCrystal_I2C.h"
#include "Wire.h"

// for pretty lights
int pulseSpeed = 1;
int ldrPin = 0; // LDR (Light Dependent Resistor) in Analog 0
int redLed = 9;
int greenLed = 10;
int blueLed = 11;
int ambientLight; // light value in the room
int power = 200;
float RGB[3];
float CommonMathVariable = 180 / PI;
int song = 3;

// Use pins 2 and 3 to communicate with DFPlayer Mini
static const uint8_t PIN_MP3_TX = 2; // Connects to module's RX 
static const uint8_t PIN_MP3_RX = 3; // Connects to module's TX 
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

//initialize the liquid crystal library
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Create the Player object
DFRobotDFPlayerMini player;

void setup() {

  // tells the UNO R3 to send data out to the LEDs
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);

  // sets all the outputs to LOW (off)
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
  digitalWrite(blueLed, LOW);

  // Init USB serial port for debugging
  Serial.begin(9600);
  // Init serial port for DFPlayer Mini
  softwareSerial.begin(9600);

  // Start communication with DFPlayer Mini
  if (player.begin(softwareSerial)) {
   Serial.println("OK");

    // Set volume to maximum (0 to 30).
    player.volume(30);
    // Play the first MP3 file on the SD card
    player.play(song);
  } else {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }

  //initialize lcd screen
  lcd.init();
  // turn on the backlight
  lcd.backlight();
}



void loop() {

  //wait for a second
  delay(1000);
  if (song == 1) {
    // write on the top row
    lcd.setCursor(0,0);
    lcd.print("Tom & Jerry");
    // write on the bottom row
    lcd.setCursor(0,1);
    lcd.print("Classical Music");
  } else if (song == 2) {
    // write on the top row
    lcd.setCursor(0,0);
    lcd.print("Dennis Lloyd");
    // write on the bottom row
    lcd.setCursor(0,1);
    lcd.print("NEVERMIND");
  } else if (song == 3) {
    // write on the top row
    lcd.setCursor(0,0);
    lcd.print("Mozart");
    // write on the bottom row
    lcd.setCursor(0,1);
    lcd.print("Lacrimosa");
  } else if (song == 4) {
    // write on the top row
    lcd.setCursor(0,0);
    lcd.print("Tiktok");
    // write on the bottom row
    lcd.setCursor(0,1);
    lcd.print("Vorbeste Lumea");
  }

  for (float x = 0; x < PI; x = x + -.00001) {

    // red LED
    RGB[0] = power * abs(sin(x * (CommonMathVariable)));

    // green LED
    RGB[1] = power * abs(sin((x + PI / 3) * (CommonMathVariable)));

    // blue LED
    RGB[2] = power * abs(sin((x + (2 * PI) / 3) * (CommonMathVariable)));

    ambientLight = analogRead(ldrPin);


    if (ambientLight > 600) {
      analogWrite(redLed, RGB[0]);
      analogWrite(greenLed, RGB[1]);
      analogWrite(blueLed, RGB[2]);
    }
    else {
      digitalWrite(redLed, LOW);
      digitalWrite(greenLed, LOW);
      digitalWrite(blueLed, LOW);
    }


    // Calculate the delay for each color depending on color
    // brightness; brighter LEDs will change colour slower
    for(int i = 0; i < 3; i++) {
      if(RGB[i] < 1) {
        delay(20 * pulseSpeed);
      }
      else if (RGB[i] < 5) {
        delay(10 * pulseSpeed);
      }
      else if (RGB[i] < 10) {
        delay(2 * pulseSpeed);
      }
      else if (RGB[i] < 100) {
        delay(1 * pulseSpeed);
      }
      else {}
    }

    delay(1);

  }
}
