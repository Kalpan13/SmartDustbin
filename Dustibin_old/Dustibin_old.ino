#include <Servo.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#define WIFI_SSID "KALPAN"
#define WIFI_PASSWORD "kalpan1998"

const int trigPin = 2;  //D4
const int echoPin = 0;  //D3

const int trigPin2 = 14;  //D5
const int echoPin2 = 12;  //D6

long duration;
long duration2;
int distance;
int distance2;
Servo myservo;

void setup() {
        Serial.println('In the setup phase');
        myservo.attach(4); //D2

        myservo.write(0);
        
        pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
        pinMode(echoPin, INPUT); // Sets the echoPin as an Input
        pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
        pinMode(echoPin2, INPUT); // Sets the echoPin as an Input
      
        delay(2000);
    
        Serial.begin(9600);
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        Serial.print("connecting");
        while (WiFi.status() != WL_CONNECTED) {
            Serial.print(".");
            delay(500);
        }
        Serial.println();
        Serial.print("connected: ");
        
  }

void loop() {
  
  int ang;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  
  distance= duration*0.034/2;
  Serial.print("Distance1: ");
  Serial.println(distance);
  
  if(distance<30)
  {  
   
  myservo.write(0);  
  delay(5000);
  myservo.write(180);
  }
  
  
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  duration2 = pulseIn(echoPin2, HIGH);
  
  distance2= duration2 *0.034/2;
  Serial.print("Distance2: ");
  Serial.println(distance2);
  
  
   Firebase.setInt("Distance:",distance2);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
   Serial.print("IN the loop");
    
}
