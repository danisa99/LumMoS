
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "mystatus.h" //Our HTML webpage contents with javascripts
/*#include "myhistory.h" //Our HTML webpage contents with javascripts
#include "overall.h" //Our HTML webpage contents with javascripts
*/


const int FLEX_PIN = A0; // Pin connected to voltage divider output
const int ledPin = D1;   // Pin connected to LED/vibrator

const float VCC = 3.33; // Measured voltage of Ardunio 3.3V line
const float R_DIV = 46000.0; // Measured resistance of resistor

const float STRAIGHT_RESISTANCE = 12700.0; // flex resistance when straight
const float BEND_RESISTANCE = 32000.0; // flex resistance at 90 deg

const char* ssid = "Danisa";            //wifi SSID
const char* password = "12345678abc";   //wifi password

ESP8266WebServer server(80); //Server on port 80

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void Flex(){
  int flexADC = analogRead(FLEX_PIN);
            float flexV = flexADC * VCC / 1023.0;
            float flexR = R_DIV * (VCC / flexV - 1.0);
            Serial.println("Resistance: " + String(flexR) + " ohms");

            // Use the calculated resistance to estimate the sensor's
            // bend angle:
            float angle = map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE,
                          0, 90.0);
  
            Serial.println("Bend: " + String(angle) + " degrees");
            Serial.println();
/*
            if(angle>40){

            digitalWrite(ledPin,HIGH);
            }
            else
            {
            digitalWrite(ledPin,LOW);
            }*/
}

void Status() {
 String s = status_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

/*void History() {
 String h = history_page; //Read HTML contents
 server.send(200, "text/html", h); //Send web page
}

void Overall() {
 String o = overall_page; //Read HTML contents
 server.send(200, "text/html", o); //Send web page
}
*/


void handleBend() {
  int flexADC = analogRead(FLEX_PIN);
            float flexV = flexADC * VCC / 1023.0;
            float flexR = R_DIV * (VCC / flexV - 1.0);
            //Serial.println("Resistance: " + String(flexR) + " ohms");

            // Use the calculated resistance to estimate the sensor's
            // bend angle:
            float angle = map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE,
                          0, 90.0);
  String angleValue = String(angle);
 
  server.send(200, "text/plane", angleValue); //Send ADC value only to client ajax request
}


                
void handleLED() {
  String ledState = "GOOD POSTURE!";
  int flexADC1 = analogRead(FLEX_PIN);
            float flexV1 = flexADC1 * VCC / 1023.0;
            float flexR1 = R_DIV * (VCC / flexV1 - 1.0);
            
            // Use the calculated resistance to estimate the sensor's
            // bend angle:
            float angle1 = map(flexR1, STRAIGHT_RESISTANCE, BEND_RESISTANCE,
                          0, 90.0);
  
             if(angle1>=1)
             {
              digitalWrite(ledPin,HIGH); //LED ON
              ledState = "BAD POSTURE!"; //Feedback parameter
              }
             else
             {
              digitalWrite(ledPin,LOW); //LED OFF
              ledState = "GOOD POSTURE!"; //Feedback parameter  
             }
 
 server.send(200, "text/plane", ledState); //Send web page
}

//==============================================================
//                  SETUP
//==============================================================
void setup(void){
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  //Onboard LED port Direction output
  pinMode(FLEX_PIN, INPUT);
  pinMode(ledPin, OUTPUT); 
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
  server.on("/", Status);      //Which routine to handle at root location. This is display page
  server.on("/readFlex", handleBend);
  server.on("/setLED", handleLED);
 /* server.on("/overall.html", Overall);
  server.on("/myhistory.html", History);
 */

  server.begin();    //Start server
  Serial.println("HTTP server started");
}
//==============================================================
//                     LOOP
//==============================================================
void loop(void){
  server.handleClient();      //Handle client requests
  
  //Flex();
  //delay(500);
  
}
