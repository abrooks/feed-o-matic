/*
 
feed-o-matic - periodic interval pet feeder

This program drives an Adafruit Trinket (5v) controlling a PowerSwitch Tail 2
(opto-isolated, 3-12v switched, inline AC relay).

The general operation is that food is dispensed for X duration, every Y
interval seconds (msec). The goal is small feedings, through out the day.

To use this with the PowerSwitch, connect PowerSwitch terminal #1 (+IN) to the
Trinket GPIO pin #1 (the one wired in parallel with the LED) and PowerSwitch
terminal #2 (-IN) to Trinket ground pin (GND).

*/

int LED = 1; // blink 'digital' pin 1 - AKA the built in red LED
int LED_STATE = LOW;

unsigned long FEEDING_INTERVAL = 1 * 60 * 60 * 1000;
unsigned long FEEDING_DURATION = 6 * 1000;

void setup() {
  // initialize the digital pin as an output.
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LED_STATE);
}

void loop() {

  // 32-bits of milliseconds will overflow every 49.7 days.
  // This is okay as:
  //   (A) we expect to be reset regularly for nighttime feedings and
  //   (B) since feeding is at the top of the interval, the overflow event
  //       means a early feeding once every 49.7 days -- not a big deal.
  unsigned long now_msec = millis();

  if((now_msec % FEEDING_INTERVAL) < FEEDING_DURATION) {
    if(LED_STATE == LOW) {
      digitalWrite(LED, LED_STATE=HIGH);
    }
  } else {
    if(LED_STATE == HIGH) {
      digitalWrite(LED, LED_STATE=LOW);
    }
  }
}


