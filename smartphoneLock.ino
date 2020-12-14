#include <Keypad.h>    // 引用Keypad程式庫
#include <Servo.h>
#include <SPI.h>
#include <RFID.h>

Servo myservo; // 建立Servo物件，控制伺服馬達



#define KEY_ROWS 4 // 按鍵模組的列數
#define KEY_COLS 4 // 按鍵模組的行數
#define SDA_DIO 9
#define RESET_DIO 8
RFID RC522(SDA_DIO, RESET_DIO); 

// 依照行、列排列的按鍵字元（二維陣列）
char keymap[KEY_ROWS][KEY_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte colPins[KEY_COLS] = {22,24,26,28};     // 按鍵模組，行1~4接腳。
byte rowPins[KEY_ROWS] = {30,32,34,36}; // 按鍵模組，列1~4接腳。 

// 初始化Keypad物件
// 語法：Keypad(makeKeymap(按鍵字元的二維陣列), 模組列接腳, 模組行接腳, 模組列數, 模組行數)
Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, KEY_ROWS, KEY_COLS);

int T;

void setup(){
  T = 0;
  Serial.begin(9600);
  myservo.attach(2); // 連接數位腳位2，伺服馬達的訊號線
  SPI.begin();
  RC522.init();
  Serial.println("RFID reader is ready!");
}
  
void loop(){
  // 透過Keypad物件的getKey()方法讀取按鍵的字元
  char key = myKeypad.getKey();
  Serial.println(key);

  if (key=='A'){  // 若有按鍵被按下…
    T=setTime();
    Serial.print("set time to ");
    Serial.println(T);
    myservo.write(180);
    delay(30);
  }
    

    if (RC522.isCard())
  {
    
    /* If so then get its serial number */
      RC522.readCardSerial();
      Serial.println("Card detected:");
      for(int i=0;i<5;i++)
      {
      Serial.print(RC522.serNum[i],DEC);
      Serial.print(RC522.serNum[i],HEX); //to print card detail in Hexa Decimal format
      }
      Serial.println();
      Serial.println();
  }
  delay(1000);
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
     if(Serial.read() == "99311111231" )
     {
      
     }
  }
  
  return t;
}



//
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
//int numToShow = 0; // 要顯示的數值
//
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
//void loop() {
//  show4Num(numToShow);
//
//  if(Serial.available())
//  {
//    char c = Serial.read();
//    if(c == '@')
//    {
//      numToShow = Serial.parseInt();
//    }
//  }
//}
//
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

// 
//
// 
//
// 
