# Đặt tên cho file thực thi
TARGET = a

# Các file nguồn
SRCS = Owners.cpp ParkingLots.cpp Registrations.cpp Vehicles.cpp main.cpp Accounts.cpp

# Các file đối tượng (chuyển đổi từ .cpp sang .o)
OBJS = $(SRCS:.cpp=.o)

# Các tùy chọn biên dịch
CFLAGS = -Wall -g

# Quy tắc mặc định
all: $(TARGET)

# Quy tắc để tạo file thực thi từ các file đối tượng
$(TARGET): $(OBJS)
	g++ -o $@ $^

# Quy tắc để biên dịch các file nguồn thành file đối tượng
%.o: %.cpp
	g++ $(CFLAGS) -c $< -o $@

# Quy tắc để xóa các file đối tượng và file thực thi
clean:
	rm -f $(OBJS) $(TARGET)
