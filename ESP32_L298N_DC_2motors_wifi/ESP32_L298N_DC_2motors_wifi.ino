#include <Robojax_L298N_DC_motor.h>

// Add the copyright stuff back

#include <Robojax_L298N_DC_motor.h>

// motor 1 settings
#define CHA 1
#define ENA 4
#define IN1 17
#define IN2 16

// motor 2 settings
#define CHB 0
#define ENB 19
#define IN3 18
#define IN4 5

// motor 3 settings
#define CHC 2
#define ENC 33
#define IN5 26
#define IN6 25

//motor 4 settings
#define CHD 2
#define END 12
#define IN7 27
#define IN8 14

const int CCW = 2;
const int CW  = 1;

#define motor1 1
#define motor2 2
#define motor3 3
#define motor4 4

// Initialise motors using two seperare H-bridges
Robojax_L298N_DC_motor motors_right(IN5, IN6, ENC, CHC, IN7, IN8, END, CHD);
Robojax_L298N_DC_motor motors_left(IN3, IN4, ENB, CHB, IN1, IN2, ENA, CHA);

int       motor1Direction = CW; // default direction of rotation
const int motor1changeStep = 30; // 30 is 30% every time button is pushed
int       motor1Speed = 70; // variable holding the light output vlaue (initial value) 40 means 40%
const int motor1MinimumSpeed = 70;
const int motor1MaximumSpeed = 100;
int       motor1StopState = HIGH; //Stop state of motor (HIGH means STOP) and Minimum means Start

int       motor2Direction = CW;
const int motor2changeStep = 30;
int       motor2Speed = 70;
const int motor2MinimumSpeed = 70;
const int motor2MaximumSpeed = 100;
int       motor2StopState = HIGH;

int       motor3Direction = CW;
const int motor3changeStep = 30;
int       motor3Speed = 70;
const int motor3MinimumSpeed = 70;
const int motor3MaximumSpeed = 100;
int       motor3StopState = HIGH;

int       motor4Direction = CCW;
const int motor4changeStep = 30;
int       motor4Speed = 70;
const int motor4MinimumSpeed = 70;
const int motor4MaximumSpeed = 100;
int       motor4StopState = HIGH;

#include "ESP32_L298N_DC_motor_wifi_page.h"

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

const char *ssid = "HackTheNorth";
const char *password = "HTNX2023";

WebServer server(80);

void handleRoot() {
String HTML_page = motorControlHeader_1; 

 HTML_page.concat(".bar1 {width: " + String(motor1Speed)  + "%;}\n");
 HTML_page.concat(".bar2 {width: " + String(motor3Speed) + "%;}\n");
 HTML_page.concat(motorControlHeader_2);

 ///motor 1 and 2 begins
 HTML_page.concat(motor1Control_p1);
   
 if(motor1Direction == CW)
 {
      if(motor1StopState == HIGH)
      {
        HTML_page.concat("<strong>Stopped - CW at ");
      } else{
        HTML_page.concat("<strong>Running - CW at ");        
      }
 } else{
      if(motor1StopState == HIGH)
      {
        HTML_page.concat("<strong>Stopped - CCW at ");
      } else{
        HTML_page.concat("<strong>Running - CCW at ");        
      }
 }

 HTML_page.concat(motor1Speed);
 HTML_page.concat(motor1Control_p2);

 if(motor1StopState == HIGH)
 {
   HTML_page.concat("m1START\">START");
 } else{
   HTML_page.concat("m1STOP\">STOP"); 
 }

 HTML_page.concat(motor1Control_p3); 

///motor 3 and 4 begins
 HTML_page.concat(motor3Control_p1);
   
 if(motor3Direction == CW)
 {
      if(motor3StopState == HIGH)
      {
        HTML_page.concat("<strong>Stopped - CW at ");
      } else{
        HTML_page.concat("<strong>Running - CW at ");        
      }
 } else{
      if(motor3StopState == HIGH)
      {
        HTML_page.concat("<strong>Stopped - CCW at ");
      } else{
        HTML_page.concat("<strong>Running - CCW at ");        
      }  
 }

 HTML_page.concat(motor3Speed);
 HTML_page.concat(motor3Control_p2);

 if(motor3StopState == HIGH)
 {
   HTML_page.concat("m3START\">START");
 } else{
   HTML_page.concat("m3STOP\">STOP"); 
 }

 HTML_page.concat(motor3Control_p3); 
 
 HTML_page.concat("</body>\n</html>");
 server.send(200, "text/html", HTML_page);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
}

