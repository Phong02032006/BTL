
# BTL

# 🕹️ Game Pong – Bài tập lớn môn Lập trình Nâng Cao

Đây là sản phẩm game **Pong cổ điển** được lập trình bằng **C++** và thư viện **SDL2**.  
Game được phát triển như một bài tập lớn cho môn *Lập trình Nâng Cao*.

---
## 🎓 Thông tin tác giả

- **Họ tên**: Nguyễn Tiên Phong  
- **MSV**: 24022823
- **Môn học**: Lập trình nâng cao  
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
  - Sau khi kết thúc game sẽ reset,có thể bấm ESC để out ra menu và tiếp tục chơi

- **Âm thanh & hình ảnh**:
  - Nhạc nền
  - Âm thanh va chạm, click chuột
  - Giao diện đơn giản, dễ thao tác
 
- **Hiệu ứng hover trong menu**:
  - Các nút bấm trong menu chính (PVP, PVE, Quit) sẽ có hiệu ứng hover khi di chuột qua.
  - Viền của các nút sẽ được làm sáng lên khi hover để người chơi dễ dàng nhận diện lựa chọn.
  - Tính năng này giúp cải thiện trải nghiệm người dùng và làm cho giao diện trở nên trực quan hơn.

- **Thiết kế hướng đối tượng**:
  - Các class chính:  `Ball`, `Paddle`,`Bot`,`Menu`

---

## 🛠️ Yêu cầu cài đặt

Cần cài đặt các thư viện sau:

- `SDL2`
- `SDL2_image`
- `SDL2_mixer`
- `SDL2_ttf`
## ⬇️ Cách tải game

### 🟢 Cách 1: **Tải game không bao gồm source code**
- Tải file nén `.zip`, sau đó giải nén và chạy file `.exe` để chơi game.
- Link tải:  
  👉 [Tải tại đây (Google Drive)](https://drive.google.com/drive/folders/1UIkwJcgel3I4fHCtVg6-SCQrzOe1ukbm?fbclid=IwY2xjawGNvh5leHRuA2FlbQIxMAABHVQj4-ITpUksVDAW7LuHvUW8AZk0N7DjVy5Wy0cTr7OaNA47_cQicOzuvA_aem_EvZzzuGsjMeY5ZW7llLD7g)

---

### 🔵 Cách 2: **Tải game kèm theo mã nguồn (source code)**
1. Clone repository này về bằng Visual Studio  
   *(hoặc chọn **Code → Download ZIP**).*
2. Mở project trong Visual Studio.
3. Nhấn `Ctrl + Alt + L` để mở **Solution Explorer**.
4. Mở các thư mục `Source Files` và `Header Files` để xem code.
5. Nhấn `Ctrl + F5` để chạy chương trình.

---


## 📂 Cấu trúc thư mục 

```
pong-game/
├── assets/           # Ảnh, âm thanh, nhạc nền
├── Ball.cpp / Ball.h
├── Paddle.cpp / Paddle.h
└──Menu.cpp/Menu.h
└──Bot.cpp/Bot.h
├── main.cpp
└── README.md

```

---
## 🎬 Video demo

https://www.youtube.com/watch?v=EWVXdvxMs1k&list=PLhl0hMaBZsIyVEbiKiRU9pCMK9S5j0cHE&index=2
---

## 📌 Ghi chú thêm

- Game sử dụng **SDL2** để xử lý đồ họa, âm thanh và sự kiện bàn phím.
- AI trong chế độ chơi với máy phản ứng theo vị trí bóng.
- Có thể mở rộng thêm hiệu ứng, tăng độ khó hoặc thêm tùy chọn chơi mạng trong tương lai.

---

### 📄 Về source code của game:

- **Ball.cpp** và **Ball.h**:  
  Định nghĩa và triển khai lớp **Ball**, quản lý chuyển động và va chạm của bóng.

- **Paddle.cpp** và **Paddle.h**:  
  Định nghĩa và triển khai lớp **Paddle**, xử lý điều khiển và hiển thị paddle của người chơi.

- **Bot.cpp** và **Bot.h**:  
  Định nghĩa và triển khai lớp **Bot**, điều khiển paddle của máy (**AI**) trong chế độ chơi với máy.

- **Menu.cpp** và **Menu.h**:  
  Quản lý giao diện **menu chính** và **menu tạm dừng** trong game, hiển thị các nút để người chơi tương tác.

- **main.cpp**:  
  Chứa hàm **main()**, khởi tạo trò chơi, tạo cửa sổ game, quản lý vòng lặp chính và xử lý các input từ bàn phím.

- **Thư mục assets/**:  
  Lưu trữ các tài nguyên như **âm thanh** và **hình ảnh** cho trò chơi.

---
## 📈 Ngưỡng điểm đề xuất: **7.5 – 8.0**

---

## 🔍 Lý do đề xuất ngưỡng điểm

- Dự án được phát triển với **sự hỗ trợ từ công cụ AI**, tuy nhiên em đã:
  - **Hiểu được cấu trúc code** và các class chính như `Ball`, `Paddle`, `Bot`, `Menu`.
  - **Tự tìm hiểu cách tích hợp** nhạc nền, hiệu ứng âm thanh, hiệu ứng hover cho menu.
  - **Tự chỉnh sửa logic bot** và tổ chức lại menu theo hướng rõ ràng và dễ dùng hơn.
  - **Triển khai các tính năng** như menu pause (`ESC`), reset game, điều khiển bằng bàn phím.
- Tự học cách sử dụng và cài đặt **thư viện SDL2 và các thành phần liên quan** (`SDL2_image`, `SDL2_mixer`, `SDL2_ttf`).
- Đã làm video demo và tổ chức repo đầy đủ tài liệu, file chạy và mã nguồn.
- Update  game thường xuyên hàng tuần.
---


🎉 **Cảm ơn thầy đã xem qua sản phẩm của em!**
