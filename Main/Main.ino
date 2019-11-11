#include <Servo.h>
#include <ESP8266WiFi.h>
#include <WebSocketClient.h>

#define WIFI_SSID "Kalpan13"          //Wifi Name
#define WIFI_PASSWORD "Kalpan12345"   //Password

boolean handshakeFailed=0;
String data= "";
char path[] = "/";   
char* host = "192.168.43.220";      //Server IP
const int espport= 3000;            //Server's port
int ans = 0;

WebSocketClient webSocketClient;
unsigned long interval=3000;       //Interval for sending data to server
WiFiClient client;

const int trigPin = 2;  //D4
const int echoPin = 0;  //D3

const int trigPin2 = 14;  //D5
const int echoPin2 = 12;  //D6

long duration;
long duration2;
int distance;
int distance2;
Servo myservo;
int previousMillis;
int currentMillis;

void setup() {
        Serial.println('In the setup phase');
        myservo.attach(4); //D2
        myservo.write(0);
        pinMode(trigPin, OUTPUT); 
        pinMode(echoPin, INPUT); 
        pinMode(trigPin2, OUTPUT); 
        pinMode(echoPin2, INPUT); 
        delay(2000);
        previousMillis = 0;
        Serial.begin(115200);

        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        Serial.print("connecting");
        while (WiFi.status() != WL_CONNECTED) {
            Serial.print(".");
            delay(500);
        }
        Serial.println();
        Serial.print("connected: ");
        Serial.println(WiFi.localIP());
        wsconnect();
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
         myservo.write(180);
         delay(3000);
         myservo.write(0);  
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

        currentMillis=millis(); 
          
          if (abs(currentMillis - previousMillis) >= interval) 
           {
            sendata(distance2);//Distane from Ultra Sensor
            previousMillis = currentMillis;
           }         
}
void sendata(int distance)
{
        Serial.println("Sending data server");
        if (client.connected())
        {
          Serial.println("Client Connected");
          webSocketClient.getData(data);  
          data= String(distance);  
          webSocketClient.sendData(data);
          Serial.println("Data Sent");
         }
        
        else{
          Serial.println("Client Not Connected");
            }
        delay(5);
  }
  

void wsconnect(){
       if (client.connect(host, espport)) 
       {
       Serial.println("Connected");
       } else 
       {
         Serial.println("Connection failed.");
         delay(1000);  
         if(handshakeFailed)
         {
           handshakeFailed=0;
           ESP.restart();
         }
         handshakeFailed=1;
       }
      webSocketClient.path = path;
      webSocketClient.host = host;
      if (webSocketClient.handshake(client)) 
      {
        Serial.println("Handshake successful");
      } 
      else 
      {
        Serial.println("Handshake failed.");
        delay(2000);  
        if(handshakeFailed)
        {
          handshakeFailed=0;
          ESP.restart();
        }
        handshakeFailed=1;
      }
}
