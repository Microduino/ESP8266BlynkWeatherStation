#include <ESP8266_HardSer.h>
#include <BlynkSimpleShieldEsp8266_HardSer.h>
#include <SimpleTimer.h>

// Set ESP8266 Serial object
#define EspSerial Serial1

ESP8266 wifi(EspSerial);

SimpleTimer temHumtimer;

void senTempHumi() {
  Blynk.virtualWrite(V2, sensor_tem);
  Blynk.virtualWrite(V3, sensor_hum); 
}

BLYNK_READ(V4) {
  Blynk.virtualWrite(V4, sensor_light);
}
BLYNK_READ(V5) {
  Blynk.virtualWrite(V5, Sensor_etoh);
  //BLYNK_PRINT.println(Sensor_etoh);
}

BLYNK_READ(V6) {
  Blynk.virtualWrite(V6, sensorPM25);
  //BLYNK_PRINT.println(sensorPM25);
}