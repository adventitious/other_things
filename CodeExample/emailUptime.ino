/*
  Yún HTTP Client

 This example for the YunShield/Yún shows how create a basic
 HTTP client that connects to the internet and downloads
 content. In this case, you'll connect to the Arduino
 website and download a version of the logo as ASCII text.

 created by Tom igoe
 May 2013

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/HttpClient

 */

#include <Bridge.h>
#include <HttpClient.h>

int prevState = LOW;
HttpClient client;
  
void setup() 
{
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);

  SerialUSB.begin(9600);

  while (!SerialUSB); // wait for a serial connection
}


String publishSystemUptime() 
{
  long millisecs = millis();
  int systemUpTimeMn = int((millisecs / (1000 * 60)) % 60);
  int systemUpTimeHr = int((millisecs / (1000 * 60 * 60)) % 24);
  int systemUpTimeDy = int((millisecs / (1000 * 60 * 60 * 24)) % 365);

  String sDy = String( systemUpTimeDy);
  String sHr = String( systemUpTimeHr);
  String sMn = String( systemUpTimeMn);

  String timeString = "uptime_" + sDy + "_" + sHr + "_" + sMn;

  return timeString;
}

void loop() 
{
  int pinState = digitalRead( 8 );
  if( pinState == HIGH && prevState == LOW )  // pintState
  {
    SerialUSB.print("send request!");
    prevState = HIGH;
    String s1 = publishSystemUptime();
    client.get("http://api.pushingbox.com/pushingbox?devid=v8B5DE10C1F71FB8&message=" + publishSystemUptime()  );
    while (client.available()) 
    {
      char c = client.read();
      SerialUSB.print(c);
    }
    SerialUSB.flush();
  }
  if( pinState == LOW && prevState == HIGH )
  {
    SerialUSB.print("did it send?");
    prevState = LOW;    
  }
  
  delay(25);
}
