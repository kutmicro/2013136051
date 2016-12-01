#include <SoftwareSerial.h>
#define btn1  11  // ��ư1�� �Ƶ��̳� �ɹ�ȣ ����
#define btn2  10  // ��ư2�� �Ƶ��̳� �ɹ�ȣ ����
#define btn3  9   // ��ư3�� �Ƶ��̳� �ɹ�ȣ ����
#define btn4  8   // ��ư4�� �Ƶ��̳� �ɹ�ȣ ����
// 3:midi rx , 4:midi reset  �Ƶ��̳� �� 3�� 4���� �̹� �����
#define laz1 A0
#define laz2 A1
#define laz3 A2
#define laz4 A3

SoftwareSerial mySerial(2, 3); //SW�ø����� ���� D3�� MIDI��ȣ ���ۿ�,  D2�� �̻�� 

byte note = 0; //The MIDI���ֵ� note(����)
byte resetMIDI = 4; // VS1053 Reset�� ��
byte ledPin = 13; //MIDI Ʈ���� ǥ�ÿ� LED

boolean br1;  // ��ư1 ���� Ȯ�ο� �Է°� �ӽ������
boolean br2;  // ����, ���� ����
boolean br3;
boolean br4;

int lazVal1 = 0;
int lazVal2 = 0;
int lazVal3 = 0;
int lazVal4 = 0;
int patch = 0; //�Ǳ� ����, ���ֵ� �Ǳ� ���� (0~127: �⺻ 128 ���� ���ð���)

int bn1 = 60; //��ư1��  note(����)  ���� "��"  0~127���� �������� (��Ȯ�� ���� ������ MIDI������������)
int bn2 = 62; //��ư2��  note(����)  ���� "��"
int bn3 = 64; //��ư3��  note(����)  ���� "��"
int bn4 = 65; //��ư4��  note(����)  ���� "��"

byte byteData;

void setup() {
	Serial.begin(31250);
	//�̵���Ʈ���� ���� ����Ʈ���� �ø����� �غ��մϴ�.
	mySerial.begin(31250);
	//VS1053�� �ʱ�ȭ�ϰ� ����� �غ� �մϴ�.
	pinMode(resetMIDI, OUTPUT);
	digitalWrite(resetMIDI, LOW);
	delay(100);
	digitalWrite(resetMIDI, HIGH);
	delay(100);

	pinMode( btn1, INPUT);      // ��ư1 �Է¿� �ɸ�带  �Է¸��� ��ȯ
	digitalWrite( btn1, HIGH);  // ���� PullUp ����, ����ġ�� ������ �Ѽ��� GND�� ������ �˴ϴ�.(�ʰ���)
	pinMode( btn2, INPUT);      // ����, ���� ����
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
//��Ʈ �� �̵� �޼����� �����մϴ�. ��ư�� �������¿� �����ϴ�.
//ä�� ������ 0-15 �Դϴ�.
void noteOn(byte channel, byte note, byte attack_velocity) {
	talkMIDI( (0x90 | channel), note, attack_velocity);
}

//��Ʈ ���� �̵� �޼����� �����մϴ�. ��ư�� ������ ���� ���¿� �����ϴ�.
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