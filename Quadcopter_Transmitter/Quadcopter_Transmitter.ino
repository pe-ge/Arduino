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

void setup() {
  radio.begin();
  radio.openWritingPipe(writingPipe);
  radio.enableDynamicPayloads();
  radio.setAutoAck(false) ;
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(108);
  radio.powerUp();

  if (DEBUG) Serial.begin(57600);
}

void loop() {
  packet.throttle = map(analogRead(3), 0, 1023, 255, 0);
  packet.yaw      = map(analogRead(0), 0, 1023, 255, 0);
  packet.pitch    = map(analogRead(1), 0, 1023, 255, 0);
  packet.roll     = map(analogRead(2), 0, 1023, 255, 0);

  radio.write(&packet, sizeof(packet));

  if (DEBUG) {
    Serial.print(packet.throttle);
    Serial.print(" ");
    Serial.print(packet.yaw);
    Serial.print(" ");
    Serial.print(packet.pitch);
    Serial.print(" ");
    Serial.print(packet.roll);
    Serial.println();
  }
}
