#define common_cathode 0 
#define common_anode 1 
bool mode = common_anode;// my display is common anode 
#define pinA 2 
#define pinB 3
#define pinC 4 
#define pinD 5 
#define pinE 7 
#define pinF 12 
#define pinG 8 
#define pinDP 13 
#define D1 6 
#define D2 9 
#define D3 10 
#define D4 11

#define trigPin 22
#define echoPin 24
#include "array.h" 
#include "functions.h" 

float duration, distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pinA, OUTPUT);      
	pinMode(pinB, OUTPUT);      
	pinMode(pinC, OUTPUT);      
	pinMode(pinD, OUTPUT);      
	pinMode(pinE, OUTPUT);      
	pinMode(pinF, OUTPUT);      
	pinMode(pinG, OUTPUT);  
	pinMode(pinDP, OUTPUT);   
	pinMode(D1, OUTPUT);   
	pinMode(D2, OUTPUT);   
	pinMode(D3, OUTPUT);   
	pinMode(D4, OUTPUT);  

  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //Calculate distance
  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;

  //Show on display
  String distanceString = String((int)distance);
  Serial.println("Distance: " + distanceString);
  printDisplay(distanceString, 1000);
  Reset();
}