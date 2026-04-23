#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>

const int MPU_ADDR=0x68; // I2C address of the MPU-6050

int16_t accel_x, accel_y, gyroz;
 

const int control = 2;
const int laser = 3;
const int sda = 6;
const int scl = 7;



bool bounced;
bool laserbounce = false;


uint8_t receiverMAC[] = {0xA4, 0xF0, 0x0F, 0x61, 0xF4, 0x10}; // YOUR OTHER ESP WIFI CODE HERE

typedef struct {
  bool contact;
  int x;
  int y;
  int homex;
  int homey;
  int gyroz;
  int homegyroz;
  bool laser;
  bool claw;
} Payload;
Payload data;


void onSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //pinMode(led, OUTPUT);
  delay(1000);
  //Getting WIFI Setup
  WiFi.mode(WIFI_STA);
  Serial.println(WiFi.macAddress());
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb(onSent);
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverMAC, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  esp_now_add_peer(&peerInfo);

  //reset position and jitter to allow capacitors to do their thing
  //claw position = false

  //claw position: false = closed, true = open
  pinMode(control, INPUT_PULLUP);
  pinMode(laser, INPUT_PULLUP);

  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0);    // set to zero (wakes up the MPU-605
  Wire.endTransmission(true);
  laserbounce = false;

}

void loop() {
  // put your main code here, to run repeatedly:
  //data.led = random(0, 3);

  // No idea what is this but it gets gy-521 data

  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 4, true); // request a total of 4 registers
  if(Wire.available() >= 4) {
    accel_x = Wire.read() << 8 | Wire.read();
    accel_y = Wire.read() << 8 | Wire.read();
    gyroz = Wire.read() << 8 | Wire.read();
  }

// Psuedocode
// detect if button is pressed, if not ignore
// data.x = gy-521 x
// data.y = gy-521 y
// if claw button pressed, check if true/false then flip value and send
  data.x = accel_x;
  data.y = accel_y;
  data.gyroz = gyroz;

  //Set a home position
  if (digitalRead(control) == LOW && !bounced) {
    data.homex = accel_x;
    data.homey = accel_y;
    data.gyroz = gyroz;
    data.homegyroz = gyroz;
    bounced = true;
    data.contact = true;
  } else if (digitalRead(control) == HIGH) {
    data.contact = false;
    bounced = false;
  }

  if (digitalRead(laser) == LOW && !laserbounce) {
    data.laser = !data.laser;
    laserbounce = true;
  } else if (digitalRead(laser) == HIGH) {
    laserbounce = false;
  }
  
  esp_err_t result = esp_now_send(receiverMAC, (uint8_t *)&data, sizeof(data));
  delay(1000);
}
