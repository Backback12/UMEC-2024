#include <Arduino_APDS9960.h>

int r, g, b;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial);

  if (!APDS.begin()) {
    Serial.println("Error initializing APDS9960 sensor!");
  }
  APDS.setLEDBoost(3);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (APDS.colorAvailable()) {
    APDS.readColor(r, g, b);
    Serial.print("Red: ");
    Serial.println(r);
    Serial.print("Green: ");
    Serial.println(g);
    Serial.print("Blue: ");
    Serial.println(b);
  }
  delay(500);
}
