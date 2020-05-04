#include "Playground.hpp"

Playground::Playground(Game *owner)
{
	game = owner;
	fireball = NULL;
}

void Playground::update(Event* event)
{
	if(cameBack != balls.size())
	{
		if(fire)
		{
			hitWall(fireball);
			hitBirik(fireball);
			hitLifeBall(fireball);
			hitFireBall(fireball);
			hitBomb(fireball);
		}
		for(int i = 0; i < balls.size(); i++)
		{
			hitWall(&balls[i]);
			hitBirik(&balls[i]);
			hitLifeBall(&balls[i]);
			hitFireBall(&balls[i]);
			hitBomb(&balls[i]);
		}
		killBirik();
	}
	else if(!canShoot)
	{
		canShoot = true;
		score++;
		addRow();
		addBalls();
	}
	
	if (shooting == true)
	{
		if(fire)
		{
			fireball->setVelocity(velocityX, velocityY);
			shooting = false;
		}
		timeSinceLastShot += DELAY_TIME;
		if(timeSinceLastShot >= TIME_INTERVAL)
		{
			balls[shootCount].setVelocity(velocityX, velocityY);
			shootCount++;
			timeSinceLastShot = 0;
			if(shootCount == balls.size())
			{
				shooting = false;
			}
		}
	}

	if(fire)
	{
		fireball->update(event);
	}
	else
	{
		for (int i = 0; i < balls.size(); ++i)
		{
			balls[i].update(event);
		}
	}
	
	if(event->type() == KEY_PRESS)
	{
		char btn = event->pressedKey();
		if(btn == RIGHT_BUTTON)
		{
			angle += 5;
			if(angle > 180)
			{
				angle -= 360;
			}
			if(angle >= -98 && angle <= 98)
			{
				angle = -98;
			}
		
		}

		else if(btn == LEFT_BUTTON)
		{
			angle -= 5;
			if(angle <= -180)
			{
				angle += 360;
			}
			if(angle <= 98 && angle >= -98)
			{
				angle = 98;
			}
		
		}
		else if(btn == SPACE_BUTTON && canShoot)
		{
			shoot();
		}
	}
	else if(event->type() == LCLICK && !targetting)
	{
		targetting = true;
	}
	else if(event->type() != NA && targetting)
	{
		angle = -atan2((event->mouseX() - position.x), (event->mouseY() - position.y))*180/PI;
		if(event->type() == LRELEASE && canShoot)
		{
			targetting = false;
			shoot();
		}
		if(angle < 98 && angle > 0)
		{
			angle = 98;
		}
		else if(angle > -98 && angle <= 0)
		{
			angle = -98;
		}
	}
}


void Playground::draw(Window* window)
{
	window->fill_rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, WHITE);
	if(canShoot == true)
	{
		window->draw_png(ARROW_IMG, position.x - ARROW_SIZE/2, position.y - ARROW_SIZE, ARROW_SIZE, ARROW_SIZE*2, angle);
		window->show_text("x " + convertIntegerToString(balls.size()), position.x - 10, position.y + 10, BLACK, FONT_NAME, FONT_SIZE - 15);
	}
	window->draw_line(10, 2*MARGIN, WINDOW_WIDTH - 10, 2*MARGIN, BLACK);
	window->draw_line(10, WINDOW_HEIGHT - 3*MARGIN, WINDOW_WIDTH - 10, WINDOW_HEIGHT - 3*MARGIN, BLACK);
	window->show_text(game->getUsername(), 10 , 10, BLACK, FONT_NAME, FONT_SIZE - 10);
	window->show_text("Score: " + convertIntegerToString(score), 10 , 40, BLACK, FONT_NAME, FONT_SIZE - 10);
	window->show_text("Record: " + convertIntegerToString(game->getHighscore()), 10 , 70, BLACK, FONT_NAME, FONT_SIZE - 10);
	

	for(int i = 0; i < bricks.size(); i++)
	{
		bricks[i].draw(window);
	}
	if(fire)
	{
		fireball->draw(window);
	}
	else
	{
		for(int i = 0; i < balls.size(); i++)
		{
			balls[i].draw(window);
		}
	}
	for(int i = 0; i < lifeballs.size(); i++)
	{
		lifeballs[i].draw(window);
	}

	for(int i = 0; i < fireballs.size(); i++)
	{
		fireballs[i].draw(window);
	}

	for(int i = 0; i < bombs.size(); i++)
	{
		bombs[i].draw(window);
	}

}

