#include <SoftwareSerial.h>
#define btn1  11  // 버튼1의 아두이노 핀번호 정의
#define btn2  10  // 버튼2의 아두이노 핀번호 정의
#define btn3  9   // 버튼3의 아두이노 핀번호 정의
#define btn4  8   // 버튼4의 아두이노 핀번호 정의
// 3:midi rx , 4:midi reset  아두이노 핀 3번 4번은 이미 사용중
#define laz1 A0
#define laz2 A1
#define laz3 A2
#define laz4 A3

SoftwareSerial mySerial(2, 3); //SW시리얼핀 정의 D3이 MIDI신호 전송용,  D2는 미사용 

byte note = 0; //The MIDI연주될 note(음계)
byte resetMIDI = 4; // VS1053 Reset용 핀
byte ledPin = 13; //MIDI 트래픽 표시용 LED

boolean br1;  // 버튼1 상태 확인용 입력값 임시저장용
boolean br2;  // 이하, 위와 유사
boolean br3;
boolean br4;

int lazVal1 = 0;
int lazVal2 = 0;
int lazVal3 = 0;
int lazVal4 = 0;
int patch = 0; //악기 대응, 연주될 악기 종류 (0~127: 기본 128 가지 선택가능)

int bn1 = 60; //버튼1의  note(음계)  가령 "도"  0~127까지 지정가능 (정확한 음계 설정은 MIDI관련정보참고)
int bn2 = 62; //버튼2의  note(음계)  가령 "레"
int bn3 = 64; //버튼3의  note(음계)  가령 "미"
int bn4 = 65; //버튼4의  note(음계)  가령 "파"

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
}
void loop() {
	br1 = digitalRead(btn1);
	br2 = digitalRead(btn2);
	br3 = digitalRead(btn3);
	br4 = digitalRead(btn4);

	lazVal1 = analogRead(laz1); //read analog 
	check = setNote1(br1) + setNote2(br2) + setNote3(br3) + setNote4(br4);
	/*  
	if(setNote1(br1, lazVal) == 59 || setNote1(br2, lazVal) == 59 || (br3, lazVal) == 59 || setNote1(br4, lazVal) == 59) {
	noteOn(0, 59, 100);
	delay(500);
	noteOff(0, 59, 0);
	Serial.print("default");
	Serial.print("\n");
	}  */ 
	if(lazVal < 900) {
		if(check==1000) {
			noteOn(0, note60, 100);
			delay(500);
			noteOff(0, note60, 0);
			Serial.println(1000);
		}
		else if(check==111){
			noteOn(0, note62, 100);
			delay(500);
			noteOff(0, note62, 0);
			Serial.println(111);
		} 
		else if(check==100){
			noteOn(0, note64, 100);
			delay(500);
			noteOff(0, note64, 0);
			Serial.println(100);
		}
		else if(check==101){
			noteOn(0, note65,100);
			delay(500);
			noteOff(0, note65, 0);
			Serial.println(101);
		}
		else if(check==1110){
			noteOn(0, note67,100);
			delay(500);
			noteOff(0, note67, 0);
			Serial.println(1110);
		}
		else if(check==11){
			noteOn(0, note69,100);
			delay(500);
			noteOff(0, note69, 0);
			Serial.println(11);
		}
		else if(check==1111){
			noteOn(0, note71,100);
			delay(500);
			noteOff(0, note71, 0);
			Serial.println(1111);
		}
		else if(check==0){ 
			noteOn(0, 59, 100);
			delay(500);
			noteOff(0, 59, 0);
			Serial.println(59);
		}
	}
	if(Serial.available() > 0)
	{
		byteData =  Serial.read();
		mySerial.write( byteData );
	}  
	delay(50);
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