#adv_game is the consolidated compilation of both object files created in the "adv_game.o" instruction below.
adv_game: adv_game.o player_enemy.o
	g++ -o adv_game adv_game.o player_enemy.o

#the objectification of adv_game.cpp with path to the header included in the instructions (line 6)
#I do not know why the header is included in the "instructions".
adv_game.o: adv_game.cpp ./external/player_enemy.h
	g++ -std=c++11 -c adv_game.cpp

#defines the compilation process of the player_enemy header file.
#the player_enemy.cpp file isn't included in the compilation process because it is linked within the header.
player_enemy.o: ./external/player_enemy.cpp ./external/player_enemy.h
	g++ -std=c++11 -c ./external/player_enemy.cpp

clean:
	rm adv_game.o
	rm player_enemy.o
