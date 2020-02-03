#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "EfVfEhPbhIkkam0PdRNVRkDkSPFZaPIX";
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "IOT";
char pass[] = "univalletulua";

float temperature=0.0;
float lectura=0.0;

BlynkTimer timer;
WidgetTerminal terminal(V1);

void myTimerEvent()
{
  lectura=analogRead(0);
  temperature=map(lectura,0,1023,0,100);
  temperature*=3.3;
  Blynk.virtualWrite(V5, temperature);
}
BLYNK_WRITE(V1)
{
  Serial.println(param.asStr());
  if (String("Marco") == param.asStr()) {
    terminal.println("You said: 'Marco'") ;
    terminal.println("I said: 'Polo'") ;
  } else {
    terminal.print("You said:");
    terminal.write(param.getBuffer(), param.getLength());
    terminal.println();
  }
  // Ensure everything is sent
  terminal.flush();
}
void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}
void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
