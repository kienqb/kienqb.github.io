# Kiên Nguyễn — Các dự án linh tinh

Trang cá nhân của **Kiên Nguyễn** (Quảng Bình) — nơi tổng hợp các dự án tự làm: website, ứng dụng và đồ điện tử DIY. Mọi thứ ở đây đều do mình tự mày mò xây dựng phục vụ công việc và sở thích.

👉 **Xem trang tại: https://kienqb.is-a.dev**

---

## 🚕 Taxi Quảng Bình

Website dịch vụ taxi tại Đồng Hới, Quảng Bình.

- Đặt xe 4 / 7 / 16 chỗ, phục vụ 24/7
- Đưa đón sân bay Đồng Hới, đi Phong Nha – Kẻ Bàng và các tuyến liên tỉnh
- Hotline: **0787 33 73 73**
- Website: [quangbinhtaxi.com](https://quangbinhtaxi.com)

## 🦀 Hải Sản Hồng Lài

Cửa hàng hải sản tại Quảng Bình, giao hàng toàn quốc.

- Mặt hàng chính: Tôm Hùm, Tôm Sú, Tôm Bạc, Cá Mú, Ghẹ Xanh, Ghẹ Đỏ…
- Nhận đơn qua Zalo: **0865 777 073**
- Kèm theo là hệ thống quản lý bán hàng và công nợ tự xây dựng cho cửa hàng (ghi bán hàng, theo dõi công nợ khách, doanh thu ngày/tuần/tháng, tự sao lưu dữ liệu hằng ngày): [honglai.quangbinhtaxi.com](https://www.honglai.quangbinhtaxi.com)

## 🎵 Dex Music

Ứng dụng Android nghe nhạc lấy nguồn từ các kênh share nhạc trên Telegram, tự viết để dùng trên đầu Android ô tô.

- Đăng nhập bằng chính tài khoản Telegram của người dùng (số điện thoại + mã OTP)
- Nghe nhạc từ kênh mặc định hoặc tự thêm nguồn bằng @username / link kênh
- Vừa tải vừa phát, có bộ nhớ đệm trong phiên nghe; phát nền, điều khiển qua thông báo và qua nút cứng trên ô tô (qua bài / lùi bài / dừng phát)
- Yêu thích, danh sách phát tự tạo, danh sách chờ phát chọn nhanh ngay trong trình phát
- Chỉnh EQ theo dải tần + tăng bass, hiệu ứng cột phổ nhạc cầu vồng nhảy theo nhạc thật
- Phiên bản hiện tại: **1.44** — Android 6.0 trở lên
- ⬇ **[Tải APK 1.44 (25 MB)](https://github.com/kienqb/kienqb.github.io/releases/download/dex-music-v1.44/dex-music-v1.44.apk)**

## 🛰️ Module GPS Bluetooth

Dự án DIY định vị: **ESP32 + u-blox NEO-M10**.

- ESP32 đọc dữ liệu từ module GPS NEO-M10 rồi phát câu NMEA về điện thoại qua Bluetooth SPP (tên thiết bị `NEO-M10_GPS`)
- Tốc độ truyền cố định **38400 baud**, bắt được GPS + BeiDou + Galileo (đã test: fix 3D với 8 vệ tinh)
- Dùng kèm app vị trí giả lập (mock location) để Google Maps và các app bản đồ dùng tín hiệu GPS ngoài chính xác hơn GPS của máy
- ⬇ **[Tải code ESP32 + hướng dẫn (.zip)](https://kienqb.is-a.dev/gps-bluetooth/gps-bluetooth-esp32-neo-m10.zip)** — trong zip gồm file code `GPS_BT_Bridge.ino` và file hướng dẫn đấu nối/cài đặt

## 📺 TV Launcher Mod

Bản mod giao diện màn hình chính (launcher) cho Android TV Sony, phát triển và kiểm thử trên **Sony BRAVIA KD-55X7500F (Android 9)**.

- Giao diện gọn nhẹ: lời chào, dock ứng dụng tùy chỉnh, font Be Vietnam Pro, đặt được hình nền cá nhân
- Khóa mở máy bằng **mã TOTP 6 số đổi mỗi 30 giây** (kiểu Google Authenticator) kèm mã dự phòng; hết phiên xem phải nhập lại mã
- Bản chia sẻ (share) dùng giao diện và lời chào mặc định, credit *Mod by Kiên Nguyễn*
- ⬇ **[Tải bản share (APK)](https://kienqb.is-a.dev/tv-launcher/launcher-tvhome-share.apk)**

---

## Tải xuống nhanh

| Dự án | File | Link |
|---|---|---|
| Dex Music 1.44 | APK Android (25 MB) | [Tải về](https://github.com/kienqb/kienqb.github.io/releases/download/dex-music-v1.44/dex-music-v1.44.apk) |
| Module GPS Bluetooth | Code ESP32 + hướng dẫn (.zip) | [Tải về](https://kienqb.is-a.dev/gps-bluetooth/gps-bluetooth-esp32-neo-m10.zip) |
| TV Launcher Mod | APK bản share | [Tải về](https://kienqb.is-a.dev/tv-launcher/launcher-tvhome-share.apk) |

## Cấu trúc thư mục

- `index.html` — trang chủ của site
- `dex-music/` — file APK của app Dex Music
- `gps-bluetooth/` — code ESP32, hướng dẫn và bản .zip của module GPS
- `tv-launcher/` — file APK bản share của TV Launcher Mod
- `CNAME` — tên miền riêng kienqb.is-a.dev

---

© 2026 Kiên Nguyễn • Trang cá nhân phục vụ học hỏi và chia sẻ dự án.
