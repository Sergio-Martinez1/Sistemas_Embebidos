#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);

const byte NumMenuP = 4;
const byte NumMaxSubM = 3;
const byte NumBttn = 5;


byte Buttn[NumBttn] = {
  2, //UP
  3, //RIGHT
  4, //DOWN
  5, //INT
  6 //LEFT
};

String MenuP[NumMenuP] = {
  "*INICIO*",
  "*ENCENDER LED*",
  "*ENCENDER LED2*",
  "*INTEGRANTES*",
};

String SubMenus[NumMenuP][NumMaxSubM] = {
  {"Sub item 1","Sub item 2", "Sub item 3"},
  {"LED ON","LED OFF", ""},
  {"LED ON","LED OFF", ""},
  {"Sergio David","Julio Rangel", "Jesus Emiliano"},
};

int tecla = -1;
int teclaAnt = -1;
boolean cursorAct = false;
unsigned long tiempo;
int x = -1;
int y = 0;
int LED = 8;
int LED1 = 9;
int cuenta = 0; 
int cuenta2 = 0; 

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < NumBttn; i++) {
    pinMode(Buttn[i], INPUT);
  }
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("*Menu LCD 20x4*");
  lcd.setCursor(3,1);
  lcd.print("Arduino");
  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" MENU PRINCIPAL");
  lcd.setCursor(0,2);
  lcd.print(" Presione cualquier");
  lcd.setCursor(0,3);
  lcd.print(" tecla...");
  tiempo = millis();
  pinMode(LED, OUTPUT);
  pinMode(LED1, OUTPUT);
}

void loop() {
  if(millis() - tiempo > 5000){
    cuenta2 = cuenta2 + 1;
    if(cuenta2 == 1){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(" MENU PRINCIPAL");
      lcd.setCursor(0,2);
      lcd.print(" Presione cualquier");
      lcd.setCursor(0,3);
      lcd.print(" tecla...");
    }
    //lcd.noBlink();
    //cursorAct = false;
  }

  tecla = get_Key(Buttn);
  
  if(tecla != teclaAnt){
  
    delay(50);
    tecla = get_Key(Buttn);
    if(tecla != teclaAnt){
      tiempo = millis();
      cuenta2 = 0;
      teclaAnt = tecla;
      if(tecla >= 0){
        lcd.blink();
      }
      
      if(tecla == 2){ //DOWN
        x++;
        y = 0;
        if(x > NumMenuP - 1) x = NumMenuP - 1;
      }

      if(tecla == 0){ //UP
        x--;
        if( x < 0) x = 0;
        y = 0;
        Serial.println(x);
      }

      if(tecla == 1){ //RIGTH
        y++;
        if( y > NumMaxSubM - 1) y = NumMaxSubM - 1;
      }

      if(tecla == 4){ //LEFT
        y--;
        if(y < 0) y = 0;
      }

      if(tecla == 3){
        cuenta = cuenta + 1;
        if (cuenta == 1){
          x++; 
        }
        if(x == 1 && y == 0){
          digitalWrite(LED, HIGH);
        } else if (x == 1 && y == 1){
          digitalWrite(LED, LOW);
        }
        if(x == 2 && y == 0){
          digitalWrite(LED1, HIGH);
        } else if (x == 2 && y == 1){
          digitalWrite(LED1, LOW);
        }
      }

      lcd.clear();
      lcd.print(MenuP[x]);
      lcd.setCursor(0,1); 
      lcd.print(SubMenus[x][y]);
    }
  }
  delay(50);
}

int get_Key(byte args[]) {
  int k;
  if (digitalRead(args[0]) == HIGH) {
    k = 0;
  } else if (digitalRead(args[1]) == HIGH) {
    k = 1;
  } else if (digitalRead(args[2]) == HIGH) {
    k = 2;
  } else if (digitalRead(args[3]) == HIGH) {
    k = 3;
  } else if (digitalRead(args[4]) == HIGH) {
    k = 4;
  } else {
    k = -1;
  }
  return k;
}
