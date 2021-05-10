#include <Keypad.h>    // 引用Keypad程式庫

#define KEY_ROWS 4 // 按鍵模組的列數
#define KEY_COLS 4 // 按鍵模組的行數

// 依照行、列排列的按鍵字元（二維陣列）
char keymap[KEY_ROWS][KEY_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte colPins[KEY_COLS] = {22, 24, 26, 28};     // 按鍵模組，行1~4接腳。
byte rowPins[KEY_ROWS] = {30, 32, 34, 36}; // 按鍵模組，列1~4接腳。 

// 初始化Keypad物件
// 語法：Keypad(makeKeymap(按鍵字元的二維陣列), 模組列接腳, 模組行接腳, 模組列數, 模組行數)
Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, KEY_ROWS, KEY_COLS);

int T;

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
      {
        t=0;
        digis=0;
      }

     }
  }

  return t;
}
