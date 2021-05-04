#include <Keypad.h>
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>

Servo servo; // 建立Servo物件，控制伺服馬達
#define RST_PIN      8  // 讀卡機的重置腳位
#define SS_PIN       9  // 晶片選擇腳位
#define SERVO_PIN    2   // 伺服馬達的控制訊號接腳
#define KEY_ROWS 4 // 按鍵模組的列數
#define KEY_COLS 4 // 按鍵模組的行數

bool lockerSwitch = false;  // 伺服馬達的狀態



struct RFIDTag {   // 定義結構
   byte uid[4];
   char *name;
};

struct RFIDTag tags[] = {  // 初始化結構資料，請自行修改RFID識別碼。
  {{99,31,111,12},"1"}
};


byte totalTags = sizeof(tags) / sizeof(RFIDTag);  // 計算結構資料筆數，結果為3。
MFRC522 mfrc522(SS_PIN, RST_PIN);  // 建立MFRC522物件

// 依照行、列排列的按鍵字元（二維陣列）
char keymap[KEY_ROWS][KEY_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte colPins[KEY_COLS] = {22,24,26,28};     // 按鍵模組，行1~4接腳。
byte rowPins[KEY_ROWS] = {30,32,34,36}; // 按鍵模組，列1~4接腳。 
Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, KEY_ROWS, KEY_COLS);// 初始化Keypad物件
int T;
int digitNumber[11] = 
{252,96,218,242,102,
182,190,224,254,246,0};

int latchPin = 44;
int clockPin = 29;
int dataPin = 23;
int d0=45;
int d1=46;
int d2=25;
int d3=27;

int numToShow = 0;

// 開鎖或關鎖
void locker(bool toggle) {
  if (toggle) {
      servo.write(90);  // 開鎖
  } else {
      servo.write(0);   // 關鎖
  }
  delay(15);    // 等伺服馬達轉到定位
}
void setup() {
  T = 0;
  Serial.begin(9600);
  Serial.println();
  Serial.print("size of RFIDTag:");
  Serial.println(sizeof(RFIDTag));
  Serial.print("size of tag:");
  Serial.println(sizeof(tags));
  Serial.println("RFID reader is ready!");
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(d0, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  Serial.begin(9600);

  SPI.begin();
  mfrc522.PCD_Init();       // 初始化MFRC522讀卡機模組
  servo.attach(SERVO_PIN);  // 將伺服馬達物件附加在數位2腳
  locker(lockerSwitch);

}

void loop() {
   // 透過Keypad物件的getKey()方法讀取按鍵的字元
    char key = myKeypad.getKey();
    Serial.println(key);

    if (key=='A'){  // 若有按鍵被按下…
    T=setTime();
    Serial.print("set time to ");
    Serial.println(T);
       show4Num(numToShow);

  if(Serial.available())
  {
    char c = Serial.read();
    if(c == '@')
    {
      numToShow = Serial.parseInt();
    }
  }

    
   // 確認是否有新卡片
    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
      byte *id = mfrc522.uid.uidByte;   // 取得卡片的UID
      byte idSize = mfrc522.uid.size;   // 取得UID的長度
      bool foundTag = false;    // 是否找到紀錄中的標籤，預設為「否」
      
      for (byte i=0; i<totalTags; i++) {
        if (memcmp(tags[i].uid, id, idSize) == 0) {  // 比對陣列資料值
          Serial.println(tags[i].name);  // 顯示標籤的名稱
          foundTag = true;  // 設定成「找到標籤了！」
          
          lockerSwitch = !lockerSwitch;  // 切換鎖的狀態
          locker(lockerSwitch);          // 開鎖或關鎖
          break;  // 退出for迴圈
        }
      }

      if (!foundTag) {  // 若掃描到紀錄之外的標籤，則顯示"Wrong card!"。
        Serial.println("Wrong card!");

        // 如果鎖是開啟狀態，則關閉它。
        if (lockerSwitch) {
          lockerSwitch = false;
          locker(lockerSwitch);
        }
      }

      mfrc522.PICC_HaltA();  // 讓卡片進入停止模式      
    } 
void showNum(int num, int digit) {
  if(num>=0 && num<=10)
  {
    for(int i=d0; i<=d3; i++)
    {
        digitalWrite(i,HIGH);
    }
    
    int numberToDisplay = digitNumber[num];
    byte low_Byte = lowByte(numberToDisplay);
      
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, low_Byte);  
    digitalWrite(latchPin, HIGH);

    digitalWrite(digit, LOW);
  }

}
int setTime()
{
  int t=0;
  int digis = 0;

  while(true)
  {
    char key = myKeypad.getKey();
    if(key)
    {
      if(key=='#')
        break;
      else if(key>='0' && key<='9' && digis<4)
      {
        t = t*10 + (key-'0');
        digis++;
        Serial.println(t);
      }
      else if(key=='*')
        t=0;
        digis=0;
     }
     if(Serial.read() == "" )
     {
      
     }
  } 
  return t;
}

//int digitNumber[11] = 
//{252,96,218,242,102,
//182,190,224,254,246,0};
//
//int latchPin = 3;
//int clockPin = 4;
//int dataPin = 2;
//int d0=5;
//int d1=6;
//int d2=7;
//int d3=8;
//
//void setup() {
//  pinMode(latchPin, OUTPUT);
//  pinMode(clockPin, OUTPUT);
//  pinMode(dataPin, OUTPUT);
//  pinMode(d0, OUTPUT);
//  pinMode(d1, OUTPUT);
//  pinMode(d2, OUTPUT);
//  pinMode(d3, OUTPUT);
//  Serial.begin(9600);
//}
//
//void loop() {
//  show4Num(1234);
//}
//void showNum(int num, int digit) {
//  if(num>=0 && num<=10)
//  {
//    for(int i=d0; i<=d3; i++)
//    {
//        digitalWrite(i,HIGH);
//    }
//    
//    int numberToDisplay = digitNumber[num];
//    byte low_Byte = lowByte(numberToDisplay);
//      
//    digitalWrite(latchPin, LOW);
//    shiftOut(dataPin, clockPin, MSBFIRST, low_Byte);  
//    digitalWrite(latchPin, HIGH);
//
//    digitalWrite(digit, LOW);
//  }
//}
//void show4Num(int num)
//{
//  if(num>=0 && num<=9999)
//  {
//    int d = num/1000;
//    showNum(d, d3);
//    num = num%1000;
//    delay(5);
//
//    d = num/100;
//    showNum(d, d2);
//    num = num%100;
//    delay(5);
//
//    d = num/10;
//    showNum(d, d1);
//    num = num%10;
//    delay(5);
//
//    d = num;
//    showNum(d, d0);
//    delay(5);
//  }
//}

