void Starting_Page() {
  lcd.setCursor(0, 0);
  lcd.print ("Anything to DRY?");
  lcd.setCursor(0, 1);
  lcd.print ("Press any button");
}

void Mode_Page(int a) {
  if (a == 0) {
    lcd.setCursor(0, 0);
    lcd.print("Auto       <-   ");
    lcd.setCursor(0, 1);
    lcd.print("Manual          ");
  }

  else {
    lcd.setCursor(0, 0);
    lcd.print("Auto            ");
    lcd.setCursor(0, 1);
    lcd.print("Manual     <-   ");
  }
}

void Auto_Page() {
  lcd.setCursor(0, 0);
  lcd.print("Humidity :   %  ");
  lcd.setCursor(10, 0);
  lcd.print(h);
  lcd.setCursor(0, 1);
  lcd.print("Temp:     C     ");
  lcd.setCursor(7, 1);
  lcd.print(t);
}

void Manual_Setting_Page() {
  lcd.setCursor(0, 0);
  lcd.print("Running time set");
  lcd.setCursor(0, 1);
  lcd.print("   ");
  if (setted_minute < 10) {
    lcd.setCursor(1, 1);
    lcd.print(setted_minute);
  }
  else {
    lcd.setCursor(0, 1);
    lcd.print(setted_minute);
  }
  lcd.setCursor(3, 1);
  lcd.print("Min");
}

void Manual_Count_Page(int minute, int second) {
  static int prev_minute = -1;
  static int prev_second = -1;

  if ( minute == prev_minute && second == prev_second ) {
    return;
  }

  prev_minute = minute;
  prev_second = second;
  lcd.setCursor(0, 0);
  lcd.print("Drying...      ");
  lcd.setCursor(0, 1);
  lcd.print("Remain         ");

  if (minute < 10) {
    lcd.setCursor(8, 1);
    lcd.print(minute);
  }
  else {
    lcd.setCursor(7, 1);
    lcd.print(minute);
  }

  lcd.setCursor(9, 1);
  lcd.print(":");
  
  if (second < 10) {
    lcd.setCursor(10, 1);
    lcd.print("0");
    lcd.setCursor(11, 1);
    lcd.print(second);
  }
  else {
    lcd.setCursor(10, 1);
    lcd.print(second);
  }
}



