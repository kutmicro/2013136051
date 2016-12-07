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
//Digital3 (SoftSerial TX) : VS1053 RX 
//SW시리얼핀 정의 D3이 MIDI신호 전송용,  D2는 미사용 
byte note = 0;      //The MIDI연주될 note(음계)
byte resetMIDI = 4; //VS1053 Reset용 핀(MIDI쉴드 제어용)
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
/*
  풀업 저항을 사용한다면 스위치가 열려 있을 때(Off) 칩에는 항상 5V의 전압이 가해진다. 
  따라서 회로에 입력을 몰라도 항상 5V의 전압을가진 상태가 된다. 
  스위치를 닫는다면(On) 그라운드 쪽으로 전류가 흐르게 되며 회로의 전압은 0V가 되며, 
  1을 입력한 것으로 인식하게 된다. 핀을 높은 저항에 매달아 둔다는 뜻에서 '풀 업 저항'이라 한다.
*/
  pinMode(trigPin, OUTPUT);   //trigPin을 출력으로 설정
  pinMode(echoPin, INPUT);    //echoPin을 입력으로 설정

  talkMIDI(0xc0, 25, 0);      //MIDI에서 25번 악기의 소리를 내라는 명령
}
void loop() {
  br1 = digitalRead(btn1);    //btn1의 입력값을 br1에 저장
  br2 = digitalRead(btn2);    //이하, 위와 유사
  br3 = digitalRead(btn3);
  br4 = digitalRead(btn4);

  lazVal1 = analogRead(laz1);   //read analog (0~1023까지의 값이 들어옴)
  lazVal2 = analogRead(laz2);   //read analog 
  lazVal3 = analogRead(laz3);   //read analog 
  lazVal4 = analogRead(laz4);   //read analog 

  digitalWrite(trigPin, HIGH);  //trigPin에 HIGH 신호를 줌
  delay(10);                    //trigPin이 신호를 보냈던 시간 0.01초
  digitalWrite(trigPin, LOW);   //trigPin에 LOW 신호를 줌

  duration = pulseIn(echoPin, HIGH);  //echoPin 이 HIGH를 유지한 시간을 저장 한다.
  distance = ((float)(340 * duration) / 10000) / 2;
  // HIGH 였을 때 시간(초음파가 보냈다가 다시 들어온 시간)을 가지고 거리를 계산 한다.
  // 340은 초당 초음파(소리)의 속도, 10000은 밀리세컨드를 세컨드로, 왕복거리이므로 2로 나눠준다.
  check = setNote1(br1) + setNote2(br2) + setNote3(br3) + setNote4(br4);
  // 버튼의 입력 유무에 따라 이진수 0부터 1111까지가 저장된다.
  if(lazVal1 > 100 || lazVal2 > 100 || lazVal3 > 100 || lazVal4 > 100) {
   // 4개의 조도센서에서 받은 빛의 밝기가 하나라도 100보다 클 때
    if(check==1000){              //check의 값에 따라 다른 소리를 낸다.
      noteOn(note, note60, setVelocity(distance));  //첫번째 파라미터 note = 어떤 MIDI채널을 연주할 것인지
      //두번째 파라미터 note60 = 실제 연주할 음, 세번째 파라미터 setVelocity(distance) = 거리에 따른 음의 세기
      Serial.println("도");      //noteOn()는 MIDI에 명령을 보내 소리를 내게 함, 호출 이후 50ms 의 딜레이가 존재
      delay(200);                 //0.2초 딜레이
      noteOff(note, note60, 0);   //MIDI에 명령을 보내 소리를 내지 않게 함
    }
    else if(check==100) {         //이하, 위와 같음
      noteOn(note, note62, setVelocity(distance));
      Serial.println("레");
      delay(200);
      noteOff(note, note62, 0);
    } 
    else if(check==10){
      noteOn(note, note64, setVelocity(distance));
      Serial.println("미");
      delay(200);
      noteOff(note, note64, 0);
    }
    else if(check==1){
      noteOn(note, note65, setVelocity(distance));
      Serial.println("파");
      delay(200);
      noteOff(note, note65, 0);
    }
    else if(check==11){
      noteOn(note, note67, setVelocity(distance));
      Serial.println("솔");
      delay(200);
      noteOff(note, note67, 0);
    }
    else if(check==111){
      noteOn(note, note69, setVelocity(distance));
      Serial.println("라");
      delay(200);
      noteOff(note, note69, 0);
    } 
    else if(check==1111){
      noteOn(note, note71, setVelocity(distance));
      Serial.println("시");
      delay(200);
      noteOff(note, note71,0);
    } 
    else if(check==1110){
      noteOn(note, note72, setVelocity(distance));
      Serial.println("높은도");
      delay(200);
      noteOff(note, note72, 0);
    }
    else if(check==1100){
      noteOn(note, note74, setVelocity(distance));
      Serial.println("높은레");
      delay(200);
      noteOff(note, note74, 0);
    }
    else if(check==1101){
      noteOn(note, note76, setVelocity(distance));
      Serial.println("높은미");
      delay(200);
      noteOff(note, note76, 0);
    }
    else if(check==1001){
      noteOn(note, note77, setVelocity(distance));
      Serial.println("높은파");
      delay(200);
      noteOff(note, note77, 0);
    }
    else if(check==1010){
      noteOn(note, note79, setVelocity(distance));
      Serial.println("높은솔");
      delay(200);
      noteOff(note, note79, 0);
    }
    else if(check==1011){
      noteOn(note, note81, setVelocity(distance));
      Serial.println("높은라");
      delay(200);
      noteOff(note, note81, 0);
    }
    else if(check==101){
      noteOn(note, note83, setVelocity(distance));
      Serial.println("높은시");
      delay(200);
      noteOff(note, note83, 0);
    }
    else if(check==110){
      noteOn(note, note84, setVelocity(distance));
      Serial.println("더높은도");
      delay(200);
      noteOff(note, note84, 0);
    }
    //버튼 입력이 없이 조도센서 하나만 레이저를 막았을 때의 경우 (default 음)
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
  if(Serial.available() > 0)    //available() 함수는 Serial 을 통해 수신한 데이터가 있을 때 true를 리턴.
  {
    byteData =  Serial.read();  //Serial에서 수신한 값을 1byte씩 읽어서 byteData에 저장
    mySerial.write(byteData);  //mySerial(MIDI)에 byteData를 출력
  }
  Serial.println(setVelocity(distance));    //음의 세기를 Serial Moniter에 출력
  delay(50);      //원활한 소리 재생을 위한 딜레이
}
int setVelocity(int distance) { //매개변수로 받은 distance로 음의 세기를 반환
  int vel;
  if(distance <= 18){           //초음파센서와 레이저가 있는 곳까지의 거리가 약 18cm
    vel = (int)((distance / 18.0 * 50) + 60);   //변환하여 vel에 저장
    if (vel >= 100) { //vel이 100보다 크면
     return 100;      //100 반환                      
    }
  }
  else                //18이 넘어가면
    return 100;       //100 반환
  return vel;         //vel 반환
}
int setNote1(boolean btn) { //btn1이 true 이면 1 반환
  if (btn == true)          
    return 1;
  else 
    return 0;
}
int setNote2(boolean btn) { //btn2이 true 이면 10 반환
  if (btn == true)
    return 10;
  else 
    return 0;
}
int setNote3(boolean btn) { //btn3이 true 이면 100 반환
  if (btn == true)
    return 100;
  else 
    return 0;
}
int setNote4(boolean btn) { //btn4이 true 이면 1000 반환
  if (btn == true)
    return 1000;
  else 
    return 0;
}
//노트 온 미디 메세지를 송출합니다. 
//채널 범위는 0-15 입니다.
void noteOn(byte channel, byte note, byte attack_velocity) {
  talkMIDI( (0x90 | channel), note, attack_velocity);
}
//노트 오프 미디 메세지를 송출합니다.
void noteOff(byte channel, byte note, byte release_velocity) {
  talkMIDI( (0x80 | channel), note, release_velocity);
}
//MIDI와 Arduino의 통신
void talkMIDI(byte cmd, byte data1, byte data2) {
  digitalWrite(ledPin, HIGH); //ledPin 켬
  mySerial.write(cmd);        //mySerial(MIDI)에 cmd를 출력
  mySerial.write(data1);      //mySerial에 data1를 출력

  if( (cmd & 0xF0) <= 0xB0) //cmd와 0xF0의 AND가 OxB0보다 작거나 같으면
    mySerial.write(data2);  //data2값을 mySerial에 출력

  digitalWrite(ledPin, LOW);  //ledPin 끔
}
