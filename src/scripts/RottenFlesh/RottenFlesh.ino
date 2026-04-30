//KUTUPHANELER
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

//SENSORLER
int mq4_pin = A0;    //ANALOG 0 MQ-4
int mq135_pin = A1;  //ANALOG 1 MQ-135
int mq136_pin = A2;  //ANALOG 2 MQ-136

//VERILER
int mq136_value;
int mq135_value;
int mq4_value;

//FLAGS
bool first_boot = true;

void setup() {
  Serial.begin(9600);                            //BILGISAYAR ILE ILETISIMI **9600 HIZINDA** BASLATIYORUZ BURDAN GELEN VERILERI OKUYCAZ
  pinMode(mq4_pin, INPUT);
  pinMode(mq135_pin, INPUT);
  pinMode(mq136_pin, INPUT);
  pinMode(2,OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
}

void mq136() {
  mq136_value = analogRead(mq136_pin);                  //MQ-136 NIN DONDURDUGU DEGERI DEGISKENE VERIYORUZ
  Serial.println("--MQ136--: " + String(mq136_value));  //VERIYI EKRANA YAZDIRIYORUZ
}

void mq135() {
  mq135_value = analogRead(mq135_pin);               //MQ-135 IN DONDURDUGU DEGERI DEGISKENE VERIYORUZ
  Serial.println("MQ-135: " + String(mq135_value));  //VERIYI EKRANA YAZDIRIYORUZ
}

void mq4() {
  mq4_value = analogRead(mq4_pin);               //MQ-4 IN DONDURDUGU DEGERI DEGISKENE VERIYORUZ
  Serial.println("MQ-4: " + String(mq4_value));  //VERIYI EKRANA YAZDIRIYORUZ
}

void screen() {
  lcd.clear();

  //MQ_136
  lcd.setCursor(0, 0);
  lcd.print("MQ_136: ");
  lcd.setCursor(7,0);
  lcd.print(mq136_value);

  //MQ_135
  lcd.setCursor(0, 1);
  lcd.print("MQ_135:");
  lcd.setCursor(7,1);
  lcd.print(mq135_value);
}

void loop() {

  if(first_boot == true) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("ILK ACILISTA 24S");
    lcd.setCursor(0,1);
    lcd.print("ISINMA BEKLENIYOR");

    delay(5000);

    first_boot = false; // Bir kez çalıştıktan sonra false yap ki döngüye girmesin
  }

  digitalWrite(2,HIGH);

  delay(1000);
  //mq4();
  mq135();
  mq136();
  screen();
}
