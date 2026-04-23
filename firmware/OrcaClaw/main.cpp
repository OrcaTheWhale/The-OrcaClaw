#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <ESP32Servo.h>

const int ydof = 2;
const int xdof = 3;
const int clawpin = 4;


Servo ServoX;
Servo ServoY;
Servo Claw;


int accelx, accely, homex, homey;
// degrees of freedom for y, and x

int xmaximum = 160; // max degrees of freedom for x, can be changed after testing
int xminimum = 0;
int xdegree;

int yminimum = 60;
int ymaximum = 115; // <-- IMPORTANT TO CHANGE THIS TO REDUCE STALL
int ydegree;

int servostep = 5; // degrees to move per loop, can be changed after testing

typedef struct {
  int x;
  int y;
  int homex;
  int homey;
  bool claw;
} Payload;

Payload incoming;

void onReceive(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
  
  memcpy(&incoming, data, sizeof(incoming));

  accelx = incoming.x;
  accely = incoming.y;
  homex = incoming.homex;
  homey = incoming.homey;

  if (accelx < homex + 300) { //300 is the threshold for movement, can be changed after testing
    if (xdegree > xminimum) {
      xdegree -= servostep; 
    }
  } else if (accelx > homex - 300) {
    if (xdegree < xmaximum) {
      xdegree += servostep;
    }
  }
  if (accely > homey + 300) {
    if (ydegree < ymaximum) {
      ydegree += servostep;
    }
    // raise arm
  } else if (accely < homey - 300) {
    if (ydegree > yminimum) {
      ydegree -= servostep;
    }
    // lower arm
  }
  


  // receive x, y from gy-521
  // store first recieved x and y after button pressed as "home" position
  // if x < left of home position, turn left
  // if x > right of home position, turn right
  // if y > home position, raise arm
  // if y < home position, lower arm
  
  //track degree. If degree of freedom is greater than threshold, do not allow movement (preventing high current pull from stall)
  //

  //button 2 recieve, open / close claw
  

  Serial.print("(Signature: Edward) Received: ");
  Serial.print(incoming.x);
  Serial.print(", ");
  Serial.println(incoming.y);
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);


  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }



  //reset position and jitter to allow capacitors to do their thing
  

esp_now_register_recv_cb(onReceive);

}

void loop() {
  // put your main code here, to run repeatedly:
}

