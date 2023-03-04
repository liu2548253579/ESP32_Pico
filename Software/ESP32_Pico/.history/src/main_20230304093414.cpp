#include <Arduino.h>
#include <HCSR04.h>

UltraSonicDistanceSensor distanceSensor(2, 4);  // Initialize sensor that uses digital pins 13 and 12.
float distance;//采集的距离
bool open_flag;//开合标志位
int time_open;//打开的持续时间

int channel = 8;    // 通道(高速通道（0 ~ 7）由80MHz时钟驱动，低速通道（8 ~ 15）由 1MHz 时钟驱动。)
const int led = 15;

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

void servo_open (int speed)
{
  for (int d = 0; d <= 180; d += 10)
  {
    ledcWrite(channel, calculatePWM(d)); // 输出PWM
    Serial.printf("Opening: value=%d,calcu=%d\r\n", d, calculatePWM(d));
    delay(speed);
  } 
}

void servo_close (int speed)
{
  for (int d = 0; d <= 180; d += 10)
  {
    ledcWrite(channel, calculatePWM(d)); // 输出PWM
    Serial.printf("Closing: value=%d,calcu=%d\r\n", d, calculatePWM(d));
    delay(speed);
  } 
}

void detect_distance (void *pt)
{
while(1)
{
    // Every 200 miliseconds, do a measurement using the sensor and print the distance in centimeters.
    distance=distanceSensor.measureDistanceCm();
    if(distance==-1){distance=999;}
    Serial.printf("Current distance%.2f\r\n",distance);
    vTaskDelay(100);
}

}


void task_center (void *pt)
{

while(1)
{
  if(distance<=10){open_flag=1;servo_open(1);}
  if(open_flag){time_open++;if(time_open==500){time_open=0;open_flag=0;}}
  if(!open_flag)


    vTaskDelay(10);
}
}



void setup()
{
  Serial.begin(115200);
  ledcSetup(channel, 50, 8); // 设置通道 50hz频率 8bit分辨率
  ledcAttachPin(led, channel);          // 将通道与对应的引脚连接
  pinMode(13,OUTPUT);
  xTaskCreate(detect_distance,"detect_distance",4096,NULL,1,NULL);
  xTaskCreate(task_center,"task_center",4096,NULL,2,NULL);
}
 
void loop()
{
// servo_open(1);
// servo_close(1);
}