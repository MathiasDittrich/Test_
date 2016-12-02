/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <ESP8266WiFi.h>

//const char* ssid = "UPC497BF84";
//const char* password = "md5uuxzhfXCt";
const char* ssid = "HUAWEI-E5180-795D";
const char* password = "R0T0R895839";


//const char* host = "192.168.0.45";
const char* host = "192.168.8.102";
const int httpPort = 50000;

// Use WiFiClient class to create TCP connections
WiFiClient client;
  
void setup() {
//  pinMode(2, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);     //Pin 16 = LED_BUILTIN
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network
  Serial.println(LED_BUILTIN);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("connecting to ");
  Serial.println(host);
}

int value = 0;

void loop() 
{
  while(!client.connected())
  {
     Serial.println("try to establish connection");
     if (!client.connect(host, httpPort)) 
     {
        Serial.println("connection failed");
        delay(500);
        continue;
    }
    else
    {
      long rssi = WiFi.RSSI();
      Serial.print("RSSI:");
      Serial.println(rssi);
    }
  }
//  delay(500); 

  // This will send the request to the server
//  if(digitalRead(2) == HIGH)
//  {
//    client.print("8===D\n");
//  }
//  else
//  {
//     client.print("8=D\n"); 
//  }
//  unsigned long timeout = millis();
//  while (client.available() == 0) {
//    if (millis() - timeout > 5000) {
//      Serial.println(">>> Client Timeout !");
//      client.stop();
//      return;
//    }
//  }
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available())
  {
    String line = client.readStringUntil('\n');
    Serial.println(line);
    if(line[0] == 'a')
    {
       analogWrite(LED_BUILTIN,0);
       //digitalWrite(LED_BUILTIN, LOW);
    }
    else if(line[0] == 'b')
    {
       analogWrite(LED_BUILTIN,PWMRANGE);
       //digitalWrite(LED_BUILTIN, HIGH);
    }
    else if(line[0] == 'c')
    {
      analogWrite(LED_BUILTIN, PWMRANGE/2);
    }
  }
  
//  Serial.println();
//  Serial.println("closing connection");
}

