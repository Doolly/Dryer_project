#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <MsTimer2.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD address to 0x27 for 16*2 clcd SDA=A4,SCL=A5

#define up_button 7
#define down_button 4
#define cancel_button 3
#define enter_button 2            //External interrupt
#define Moter_Ctrl 6              //PWM
#define Fan_Ctrl 5                //PWM
#define Hair_Dry_Ctrl 12
#define Speaker 14
#define DHTPIN 8                 //humidity,temperature sensor

#define DHTTYPE DHT21
DHT dht(DHTPIN, DHTTYPE);
// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor


int h;
int t;
int setted_minute = 1;
int setted_second;
int minute;
int second;

int button;
int stage;
int pause;

void setup() {
  pinMode(up_button, INPUT);
  pinMode(down_button, INPUT);
  pinMode(cancel_button, INPUT);
  pinMode(enter_button, INPUT);
  pinMode(Moter_Ctrl, OUTPUT);
  pinMode(Hair_Dry_Ctrl, OUTPUT);
  pinMode(Fan_Ctrl, OUTPUT);
  pinMode(Speaker, OUTPUT);

  lcd.init();
  lcd.backlight();
  dht.begin();
  Control(0);
  MsTimer2::set(1000, Timer);
  MsTimer2::start();
  attachInterrupt(0, Pause, RISING);
  Serial.begin(9600);
}

void loop() {
  ////////////////////////stage 0 initial stage//////////////////////////////////////////////////////////////////

  while (stage == 0) {
    Starting_Page();
    Control(0);
    button = Get_Key();

    if (button != 0)
      stage = 1;
  }

  lcd.clear();///////////////////////stage 1 mode select stage////////////////////////////////////////////////////////////////////

  while (stage == 1) {
    static int i = 0;
    Mode_Page(i);
    Control(0);
    button = Get_Key();

    if (button == up_button || button == down_button)
      i ^= 1;

    if (button == cancel_button)
      stage = 0;

    if (button == enter_button) {
      if (i == 0)
        stage = 2;
      else
        stage = 3;
    }
  }

  lcd.clear(); ////////////////////stage 2 auto running stage////////////////////////////////////////////////////////////////////
  pause = 0;
  while (stage == 2) {
    Auto_Page();
    Sensor();
    Control(255);

    button = Get_Key();

    if (h < 21)
      stage = 5;

    if (button == cancel_button)
      stage = 1;

    while (pause == 1) {
      Control(0);
      delay(5);
    }
  }

  lcd.clear(); ////////////////////stage 3 manual setting stage//////////////////////////////////////////////////////////////////////

  while (stage == 3) {
    Manual_Setting_Page();
    Control(0);
    button = Get_Key();

    if (button == up_button) {
      setted_minute++;
      if (setted_minute > 30)
        setted_minute = 1;
    }
    if (button == down_button) {
      setted_minute--;
      if (setted_minute < 1)
        setted_minute = 30;
    }

    if (button == cancel_button)
      stage = 1;
    if (button == enter_button)
      stage = 4;
  }

  lcd.clear();
  setted_second = setted_minute * 60;
  pause = 0;
  /////////////////////////stage 4 manual running stage/////////////////////////////////////////////////////////////////

  while (stage == 4) {
    Manual_Count_Page(minute, second);
    Control(255);
    button = Get_Key();

    if (button == cancel_button)
      stage = 1;

    while (pause == 1) {
      Control(0);
      delay(5);
    }
  }

  //////////////////////////////stage 5 byebye stage////////////////////////////////////////////////////////////
  if (stage == 5) {
    Control(0);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Bye Bye         ");
    speaker();
    stage = 0;
  }

}





