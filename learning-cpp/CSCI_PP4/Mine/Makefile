CXX = g++
TARGET = adv_game
#CXXFLAGS = (-std=c++11)(-I ./external/)

#adv_game is the consolidated compilation of both object files created in the "adv_game.o" instruction below.
$(TARGET): adv_game.o player_enemy.o console_reader.o
	$(CXX) -std=c++11 -o adv_game adv_game.o objs.o console_reader.o

#the objectification of adv_game.cpp with path to the header included in the instructions (line 7)
#I do not know why the header is included in the "instructions".
adv_game.o: adv_game.cpp ./external/objs.h ./external/console_reader.h
	$(CXX) -std=c++11 -c adv_game.cpp

#defines the compilation process of the player_enemy header file.
#the player_enemy.cpp file isn't included in the compilation process because it is linked within the header.
player_enemy.o: ./external/objs.cpp ./external/objs.h
	$(CXX) -std=c++11 -c ./external/objs.cpp

console_reader.o: ./external/console_reader.cpp ./external/console_reader.h
	$(CXX) -std=c++11 -c ./external/console_reader.cpp

clean:
	rm adv_game.o
	rm objs.o
	rm console_reader.o
