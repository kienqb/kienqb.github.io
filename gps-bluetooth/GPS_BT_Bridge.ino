/*
 * ESP32 + u-blox NEO-M10 -> Bluetooth GPS Bridge  (v3)
 * ------------------------------------------------
 * ESP32 doc cau NMEA tu module GPS NEO-M10 qua UART (Serial2)
 * roi phat qua Bluetooth Classic (SPP) cho dien thoai.
 * Dung duoc voi app Android: "Serial Bluetooth Terminal",
 * "Bluetooth GPS", "GPS Connector"...
 *
 * Diem chinh cua v3:
 *  - BAUD CO DINH 38400 (mac dinh goc cua NEO-M10), khong tu do nua.
 *  - Chuyen du lieu theo khoi (nhanh, on dinh).
 *  - Chi phat Bluetooth khi dien thoai da ket noi.
 *
 * Dau day:
 *   NEO-M10 VCC -> ESP32 3V3 (hoac 5V tu chan VIN khi ESP32 cam USB)
 *   NEO-M10 GND -> ESP32 GND
 *   NEO-M10 TX  -> ESP32 GPIO16 (RX2)
 *   NEO-M10 RX  -> ESP32 GPIO17 (TX2)
 *
 * Luu y: chan GPIO cua ESP32 chi chiu 3.3V, KHONG dua 5V vao GPIO.
 *         (5V chi duoc phep vao chan NGUON VCC cua board GPS.)
 */

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth chua bat! Hay cai ESP32 core ban moi va chon dung board ESP32.
#endif

#include "BluetoothSerial.h"

// ---------- CAU HINH ----------
#define BT_NAME    "NEO-M10_GPS"  // ten Bluetooth hien tren dien thoai
#define GPS_BAUD   38400          // CO DINH: baud mac dinh goc cua NEO-M10
#define PIN_GPS_RX 16             // ESP32 RX2 <- GPS TX
#define PIN_GPS_TX 17             // ESP32 TX2 -> GPS RX
#define PIN_LED    2              // LED bao: nhay = cho pair, sang dung = da ket noi
#define DEBUG_ECHO 0              // 1 = in luong NMEA ra Serial Monitor (USB) de debug

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);                                        // monitor USB (debug)
  Serial2.begin(GPS_BAUD, SERIAL_8N1, PIN_GPS_RX, PIN_GPS_TX); // UART noi GPS (38400 co dinh)

  pinMode(PIN_LED, OUTPUT);

  // SerialBT.setPin("1234"); // bo comment neu muon dat ma PIN khi pair
  SerialBT.begin(BT_NAME);     // bat Bluetooth, che do slave (cho dien thoai ket noi)

  Serial.println();
  Serial.println("Bluetooth GPS bridge started (baud GPS co dinh 38400)");
  Serial.print("Pair dien thoai voi: ");
  Serial.println(BT_NAME);
}

void loop() {
  // GPS -> Bluetooth: day theo khoi, chi khi dien thoai da ket noi
  if (SerialBT.connected()) {
    uint8_t buf[128];
    size_t n = 0;
    while (Serial2.available() && n < sizeof(buf)) {
      buf[n++] = (uint8_t)Serial2.read();
    }
    if (n > 0) {
      SerialBT.write(buf, n);
#if DEBUG_ECHO
      Serial.write(buf, n);
#endif
    }
  } else {
    // Chua co dien thoai ket noi: xa bot de khong tran buffer UART
    while (Serial2.available()) Serial2.read();
  }

  // Bluetooth -> GPS: cho phep gui lenh cau hinh tu dien thoai (vd: u-center qua BT)
  while (SerialBT.available()) {
    Serial2.write(SerialBT.read());
  }

  // LED bao trang thai ket noi
  static unsigned long lastBlink = 0;
  if (SerialBT.connected()) {
    digitalWrite(PIN_LED, HIGH);                  // sang dung = da ket noi
  } else if (millis() - lastBlink > 500) {
    digitalWrite(PIN_LED, !digitalRead(PIN_LED)); // nhay = dang cho pair
    lastBlink = millis();
  }

  delay(1); // nhuong CPU cho stack Bluetooth
}
