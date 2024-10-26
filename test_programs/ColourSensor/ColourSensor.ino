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


  Serial.println("R:,G:,B:,CUTOFF");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (APDS.colorAvailable()) {
    APDS.readColor(r, g, b);
//    Serial.print("Red: ");
    Serial.print(r);
    Serial.print(", ");
    Serial.print(g);
    Serial.print(", ");
    Serial.print(b);
    
    // cutoff = 60% of RED
    Serial.print(", ");
    Serial.println(r * 0.6);
  }
  delay(50);
}
