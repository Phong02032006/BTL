<<<<<<< HEAD
# BTL
=======
# 🕹️ Game Pong – Bài tập lớn môn Lập trình Nâng Cao

Đây là sản phẩm game **Pong cổ điển** được lập trình bằng **C++** và thư viện **SDL2**.  
Game được phát triển như một bài tập lớn cho môn *Lập trình Nâng Cao*.

---

## 📌 Giới thiệu tính năng

- **Menu chính** gồm 3 lựa chọn:
  - Chơi 2 người (PVP)
  - Chơi với máy (PVE – Bot)
  - Thoát game

- **Menu tạm dừng** (nhấn phím `ESC` khi đang chơi):
  - Tiếp tục chơi
  - Quay lại menu chính

- **2 chế độ chơi**:
  - 👥 PVP: 2 người chơi trên cùng bàn phím
  - 🤖 PVE: Người chơi đấu với bot tự động

- **Cơ chế game**:
  - Bóng di chuyển và phản xạ khi va vào paddle
  - Ghi điểm và thông báo người thắng khi kết thúc trận
  - Game tự khởi động lại sau khi kết thúc

- **Âm thanh & hình ảnh**:
  - Nhạc nền
  - Âm thanh va chạm, click chuột
  - Giao diện đơn giản, dễ thao tác

- **Thiết kế hướng đối tượng**:
  - Các class chính: `Game`, `Ball`, `Paddle`,`Bot`

---

## 🛠️ Yêu cầu cài đặt

Cần cài đặt các thư viện sau:

- `SDL2`
- `SDL2_image`
- `SDL2_mixer`
- `SDL2_ttf` 
## 🚀 Cách biên dịch và chạy chương trình



## 📂 Cấu trúc thư mục 

```
pong-game/
├── assets/           # Ảnh, âm thanh, nhạc nền
├── Ball.cpp / Ball.h
├── Paddle.cpp / Paddle.h
├── Game.cpp / Game.h
└──Bot.cpp/Bot.h
├── main.cpp
└── README.md

```

---

## 🎓 Thông tin tác giả

- **Họ tên**: Nguyễn Tiên Phong  
- **MSV**: 24028223 
- **Môn học**: Lập trình nâng cao  
---

## 🎬 Video demo

https://www.youtube.com/watch?v=EWVXdvxMs1k

---

## 📌 Ghi chú thêm

- Game sử dụng SDL2 để xử lý đồ họa, âm thanh, và sự kiện bàn phím.
- AI trong chế độ chơi với máy phản ứng theo vị trí bóng.
- Có thể mở rộng thêm hiệu ứng, tăng độ khó hoặc tùy chọn chơi mạng trong tương lai.

---

🎉 **Cảm ơn thầy đã xem qua sản phẩm của em!**
>>>>>>> 6acedac (Update README.md)
