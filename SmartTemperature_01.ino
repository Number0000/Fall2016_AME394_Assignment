/*
  Reading a serial ASCII-encoded string.

  This sketch demonstrates the Serial parseInt() function.
  It looks for an ASCII string of comma-separated values.
  It parses them into ints, and uses those to fade an RGB LED.

  Circuit: Common-Cathode RGB LED wired like so:
   Red anode: digital pin 3
   Green anode: digital pin 5
   Blue anode: digital pin 6
   Cathode : GND

  created 13 Apr 2012
  by Tom Igoe

  modified 14 Mar 2016
  by Harry Chang
*/

// pins for the LEDs:
const int p1 = 2;
const int p2 = 3;
const int p3 = 4;
const int p4 = 5;
const int p5 = 6;
const int p6 = 7;
const int p7 = 8;
const int p8 = 9;
const int p9 = 10;
const int p10 = 11;
//pin for temperature sensor
int sensorPin = 12;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // make the pins outputs:
  pinMode(p1, OUTPUT);
  pinMode(p2, OUTPUT);
  pinMode(p3, OUTPUT);
  pinMode(p4, OUTPUT);
  pinMode(p5, OUTPUT);
  pinMode(p6, OUTPUT);
  pinMode(p7, OUTPUT);
  pinMode(p8, OUTPUT);
  pinMode(p9, OUTPUT);
  pinMode(p10, OUTPUT);
  pinMode(sensorPin, INPUT);
}

void loop() {
  // if there's any serial available, read it:
  int reading = analogRead(sensorPin);

  float voltage = reading * 5.0;
  voltage /= 1024.0;
  float temperatureC = (voltage - 0.49) * (100);
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;

  //Serial.println(temperatureC);

  //while (Serial.available() > 0) {
  //Serial.println(temperatureC);
      //No while loop cause it check for the serial.available, 
      //which everytime serial input is !empty, it is called
  // find the percent of the battery
  int percent = Serial.parseInt();

  //get input signal from A0, convert it into angle value)
  int val = temperatureC;
  percent = val;
  Serial.println(percent);
  //int position = map(analogRead(voltage), 0, 1023, 0, 100);
  //int percent = position;


  //This is the temperature that it is in
  if (percent > 40) {
    digitalWrite(p1, HIGH);
  } else {
    digitalWrite(p1, LOW);
  }
  if (percent > 50) {
    digitalWrite(p2, HIGH);
  } else {
    digitalWrite(p2, LOW);
  }
  if (percent > 60) {
    digitalWrite(p3, HIGH);
  } else {
    digitalWrite(p3, LOW);
  }
  if (percent > 70) {
    digitalWrite(p4, HIGH);
  } else {
    digitalWrite(p4, LOW);
  }
  if (percent > 80) {
    digitalWrite(p5, HIGH);
  } else {
    digitalWrite(p5, LOW);
  }
  if (percent > 90) {
    digitalWrite(p6, HIGH);
  } else {
    digitalWrite(p6, LOW);
  }
  if (percent > 100) {
    digitalWrite(p7, HIGH);
  } else {
    digitalWrite(p7, LOW);
  }
  if (percent > 110) {
    digitalWrite(p8, HIGH);
  } else {
    digitalWrite(p8, LOW);
  }

  if (percent > 120) {
    digitalWrite(p9, HIGH);
  } else {
    digitalWrite(p9, LOW);
  }

  if (percent > 130) {
    digitalWrite(p10, HIGH);
  } else {
    digitalWrite(p10, LOW);
  }


  delay(1000);
}

