CC = clang++
CFLAGS = -O2 -std=c++20

TARGET = app.exe
OBJS = \
	./out/console/Console.o ./out/logger/BaseLogger.o ./out/logger/ConsoleLogger.o \
	./out/networks/SocketInterfaces.o ./out/networks/Client.o ./out/networks/LinuxSockets.o \
	./out/networks/Server.o ./out/networks/SocketExceptions.o ./out/networks/Buffer.o \
	./out/exceptions/Exceptions.o

dirs:
	mkdir out
	mkdir out/console
	mkdir out/logger
	mkdir out/networks
	mkdir out/exceptions

clean:
	rm -rf *.o *.exe out

app.exe: $(OBJS) ./out/main.o
	$(CC) $(CFLAGS) $^ -o app.exe

./out/main.o: ./main.cpp
	$(CC) $(CFLAGS) -c $< -o ./out/main.o

./out/%.o : ./%.cpp ./%.hpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean dirs
