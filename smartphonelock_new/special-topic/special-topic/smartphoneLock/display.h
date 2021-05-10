int digitNumber[11] = 
{3,159,37,13,153,
73,65,31,1,9,255};

int latchPin = 3;
int clockPin = 4;
int dataPin = 2;
int d0=8;
int d1=7;
int d2=6;
int d3=5;


void showNum(int num, int digit) {
  if(num>=0 && num<=10)
  {
    for(int i=d0; i<=d3; i++)
    {
        digitalWrite(i,LOW);
    }
    
    int numberToDisplay = digitNumber[num];
    byte low_Byte = lowByte(numberToDisplay);
      
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, low_Byte);  
    digitalWrite(latchPin, HIGH);

    digitalWrite(digit, HIGH);
  }
}
void show4Num(int num)
{
  if(num>=0 && num<=9999)
  {
    int d = num/1000;
    showNum(d, d3);
    num = num%1000;
    delay(5);

    d = num/100;
    showNum(d, d2);
    num = num%100;
    delay(5);

    d = num/10;
    showNum(d, d1);
    num = num%10;
    delay(5);

    d = num;
    showNum(d, d0);
    delay(5);
  }
}
