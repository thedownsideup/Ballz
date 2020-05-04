all: main.o Game.o MainMenu.o Scoreboard.o NameEditor.o Playground.o Ball.o LifeBall.o FirePower.o FireBall.o Bomb.o GameOver.o Brick.o Button.o Point.o rsdl.o
	g++ main.o Game.o MainMenu.o Scoreboard.o NameEditor.o Playground.o Ball.o LifeBall.o FirePower.o FireBall.o Bomb.o GameOver.o Brick.o Button.o Point.o rsdl.o -o awesomBirikBereker -l SDL2 -l SDL2_image -l SDL2_ttf

clean: clear all

clear:
	rm *.o

main.o: src/main.cpp
	g++ -c src/main.cpp

MainMenu.o: src/MainMenu.cpp
	g++ -c src/MainMenu.cpp

Game.o: src/Game.cpp
	g++ -c src/Game.cpp

Scoreboard.o: src/Scoreboard.cpp
	g++ -c src/Scoreboard.cpp

Button.o: src/Button.cpp
	g++ -c src/Button.cpp

NameEditor.o: src/NameEditor.cpp
	g++ -c src/NameEditor.cpp

Playground.o: src/Playground.cpp
	g++ -c src/Playground.cpp

GameOver.o: src/GameOver.cpp
	g++ -c src/GameOver.cpp

Ball.o: src/Ball.cpp
	g++ -c src/Ball.cpp

Brick.o: src/Brick.cpp
	g++ -c src/Brick.cpp

LifeBall.o: src/LifeBall.cpp
	g++ -c src/LifeBall.cpp

FirePower.o: src/FirePower.cpp
	g++ -c src/FirePower.cpp

FireBall.o: src/FireBall.cpp
	g++ -c src/FireBall.cpp

Bomb.o: src/Bomb.cpp
	g++ -c src/Bomb.cpp

Point.o: src/Point.cpp
	g++ -c src/Point.cpp

rsdl.o: src/RSDL/src/rsdl.cpp src/RSDL/src/rsdl.hpp
	g++ -c src/RSDL/src/rsdl.cpp