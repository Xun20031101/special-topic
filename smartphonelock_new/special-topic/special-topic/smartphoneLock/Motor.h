#include <Servo.h>
#define SERVO_PIN    2   // 伺服馬達的控制訊號接腳

Servo servo; // 建立Servo物件，控制伺服馬達
bool lockerSwitch = false;  // 伺服馬達的狀態

// 開鎖或關鎖
void locker(bool toggle)
{
  servo.attach(SERVO_PIN);  // 將伺服馬達物件附加在數位2腳
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