void setup(void) {
  Serial.begin(115200);
  motors_right.begin();
  motors_left.begin();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/speed", HTTP_GET, handleMotorSpeed);  
  server.on("/direction", HTTP_GET, handleMotorDirection); 
  server.on("/stop", HTTP_GET, handleMotorBrake);     
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started"); 
}

void loop(void) {
  server.handleClient();

  if(motor1StopState == HIGH)
  {
    motors_right.brake(motor1);
    motors_right.brake(motor2);  
  }else{
    motors_right.rotate(motor1, motor1Speed, motor1Direction); // run motor1 at motor1Speed% speed in motor1Direction 
    motors_right.rotate(motor2, motor2Speed, motor2Direction); // run motor2 at motor2Speed% speed in motor2Direction 
  }
  
  if(motor3StopState == HIGH)
  {
    motors_left.brake(motor3);  
    motors_left.brake(motor4);  
  }else{
    motors_left.rotate(motor3, motor3Speed, motor3Direction);//run motor3 at motor3Speed% speed in motor3Direction 
    motors_left.rotate(motor4, motor4Speed, motor4Direction);//run motor4 at motor4Speed% speed in motor4Direction 
  }

  delay(100);  
}


/*
 * handleMotorSpeed()
 * Slows down or speeds up the motor
 * returns nothing
 * Written by Ahmad Shamshiri on Dec 27, 2019
 * www.Robojax.com
 */
void handleMotorSpeed() {
  if(server.arg("do") == "m1slower" )
  {
    motor1Speed -= motor1changeStep;
    motor2Speed -= motor2changeStep;
    
      if(motor1Speed < motor1MinimumSpeed)
      {
        motor1Speed = motor1MinimumSpeed;
        motor2Speed = motor2MinimumSpeed;
      }
  } else if(server.arg("do") == "m1faster")
  {
    motor1Speed += motor1changeStep;
    motor2Speed += motor2changeStep;   
     
      if(motor1Speed > motor1MaximumSpeed)
      {
        motor1Speed = motor1MaximumSpeed;
        motor2Speed = motor2MaximumSpeed;
      } 
  } else if(server.arg("do") == "m3slower")
  {
    motor3Speed -= motor3changeStep;
    motor4Speed -= motor4changeStep;
    
      if(motor3Speed < motor3MinimumSpeed)
      {
        motor3Speed = motor3MinimumSpeed;
        motor4Speed = motor4MinimumSpeed;
      }
  } else if(server.arg("do") == "m3faster")
  {
    motor3Speed += motor3changeStep;
    motor4Speed += motor4changeStep;   
     
      if(motor3Speed > motor3MaximumSpeed)
      {
        motor3Speed = motor3MaximumSpeed;
        motor4Speed = motor4MaximumSpeed;
      }
  
  }else{
    motor1Speed = 0;
  }

  handleRoot();
}//handleMotorSpeed() end

/*
 * handleMotorDirection()
 * changes the direction of motor
 * returns nothing
 * Written by Ahmad Shamshiri on Dec 27, 2019
 * www.Robojax.com
 */
void handleMotorDirection() {
  if(server.arg("dir") == "m1CW")
  {
    motor1Direction = CW;
    motor2Direction = CW;

  }else if(server.arg("dir") == "m1CCW")
  {
    motor1Direction = CCW;
    motor2Direction = CCW;

  }else if(server.arg("dir") == "m3CW")
  {
    motor3Direction = CW;
    motor4Direction = CW;

  }else{
    motor3Direction = CCW; 
    motor4Direction = CCW;
  }

  handleRoot();
}//

/*
 * handleMotorBrake()
 * applies brake to the motor
 * returns nothing
 * Written by Ahmad Shamshiri on Dec 27, 2019
 * www.Robojax.com
 */
void handleMotorBrake() {
  if(server.arg("do") == "m1START")
  {  
      motor1StopState=LOW;
      motor2StopState=LOW;
  } else if(server.arg("do") == "m1STOP")
  {  
      motor1StopState=HIGH;
      motor2StopState=HIGH;
  } else if(server.arg("do") == "m3START")
  {  
      motor3StopState=LOW;
      motor4StopState=LOW;
  } else{
      motor3StopState=HIGH;
      motor4StopState=HIGH;    
  }
  handleRoot();
}
