//출력핀(trig)과 입력핀(echo) 연결 설정, 다른 핀을 연결해도 됨.
int trigPin1 = 7;
int echoPin1 = 6;
int trigPin2 = 5;
int echoPin2 = 4;

//시리얼 속도설정, trigPin을 출력, echoPin을 입력으로 설정
void setup(){
  Serial.begin(9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
}
 
//초음파를 보낸다. 다 보내면 echo가 HIGH(신호받기) 상태로 대기
void loop(){
  float duration1, distance1;
  float duration2, distance2;
  digitalWrite(trigPin1, HIGH);
  delay(10);
  digitalWrite(trigPin1, LOW);

  digitalWrite(trigPin2, HIGH);
  delay(10);
  digitalWrite(trigPin2, LOW);
 
  // echoPin 이 HIGH를 유지한 시간을 저장 한다.
  duration1 = pulseIn(echoPin1, HIGH);
  duration2 = pulseIn(echoPin2, HIGH);
  // HIGH 였을 때 시간(초음파가 보냈다가 다시 들어온 시간)을 가지고 거리를 계산 한다.
  // 340은 초당 초음파(소리)의 속도, 10000은 밀리세컨드를 세컨드로, 왕복거리이므로 2로 나눠준다.
  distance1 = ((float)(340 * duration1) / 10000) / 2;
  distance2 = ((float)(340 * duration2) / 10000) / 2;
  //시리얼모니터에 Echo가 HIGH인 시간 및 거리를 표시해준다.
  Serial.print("Duration1:");
  Serial.print(duration1);
  Serial.print("\nDIstance1:");
  Serial.print(distance1);
  Serial.println("cm\n");
  delay(500);

  Serial.print("Duration2:");
  Serial.print(duration2);
  Serial.print("\nDIstance2:");
  Serial.print(distance2);
  Serial.println("cm\n");
  delay(500);
}