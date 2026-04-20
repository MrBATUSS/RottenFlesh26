//SENSORLER
int mq4_pin = A0;    //ANALOG 0 MQ-4
int mq135_pin = A1;  //ANALOG 1 MQ-135
//int mq136_pin = A2;  //ANALOG 2 MQ-136
int energy = 13;

//RGB_LED
int redPin = 10;
int greenPin = 9;
int bluePin = 8;

//VERILER
int mq135_value;
int mq4_value;

void setup() {
  Serial.begin(9600);                            //BILGISAYAR ILE ILETISIMI **9600 HIZINDA** BASLATIYORUZ BURDAN GELEN VERILERI OKUYCAZ
  pinMode(mq4_pin & mq135_pin, INPUT);           //PINLERI INPUT(GIRIS) MODUNA ALIYORUZ SENSORLER KARTA VERI AKISI VEREBILMASI ICIN
  pinMode(redPin & greenPin & bluePin & energy, OUTPUT);  //LEDIN BAGLI OLDUGU DIGITAL PINLERI OUTPUT(CIKIS) MODUNA ALIYORUZ BURDAN KART KOSULLAR SAGLANDIĞINDA(0,1) VOLTAJ VERECEK
}

void mq135() {
  mq135_value = analogRead(mq135_pin);               //MQ-135 IN DONDURDUGU DEGERI DEGISKENE VERIYORUZ
  Serial.println("MQ-135: " + String(mq135_value));  //VERIYI EKRANA YAZDIRIYORUZ
  //FALAN FILAN - REDD
}

void mq4() {
  mq4_value = analogRead(mq4_pin);               //MQ-4 IN DONDURDUGU DEGERI DEGISKENE VERIYORUZ
  Serial.println("MQ-4: " + String(mq4_value));  //VERIYI EKRANA YAZDIRIYORUZ
  //FALAN FILAN - REDD
}

void loop() {
  // GENEL ALGORİTMA
  delay(500);  // TAZELEME MIZI (MS)
  mq4();
  mq135();
}
