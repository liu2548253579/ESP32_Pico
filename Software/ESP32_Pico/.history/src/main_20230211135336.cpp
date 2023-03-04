/*
 * @Author: Frank 2548253579@qq.com
 * @Date: 2023-02-11 13:47:17
 * @LastEditors: Frank 2548253579@qq.com
 * @LastEditTime: 2023-02-11 13:53:17
 * @FilePath: \ESP32_Pico\src\main.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <Arduino.h>
#include <HCSR04.h>

UltraSonicDistanceSensor distanceSensor(2, 4);  // Initialize sensor that uses digital pins 13 and 12.
int distance;


void setup () {
    Serial.begin(115200);  // We initialize serial connection so that we could print values from sensor.
pinMode(13,OUTPUT);
}

void loop () {
    // Every 500 miliseconds, do a measurement using the sensor and print the distance in centimeters.
    distance=distanceSensor.measureDistanceCm();
    Serial.println(distance);
    if(distance<=9){  digitalWrite(13,HIGH);}
    else{digitalWrite(13,LOW);}
    delay(100);
}
