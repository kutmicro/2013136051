void loop() {
  br1 = digitalRead(btn1);
  br2 = digitalRead(btn2);
  br3 = digitalRead(btn3);
  br4 = digitalRead(btn4);

  lazVal = analogRead(laz1); //read analog 
  
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