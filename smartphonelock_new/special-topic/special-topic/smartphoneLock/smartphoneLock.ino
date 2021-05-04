#include "display.h"
#include "Motor.h"
#include "rfid.h"
#include "settime.h"

void setup() {
  T = 0;
  Serial.begin(9600);
  Serial.print("size of RFIDTag:");
  Serial.println(sizeof(RFIDTag));
  Serial.print("size of tag:");
  Serial.println(sizeof(tags));
  Serial.println("RFID reader is ready!");
  SPI.begin();
  mfrc522.PCD_Init();       // 初始化MFRC522讀卡機模組
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(d0, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
}

void loop() {
  // 透過Keypad物件的getKey()方法讀取按鍵的字元
  char key = myKeypad.getKey();

  if (key=='A')
  {  // 若有按鍵被按下…
    T=setTime();
    Serial.print("set time to ");
    Serial.println(T);
  }
  int show4Num(1234);
  // 確認是否有新卡片
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) 
  {
    byte *id = mfrc522.uid.uidByte;   // 取得卡片的UID
    byte idSize = mfrc522.uid.size;   // 取得UID的長度
    bool foundTag = false;    // 是否找到紀錄中的標籤，預設為「否」
  
    for (byte i=0; i<totalTags; i++) 
    {
      if (memcmp(tags[i].uid, id, idSize) == 0) 
      {  // 比對陣列資料值
        Serial.println(tags[i].name);  // 顯示標籤的名稱
        foundTag = true;  // 設定成「找到標籤了！」

        lockerSwitch = !lockerSwitch;  // 切換鎖的狀態
        locker(lockerSwitch);          // 開鎖或關鎖
        break;  // 退出for迴圈
      }
     }
  }
}
