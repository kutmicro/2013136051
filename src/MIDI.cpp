#include <SoftwareSerial.h>
#define btn1  11  // 버튼1의 아두이노 핀번호 정의
#define btn2  10  // 버튼2의 아두이노 핀번호 정의
#define btn3  9   // 버튼3의 아두이노 핀번호 정의
#define btn4  8   // 버튼4의 아두이노 핀번호 정의
// 3:midi rx , 4:midi reset  아두이노 핀 3번 4번은 이미 사용중

SoftwareSerial mySerial(2, 3); //SW시리얼핀 정의 D3이 MIDI신호 전송용,  D2는 미사용 

byte note = 0; //The MIDI연주될 note(음계)
byte resetMIDI = 4; // VS1053 Reset용 핀
byte ledPin = 13; //MIDI 트래픽 표시용 LED
 
boolean bs1 = false;  // 버튼1의 현재상태(눌림 or 안눌림)
boolean bs2 = false;  // 이하, 위와 유사
boolean bs3 = false;
boolean bs4 = false;

boolean br1;  // 버튼1 상태 확인용 입력값 임시저장용
boolean br2;  // 이하, 위와 유사
boolean br3;
boolean br4;
int check = 0;
int patch = 0; //악기 대응, 연주될 악기 종류 (0~127: 기본 128 가지 선택가능)

int bn1 = 60; //버튼1의  note(음계)  가령 "도"  0~127까지 지정가능 (정확한 음계 설정은 MIDI관련정보참고)
int bn2 = 62; //버튼2의  note(음계)  가령 "레"
int bn3 = 64; //버튼3의  note(음계)  가령 "미"
int bn4 = 65; //버튼4의  note(음계)  가령 "파"
int bn5 = 67; //버튼4의  note(음계)  가령 "파"
int bn6 = 69; //버튼4의  note(음계)  가령 "파"
int bn7 = 71; //버튼4의  note(음계)  가령 "파"

byte byteData;
 int setNote1(boolean ls1){
    if (ls1 == true)
      return 1;
   else 
   return 0;
  }
  int setNote2(boolean ls2){
    if (ls2 == true)
      return 10;
   else 
   return 0;
  }
  int setNote3(boolean ls3){
    if (ls3 == true)
      return 100;
   else 
   return 0;
  }
  int setNote4( boolean ls4){
    if (ls4 == true)
      return 1000;
   else 
   return 0;
  }
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
}

void loop() {
    br1 = digitalRead(btn1);
    br2 = digitalRead(btn2);
    br3 = digitalRead(btn3);
    br4 = digitalRead(btn4);

    check = setNote1(br1) + setNote2(br2) + setNote3(br3) + setNote4(br4);
   if(check==1000){
     noteOn(0, bn1,100);
     Serial.println("1");
     delay(500);
     noteOff(0, bn1,0);
   }
   else if(check==111){
     noteOn(0, bn2,100);
     Serial.println("2");
     delay(500);
     noteOff(0, bn2,0);
   } 
   else if(check==100){
     noteOn(0, bn3,100);
     Serial.println("3");
     delay(500);
     noteOff(0, bn3,0);
   }
   else if(check==101){
     noteOn(0, bn4,100);
     Serial.println("4");
     delay(500);
     noteOff(0, bn4,0);
   }else if(check==1110){
     noteOn(0, bn5,100);
     Serial.println("5");
     delay(500);
     noteOff(0, bn5,0);
   }else if(check==11){
     noteOn(0, bn6,100);
     Serial.println("6");
     delay(500);
     noteOff(0, bn6,0);
   }else if(check==1111){
     noteOn(0, bn7,100);
     Serial.println("7");
     delay(500);
     noteOff(0, bn7,0);
   }
  if(Serial.available() > 0)
  {
    byteData =  Serial.read();
    mySerial.write( byteData);
  }  
  delay(50);
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

  //모든 명령은 1바이트를 지니며, 모든 cmds는   0xBn보다  2 데이터 바이트를 덜 지닙니다.  
  //(sort of: http://253.ccarh.org/handout/midiprotocol/)
  if( (cmd & 0xF0) <= 0xB0)
    mySerial.write(data2 );

  digitalWrite(ledPin, LOW);
}
	digitalWrite( btn3, HIGH);
	pinMode( btn4, INPUT);
	digitalWrite( btn4, HIGH);
}

