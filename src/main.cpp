// Blynk App
#define BLYNK_AUTH_TOKEN_WATER_PUMP "0BVxluy8unor3WZHVLYNys90EzRM5IZi"
#define BLYNK_PRINT Serial

// include the libraries
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define PUMP 18
#define LED 2

// Your WiFi credentials.
char ssid[] = "pornnapat";
char pass[] = "0961514599";

int pinValue;

BLYNK_WRITE(V0)
{
    pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
    if (pinValue == 1)
    {
        digitalWrite(PUMP, HIGH);
    }
    else
    {
        digitalWrite(PUMP, LOW);
    }
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
    // Change Web Link Button message to "Congratulations!"
    Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
    Blynk.setProperty(V3, "onImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
    Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
    digitalWrite(LED, HIGH);
}

void setup()
{
    Serial.begin(9600);
    Blynk.begin(BLYNK_AUTH_TOKEN_WATER_PUMP, ssid, pass, "blynk.iot-cm.com", 8080); //Blynk
    pinMode(LED, OUTPUT);
    pinMode(PUMP, OUTPUT);
}

void loop()
{
    Blynk.run(); // Blynk
    Serial.println(pinValue);
}