#include <SPI.h>
#include <RF24.h>
#include "printf.h"

RF24 radio(7, 8);
const uint64_t pipe = 0xF0F0F0F0E1LL;

void setup(void)
{
  Serial.begin(57600);
  printf_begin();

  radio.begin();

  radio.openReadingPipe(1,pipe);

  radio.enableDynamicPayloads() ;
  radio.setAutoAck( true ) ;
  radio.powerUp() ;
  radio.startListening();

  radio.printDetails();
}

void loop(void)
{
  if ( radio.available() )
  {
    // Dump the payloads until we've gotten everything
    unsigned long got_time;
    bool done = false;
    while (!done)
    {
      // Fetch the payload, and see if this was the last one.
      done = radio.read( &got_time, sizeof(unsigned long) );
    }
    printf("Sent response %lu\n\r", got_time);
  }
}
