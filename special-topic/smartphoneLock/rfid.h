#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN      8  // 讀卡機的重置腳位
#define SS_PIN       9  // 晶片選擇腳位

struct RFIDTag {   // 定義結構
   byte uid[4];
   char *name;
};

struct RFIDTag tags[] = {  // 初始化結構資料，請自行修改RFID識別碼。
  {{99,31,111,12},"1"}
};

byte totalTags = sizeof(tags) / sizeof(RFIDTag);  // 計算結構資料筆數，結果為3。
MFRC522 mfrc522(SS_PIN, RST_PIN);  // 建立MFRC522物件

void setup() {
  
  Serial.begin(9600);
  Serial.print("size of RFIDTag:");
  Serial.println(sizeof(RFIDTag));
  Serial.print("size of tag:");
  Serial.println(sizeof(tags));
  Serial.println("RFID reader is ready!");

  SPI.begin();
  mfrc522.PCD_Init();       // 初始化MFRC522讀卡機模組
  
}
void loop() {
   

   // 確認是否有新卡片
    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
      byte *id = mfrc522.uid.uidByte;   // 取得卡片的UID
      byte idSize = mfrc522.uid.size;   // 取得UID的長度
      bool foundTag = false;    // 是否找到紀錄中的標籤，預設為「否」

      for (byte i=0; i<totalTags; i++) {
        if (memcmp(tags[i].uid, id, idSize) == 0) {  // 比對陣列資料值
          Serial.println(tags[i].name);  // 顯示標籤的名稱
          foundTag = true;  // 設定成「找到標籤了！」

          return 200;
        }
      }
