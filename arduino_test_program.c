#include <Wire.h>

long timeout;
int flashTime = 1000;

/**
 * Test program for the roboRIO to Arduino connection.
 * The blink rate will change based on the bytes received.
 */
void setup() {
  Wire.begin(4);
  Wire.onReceive(receiveEvent); 
  pinMode(LED_BUILTIN, OUTPUT);
  timeout = millis() + 100;
}

void loop() {
  if (millis() > timeout)  {
    digitalWrite(LED_BUILTIN, digitalRead(LED_BUILTIN) == LOW ? HIGH : LOW);
    timeout = millis() + flashTime;
  }
  delay(100);
}


void receiveEvent(int howMany) {
  while (0 < Wire.available()) {
    int x = Wire.read();
    switch (x) {
      case 1 :
        flashTime = 100;
        break;
      case 2 :
        flashTime = 500;
        break;
      case 3 :
        flashTime = 2000;
        break;
      default :
        flashTime = 5000;
    }
  }
}