#define laz1 7
#define laz2 6
#define laz3 5
#define laz4 4

boolean ls1 = false;   // 버튼1의 현재상태(눌림 or 안눌림)
boolean ls2 = false;   // 이하, 위와 유사
boolean ls3 = false;
boolean ls4 = false;

boolean lr1;           // 버튼1 상태 확인용 입력값 임시저장용
boolean lr2;           // 이하, 위와 유사
boolean lr3;
boolean lr4;

int sensVal1 = 0;
int sensVal2 = 0;
int sensVal3 = 0;
int sensVal4 = 0;

int ln1 = 60;         //버튼1의  note(음계)  가령 "도"  0~127까지 지정가능 
int ln2 = 62;         //버튼2의  note(음계)  가령 "레"
int ln3 = 64;         //버튼3의  note(음계)  가령 "미"
int ln4 = 65;         //버튼4의  note(음계)  가령 "파"

void setup() {
	Serial.begin(9600);

	pinMode( laz1, INPUT);  
	digitalWrite( laz1, HIGH);  // 내부 PullUp 설정, 스위치의 나머지 한선은 GND에 물림


	pinMode( laz2, INPUT);
	digitalWrite( laz2, HIGH);
  
	pinMode( laz3, INPUT);
	digitalWrite( laz3, HIGH);
  
	pinMode( laz4, INPUT);
	digitalWrite( laz4, HIGH);
}
void loop() {
   //버튼 상태 확인용 입력값 임시저장용
    sensVal1 = analogRead(laz1);
    sensVal2 = analogRead(laz2);
    sensVal3 = analogRead(laz3);
    sensVal4 = analogRead(laz4);
//조도센서가 빛을 받으면 값이 작아진다. (수정 ) 
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