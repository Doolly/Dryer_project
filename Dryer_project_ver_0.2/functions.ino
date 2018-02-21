void Timer() {
  if (stage == 4) {
    if (pause == 1)
      return;

    second = setted_second % 60;
    minute = setted_second / 60;
    setted_second--;

    if (setted_second < 0)
      stage = 5;
  }
}
void Pause() { //toggle 변수가 계속 전역으로 살아있음 맨처음 구동에서 오류 , 일시정지 상태에서 뒤로가기 가능하게
  //if( stage != 4 || stage !=2 ) return;

  if ( stage == 4 || stage == 2 )  
    pause ^= 1;
  
    else return;
  
}

int Get_Key(void)
{
  char up_val = 0, down_val = 0, cancel_val = 0, enter_val = 0;
  up_val = digitalRead(up_button);
  down_val = digitalRead(down_button);
  cancel_val = digitalRead(cancel_button);
  enter_val = digitalRead(enter_button);

  while ((digitalRead(up_button) == 1 || digitalRead(down_button) == 1 || digitalRead(cancel_button) == 1 || digitalRead(enter_button) == 1));

  if (up_val == 1)
    return up_button;
  else if (down_val == 1)
    return down_button;
  else if (cancel_val == 1)
    return cancel_button;
  else if (enter_val == 1)
    return enter_button;
  else
    return 0;
}

int Wait_Key(void)
{
  char up_val = 0, down_val = 0, cancel_val = 0, enter_val = 0;
  while ((digitalRead(up_button) == 0 || digitalRead(down_button) == 0 || digitalRead(cancel_button) == 0 || digitalRead(enter_button) == 0));

  up_val = digitalRead(up_button);
  down_val = digitalRead(down_button);
  cancel_val = digitalRead(cancel_button);
  enter_val = digitalRead(enter_button);

  while ((digitalRead(up_button) == 1 || digitalRead(down_button) == 1 || digitalRead(cancel_button) == 1 || digitalRead(enter_button) == 1));

  if (up_val == 1)
    return up_button;
  else if (down_val == 1)
    return down_button;
  else if (cancel_val == 1)
    return cancel_button;
  else if (enter_val == 1)
    return enter_button;
  else
    return 0;
}

void Control (int PWM_val) {
  if (PWM_val == 0) {
    analogWrite(Moter_Ctrl, PWM_val);
    analogWrite(Fan_Ctrl, PWM_val);
    digitalWrite(Hair_Dry_Ctrl, 0);
  }
  else  {
    analogWrite(Moter_Ctrl, PWM_val);
    analogWrite(Fan_Ctrl, PWM_val);
    digitalWrite(Hair_Dry_Ctrl, 1);
  }
}

void Sensor(void) {
  h = int(dht.readHumidity());
  // Read temperature as Celsius (the default)
  t = int(dht.readTemperature());
  // Check if any reads failed and exit early (to try again).

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");
}

void speaker(void) {
  digitalWrite(Speaker, HIGH);
  delay(1000);
  digitalWrite(Speaker, LOW);
  delay(500);
  digitalWrite(Speaker, HIGH);
  delay(1000);
  digitalWrite(Speaker, LOW);
  delay(500);
  digitalWrite(Speaker, HIGH);
  delay(1000);
  digitalWrite(Speaker, LOW);
  delay(500);
}