std::string Playground::convertIntegerToString(int stringWannaBe)
{
	std::stringstream ss;
	ss << stringWannaBe;
	return ss.str();
}

void Playground::hitWall(Ball* ball)
{
	if(ball->getTop().y < 2*MARGIN && ball->getVelocityY() < 0)
	{
		if(ball->type() == FIRE_BALL)
		{
			cameBack = balls.size();
			ball->setPosition(position);
			ball->setVelocity(0,0);
		}
		else
		{
			ball->setVelocity(ball->getVelocityX(),-ball->getVelocityY());
		}
	}
	if(ball->getBottom().y > WINDOW_HEIGHT - 3*MARGIN && ball->getVelocityY() > 0)
	{
		cameBack++;
		ball->setVelocity(0, 0);
		if(cameBack == 1)
		{
			position.x = ball->getBottom().x;
			fireball->setPosition(position);
		}
		ball->setPosition(position);
	}
	if(ball->getLeft().x < 0 && ball->getVelocityX() < 0)
	{
		if(ball->type() == FIRE_BALL)
		{
			cameBack = balls.size();
			ball->setPosition(position);
			ball->setVelocity(0,0);
		}
		else
		{
			ball->setVelocity(-ball->getVelocityX(), ball->getVelocityY());
		}
	}
	if(ball->getRight().x > WINDOW_WIDTH && ball->getVelocityX() > 0)
	{
		if(ball->type() == FIRE_BALL)
		{
			cameBack = balls.size();
			ball->setPosition(position);
			ball->setVelocity(0,0);
		}
		else
		{
			ball->setVelocity(-ball->getVelocityX(), ball->getVelocityY());
		}
	}
}

void Playground::hitBirik(Ball* ball)
{	
	for (int j = 0; j < bricks.size(); ++j)
	{
		
		if(bricks[j].isInside(ball->getLeft()))
		{
			if(ball->type() == FIRE_BALL)
			{
				bricks[j].die();
			}
			else if(ball->getVelocityX() < 0)
			{
				bricks[j].takeDamage();
				ball->setVelocity(-ball->getVelocityX(), ball->getVelocityY());
			}
		}
		else if(bricks[j].isInside(ball->getTop()))
		{
			if(ball->type() == FIRE_BALL)
			{
				bricks[j].die();
			}
			else if(ball->getVelocityY() < 0)
			{
				bricks[j].takeDamage();
				ball->setVelocity(ball->getVelocityX(), -ball->getVelocityY());
			}
		}

		else if(bricks[j].isInside(ball->getRight()))
		{
			if(ball->type() == FIRE_BALL)
			{
				bricks[j].die();
			}
			else if (ball->getVelocityX() > 0)
			{
				bricks[j].takeDamage();
				ball->setVelocity(-ball->getVelocityX(), ball->getVelocityY());
			}
		}
		else if(bricks[j].isInside(ball->getBottom()))
		{
			if(ball->type() == FIRE_BALL)
			{
				bricks[j].die();
			}
			else if(ball->getVelocityY() > 0)
			{
				bricks[j].takeDamage();
				ball->setVelocity(ball->getVelocityX(), -ball->getVelocityY());
			}
		}
	}
}

void Playground::killBirik()
{
	for (int i = 0; i < bricks.size(); ++i)
	{
		if(bricks[i].hasDied())
		{
			bricks.erase(bricks.begin() + i);
			i--;
		}
	}
}

