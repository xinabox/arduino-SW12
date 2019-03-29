#include <xCore.h>
#include <xSW12.h>

xSW12 SW12;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  SW12.begin();

  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  float hum = SW12.getHumidity();
  float tem = SW12.getTempC();
  Serial.print("Hum: ");
  Serial.println(hum);
  Serial.print("Tem: ");
  Serial.println(tem);
  delay (2000);
}
