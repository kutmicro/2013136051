#define laz1 A0   //조도센서1의 아두이노 핀번호 정의
#define laz2 A1   //조도센서2의 아두이노 핀번호 정의
#define laz3 A2   //조도센서3의 아두이노 핀번호 정의
#define laz4 A3   //조도센서4의 아두이노 핀번호 정의

int lazVal1 = 0;  //조도센서1 에서 받은 AnalogRead 값
int lazVal2 = 0;  //이하, 위와 유사  
int lazVal3 = 0;  
int lazVal4 = 0;  

void setup() {
  Serial.begin(9600);
}
void loop() {
  lazVal1 = analogRead(laz1); //read analog 
  lazVal2 = analogRead(laz2); //read analog 
  lazVal3 = analogRead(laz3); //read analog 
  lazVal4 = analogRead(laz4); //read analog 
  
  Serial.println(lazVal1);
  Serial.println(lazVal2);
  Serial.println(lazVal3);
  Serial.println(lazVal4);

  delay(50);
}
