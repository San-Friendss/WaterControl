// Blynk App
#define BLYNK_AUTH_TOKEN_WATER_PUMP "0BVxluy8unor3WZHVLYNys90EzRM5IZi"
#define BLYNK_AUTH_TOKEN_OLED "nNcNxAOxQ35qNH5xYhsk2_bwIDnif8Nx"
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

WidgetBridge bridge1(V0);

int openPump = 0; // 0 = close, 1 = open
int wateringCycle = 0;
int mode = 0; // 0 = manual, 1 = auto

BLYNK_WRITE(V0) // open - close pump
{
    openPump = param.asInt();
    if (openPump == 1)
    {
        digitalWrite(PUMP, HIGH);
    }
    else
    {
        digitalWrite(PUMP, LOW);
    }
}

BLYNK_WRITE(V1) // change watering cycle
{
    wateringCycle = param.asInt(); 
    Serial.print("watering cycle: ");
    Serial.println(wateringCycle);
}

BLYNK_WRITE(V2) // read mode
{
    mode = param.asInt(); 
    Serial.print("mode: ");
    Serial.println(mode);
    bridge1.virtualWrite(V0, mode);
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
    // Change Web Link Button message to "Congratulations!"
    Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
    Blynk.setProperty(V3, "onImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
    Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
    bridge1.setAuthToken(BLYNK_AUTH_TOKEN_OLED);
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
    if (mode == 1) // auto mode
    {
        if (openPump == 1)
        {
            digitalWrite(PUMP, HIGH);
            delay(2000); // watering for 2 seconds
            digitalWrite(PUMP, LOW);
            openPump = 0;
        }
        else
        {
            delay(wateringCycle * 1000);
            openPump = 1;
        }
    }
    else
    {
        if (openPump == 1)
        {
            digitalWrite(PUMP, HIGH);
        }
        else
        {
            digitalWrite(PUMP, LOW);
        }
    }
}