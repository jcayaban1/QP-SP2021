#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>


Adafruit_MMA8451 mma = Adafruit_MMA8451();

void setup(void) {
  // put your setup code here, to run once:
  Serial.begin(9600);

  if (! mma.begin()) {
    Serial.println("Couldnt start");
    while (1);
  }
  mma.setRange(MMA8451_RANGE_2_G);


}

void loop() {

  mma.read();

  sensors_event_t event; 
  mma.getEvent(&event);

  Serial.print(event.acceleration.y); 
  Serial.print(",");
  Serial.println(event.acceleration.x);
  delay(50);

}
