
#include <dht.h>
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 5, 4, 6, 7);
//int output_pin10 = 10;
//int contrast = 75;

RF24 receive (2,3);                         //create object called receive
byte address [5] = "00001"; //creat an array with 5 elements, where each element is 1 byte;

struct package
  {
    float temperature = 0;
    float humidity = 0;
  };

typedef struct package Package;
Package data;

void setup() {
  Serial.begin(9600);
  Serial.print("Starting Receiver \n");
   lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Now Receiving");
 // pinMode(output_pin10, OUTPUT);
  //analogWrite(output_pin10, contrast);
  receive.begin();
  receive.openReadingPipe(0,address);      //open reading pipe 0 at address 00001 
  receive.setPALevel(RF24_PA_MAX);         //Set RF output to minimum
  receive.setDataRate(RF24_250KBPS);       //set datarate to 250kbps
  receive.setChannel(100);                 //set frequency to channel 100 
  receive.startListening();                
  }

void loop() {

  if (receive.available())                //check when received data available
  {
    receive.read(&data, sizeof(data));
     lcd.setCursor(0,1);
     delay(2000);
      lcd.print(data.temperature);
      lcd.print((char)223);
    lcd.print("C ");
    lcd.print(data.humidity);
    lcd.print("%");
    Serial.print(data.temperature);
      Serial.println("C ");
    Serial.print(data.humidity);//print data to serial monitor
     Serial.println("%");
  }
    
}
