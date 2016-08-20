#include <SPI.h>
#include <RF24.h>
#include <Servo.h>

RF24 radio(7,8);
const uint64_t readingPipe = 0xF0F0F0F0E1LL;

Servo esc1;
Servo esc2;
Servo esc3;
Servo esc4;

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

    esc1.attach(3);
    esc2.attach(5);
    esc3.attach(6);
    esc4.attach(9);
}

void loop() {
    if (radio.available()) {
        radio.read(&values, sizeof(values));
        int val = map(values.throttle, 0, 255, 0, 180);
        esc1.write(val);
        esc2.write(val);
        esc3.write(val);
        esc4.write(val);
        printSerial();
    }
}
