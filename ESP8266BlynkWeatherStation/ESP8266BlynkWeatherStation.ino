#define BLYNK_PRINT Serial // Enables Serial Monitor

#include "userDef.h"
#include "sensor.h"
#include "oled.h"
#include "WiFiBlynk.h"

void setup() {
  Serial.begin(9600); // See the connection status in Serial Monitor
  // Set ESP8266 baud rate
  EspSerial.begin(115200);
  
  Blynk.begin(auth, wifi, SSID, PASS);

  // Setup a function to be called every second
  temHumtimer.setInterval(2000L, senTempHumi);

  delay(10);
}


void loop() {
  Blynk.run(); // All the Blynk Magic happens here...
  temHumtimer.run(); // Initiates SimpleTimer

  updateTempHumi();
  updateLight();
  updateCH4();

  if (pm25_time > millis()) pm25_time = millis();
  if (millis() - pm25_time > INTERVAL_pm25) {   
    sensorPM25=PM25();
    pm25_time = millis();    //更新计时器
  }

  oled(sensor_tem, sensor_hum, sensor_light, sensorPM25, Sensor_etoh); 

}



