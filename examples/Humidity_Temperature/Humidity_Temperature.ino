/*************************************************************
	This is an examples for the SW12
	Digital Temperature and Humidity Sensor
	
	You can buy one on our store!
	-----> https://xinabox.cc/SW12/
	
	This example request a temperature meausrement and
  humidity reading to be made by the SW12 and display 
  the data over the Serial.
	
	The sensor communicates over the I2C Bus.
	
*************************************************************/
#include <xCore.h>
#include <xSW12.h>

xSW12 SW12;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // Stat the I2C Bus
  Wire.begin();

  // Start the SW12 Sensor
  SW12.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  float hum, tempC;

  // Get the Humidity Value
  SW12.getHumidity(hum);

  // Get the Temperature Value
  SW12.getTempC(tempC);

  Serial.print("Hum: ");
  Serial.print(hum);
  Serial.println("%");

  Serial.print("Temp: ");
  Serial.print(tempC);
  Serial.println("°C");
  delay (2000);
}
