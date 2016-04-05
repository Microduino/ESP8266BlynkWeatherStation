#include <SoftwareSerial.h>
#include <AM2321.h>

#define INTERVAL_pm25             200 
unsigned long pm25_time = millis();

SoftwareSerial pmSerial(4,5);   //PM2.5传感器通讯软串口

AM2321 am2321;

float sensor_tem,sensor_hum,sensor_light,
Sensor_etoh;

float sensorPM25;


float PM25() {
  int data_s = 0;    //串口接收数据
  int num = -1;      //串口接收数据计数
  int sum = 0;       //校验和
  int cal[5];        //接收数据缓存
  float dustDensity = 0;  //PM2.5浓度
  
  pmSerial.begin(2400);   //首先启动软串口
  pmSerial.flush();       //清空串口缓存
  
  while(1) { 
    if(pmSerial.available() > 0) { //串口缓存有数据
      data_s = pmSerial.read();   //读取串口缓存数据
      if(data_s == 0xAA) {         //得到数据帧起始位
        num = 0;                  //开始计数
      }
      else if(num >= 0) {    
        num++;                //读到数据，计数+1
        cal[num-1] = data_s;  //数据保存到缓存中
        if(num == 6) {         //读到数据帧最后一位
          sum = cal[0] + cal[1] + cal[2] + cal[3];  //计算校验和
          if(sum == cal[4] && cal[5] == 0xFF) {     //校验和匹配，数据帧最后一位为0xFF，说明接收的数据帧正常
            dustDensity = (cal[0]*256 + cal[1])*(5.0/1024)*550;   //计算PM2.5浓度，单位ug/m3
          }
          else {     //接收的数据不正常
            dustDensity = 0;    //浓度清零
          }
          break;
        }
      }
    }   
  }
  pmSerial.end();     //关闭软串口
  return dustDensity; //返回值
}


void updateLight() {
  sensor_light = map(analogRead(A0), 0, 1023, 0, 255);
}

void updateCH4() {
  Sensor_etoh= map(analogRead(A2), 0, 1023, 0, 30);
}

void updateTempHumi() {
  am2321.read();
  sensor_tem = am2321.temperature / 10.0;
  sensor_hum = am2321.humidity / 10.0;
}