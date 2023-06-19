//BURADAKİ VERİLER GÖNDERİCİ LORAYA GİDECEK
#include <SPI.h>
#include <LoRa.h>
String inputString = "";     // a string to hold incoming data
bool stringComplete = false; // whether the string is complete
void setup() {

  Serial.begin(9600);
  while (!Serial);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("LoRa Sender");

  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  if(stringComplete)
	{
     while (LoRa.beginPacket() == 0) 
     {
      //Serial.print("waiting for radio ... ");
      delay(10);
    }
		LoRa.beginPacket();
		LoRa.print(inputString);
    LoRa.endPacket(false);
    digitalWrite(LED_BUILTIN, LOW);
    stringComplete =false;

	} 
}

void serialEvent()
{
	while (Serial.available())
	{
		char inChar = Serial.read();		 // get the new byte:
		inputString += inChar; // add it to the inputString:
		if (inChar == '\n')
		{
			stringComplete = true;
      digitalWrite(LED_BUILTIN, HIGH);

		}
	}
	
}