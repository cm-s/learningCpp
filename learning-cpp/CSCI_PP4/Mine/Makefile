CXX = g++ -std=c++17
TARGET = adv_game
#CXXFLAGS = (-std=c++11)(-I ./external/)

$(TARGET): adv_game.o objs.o console_reader.o
	$(CXX) -o adv_game adv_game.o objs.o console_reader.o

adv_game.o: adv_game.cpp ./external/objs.h ./external/console_reader.h
	$(CXX) -c adv_game.cpp

objs.o: ./external/objs.h ./external/objs.cpp ./external/cm.std.cpp
	$(CXX) -c ./external/objs.h ./external/objs.cpp ./external/cm.std.cpp

console_reader.o: ./external/console_reader.cpp ./external/console_reader.h
	$(CXX) -c ./external/console_reader.cpp

clean:
	rm *.o