void Playground::addRow()
{
	for(int i = 0; i < bricks.size(); i++)
	{
		bricks[i].setPosition(Point(bricks[i].getPosition().x, bricks[i].getPosition().y + BRICK_SPACING + BRICK_HEIGHT));
		if(bricks[i].getPosition().y >= BRICK_HEIGHT + 2*MARGIN + 5*(BRICK_HEIGHT + BRICK_SPACING))
		{
			lose();
		}
	}
	for(int i = 0; i < lifeballs.size(); i++)
	{
		lifeballs[i].setPosition(Point(lifeballs[i].getPosition().x, lifeballs[i].getPosition().y + BRICK_SPACING + BRICK_HEIGHT));
		if(lifeballs[i].getPosition().y >= BRICK_HEIGHT + 2*MARGIN + 5*(BRICK_HEIGHT + BRICK_SPACING))
		{
			lifeballs.erase(lifeballs.begin() + i);
			i--;
		}
	}

	for(int i = 0; i < fireballs.size(); i++)
	{
		fireballs[i].setPosition(Point(fireballs[i].getPosition().x, fireballs[i].getPosition().y + BRICK_SPACING + BRICK_HEIGHT));
		if(fireballs[i].getPosition().y >= BRICK_HEIGHT + 2*MARGIN + 5*(BRICK_HEIGHT + BRICK_SPACING))
		{
			fireballs.erase(fireballs.begin() + i);
			i--;
		}
	}

	for(int i = 0; i < bombs.size(); i++)
	{
		bombs[i].setPosition(Point(bombs[i].getPosition().x, bombs[i].getPosition().y + BRICK_SPACING + BRICK_HEIGHT));
		if(bombs[i].getPosition().y >= BRICK_HEIGHT + 2*MARGIN + 5*(BRICK_HEIGHT + BRICK_SPACING))
		{
			lose();
		}
	}

	int brickCount;
	if(score%5 < 3)
	{
		brickCount = 2;
	}
	else if(score%5 < 4)
	{
		brickCount = 1;
	}
	else 
	{
		brickCount = 4;
	}

	std::vector<bool> isBirik;
	for(int i = 0; i < brickCount; i++)
	{
		isBirik.push_back(true);
	}

	for (int i = brickCount; i < COLUMNS; ++i)
	{
		isBirik.push_back(false);
	}
	std::random_shuffle(isBirik.begin(), isBirik.end());

	for(int i = 0; i < COLUMNS; i++)
	{
		if(isBirik[i] == true)
		{
			bricks.push_back(Brick(Point((i+1)*BRICK_SPACING + i * BRICK_WIDTH, 2*MARGIN + 10), BRICK_WIDTH, BRICK_HEIGHT, score + 1));
		}
		else
		{
			int random = rand()%100;
			if(random < 30)
			{
				lifeballs.push_back(LifeBall(Point((i+1)*BRICK_SPACING + i * BRICK_WIDTH + BRICK_WIDTH/2 - LIFEBALL_RADIUS, 2*MARGIN + 10 + BRICK_HEIGHT/2 - LIFEBALL_RADIUS), 2*LIFEBALL_RADIUS, 2*LIFEBALL_RADIUS));
			}
			else if(random < 40)
			{
				fireballs.push_back(FirePower(Point((i+1)*BRICK_SPACING + i * BRICK_WIDTH + BRICK_WIDTH/2 - FIREPOWER_RADIUS, 2*MARGIN + 10 + BRICK_HEIGHT/2 - FIREPOWER_RADIUS), 2*FIREPOWER_RADIUS, 2*FIREPOWER_RADIUS));	
			}
			else if(random < 50)
			{
				bombs.push_back(Bomb(Point((i+1)*BRICK_SPACING + i * BRICK_WIDTH, 2*MARGIN + 10), BRICK_WIDTH, BRICK_HEIGHT));
			}
		}
	}


}

void Playground::hitLifeBall(Ball *ball)
{
	for (int j = 0; j < lifeballs.size(); ++j)
	{
		if(lifeballs[j].isInside(ball->getTop()))
		{
			lifeballHits++;
			lifeballs.erase(lifeballs.begin() + j);
			j--;
		}
		else if(lifeballs[j].isInside(ball->getBottom()))
		{
			lifeballHits++;
			lifeballs.erase(lifeballs.begin() + j);
			j--;
		}
		else if(lifeballs[j].isInside(ball->getLeft()))
		{
			lifeballHits++;
			lifeballs.erase(lifeballs.begin() + j);
			j--;
		}
		else if(lifeballs[j].isInside(ball->getRight()))
		{
			lifeballHits++;
			lifeballs.erase(lifeballs.begin() + j);
			j--;
		}
	}
}

void Playground::hitFireBall(Ball* ball)
{
	for (int j = 0; j < fireballs.size(); ++j)
	{
		if(fireballs[j].isInside(ball->getTop()))
		{
			firepowerHit = true;
			fireballs.erase(fireballs.begin() + j);
			j--;
		}
		else if(fireballs[j].isInside(ball->getBottom()))
		{
			firepowerHit = true;
			fireballs.erase(fireballs.begin() + j);
			j--;
		}
		else if(fireballs[j].isInside(ball->getLeft()))
		{
			firepowerHit = true;
			fireballs.erase(fireballs.begin() + j);
			j--;
		}
		else if(fireballs[j].isInside(ball->getRight()))
		{
			firepowerHit = true;
			fireballs.erase(fireballs.begin() + j);
			j--;
		}
	}
}

