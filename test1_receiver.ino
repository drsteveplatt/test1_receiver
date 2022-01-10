// RF24 TEST1 receiver
// SMP
// 2015-1003 Ver. 1.0

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define PRINTING 0

// which pin the LED is on
#define LED  8

// and where the radio is
#define RF24_CE 9
#define RF24_CSN  10
#define PIPE_ID  "TEST1\0\0\0"

RF24 radio(RF24_CE, RF24_CSN);

int count;  // how many radio reads

struct Packet {
  int count;
  int val;
};

Packet packet;

void setup() {
  // put your setup code here, to run once:
#if PRINTING>0
  Serial.begin(9600);
  Serial.println("Receiver starting");
#endif

  pinMode(LED, OUTPUT);
  
  long realPipeID;
  memcpy(&realPipeID, PIPE_ID, sizeof(long));
  radio.begin();
  radio.openReadingPipe(1, realPipeID);
  radio.startListening();
  
  count = 0;
}

void loop() {
  int radioData;
  if(radio.available()) {
    radio.read(&packet, sizeof(Packet));
    radioData = packet.val;
    digitalWrite(LED, radioData==0?LOW:HIGH);
    
#if PRINTING>0
    Serial.print(count++);
    Serial.print(" -> [");
    Serial.print(packet.count);
    Serial.print(", ");
    Serial.print(packet.val);
    Serial.println("]");
#endif
  }

}
