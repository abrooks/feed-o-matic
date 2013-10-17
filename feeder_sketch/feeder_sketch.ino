/*
 
feed-o-matic - periodic interval pet feeder

This program drives an Adafruit Trinket (5v) controlling a PowerSwitch Tail 2
(opto-isolated, 3-12v switched, inline AC relay).

The general operation is that food is dispensed for X duration, every Y
interval seconds (msec). The goal is small feedings, through out the day.

To use this with the PowerSwitch, connect PowerSwitch terminal #1 (+IN) to the
Trinket GPIO pin #0 and PowerSwitch terminal #2 (-IN) to Trinket ground pin (GND).

*/

int PST = 0; // 'digital' pin 0
int LED = 1; // 'digital' pin 1 - AKA the built in red LED
int STATE = LOW;

unsigned long FEEDING_INTERVAL = 1L * 60L * 60L * 1000L;
unsigned long FEEDING_DURATION = 6L * 1000L;

// Compensate for bootloader taking about 3 seconds at start.
unsigned long FEEDING_START_OFFSET = 4L * 1000L;

// Time correction
unsigned long SIX_MINUTE_DURATION = 352L; // Treat seconds as millis
unsigned long SIX_MINUTES = 6L * 60L; // Treat seconds as millis
long SIX_MINUTE_OFFSET =  SIX_MINUTE_DURATION - SIX_MINUTES;

void setup() {
  // initialize the digital pin as an output.
  pinMode(LED, OUTPUT);
  pinMode(PST, OUTPUT);
  digitalWrite(LED, STATE);
  digitalWrite(PST, STATE);
}

void loop() {

  // 32-bits of milliseconds will overflow every 49.7 days.
  // This is okay as:
  //   (A) we expect to be reset regularly for nighttime feedings and
  //   (B) since feeding is at the top of the interval, the overflow event
  //       means a early feeding once every 49.7 days -- not a big deal.
  unsigned long now_msec = millis();

  // Compute time adjustment based on six minute observation.
  // Seconds are scaled down to msec for smoother time correction.
  long six_min_adj = (now_msec / SIX_MINUTES) * SIX_MINUTE_OFFSET;
  unsigned long now_msec_adj = now_msec + six_min_adj;
  unsigned long intvl_msec = now_msec_adj % FEEDING_INTERVAL;

  if((FEEDING_START_OFFSET < intvl_msec)
     && (intvl_msec < (FEEDING_DURATION + FEEDING_START_OFFSET))) {
    if(STATE == LOW) {
      STATE = HIGH;
      digitalWrite(LED, STATE);
      digitalWrite(PST, STATE);
    }
  } else {
    if(STATE == HIGH) {
      STATE = LOW;
      digitalWrite(LED, STATE);
      digitalWrite(PST, STATE);
    }
  }
}


