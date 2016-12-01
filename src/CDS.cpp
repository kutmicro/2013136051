#define potpin A0  //set analog interface #0 to connect photocell
int ledpin=13; 
int val=0;  //define variable val 
void setup() 
{ 
  pinMode(ledpin,OUTPUT);//set digital interface #11 as output 
  Serial.begin(9600);//set baud rate as 9600 
} 
void loop() 
{ 
  val=analogRead(potpin);//read analog 
  Serial.println(val); 
  delay(1000);//delay 0.01 s 
}
