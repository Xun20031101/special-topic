#include <Keypad.h>
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Streaming.h>

//MFRC522
#define RST_PIN      8  // 讀卡機的重置腳位
#define SS_PIN       9  // 晶片選擇腳位
#define SERVO_PIN    2   // 伺服馬達的控制訊號接腳
#define KEY_ROWS 4 // 按鍵模組的列數
#define KEY_COLS 4 // 按鍵模組的行數

Servo myservo; // 建立Servo物件，控制伺服馬達
MFRC522 myrfid(SS_PIN, RST_PIN);  // 建立MFRC522物件
Keypad myKeypad;

bool lockerSwitch = false;  // 伺服馬達的狀態
