# RottenFlesh26 – Akıllı Gıda Analiz Sistemi

![Status](https://img.shields.io/badge/status-prototype-orange)
![Platform](https://img.shields.io/badge/platform-PlatformIO-blue)
![Hardware](https://img.shields.io/badge/hardware-Arduino-green)
![Sensors](https://img.shields.io/badge/sensors-MQ135%20%2F%20MQ136-red)

---

## 📌 Proje Özeti
RottenFlesh26, protein bazlı gıdaların (et, tavuk, balık vb.) tazelik durumunu gaz sensörleri ile analiz eden bir prototip sistemdir. Sistem, gıdalardan yayılan uçucu bileşenleri ölçerek kullanıcıya **Taze / Riskli / Sakıncalı** sınıflandırması sunar.

Bu proje eğitim amaçlıdır ve sensör tabanlı çevresel analiz mantığını göstermek için geliştirilmiştir.

---

## 🎯 Amaç
- Gıda güvenliği konusunda farkındalık oluşturmak
- Gaz sensörleri ile çevresel veri analizi yapmak
- Basit eşik tabanlı karar algoritması geliştirmek
- Gömülü sistem mantığını öğrenmek

---

## 🧠 Çalışma Prensibi

```text
Ortam Havası → Kalibrasyon → Sensör Ölçümü → Veri Karşılaştırma → Sınıflandırma → Çıktı
```

---

## 🔬 Sistem Bileşenleri

### 📡 Sensörler
- MQ-135 → Genel hava kalitesi ve gaz değişimleri
- MQ-136 → Kükürt bileşikleri (bozulma göstergesi)

### 🧩 Donanım
- 16x2 LCD ekran (sonuç gösterimi)
- Buzzer (sesli uyarı sistemi)
- Kalibrasyon butonu

---

## ⚙️ Karar Mekanizması
Sistem referans temiz hava değerine göre sapma hesaplar:

- 🟢 Düşük sapma → **Taze**
- 🟡 Orta sapma → **Riskli**
- 🔴 Yüksek sapma → **Sakıncalı**

---

## 📷 Sistem Görseli

> Aşağıdaki görseller proje mimarisi ve sensör yapısını temsil eder.

![Architecture](assets/architecture.png)
![Sensor Setup](assets/sensors.png)
![Device Prototype](assets/device.png)

---

## 🚀 Kurulum (PlatformIO)

```bash
git clone https://github.com/kullaniciadi/RottenFlesh26.git
cd RottenFlesh26
pio run
pio upload
```

---

## ▶️ Kullanım
1. Cihazı açın ve sensörlerin ısınmasını bekleyin
2. Temiz ortamda kalibrasyon butonuna basın
3. Sensörü gıdaya yaklaştırın (temas ettirmeyin)
4. LCD ekrandan sonucu takip edin

---

## ⚠️ Sınırlamalar
- Bu cihaz **tıbbi veya resmi gıda güvenliği cihazı değildir**
- Sensörler sıcaklık ve nemden etkilenebilir
- Sonuçlar yalnızca eğitim ve bilgilendirme amaçlıdır
- %100 doğruluk garanti edilmez

---

## 👨‍💻 Geliştirici
Barbaros Anadolu Lisesi Öğrencileri Harezmi Projesi Ekibi (Bakınız CONTRIBUTORS)

---

## 📬 İletişim
E-posta: iletisim@example.com
