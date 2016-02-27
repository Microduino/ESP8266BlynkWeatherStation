#include <ESP8266_HardSer.h>
#include <BlynkSimpleShieldEsp8266_HardSer.h>
#include <SimpleTimer.h>

// Set ESP8266 Serial object
#define EspSerial Serial1

ESP8266 wifi(EspSerial);

SimpleTimer temHumtimer;

void senTempHumi() {
  am2321.read();
  float sensor_tem = am2321.temperature / 10.0;
  float sensor_hum = am2321.humidity / 10.0;
  Blynk.virtualWrite(V2, sensor_tem);
  Blynk.virtualWrite(V3, sensor_hum);

  oled(sensor_tem, sensor_hum, sensor_light, sensorPM25, Sensor_etoh); 
}

BLYNK_READ(V4) {
  sensor_light = map(analogRead(A0), 0, 1023, 0, 255);
  Blynk.virtualWrite(V4, sensor_light);
}
BLYNK_READ(V5) {
  Sensor_etoh= map(analogRead(A2), 0, 1023, 0, 30);
  Blynk.virtualWrite(V5, Sensor_etoh);
  //BLYNK_PRINT.println(Sensor_etoh);
}

BLYNK_READ(V6) {
  Blynk.virtualWrite(V6, sensorPM25);
  //BLYNK_PRINT.println(sensorPM25);
}