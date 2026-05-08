#include <Arduino.h>
#include <Wire.h>
#include <lib/LiquidCrystal_I2C-1.1.2/LiquidCrystal_I2C.h> // Orijinal kütüphane yolu korundu

LiquidCrystal_I2C lcd(0x27, 16, 2);

// SENSORLER (Sabit tanımlamalar RAM tasarrufu sağlar)
const uint8_t mq135_pin = A0; 
const uint8_t mq136_pin = A1; 
const uint8_t buzzer_pin = 3;

// VERILER
int mq136_value;
int mq135_value;
int mq136_maxValue = 100;
int mq135_maxValue = 100;

float mq135_base = 0; 
float mq136_base = 0; 

const int heat_time = 180; // Isınma: 3 DAKIKA 180 SANIYE
const int cal_time = 180;  // Kalibrasyon: 3 DAKIKA 180 SANIYE

// FLAGS
bool DEV_MOD = false;

void alarm();
void calibrating();

void setup()
{
  Serial.begin(9600);

  pinMode(mq135_pin, INPUT);
  pinMode(mq136_pin, INPUT);
  pinMode(buzzer_pin, OUTPUT);

  lcd.init();
  lcd.backlight();

  // Açılış sinyali
  digitalWrite(buzzer_pin, HIGH);
  delay(500);
  digitalWrite(buzzer_pin, LOW);

  if (!DEV_MOD)
  {
    for (int i = heat_time; i > 0; i--)
    {
      int minutes = i / 60;
      int seconds = i % 60;

      lcd.setCursor(0, 0);
      lcd.print("Isiniyor...     ");
      lcd.setCursor(0, 1);
      lcd.print("Lutfen Bekle: ");

      // Dakika formatı
      if (minutes < 10) {
        lcd.print("0");
        Serial.print("0");
      }
      lcd.print(minutes);
      Serial.print(minutes);
      Serial.print(":");
      lcd.print(":");

      // Saniye formatı
      if (seconds < 10) {
        lcd.print("0");
        Serial.print("0");
      }
      lcd.print(seconds);
      Serial.println(seconds);

      delay(1000);
    }
    
    lcd.clear();
    lcd.print("Isinma Tamam!");
    Serial.println("--- ISINMA TAMAMLANDI ---");
    delay(2000);
    
    calibrating();
  }
}

void alarm()
{
  for (int i = 0; i < 6; i++)
  {
    digitalWrite(buzzer_pin, HIGH);
    delay(150);
    digitalWrite(buzzer_pin, LOW);
    delay(150);
  }
}

void calibrating()
{
  lcd.clear();
  lcd.print("Kalibre Ediliyor");
  
  Serial.println("\n--- KALIBRASYON BASLIYOR ---");
  Serial.println("Sure: 3 Dakika (180 Saniye)");
  Serial.println("Saniye saniye orneklem aliniyor...");

  float total135 = 0;
  float total136 = 0;
  int sample_count = cal_time; // 180 örnek (her saniye 1 örnek)

  for (int i = 0; i < sample_count; i++)
  {
    int current_135 = analogRead(mq135_pin);
    int current_136 = analogRead(mq136_pin);
    
    total135 += current_135; 
    total136 += current_136;

    int progress = ((i + 1) * 100) / sample_count;

    // LCD Ekran Güncellemesi
    lcd.setCursor(0, 1);
    lcd.print("Ilerleme: %");
    if(progress < 10) lcd.print("0"); 
    if(progress < 100 && progress >= 10) lcd.print(""); // Yüzde hizalaması
    lcd.print(progress);
    lcd.print("  "); // Eski yazıları silmek için padding

    // Serial Port Debug Bilgilendirmesi
    Serial.print("Kalibrasyon [");
    if(progress < 10) Serial.print("0"); // Görsel hizalama
    Serial.print(progress);
    Serial.print("%] | Saniye: ");
    Serial.print(i + 1);
    Serial.print("/");
    Serial.print(sample_count);
    Serial.print(" | Anlik MQ135: ");
    Serial.print(current_135);
    Serial.print(" - Anlik MQ136: ");
    Serial.println(current_136);

    delay(1000); // Saniyede 1 okuma yaparak tam 180 saniye geçir
  }

  // Ortalamaları Hesaplama
  mq135_base = total135 / sample_count;
  mq136_base = total136 / sample_count;

  // Eşik Değerleri Belirleme (%30 tolerans)
  mq135_maxValue = mq135_base * 1.30;
  mq136_maxValue = mq136_base * 1.30;

  // Kalibrasyon Sonucu Debug Çıktısı
  Serial.println("\n--- KALIBRASYON TAMAMLANDI ---");
  Serial.print("MQ-135 Ortam Taban Degeri: "); 
  Serial.println(mq135_base);
  Serial.print("MQ-135 Risk Siniri (Max):  "); 
  Serial.println(mq135_maxValue);
  Serial.println("--------------------------------");
  Serial.print("MQ-136 Ortam Taban Degeri: "); 
  Serial.println(mq136_base);
  Serial.print("MQ-136 Risk Siniri (Max):  "); 
  Serial.println(mq136_maxValue);
  Serial.println("--------------------------------\n");

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Kalibrasyon");
  lcd.setCursor(0,1);
  lcd.print("Tamamlandi!");
  delay(2000);
  lcd.clear();
}

void loop()
{
  mq136_value = analogRead(mq136_pin);
  mq135_value = analogRead(mq135_pin);

  if (!DEV_MOD)
  {
    lcd.setCursor(0, 0);
    lcd.print("Hava Kalitesi:");

    lcd.setCursor(0, 1);

    // Sakıncalı durum için %45 tolerans sınırı
    float mq135_danger = mq135_base * 1.45;
    float mq136_danger = mq136_base * 1.45;

    if (mq135_value > mq135_danger || mq136_value > mq136_danger)
    {
      lcd.print("DURUM: SAKINCALI"); 
      Serial.println("DURUM: SAKINCALI");
      alarm();
    }
    else if (mq135_value >= mq135_maxValue || mq136_value >= mq136_maxValue)
    {
      lcd.print("DURUM: RISKLI   "); 
      Serial.println("DURUM: RISKLI");
      digitalWrite(buzzer_pin, HIGH);
      delay(100);
      digitalWrite(buzzer_pin, LOW);
    }
    else
    {
      lcd.print("DURUM: TAZE     "); 
      Serial.println("DURUM: TAZE");
    }
  }
  else
  {
    // Developer Mod
    lcd.setCursor(0, 0);
    lcd.print("V135: ");
    lcd.print(mq135_value);
    lcd.print("   "); 
    
    lcd.setCursor(0, 1);
    lcd.print("V136: ");
    lcd.print(mq136_value);
    lcd.print("   ");

    Serial.print("MQ-135: ");
    Serial.print(mq135_value);
    Serial.print(" | MQ-136: ");
    Serial.println(mq136_value);
  }
  
  delay(1000);
}