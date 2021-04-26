#include <Keypad.h>
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Streaming.h>

#define RST_PIN      8  // 讀卡機的重置腳位
#define SS_PIN       9  // 晶片選擇腳位
#define SERVO_PIN    2   // 伺服馬達的控制訊號接腳
#define KEY_ROWS 4 // 按鍵模組的列數
#define KEY_COLS 4 // 按鍵模組的行數

Servo myservo; // 建立Servo物件，控制伺服馬達
bool lockerSwih = false;  // 伺服馬達的狀態

char keymap[KEY_ROWS][KEY_COLS] = 
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte colPins[KEY_COLS] = {22,24,26,28}; // 按鍵模組，行1~4接腳。
byte rowPins[KEY_ROWS] = {30,32,34,36}; // 按鍵模組，列1~4接腳。 
Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, KEY_ROWS, KEY_COLS);// 初始化Keypad物件


//===================================================================================

int digitNumber[11] = 
{
  252,96,218,242,102,
182,190,224,254,246,0
};

struct RFIDTag // 定義結構
{   
   byte uid[4];
   char *name;
};

struct RFIDTag tags[] = // 初始化結構資料
{ 
  {{99,31,111,12},"Openno Cardo"}
};

byte totalTags = sizeof(tags) / sizeof(RFIDTag);  // 計算結構資料筆數，結果為3。
MFRC522 myrfid(SS_PIN, RST_PIN);  // 建立MFRC522物件


int latchPin = 44;
int clockPin = 29;
int dataPin = 23;
int d0=45;
int d1=46;
int d2=25;
int d3=27;

int T;

int numToShow = 0;


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
