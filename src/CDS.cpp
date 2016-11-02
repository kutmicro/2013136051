#define laz1 7
#define laz2 6
#define laz3 5
#define laz4 4

boolean ls1 = false;   // ��ư1�� �������(���� or �ȴ���)
boolean ls2 = false;   // ����, ���� ����
boolean ls3 = false;
boolean ls4 = false;

boolean lr1;           // ��ư1 ���� Ȯ�ο� �Է°� �ӽ������
boolean lr2;           // ����, ���� ����
boolean lr3;
boolean lr4;

int sensVal1 = 0;
int sensVal2 = 0;
int sensVal3 = 0;
int sensVal4 = 0;

int ln1 = 60;         //��ư1��  note(����)  ���� "��"  0~127���� �������� 
int ln2 = 62;         //��ư2��  note(����)  ���� "��"
int ln3 = 64;         //��ư3��  note(����)  ���� "��"
int ln4 = 65;         //��ư4��  note(����)  ���� "��"

void setup() {
	Serial.begin(9600);

	pinMode( laz1, INPUT);  
	digitalWrite( laz1, HIGH);  // ���� PullUp ����, ����ġ�� ������ �Ѽ��� GND�� ����


	pinMode( laz2, INPUT);
	digitalWrite( laz2, HIGH);
  
	pinMode( laz3, INPUT);
	digitalWrite( laz3, HIGH);
  
	pinMode( laz4, INPUT);
	digitalWrite( laz4, HIGH);
}
void loop() {
   //��ư ���� Ȯ�ο� �Է°� �ӽ������
    sensVal1 = analogRead(laz1);
    sensVal2 = analogRead(laz2);
    sensVal3 = analogRead(laz3);
    sensVal4 = analogRead(laz4);
//���������� ���� ������ ���� �۾�����. (���� ) 
	if(!ls1 && sensVal1 >= 100){
		noteOn(0, ln1,100);
		ls1 = true;
	}
	else if(ls1 && sensVal1 < 100){
		noteOff(0, ln1,0); 
		ls1 = false;
	}
	Serial.print(sensVal1);
	Serial.print("\t");
   
	if( !ls2 && sensVal2 >= 100 ){
		noteOn(0, ln2,100);
		ls2 = true;
	}else if(ls2 && sensVal2 < 100){
		noteOff(0, ln2,0);   
		ls2 = false;
	}   
	Serial.print(sensVal2);
	Serial.print("\t"); 
   
	if( !ls3 && sensVal3 >= 100 ){
		noteOn(0, ln3,100);
		ls3 = true;
	}else if(ls3 && sensVal3 < 100){
		noteOff(0, ln3,0);   
		ls3 = false;
	}
	Serial.print(sensVal3);
	Serial.print("\t");
    
	if( !ls4 && sensVal4 >= 100){
		noteOn(0, ln4,100);
		ls4 = true;
	}else if(ls4 && sensVal4 < 100){
		noteOff(0, ln4,0);   
		ls4 = false;
	}
	Serial.print(sensVal4);
	Serial.print("\t");
}