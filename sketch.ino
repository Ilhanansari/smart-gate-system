#include <Servo.h>

Servo servo;

int trig = 7;
int echo = 8;
int led = 5;

int threshold = 80;  // cm

long duration;
float distance;



void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(led, OUTPUT);

  servo.attach(9);
  servo.write(0); // gate closed
  
  Serial.begin(9600);   // (put this in setup, not loop)

  Serial.print("Distance:50 ");
  
  delay(500);
}

void loop() {

  // --- Measure Distance ---
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  digitalWrite(5, HIGH);
  delay(500);
  digitalWrite(5, LOW);
  delay(500);

  

  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;

  // --- Gate Logic ---
  if (distance < threshold) {

    // Opening (LED blink)
    for (int i = 0; i < 5; i++) {
      digitalWrite(led, HIGH);
      delay(50);
      digitalWrite(led, LOW);
      delay(50);
    }

    servo.write(90);  // open gate
    delay(5000);

    // Measure again
    digitalWrite(trig, LOW);
    delayMicroseconds(2);

    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    duration = pulseIn(echo, HIGH);
    distance = duration * 0.034 / 2;

    if (distance < threshold) {
      servo.write(90);  // keep open
    } else {

      // Closing (LED blink)
      for (int i = 0; i < 5; i++) {
        digitalWrite(led, HIGH);
        delay(50);
        digitalWrite(led, LOW);
        delay(50);
      }

      servo.write(0);   // close gate
    }

  } else {
    servo.write(0); // keep closed
  }

  delay(200);
}