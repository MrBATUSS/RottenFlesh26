#include <Arduino.h>
#include <Wire.h>
#include <lib/LiquidCrystal_I2C-1.1.2/LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// SENSORLER
int mq135_pin = A0; // ANALOG 1 MQ-135
int mq136_pin = A1; // ANALOG 2 MQ-136
int buzzer_pin = 3;

// VERILER
int mq136_value, mq136_maxValue = 100;
int mq135_value, mq135_maxValue = 100;

float mq135_base = 0; // Ortamın normal MQ135 değeri
float mq136_base = 0; // Ortamın normal MQ136 değeri

int heat_time = 180; // 3 DAKIKA 180 SANIYE

// FLAGS
bool DEV_MOD = true;

void setup()
{
  Serial.begin(9600);

  pinMode(mq135_pin, INPUT);
  pinMode(mq136_pin, INPUT);
  pinMode(buzzer_pin, OUTPUT);

  lcd.init();
  lcd.backlight();

  digitalWrite(buzzer_pin, HIGH);
  delay(500);
  digitalWrite(buzzer_pin, LOW);

  if (!DEV_MOD)
  {
    for (int i = heat_time; i > 0; i--)
    {
      int min = i / 60;
      int sec = i % 60;

      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Heating Up...");

      lcd.setCursor(0, 1);
      lcd.print("Pls Wait: ");

      if (min < 10)
        lcd.print("0");
      lcd.print(min);

      lcd.print(":");

      if (sec < 10)
        lcd.print("0");
      lcd.print(sec);

      delay(1000);
    }
  }

  lcd.clear();
  lcd.print("Ready to Test!");
  delay(2000);
  lcd.clear();
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
  lcd.print("Calibrating...");

  float total135 = 0;
  float total136 = 0;
  int sample_count = 50;

  for (int i = 0; i < sample_count; i++)
  {
    total135 += analogRead(mq135_pin); // Değerleri üst üste ekle
    total136 += analogRead(mq136_pin);

    // İlerleme çubuğu gibi bir görsel (isteğe bağlı)
    lcd.setCursor(0, 1);
    lcd.print("Progress: %");
    lcd.print((i * 100) / sample_count);

    delay(100); // Okumalar arasında kısa bir duraksama
  }

  mq135_base = total135 / sample_count;
  mq136_base = total136 / sample_count;

  mq135_maxValue = mq135_base * 1.30;
  mq136_maxValue = mq136_base * 1.30;

  lcd.clear();
  lcd.print("Done!");
  delay(1000);
}

void loop()
{
  mq136_value = analogRead(mq136_pin);
  mq135_value = analogRead(mq135_pin);

  if (!DEV_MOD)
  {
    lcd.setCursor(0, 1);

    if (mq135_value > (mq135_base * 1.45) || mq136_value > (mq136_base * 1.45))
    {
      lcd.print("DURUM: SAKINCALI");
      alarm();
    }
    else if (mq135_value >= mq135_maxValue || mq136_value >= mq136_maxValue)
    {
      lcd.print("DURUM: RİSKLİ");
      digitalWrite(buzzer_pin, HIGH);
      delay(100);
      digitalWrite(buzzer_pin, LOW);
    }
    else
    {
      lcd.print("Durum: Taze");
    }
  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.print("V135:");
    lcd.print(mq135_value);
    lcd.print("  ");
    lcd.setCursor(8, 0);
    lcd.print("V136:");
    lcd.print(mq136_value);
    lcd.print("  ");
  }
  delay(1000);
}
