//�����(trig)�� �Է���(echo) ���� ����, �ٸ� ���� �����ص� ��.
int trigPin1 = 7;
int echoPin1 = 6;
int trigPin2 = 5;
int echoPin2 = 4;

//�ø��� �ӵ�����, trigPin�� ���, echoPin�� �Է����� ����
void setup(){
  Serial.begin(9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
}
 
//�����ĸ� ������. �� ������ echo�� HIGH(��ȣ�ޱ�) ���·� ���
void loop(){
  float duration1, distance1;
  float duration2, distance2;
  digitalWrite(trigPin1, HIGH);
  delay(10);
  digitalWrite(trigPin1, LOW);

  digitalWrite(trigPin2, HIGH);
  delay(10);
  digitalWrite(trigPin2, LOW);
 
  // echoPin �� HIGH�� ������ �ð��� ���� �Ѵ�.
  duration1 = pulseIn(echoPin1, HIGH);
  duration2 = pulseIn(echoPin2, HIGH);
  // HIGH ���� �� �ð�(�����İ� ���´ٰ� �ٽ� ���� �ð�)�� ������ �Ÿ��� ��� �Ѵ�.
  // 340�� �ʴ� ������(�Ҹ�)�� �ӵ�, 10000�� �и������带 �������, �պ��Ÿ��̹Ƿ� 2�� �����ش�.
  distance1 = ((float)(340 * duration1) / 10000) / 2;
  distance2 = ((float)(340 * duration2) / 10000) / 2;
  //�ø������Ϳ� Echo�� HIGH�� �ð� �� �Ÿ��� ǥ�����ش�.
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