void loop() {
	br1 = digitalRead(btn1);
    	br2 = digitalRead(btn2);
    	br3 = digitalRead(btn3);
    	br4 = digitalRead(btn4);
    	//G(솔)코드 버튼 2,3,4입력
    	if( (!bs4 && !br4) && (!bs3 && !br3) && (!bs2 && !br2) && (bs1 && br1) ){
		noteOn(0, g,100);
		bs1 = false;
		bs2 = true;
		bs3 = true;
		bs4 = true;
	}else if( (bs4 && br4) && (bs3 && br3) && (bs2 && br2) && (!bs1 && !br1) ){
		noteOff(0, g,0);   
		bs1 = true;
		bs2 = false;
		bs3 = false;
		bs4 = false;
	}
    	//A(라)코드 버튼 2,1 입력
	if( (bs4 && br4) && (bs3 && br3) && (!bs2 && !br2) && (!bs1 && !br1) ){
		noteOn(0, a,100);
		bs1 = true;
		bs2 = true;
		bs3 = false;
		bs4 = false;
	}
	else if( (bs4 && br4) && (bs3 && br3) && (bs2 && br2) && (bs1 && br1) ){
		noteOff(0, a,0);   
		bs1 = false;
		bs2 = false;
		bs3 = true;
		bs4 = true;
	}   
   	//B(시)코드 버튼 1,2,3,4 입력
	if( (!bs4 && !br4) && (!bs3 && !br3) && (!bs2 && !br2) && (!bs1 && !br1) ){
		noteOn(0, b,100);
		bs1 = true;
		bs2 = true;
		bs3 = true;
		bs4 = true;
	}else if( (bs4 && br4) && (bs3 && br3) && (bs2 && br2) && (bs1 && br1) ){
		noteOff(0, b,0);   
		bs1 = false;
		bs2 = false;
		bs3 = false;
		bs4 = false;
	}
	//C(도)코드 버튼 4 입력
	if( (!bs4 && !br4) && (bs3 && br3) && (bs2 && br2) && (bs1 && br1) ){
		noteOn(0, c,100);
		bs1 = false;
		bs2 = false;
		bs3 = false;
		bs4 = true;
	} else if( (bs4 && br4) && (!bs3 && !br3) && (!bs2 && !br2) && (!bs1 && !br1) ){
		noteOff(0, c,0);   
		bs1 = true;
		bs2 = true;
		bs3 = true;
		bs4 = false;
	}
	//D(레)코드 버튼 1,2,3 입력
	if( (bs4 && br4) && (!bs3 && !br3) && (!bs2 && !br2) && (!bs1 && !br1) ){
		noteOn(0, d,100);
		bs1 = true;
		bs2 = true;
		bs3 = true;
		bs4 = false;
	} else if( (!bs4 && !br4) && (bs3 && br3) && (bs2 && br2) && (bs1 && br1) ){
		noteOff(0, d,0);   
		bs1 = false;
		bs2 = false;
		bs3 = false;
		bs4 = true;
	}
	//E(미)코드 버튼 3 입력
	if( (bs4 && br4) && (!bs3 && !br3) && (bs2 && br2) && (bs1 && br1) ){
		noteOn(0, e,100);
		bs1 = false;
		bs2 = false;
		bs3 = true;
		bs4 = false;
	}else if( (!bs4 && !br4) && (bs3 && br3) && (!bs2 && !br2) && (!bs1 && !br1) ){
		noteOff(0, e,0);   
		bs1 = true;
		bs2 = true;
		bs3 = false;
		bs4 = true;
	}
	//F(파)코드  버튼 1,3입력  
	if( (bs4 && br4) && (!bs3 && !br3) && (bs2 && br2) && (!bs1 && !br1) ){
		noteOn(0, f,100);
		bs1 = true;
		bs2 = false;
		bs3 = true;
		bs4 = false;
	} else if( (!bs4 && !br4) && (bs3 && br3) && (!bs2 && !br2) && (bs1 && br1) ){
		noteOff(0, f,0);   
		bs1 = false;
		bs2 = true;
		bs3 = false;
		bs4 = true;
	}     
/* 
if( !bs9 && !br9 ){ //patch up (max:127)
  patch++;
  if(patch >127) patch = 0;
  talkMIDI(0xc0, patch, 0);     
  bs9 = true;
}else if(bs9 && br9){
  bs9 = false;
}   
if( !bs10 && !br10 ){ //patch down (min:0)
  patch--;
  if(patch < 0) patch = 127;
  talkMIDI(0xc0, patch, 0);       
  bs10 = true;
}else if(bs10 && br10){
  bs10 = false;
}   

if( !bs11 && !br11 ){
  //bank 0x78(drum)
  talkMIDI(0xb0, 0, 0x78);
  talkMIDI(0xb0,20, 0);
  talkMIDI(0xc0, patch, 0);     
  bs11 = true;
}else if(bs11 && br11){
  bs11 = false;
}   

if( !bs12 && !br12 ){
  //bank MSB 0, default instruments
  patch = defaultPatch;
  talkMIDI(0xb0, 0, 0);
  talkMIDI(0xb0,20, 0);
  talkMIDI(0xc0, patch, 0);       
  bs12 = true;
}else if(bs12 && br12){
  bs12 = false;
}   */
	//*************** MIDI LOOPBACK ******************//
	if(Serial.available() > 0)
	{
		byteData =  Serial.read();
		mySerial.write( byteData);
	}  
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

	//모든 명령은 1바이트를 지니며, 모든 cmds는   0xBn보다  2 데이터 바이트를 덜 지닙니다.  
	//(sort of: http://253.ccarh.org/handout/midiprotocol/)
	if( (cmd & 0xF0) <= 0xB0)
		mySerial.write(data2 );
	digitalWrite(ledPin, LOW);
}
