#include <WiFi.h>
#include "ThingSpeak.h";

#define WIFI_SSID "iphoe608043"
#define WIFI_PASS "12345677"
#define SECRET_CH_ID 2785635
#define SECRET_WRITE_APIKEY "GVWS3XMGUYXB1D5A"

#define RXp2 16
#define TXp2 17

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

float t,h; //temperature, humidity
unsigned long dataMillis = 0;
WiFiClient client;
void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600,SERIAL_8N1,16,17);

  WiFi.begin(WIFI_SSID,WIFI_PASS);
  Serial.print("Connecting to Wi-fi");
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  ThingSpeak.begin(client);
}



void loop() {
  // put your main code here, to run repeatedly:

    String data = Serial2.readString();
    Serial.println(data);
    
    int comma = data.indexOf(',');
    if(comma!=-1)
    {
        t = data.substring(0,comma).toFloat();
        h = data.substring(comma+1).toFloat();
        ThingSpeak.setField(1,h);
        ThingSpeak.setField(2,t);
        if(millis() - dataMillis > 20000)
        {
          Serial.print("Temperature value: ");
          Serial.println(t);
          Serial.print("Humidity value: ");
          Serial.println(h);
          int x = ThingSpeak.writeFields(myChannelNumber,myWriteAPIKey);
          if(x==200)
          {
            Serial.println("Channel update successfull.");

          }else{
            Serial.println("Problem updating channel. HTTP error code ");
          }
        }
        delay(2000);
    }
}
