#include <Servo.h>
#define SERVO_PIN    9  // 伺服馬達的控制訊號接腳

Servo servo;
bool lockerSwitch = false;  // 伺服馬達的狀態

// 開鎖或關鎖
void locker(bool toggle)
{
  servo.attach(SERVO_PIN);  // 
  if (toggle)
  {
      servo.write(90);  // 開鎖
  }
  else
  {
      servo.write(0);   // 關鎖
  }
  delay(15);    // 等伺服馬達轉到定位
}
