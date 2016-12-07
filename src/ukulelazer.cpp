#include <SoftwareSerial.h>
#define btn1  11  //버튼1의 아두이노 핀번호 정의
#define btn2  10  //버튼2의 아두이노 핀번호 정의
#define btn3  9   //버튼3의 아두이노 핀번호 정의
#define btn4  8   //버튼4의 아두이노 핀번호 정의
// 3:midi rx , 4:midi reset  아두이노 핀 3번 4번은 이미 사용중
#define laz1 A0   //조도센서1의 아두이노 핀번호 정의
#define laz2 A1   //조도센서2의 아두이노 핀번호 정의
#define laz3 A2   //조도센서3의 아두이노 핀번호 정의
#define laz4 A3   //조도센서4의 아두이노 핀번호 정의
#define trigPin 7 //출력핀의 아두이노 핀번호 정의
#define echoPin 6 //입력핀의 아두이노 핀번호 정의
SoftwareSerial mySerial(2, 3); 
//SW시리얼핀 정의 D3이 MIDI신호 전송용,  D2는 미사용 
byte note = 0;      //The MIDI연주될 note(음계)
byte resetMIDI = 4; //VS1053 Reset용 핀
byte ledPin = 13;   //MIDI 트래픽 표시용 LED

boolean br1;    //버튼1 상태 확인용 입력값 임시저장용
boolean br2;    //이하, 위와 유사
boolean br3;
boolean br4;

int lazVal1 = 0;  //조도센서1 에서 받은 AnalogRead 값
int lazVal2 = 0;  //이하, 위와 유사  
int lazVal3 = 0;  
int lazVal4 = 0;  
float duration;   //echoPin이 HIGH를 유지한 시간을 저장
float distance;   //거리 계산
int check = 0;    //버튼 입력에 따른 정수값 저장할 변수
//0~127까지 지정가능 (정확한 음계 설정은 MIDI관련정보참고)
int note52 = 52; //note(음계) "낮은미"
int note53 = 53; //note(음계) "낮은파"
int note55 = 55; //note(음계) "낮은솔"
int note57 = 57; //note(음계) "낮은라"
int note59 = 59; //note(음계) "낮은시"
int note60 = 60; //note(음계) "도"
int note62 = 62; //note(음계) "레"
int note64 = 64; //note(음계) "미"
int note65 = 65; //note(음계) "파"
int note67 = 67; //note(음계) "솔"
int note69 = 69; //note(음계) "라"
int note71 = 71; //note(음계) "시"
int note72 = 72; //note(음계) "높은도"
int note74 = 74; //note(음계) "높은레"
int note76 = 76; //note(음계) "높은미"
int note77 = 77; //note(음계) "높은파"
int note79 = 79; //note(음계) "높은솔"
int note81 = 81; //note(음계) "높은라"
int note83 = 83; //note(음계) "높은시"
int note84 = 84; //note(음계) "더높은도"

