// This section defines pin assignmnet
#define SFTdata 9
#define SFTreset 8
#define SFTclk 7
#define SFTlatch 6
#define SFTouten 5
#define btn1 A0
#define btn2 A1
#define com A2
// This section defines numbers
#define one    B00000110
#define invone B11111001
#define two    B01011011
#define three  B01001111
#define four   B01100111

void shiftLCD(byte digit1, byte digit2);  //Shift out digits

void displaynum();  // Clock latch one cycle and enable output

void SftclkCyc();  // Shift register clock one cycle
bool outputlevel = false;

int main(){
  pinMode(SFTdata,OUTPUT);
  pinMode(SFTreset,OUTPUT);
  pinMode(SFTclk,OUTPUT);
  pinMode(SFTlatch,OUTPUT);
  pinMode(SFTouten,OUTPUT);
  pinMode(com, OUTPUT);
  pinMode(btn1,INPUT);
  pinMode(btn2,INPUT);
  pinMode(10,OUTPUT);

  digitalWrite(SFTreset,LOW);
  digitalWrite(SFTreset,HIGH);
  digitalWrite(SFTouten,HIGH);
  digitalWrite(SFTclk, LOW);
  digitalWrite(SFTdata,HIGH);
  digitalWrite(com, LOW);


  
  digitalWrite(10,HIGH);
  _delay_ms(500);
  digitalWrite(10,LOW);

  shiftOut(SFTdata,SFTclk,MSBFIRST,two);
  shiftOut(SFTdata,SFTclk,MSBFIRST,two);
//  displaynum();
//  _delay_ms(1000);
//  digitalWrite(com,HIGH);
//  shiftOut(SFTdata,SFTclk,MSBFIRST,~one);
  displaynum();
}

void shiftLCD(byte digit1, byte digit2){
  for(int i = 7; i > -1 ; i --){
    outputlevel = (digit2 & ( 1 << i )) >> i;
    digitalWrite(SFTdata,outputlevel);
    SftClkCyc();
  }
  displaynum();
  _delay_ms(500);
  for(int i = 7; i > -1 ; i --){
    outputlevel = (digit1 & ( 1 << i )) >> i;
    digitalWrite(SFTdata,outputlevel);
    SftClkCyc();
  }
  displaynum();
}

void displaynum(){
    digitalWrite(SFTlatch,LOW);
    _delay_ms(1);
    digitalWrite(SFTlatch,HIGH);
    _delay_ms(1);
    digitalWrite(SFTouten,LOW);
}

void stopdisplay(){
  digitalWrite(SFTouten,HIGH);
}

void SftClkCyc(){
  digitalWrite(SFTclk, HIGH);
  _delay_ms(1);
  digitalWrite(SFTclk,LOW);
  _delay_ms(1);
}

