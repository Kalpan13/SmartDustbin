# SmartDustbin
An IoT based Smart Dustbin that can send the status of Garbage Level to server. It can also open and close automatically whenever a person comes in the proximity of Sensor.

<b>Components Used</b> 
```
1. NodeMCU (ESP8266-12E) 
2. Ultrasonic Sensors x2
3. Servo Motor
```

<b>Requirements</b>
```
1. Libraries for Node.js and NodeMCU must be installed
2. Arduino IDE
```  
<b>Steps to Run</b>

1. Start the Node Server using `node Node_Server.js`
2. Upload [Main.ino](Main/Main.ino) file into NodeMCU using Arduino IDE
3. Open [client.html](client.html) 

<b>Library Requirements</b>

For Node.Js
* bodyParser 
* express
* http
* path
* ws

_can be installed using `npm install <module_name>`_

For ArduinoIDE
* ESP8266WiFi.h
* Servo.h
* WebSocketClient.

_can be installed using Library Manager_

Working Demo : [SmartBin](https://drive.google.com/file/d/1SaN5MZjGWM1yHQJv9Evq9iGWcE_RgZHO/view?usp=sharing)
