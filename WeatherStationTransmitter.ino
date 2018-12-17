#include <dht.h>
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

dht DHT;

#define DHT_APIN A0

RF24 transmit (2,3);                            //create RF24 object called transmit
byte address [5] = "00001";                     //set address to 00001

struct package
  {
    float temperature = 0;
    float humidity = 0;
  };

typedef struct package Package;
Package data;

void setup(){
  Serial.begin(9600);
  delay(500);
  Serial.println("DHT11 Humidity and temperature sensor\n\n");
  delay(1000);
  transmit.begin();
  transmit.openWritingPipe(address);            //open writing pipe to address 00001
  transmit.setPALevel(RF24_PA_MAX);             //set RF power output to maximum
  transmit.setDataRate(RF24_250KBPS);           //set datarate to 250kbps
  transmit.setChannel(100);                     //set frequency to channel 100
  transmit.stopListening();
}

void loop()
{
  int chk = DHT.read11(DHT_APIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
   data.temperature = DHT.temperature;
  data.humidity = DHT.humidity;
  transmit.write(&data,sizeof(data));
  delay(5000);
}

