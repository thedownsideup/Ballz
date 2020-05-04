#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "RSDL/src/rsdl.hpp"
#include "Style.hpp"
#include "Game.hpp"
#include "Ball.hpp"
#include "Point.hpp"
#include "Brick.hpp"
#include "LifeBall.hpp"
#include "FireBall.hpp"
#include "FirePower.hpp"
#include "Bomb.hpp"
#include "Controls.hpp"

const int BALL_RADIUS = 15;
const int BRICK_WIDTH = 110;
const int BRICK_HEIGHT = 55;
const float STARTING_ANGLE = 180;
const std::string ARROW_IMG = "assets/arrow.png";
const int ARROW_SIZE = 70;
const float PI = 3.14;
const int TIME_INTERVAL = 60;
const int BALL_SPEED = 5;
const int COLUMNS = 5;
const int BRICK_SPACING = 5;
const int LIFEBALL_RADIUS = 20;
const int FIREPOWER_RADIUS = 20;


class Playground
{
private:
	Game* game;
	std::vector<Ball> balls;
	std::vector<Brick> bricks;
	std::vector<LifeBall> lifeballs;
	std::vector<FirePower> fireballs;
	std::vector<Bomb> bombs;
	FireBall* fireball;
	Point position;
	float angle;
	float velocityX, velocityY;
	bool shooting;
	bool canShoot;
	int cameBack;
	int shootCount;
	int timeSinceLastShot;
	int score;
	int shooted;
	int lifeballHits;
	bool firepowerHit;
	bool fire;
	bool targetting;

	void hitWall(Ball* ball);
	void hitBirik(Ball* ball);
	void killBirik();
	void addRow();
	void lose();
	void hitLifeBall(Ball* ball);
	void addBalls();
	void hitFireBall(Ball* ball);
	void hitBomb(Ball* ball);
	void shoot();
	bool isAround(Point pos1, Point pos2);
	void explode(Point pos);

public:
	Playground(Game *owner);
	void update(Event* event);
	void draw(Window* window);
	void loadNewGame();
	std::string convertIntegerToString(int stringWannaBe);
};
 #endif