#include <Wire.h>                                          
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>             
LiquidCrystal_I2C lcd(0x27, 16, 2);           

bool get_string();
String linea = "";
const byte ROWS = 4; 
const byte COLS = 4; 

char hexa_keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte column_index = 0;
byte row_pins[ROWS] = {9, 8, 7, 6}; 
byte col_pins[COLS] = {5, 4, 3, 2};

Keypad custom_keypad = Keypad(makeKeymap(hexa_keys), row_pins, col_pins, ROWS, COLS);

void setup() {
  lcd.init();
  Wire.begin();
  lcd.backlight();
  Serial.begin(115200);
}

void loop() {
  char custom_key = custom_keypad.getKey();
  if(get_string()) {
    lcd.clear();
    column_index = 0;
    lcd.setCursor(0,0);
    lcd.print(linea);
    Serial.println(linea);
    linea = "";
  }
  if (custom_key){
    lcd.setCursor(column_index%16,1);
    lcd.print(custom_key);
    column_index++;
  }
  if (custom_key == '*') {
    lcd.clear();
    column_index = 0;
  }   
}

bool get_string() {
  while(Serial.available() > 0) {
    char c = Serial.read();
    if (c == '\n') {
      return true;
    }
    else {
      linea += c;
    }
  }
  return false;
}