void Playground::explode(Point pos)
{
	for(int i = 0; i < bombs.size(); i++)
	{
		Point otherPos = bombs[i].getPosition();
		if(isAround(pos, otherPos))
		{
			bombs.erase(bombs.begin() + i);
			i--;
			explode(pos);
		}
	}
	for(int i = 0; i < bricks.size(); i++)
	{
		if(isAround(pos, bricks[i].getPosition()))
		{
			bricks[i].die();
		}
	}
}

void Playground::hitBomb(Ball* ball)
{
	for (int j = 0; j < bombs.size(); ++j)
	{
		
		if(bombs[j].isInside(ball->getLeft()) && ball->getVelocityX() < 0)
		{
			Point pos = bombs[j].getPosition();
			bombs.erase(bombs.begin() + j);
			j--;
			explode(pos);
			if(ball->type() != FIRE_BALL)
			{
				ball->setVelocity(-ball->getVelocityX(), ball->getVelocityY());
			}
		}
		else if(bombs[j].isInside(ball->getTop()) && ball->getVelocityY() < 0)
		{
			Point pos = bombs[j].getPosition();
			bombs.erase(bombs.begin() + j);
			j--;
			explode(pos);

			if(ball->type() != FIRE_BALL)
			{
				ball->setVelocity(ball->getVelocityX(), -ball->getVelocityY());
			}
		}
		else if(bombs[j].isInside(ball->getRight()) && ball->getVelocityX() > 0)
		{
			Point pos = bombs[j].getPosition();
			bombs.erase(bombs.begin() + j);
			j--;
			explode(pos);

			if(ball->type() != FIRE_BALL)
			{
				ball->setVelocity(-ball->getVelocityX(), ball->getVelocityY());
			}
		}
		else if(bombs[j].isInside(ball->getBottom()) && ball->getVelocityY() > 0)
		{
			Point pos = bombs[j].getPosition();
			bombs.erase(bombs.begin() + j);
			j--;
			explode(pos);

			if(ball->type() != FIRE_BALL)
			{
				ball->setVelocity(ball->getVelocityX(), -ball->getVelocityY());
			}
		}
	}
}

void Playground::addBalls()
{
	if(firepowerHit)
	{
		fire = true;
	}
	else
	{
		fire = false;
	}
	firepowerHit = false;
	for(int i = 0; i < lifeballHits; i++)
	{
		balls.push_back(Ball(Point(position.x - BALL_RADIUS, position.y - BALL_RADIUS), 2*BALL_RADIUS, 2*BALL_RADIUS));
	}
	lifeballHits = 0;
}


void Playground::lose()
{
	game->addRecord(game->getUsername(), score);
	game->changeState(GAME_OVER);
}

void Playground::loadNewGame()
{
	std::srand(time(NULL));
	balls.clear();
	bombs.clear();
	bricks.clear();
	fireballs.clear();
	lifeballs.clear();
	if(fireball != NULL)
		delete fireball;
	score = 0;
	lifeballHits = 0;
	shootCount = 0;
	cameBack = 0;
	shooted = 0;
	timeSinceLastShot = 0;
	shooting = false;
	canShoot = true;
	targetting = false;
	firepowerHit = false;
	fire = false;
	angle = STARTING_ANGLE;
	position = Point(WINDOW_WIDTH/2, WINDOW_HEIGHT - 3*MARGIN - BALL_RADIUS);
	balls.push_back(Ball(Point(position.x - BALL_RADIUS, position.y - BALL_RADIUS), 2*BALL_RADIUS, 2*BALL_RADIUS));
	fireball = new FireBall(Point(position.x - BALL_RADIUS, position.y - BALL_RADIUS), 2*BALL_RADIUS, 2*BALL_RADIUS);
	addRow();
}

void Playground::shoot()
{
	cameBack = 0;
	shooting = true;
	canShoot = false;
	shootCount = 0;
	shooted = 0;
	velocityX = cos((angle+90)/180*PI)*BALL_SPEED;
	velocityY = sin((angle+90)/180*PI)*BALL_SPEED;
}

bool Playground::isAround(Point pos1, Point pos2)
{
	if(abs(pos2.x - pos1.x) <= BRICK_WIDTH + 2*BRICK_SPACING && abs(pos2.y - pos1.y) <= BRICK_HEIGHT + 2*BRICK_SPACING)
	{
		return true;
	}
	return false;
}