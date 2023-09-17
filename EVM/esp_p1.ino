#define BLYNK_TEMPLATE_ID "TMPLoEZmlwof"
#define BLYNK_DEVICE_NAME "EVM"
#define BLYNK_AUTH_TOKEN "7AnyXASie5315FMBWr7VoCeQJhEF7svL"


// Comment this out to disable prints and save space
//#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "Redmi9";
char pass[] = "shahriar";

BlynkTimer timer;

String sdata;
char rdata;
String mystring;

void myTimerEvent()
{
  
  
  sdata = mystring ;
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V1, sdata);
  mystring = "";
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  //Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  if (Serial.available() == 0)
  {
    Blynk.run();
    timer.run(); // Initiates BlynkTimer
  }
  if (Serial.available() > 0) 
  {
    rdata = Serial.read(); 
    mystring = mystring + rdata; 
  
  }
  
   
  
}
