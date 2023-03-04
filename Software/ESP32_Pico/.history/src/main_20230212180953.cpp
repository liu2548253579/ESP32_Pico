// /*
//  * @Author: Frank 2548253579@qq.com
//  * @Date: 2023-02-11 13:47:17
//  * @LastEditors: Frank 2548253579@qq.com
//  * @LastEditTime: 2023-02-12 18:00:02
//  * @FilePath: \ESP32_Pico\src\main.cpp
//  * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
//  */
// #include <Arduino.h>
// #include <HCSR04.h>

// UltraSonicDistanceSensor distanceSensor(2, 4);  // Initialize sensor that uses digital pins 13 and 12.
// float distance;


// void setup () {
// Serial.begin(115200);  // We initialize serial connection so that we could print values from sensor.
// analogSetWidth(12);
// pinMode(22,OUTPUT);
// pinMode(13,OUTPUT);
// }

// void loop () {
//     // Every 500 miliseconds, do a measurement using the sensor and print the distance in centimeters.
//     distance=distanceSensor.measureDistanceCm();
//     Serial.println(distance);
//     if(distance<=9){  digitalWrite(13,HIGH);}
//     else{digitalWrite(13,LOW);}

//     analogWrite(22,2048);
//     delay(100);
// }
// the number of the LED pin
#include <Arduino.h>
 
int freq = 50;      // 频率(20ms周期)
int channel = 8;    // 通道(高速通道（0 ~ 7）由80MHz时钟驱动，低速通道（8 ~ 15）由 1MHz 时钟驱动。)
int resolution = 8; // 分辨率
const int led = 16;
 
int calculatePWM(int degree)
{ //0-180度
 //20ms周期，高电平0.5-2.5ms，对应0-180度角度
  const float deadZone = 6.4;//对应0.5ms（0.5ms/(20ms/256）) 舵机转动角度与占空比的关系：(角度/90+0.5)*1023/20
  const float max = 32;//对应2.5ms
  if (degree < 0)
    degree = 0;
  if (degree > 180)
    degree = 180;
  return (int)(((max - deadZone) / 180) * degree + deadZone);
}
 
void setup()
{
  Serial.begin(115200);
  ledcSetup(channel, freq, resolution); // 设置通道
  ledcAttachPin(led, channel);          // 将通道与对应的引脚连接
}
 
void loop()
{
  for (int d = 0; d <= 180; d += 10)
  {
    ledcWrite(channel, calculatePWM(d)); // 输出PWM
    Serial.printf("value=%d,calcu=%d\n", d, calculatePWM(d));
    delay(1000);
  }  
}