byte byteData;  
void setup() {
  Serial.begin(31250);
  //미디컨트롤을 위한 소프트웨어 시리얼을 준비합니다.
  mySerial.begin(31250);
  //VS1053를 초기화하고 사용할 준비를 합니다.
  pinMode(resetMIDI, OUTPUT);   
  digitalWrite(resetMIDI, LOW);
  delay(100);
  digitalWrite(resetMIDI, HIGH);
  delay(100);
  
  pinMode( btn1, INPUT);      // 버튼1 입력용 핀모드를  입력모드로 전환
  digitalWrite( btn1, HIGH);  // 내부 PullUp 설정, 스위치의 나머지 한선은 GND에 물리면 됩니다.(초간단)
  pinMode( btn2, INPUT);      // 이하, 위와 유사
  digitalWrite( btn2, HIGH);
  pinMode( btn3, INPUT);
  digitalWrite( btn3, HIGH);
  pinMode( btn4, INPUT);
  digitalWrite( btn4, HIGH);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //talkMIDI(0xB0, 3, 0x78);
  talkMIDI(0xc0, 25, 0);        //악기 설정
}
void loop() {
  br1 = digitalRead(btn1);
  br2 = digitalRead(btn2);
  br3 = digitalRead(btn3);
  br4 = digitalRead(btn4);

  lazVal1 = analogRead(laz1); //read analog 
  lazVal2 = analogRead(laz2); //read analog 
  lazVal3 = analogRead(laz3); //read analog 
  lazVal4 = analogRead(laz4); //read analog 

  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = ((float)(340 * duration) / 10000) / 2;
  
  check = setNote1(br1) + setNote2(br2) + setNote3(br3) + setNote4(br4);
  
  if(lazVal1 > 100 || lazVal2 > 100 || lazVal3 > 100 || lazVal4 > 100) {
    if(check==1000){
      noteOn(note, note60, 100);
      Serial.println("도");
      delay(200);
      noteOff(note, note60, 0);
    }
    else if(check==100){
      noteOn(note, note62,100);
      Serial.println("레");
      delay(200);
      noteOff(note, note62,0);
    } 
    else if(check==10){
      noteOn(note, note64,100);
      Serial.println("미");
      delay(200);
      noteOff(note, note64,0);
    }
    else if(check==1){
      noteOn(note, note65,100);
      Serial.println("파");
      delay(200);
      noteOff(note, note65,0);
    }
    else if(check==11){
      noteOn(note, note67,100);
      Serial.println("솔");
      delay(200);
      noteOff(note, note67,0);
    }
    else if(check==111){
      noteOn(note, note69,100);
      Serial.println("라");
      delay(200);
      noteOff(note, note69,0);
    } 
    else if(check==1111){
      noteOn(note, note71,100);
      Serial.println("시");
      delay(200);
      noteOff(note, note71,0);
    } 
    else if(check==1110){
      noteOn(note, note72, 100);
      Serial.println("높은도");
      delay(200);
      noteOff(note, note72, 0);
    }
    else if(check==1100){
      noteOn(note, note74, 100);
      Serial.println("높은레");
      delay(200);
      noteOff(note, note74,0);
    }
    else if(check==1101){
      noteOn(note, note76, 100);
      Serial.println("높은미");
      delay(200);
      noteOff(note, note76, 0);
    }
    else if(check==1001){
      noteOn(note, note77, 100);
      Serial.println("높은파");
      delay(200);
      noteOff(note, note77,0);
    }
    else if(check==1010){
      noteOn(note, note79, 100);
      Serial.println("높은솔");
      delay(200);
      noteOff(note, note79,0);
    }
    else if(check==1011){
      noteOn(note, note81, 100);
      Serial.println("높은라");
      delay(200);
      noteOff(note, note81, 0);
    }
    else if(check==101){
      noteOn(note, note83, 100);
      Serial.println("높은시");
      delay(200);
      noteOff(note, note83,0);
    }
    else if(check==110){
      noteOn(note, note84, 100);
      Serial.println("더높은도");
      delay(200);
      noteOff(note, note84, 0);
    }
    else if(check==0 && lazVal4 > 100 && lazVal3 < 100 && lazVal2 < 100 && lazVal1 < 100){ 
      noteOn(note, note59, setVelocity(distance));
      Serial.println("낮은시");
      delay(200);
      noteOff(0, 59, 0);
    } else if(check==0 && lazVal4 < 100 && lazVal3 > 100 && lazVal2 < 100 && lazVal1 < 100){ 
      noteOn(note, note57, setVelocity(distance));
      Serial.println("낮은라");
      delay(200);
      noteOff(note, note57, 0);
    } else if(check==0 && lazVal4 < 100 && lazVal3 < 100 && lazVal2 > 100 && lazVal1 < 100){ 
      noteOn(note, note55, setVelocity(distance));
      Serial.println("낮은솔");
      delay(200);
      noteOff(note, note55, 0);
    } else if(check==0 && lazVal4 < 100 && lazVal3 < 100 && lazVal2 < 100 && lazVal1 > 100){ 
      noteOn(note, note53, setVelocity(distance));
      Serial.println("낮은파");
      delay(200);
      noteOff(note, note53, 0);
    } else { 
      noteOn(note, note52, setVelocity(distance));
      Serial.println("낮은미");
      delay(200);
      noteOff(note, note52, 0);
    }
  }
  if(Serial.available() > 0)
  {
    byteData =  Serial.read();
    mySerial.write( byteData );
  }
  Serial.println(setVelocity(distance));  
  delay(50);
}
int setVelocity(int distance) {
  int vel;
  if(distance <= 18){
    vel = (int)((distance / 18.0 * 50) + 60);
    if (vel >= 100) {
     return 100;
    }
  }
  else
    return 100;
  return vel; 
}
int setNote1(boolean bnt) {
  if (bnt == true)
    return 1;
  else 
    return 0;
}
int setNote2(boolean bnt) {
  if (bnt == true)
    return 10;
  else 
    return 0;
}
int setNote3(boolean bnt) {
  if (bnt == true)
    return 100;
  else 
    return 0;
}
int setNote4( boolean bnt) {
  if (bnt == true)
    return 1000;
  else 
    return 0;
}
//노트 온 미디 메세지를 송출합니다. 버튼이 눌린상태와 같습니다.
//채널 범위는 0-15 입니다.
void noteOn(byte channel, byte note, byte attack_velocity) {
  talkMIDI( (0x90 | channel), note, attack_velocity);
}
//노트 오프 미디 메세지를 송출합니다. 버튼이 눌리지 않은 상태와 같습니다.
void noteOff(byte channel, byte note, byte release_velocity) {
  talkMIDI( (0x80 | channel), note, release_velocity);
}
void talkMIDI(byte cmd, byte data1, byte data2) {
  digitalWrite(ledPin, HIGH);
  mySerial.write(cmd );
  mySerial.write(data1 );

  if( (cmd & 0xF0) <= 0xB0)
    mySerial.write(data2 );

  digitalWrite(ledPin, LOW);
}
