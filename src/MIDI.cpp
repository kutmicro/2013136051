#include <SoftwareSerial.h>
#define btn1  11  // ��ư1�� �Ƶ��̳� �ɹ�ȣ ����
#define btn2  10  // ��ư2�� �Ƶ��̳� �ɹ�ȣ ����
#define btn3  9   // ��ư3�� �Ƶ��̳� �ɹ�ȣ ����
#define btn4  8   // ��ư4�� �Ƶ��̳� �ɹ�ȣ ����
#define defaultPatch 15 //�Ǳ� �ʱ�ȭ ��ư ���� �Ǳ��ȣ

SoftwareSerial mySerial(2, 3); //SW�ø����� ���� D3�� MIDI��ȣ ���ۿ�,  D2�� �̻�� 

byte note = 0; //The MIDI���ֵ� note(����)
byte resetMIDI = 4; // VS1053 Reset�� ��
byte ledPin = 13; //MIDI Ʈ���� ǥ�ÿ� LED
 
boolean bs1 = false;  // ��ư1�� �������(���� or �ȴ���)
boolean bs2 = false;  // ����, ���� ����
boolean bs3 = false;
boolean bs4 = false;

boolean br1;  // ��ư1 ���� Ȯ�ο� �Է°� �ӽ������
boolean br2;  // ����, ���� ����
boolean br3;
boolean br4;

int patch = 0; //�Ǳ� ����, ���ֵ� �Ǳ� ���� (0~127: �⺻ 128 ���� ���ð���)

int bn1 = 60; //��ư1��  note(����)  ���� "��"  0~127���� �������� (��Ȯ�� ���� ������ MIDI������������)
int bn2 = 62; //��ư2��  note(����)  ���� "��"
int bn3 = 64; //��ư3��  note(����)  ���� "��"
int bn4 = 65; //��ư4��  note(����)  ���� "��"
int bn5 = 67; //��ư5��  note(����)  ���� "��"
int bn6 = 69; //��ư6��  note(����)  ���� "��"
int bn7 = 71; //��ư7��  note(����)  ���� "��"
//int bn8 = 72; //��ư8��  note(����)  ���� "��~"

byte byteData;

void noteOn(byte channel, byte note, byte attack_velocity);
void noteOff(byte channel, byte note, byte release_velocity);
void talkMIDI(byte cmd, byte data1, byte data2);

void setup() {
	Serial.begin(31250);

	//�̵���Ʈ���� ���� ����Ʈ���� �ø����� �غ��մϴ�.
	mySerial.begin(31250);
	//mySerial2.begin(57600);
  
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
    //G(��)�ڵ� ��ư 2,3,4�Է�
    if( !bs4 && !br4 && !bs3 && !br3 && !bs2 && !br2 && bs1 && br1){
		noteOn(0, bn5,100);
		bs1 = false;
		bs2 = true;
		bs3 = true;
		bs4 = true;
	}else if( bs4 && br4 && bs3 && br3 && bs2 && br2 && !bs1 && !br1){
		noteOff(0, bn5,0);   
		bs1 = true;
		bs2 = false;
		bs3 = false;
		bs4 = false;
	}
    //A(��)�ڵ� ��ư 2,1 �Է�
	if( bs4 && br4 && bs3 && br3 && !bs2 && !br2 && !bs1 && !br1){
		noteOn(0, bn6,100);
		bs1 = true;
		bs2 = true;
		bs3 = false;
		bs4 = false;
	}
	else if( bs4 && br4 && bs3 && br3 && bs2 && br2 && bs1 && br1){
		noteOff(0, bn6,0);   
		bs1 = false;
		bs2 = false;
		bs3 = true;
		bs4 = true;
	}   
   //B(��)�ڵ� ��ư 1,2,3,4 �Է�
	if( !bs4 && !br4 && !bs3 && !br3 && !bs2 && !br2 && !bs1 && !br1){
		noteOn(0, bn7,100);
		bs1 = true;
		bs2 = true;
		bs3 = true;
		bs4 = true;
	}else if( bs4 && br4 && bs3 && br3 && bs2 && br2 && bs1 && br1){
		noteOff(0, bn7,0);   
		bs1 = false;
		bs2 = false;
		bs3 = false;
		bs4 = false;
	}
	//C(��)�ڵ� ��ư 4 �Է�
	if( !bs4 && !br4 && bs3 && br3 && bs2 && br2 && bs1 && br1){
		noteOn(0, bn1,100);
		bs1 = false;
		bs2 = false;
		bs3 = false;
		bs4 = true;
	} else if( bs4 && br4 && !bs3 && !br3 && !bs2 && !br2 && !bs1 && !br1){
		noteOff(0, bn1,0);   
		bs1 = true;
		bs2 = true;
		bs3 = true;
		bs4 = false;
	}
	//D(��)�ڵ� ��ư 1,2,3 �Է�
	if( bs4 && br4 && !bs3 && !br3 && !bs2 && !br2 && !bs1 && !br1){
		noteOn(0, bn2,100);
		bs1 = true;
		bs2 = true;
		bs3 = true;
		bs4 = false;
	} else if( !bs4 && !br4 && bs3 && br3 && bs2 && br2 && bs1 && br1){
		noteOff(0, bn2,0);   
		bs1 = false;
		bs2 = false;
		bs3 = false;
		bs4 = true;
	}
	//E(��)�ڵ� ��ư 3 �Է�
	if( bs4 && br4 && !bs3 && !br3 && bs2 && br2 && bs1 && br1){
		noteOn(0, bn3,100);
		bs1 = false;
		bs2 = false;
		bs3 = true;
		bs4 = false;
	}else if( !bs4 && !br4 && bs3 && br3 && !bs2 && !br2 && !bs1 && !br1){
		noteOff(0, bn3,0);   
		bs1 = true;
		bs2 = true;
		bs3 = false;
		bs4 = true;
	}
	//F(��)�ڵ�  ��ư 1,3�Է�  
	if( bs4 && br4 && !bs3 && !br3 && bs2 && br2 && !bs1 && !br1){
		noteOn(0, bn4,100);
		bs1 = true;
		bs2 = false;
		bs3 = true;
		bs4 = false;
	} else if( !bs4 && !br4 && bs3 && br3 && !bs2 && !br2 && bs1 && br1){
		noteOff(0, bn4,0);   
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
	//digitalWrite(ledPin, HIGH);
	mySerial.write(cmd );
	mySerial.write(data1 );

	//��� ����� 1����Ʈ�� ���ϸ�, ��� cmds��   0xBn����  2 ������ ����Ʈ�� �� ���մϴ�.  
	//(sort of: http://253.ccarh.org/handout/midiprotocol/)
	if( (cmd & 0xF0) <= 0xB0)
		mySerial.write(data2 );
// digitalWrite(ledPin, LOW);
}