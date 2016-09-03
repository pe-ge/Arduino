#include <SPI.h>
#include <RF24.h>

#define DEBUG false

RF24 radio(9,10);
const uint64_t writingPipe = 0xF0F0F0F0E1LL;

struct packet {
  byte throttle;
  byte yaw;
  byte pitch;
  byte roll;
} packet;

int pitch_mid;
int roll_mid;

void setup() {
  radio.begin();
  radio.openWritingPipe(writingPipe);
  radio.enableDynamicPayloads();
  radio.setAutoAck(false) ;
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(108);
  radio.powerUp();

  pitch_mid = analogRead(1);
  roll_mid = analogRead(2);

  if (DEBUG) Serial.begin(57600);
}

void loop() {
  packet.throttle = map(analogRead(3), 0, 1023, 255, 0);
  packet.yaw      = map(analogRead(0), 0, 1023, 255, 0);
  //packet.yaw = 129;
  
  int pitch = analogRead(1);
  if (pitch < pitch_mid) {
    packet.pitch = map(pitch, 0, pitch_mid, 0, 128);
  } else {
    packet.pitch = map(pitch, pitch_mid, 1023, 128, 255);
  }

  int roll = analogRead(2);
  if (roll < roll_mid) {
    packet.roll = map(roll, 0, roll_mid, 255, 128);
  } else {
    packet.roll = map(roll, roll_mid, 1023, 128, 0);
  }

  radio.write(&packet, sizeof(packet));

  if (DEBUG) {
    Serial.print(packet.throttle);
    Serial.print(" ");
    Serial.print(packet.yaw);
    Serial.print(" ");
    Serial.print(packet.pitch);
    Serial.print(" ");
    Serial.print(packet.roll);
    Serial.print(" ");
    Serial.print(analogRead(1));
    Serial.print(" ");
    Serial.print(analogRead(2));
    Serial.println();
  }
}
