#include <Keypad.h>
#define yanginPin A0
#define sicaklikPin A1
#define buzzer 30
#define sifreuz 5
//#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(7,6,5,4,3,2);

float sicaklik; 
float analogSicaklik; 

int diezKontrol = 0;
int sayac = 0;
String girilenSifre;     // klavyeden girilen sifre
String sifre = "#1234"; // belirledigimiz sifre
int yesilLed=47;
int kirmiziLed=46;

const byte SATIR=4;
const byte SUTUN=3;
char klavyeTus[SATIR][SUTUN]={
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte satirPin[SATIR]={25,26,27,28};
byte sutunPin[SUTUN]={24,23,22};

Keypad myKeypad= Keypad(makeKeymap(klavyeTus), satirPin, sutunPin, SATIR,SUTUN);

int     sensor      = 10;
boolean sensorDeger = 0;
int     tetik       = 11;


void setup() {
  Serial.begin(9600);
  analogReference(INTERNAL1V1);
  lcd.begin(16,2);
  pinMode(yanginPin, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
 
  pinMode(yesilLed,OUTPUT);
  pinMode(kirmiziLed,OUTPUT);
  pinMode(sensor, INPUT);
  pinMode(tetik, OUTPUT);
  delay(50);
 
}

 void pir()
 
 { sensorDeger = digitalRead(sensor);
 if (sensorDeger == 1) {
    digitalWrite(tetik, HIGH);
    delay(25);
    sensorDeger=0;
    } 
  else
  {digitalWrite(tetik, LOW);

    }
  }
void loop() {

 int Flame = digitalRead(yanginPin);
 if(Flame==HIGH)
 { 
  digitalWrite(buzzer, HIGH);
  delay(5);
  digitalWrite(buzzer, LOW);
  }
else {
  digitalWrite(buzzer, LOW); 
  
  pir();
   
  analogSicaklik=analogRead(sicaklikPin);
  analogSicaklik =analogSicaklik*1.074188;
  sicaklik=analogSicaklik/10,0; 

if(sicaklik<20) {

  
  lcd.setCursor(0,0);
  lcd.print("SICAKLIK:");
  lcd.setCursor(10,0);
  lcd.print(sicaklik);
  lcd.setCursor(15,0);
  lcd.print("C"); 
  lcd.setCursor(0,1);
  lcd.print("SICAKLIK DUSUK");
  }
else if (sicaklik>30) {
 
  lcd.setCursor(0,0);
  lcd.print("SICAKLIK:");
  lcd.setCursor(10,0);
  lcd.print(sicaklik);
  lcd.setCursor(15,0);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("SICAKLIK YUKSEK");
  }
else{
  
  lcd.setCursor(0,0);
  lcd.print("SICAKLIK:");
  lcd.setCursor(10,0);
  lcd.print(sicaklik);
  lcd.setCursor(15,0);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("                  ");
  }


}
 char klavye = myKeypad.getKey();  // keypadden gelen değer
  if (klavye != NO_KEY) {
    if(klavye == '#') {  
       diezKontrol = 1;
       girilenSifre = "";
        sayac = 0;
    }
   
    if(diezKontrol == 1){
        digitalWrite(yesilLed,0); 
        digitalWrite(kirmiziLed,0);
    
      girilenSifre = girilenSifre + klavye;
      sayac++;
      Serial.println("sifre " + girilenSifre );
      // sifre doğru ise
      if(girilenSifre == sifre) {
        digitalWrite(yesilLed,1); 
        digitalWrite(kirmiziLed,0); 
        girilenSifre = "";
        diezKontrol = 0;
        sayac = 0;
      }
      else if ((girilenSifre != sifre) && (sayac > 4) ) { 
        digitalWrite(yesilLed,0); 
        digitalWrite(kirmiziLed,1);
        girilenSifre = "";
        diezKontrol = 0;
        sayac = 0;
      }
    }
  }  
}
