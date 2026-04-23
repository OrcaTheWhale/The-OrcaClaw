#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <ESP32Servo.h>

const int ydof = 2;
const int xdof = 3;
const int clawpin = 4;
const int laser = 9;


Servo ServoX;
Servo ServoY;
Servo Claw;


int accelx, accely, homex, homey, gyroz;
// degrees of freedom for y, and x

int xmaximum = 160; // max degrees of freedom for x, can be changed after testing
int xminimum = 0;
int xdegree = 80;

int yminimum = 60;
int ymaximum = 115; // <-- IMPORTANT TO CHANGE THIS TO REDUCE STALL
int ydegree = 70;

int servostep = 5; // degrees to move per loop, can be changed after testing

int clawopen = 0;
int clawclosed = 60;

bool clawstate = false;

typedef struct {
  bool contact;
  int x;
  int y;
  int homex;
  int homey;
  int homegyroz;
  bool laser;
  int gyroz;
  
  bool claw;
} Payload;

Payload incoming;

void onReceive(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
  
  memcpy(&incoming, data, sizeof(incoming));

  // Variables setup
  // Check if contact. New data wouldn't send anyways;
  if (incoming.contact) {
    accelx = incoming.x;
    accely = incoming.y;
    homex = incoming.homex;
    homey = incoming.homey;
    gyroz = incoming.gyroz;
    clawstate = incoming.claw;
    if (incoming.laser) {
      digitalWrite(laser, HIGH);
    } else {
      digitalWrite(laser, LOW);
    }
    if (accelx < homex + 300) { //300 is the threshold for movement, can be changed after testing
      if (xdegree > xminimum) {
        xdegree -= servostep; 
        ServoX.write(xdegree);
      }
    } else if (accelx > homex - 300) {
      if (xdegree < xmaximum) {
        xdegree += servostep;
        ServoX.write(xdegree);
      }
    }
    if (accely > homey + 300) {
      if (ydegree < ymaximum) {
        ydegree += servostep;
        ServoY.write(ydegree);
      }
    // raise arm
    } else if (accely < homey - 300) {
      if (ydegree > yminimum) {
        ydegree -= servostep;
        ServoY.write(ydegree);
      }
    // lower arm
    }

    //Open / close claw
    if (gyroz > incoming.homegyroz + 300) {
      if (clawstate) {
        Claw.write(clawopen);
        clawstate = true;
      } else if (gyroz <= incoming.homegyroz) {
        Claw.write(clawclosed);
        clawstate = false;
      } 
      
    }
  
}

  
  

  //Pseudocode
  // receive x, y from gy-521
  // store first recieved x and y after button pressed as "home" position
  // if x < left of home position, turn left
  // if x > right of home position, turn right
  // if y > home position, raise arm
  // if y < home position, lower arm
  
  //track degree. If degree of freedom is greater than threshold, do not allow movement (preventing high current pull from stall)
  //

  //button 2 recieve, open / close claw
  
/*
  Serial.print("(Signature: Edward) Received: ");
  Serial.print(incoming.x);
  Serial.print(", ");
  Serial.println(incoming.y);
  */
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);


  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  ServoX.attach(xdof);
  ServoY.attach(ydof);
  Claw.attach(clawpin);

  pinMode(laser, OUTPUT);

  ServoX.write(xdegree);
  ServoY.write(ydegree);
  Claw.write(clawopen);
 // Allow jitter for the capacitors
  delay(100);
  ServoX.write(xdegree+50);
  ServoY.write(ydegree+50);
  Claw.write(clawclosed);
  delay(100);
  ServoX.write(xdegree);
  ServoY.write(ydegree);
  Claw.write(clawopen);
  //reset position and jitter to allow capacitors to do their thing
  

esp_now_register_recv_cb(onReceive);

}

void loop() {
  // put your main code here, to run repeatedly:
}

