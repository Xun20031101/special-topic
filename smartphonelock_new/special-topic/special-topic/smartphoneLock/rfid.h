#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN      A0  // 讀卡機的重置腳位
#define SS_PIN       10  // 晶片選擇腳位

char tag[5]="open";
 
struct RFIDTag {   // 定義結構
   byte uid[4];
   char *name;
};

struct RFIDTag tags[] = {  // 初始化結構資料，請自行修改RFID識別碼。
  {{99,31,111,12},tag}
};

byte totalTags = sizeof(tags) / sizeof(RFIDTag);  // 計算結構資料筆數，結果為3。
MFRC522 mfrc522(SS_PIN, RST_PIN);  // 建立MFRC522物件
