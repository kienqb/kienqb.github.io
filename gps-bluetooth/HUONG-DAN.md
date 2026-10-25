# ESP32 + u-blox NEO-M10: Module GPS Bluetooth phát NMEA về điện thoại

## 1. Linh kiện cần
- ESP32 DevKit (DOIT, NodeMCU-32S... bản nào cũng được)
- Module u-blox NEO-M10N (board breakout, kèm anten GPS)
- 4 dây Dupont cái–cái + cáp USB để nạp code

## 2. Sơ đồ đấu dây

| NEO-M10 | → | ESP32 |
|---|---|---|
| VCC | → | 3V3 |
| GND | → | GND |
| TX | → | GPIO16 (RX2) |
| RX | → | GPIO17 (TX2) |

```
 NEO-M10N board              ESP32 DevKit
 ┌───────────┐              ┌───────────┐
 │ VCC       ├──────────────┤ 3V3       │
 │ GND       ├──────────────┤ GND       │
 │ TX        ├──────────────┤ GPIO16    │  (RX2)
 │ RX        ├──────────────┤ GPIO17    │  (TX2)
 └───────────┘              └───────────┘
        TX-RX đấu CHÉO nhau (TX→RX, RX→TX)
```

**Lưu ý quan trọng:**
- Chân GPIO của ESP32 chỉ chịu 3.3V — tuyệt đối không đưa 5V vào GPIO.
- Board NEO-M10N thường chịu nguồn 3.3–5V ở chân VCC (có ổn áp sẵn), nhưng TX/RX là logic 3.3V → nối thẳng ESP32 an toàn, không cần chuyển mức.

## 3. Nạp code
1. Arduino IDE → Boards Manager → cài **"esp32 by Espressif"** (bản mới).
2. Chọn board: **ESP32 Dev Module**.
3. Mở file `GPS_BT_Bridge/GPS_BT_Bridge.ino` → nạp.
4. Mở Serial Monitor (115200) để xem log khởi động.

## 4. Kết nối điện thoại (Android)
1. Bật Bluetooth → pair với thiết bị **`NEO-M10_GPS`**.
2. Cài app **Serial Bluetooth Terminal** → Connect → sẽ thấy các dòng `$GNGGA`, `$GNRMC`... chạy liên tục.
3. Muốn dùng GPS này cho app bản đồ/dẫn đường: cài app **Bluetooth GPS** → bật Mock location trong Developer options → chọn nguồn Bluetooth GPS.
4. Để module ở nơi thoáng, thấy trời. Lần đầu (cold start) mất khoảng 30 giây – 2 phút mới bắt được vệ tinh.

## 5. iPhone?
iOS **không hỗ trợ** Bluetooth Classic (SPP) nên code này chỉ dùng cho Android. Nếu bạn dùng iPhone, mình làm thêm bản BLE (Nordic UART Service) — cứ báo nhé.

## 6. Xử lý sự cố
- **Không thấy câu NMEA / chữ loạn trên điện thoại:** code dùng **baud cố định 38400** (mặc định gốc của NEO-M10). Nếu chữ loạn, khả năng module của bạn đã bị đổi baud (ví dụ về 9600) — kiểm tra bằng USB-TTL + Serial Monitor, baud nào hiện chữ `$GN...` rõ ràng thì đó là baud của module; sửa `GPS_BAUD` trong code cho khớp rồi nạp lại. Cũng kiểm tra đấu dây TX/RX (phải đấu chéo). Muốn xem luồng NMEA trực tiếp trên máy tính: đổi `DEBUG_ECHO` thành 1 trong code rồi nạp lại.
- **Không pair được:** thử PIN `1234` hoặc `0000`; hoặc bỏ comment dòng `SerialBT.setPin(...)` để tự đặt PIN.
- **GPS mãi không fix:** anten phải thấy bầu trời — trong nhà/bê tông dày sẽ không bắt được sóng.
- **Muốn đổi tên Bluetooth:** sửa `BT_NAME` trong code rồi nạp lại.
