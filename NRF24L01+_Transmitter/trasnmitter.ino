#include <SPI.h>
#include <RF24.h>
#include "printf.h"

RF24 radio(9, 10);
const uint64_t pipe = 0xF0F0F0F0E1LL;

void setup(void)
{


  Serial.begin(57600);
  printf_begin();

  radio.begin();
  radio.openWritingPipe(pipe);

  radio.enableDynamicPayloads() ;
  radio.setAutoAck( true ) ;
  radio.powerUp() ;

  radio.printDetails();
}

void loop(void)
{
  unsigned long time = millis();
  radio.write( &time, sizeof(unsigned long) );
}
