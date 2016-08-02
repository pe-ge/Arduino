#include <SPI.h>
#include <RF24.h>

RF24 radio(9,10);
const uint64_t readingPipe = 0xF0F0F0F0E1LL;

struct radio_values {
    byte throttle;
    byte yaw;
    byte pitch;
    byte roll;
} values;

void printSerial() {
    Serial.print(values.throttle);
    Serial.print(" ");
    Serial.print(values.yaw);
    Serial.print(" ");
    Serial.print(values.pitch);
    Serial.print(" ");
    Serial.println(values.roll);
}

void setup() {
    Serial.begin(57600);
    
    radio.begin();
    radio.openReadingPipe(1, readingPipe);
    radio.enableDynamicPayloads();
    radio.setAutoAck(false);
    radio.setDataRate(RF24_250KBPS);
    radio.setPALevel(RF24_PA_MIN); 
    radio.setChannel(108);
    radio.powerUp();
    radio.startListening();
}

void loop() {
    if (radio.available()) {
        radio.read(&values, sizeof(values));
        printSerial();
    }
}
