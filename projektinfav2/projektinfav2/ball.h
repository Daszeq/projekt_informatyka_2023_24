
class ball
{

public:
	ball(int radius, int x, int y, short speed)
	{
		_ball.setRadius(radius);
		_ball.setPosition(x,y);
		_ball.setOutlineColor(sf::Color::Black);
		_ball.setOutlineThickness(1);
		this->original_speed=speed;
		this->speed=speed;
	}

	int getX()
	{
		return _ball.getPosition().x;
	}


	int getY()
	{
		return _ball.getPosition().y;
	}

	void move()
	{
		_ball.setPosition(_ball.getPosition().x+this->angle*time,_ball.getPosition().y-this->speed*time);
	}

	sf::FloatRect getGlobalBounds()
	{
		return _ball.getGlobalBounds();
	}

	void bounce()
	{
		if(_ball.getPosition().y <= 10) 
		{
			this->original_speed=-this->original_speed;
			this->speed=this->original_speed;
		}

		else{
			double ex=(double)rand() / RAND_MAX;
			if(this->angle >= 0)this->angle=0.00+ex*(3.00-0.00);
			if(this->angle <= 0)this->angle=-3.00+ex*(0.00-(-3.00));
			this->original_speed=-this->original_speed;
			this->speed=this->original_speed;
		}


	}

	void setPosition(int x,int y)
	{
		_ball.setPosition(x,y);
	}

	void wall_bounce()
	{
		this->angle=-this->angle;
	}

	void resetAngle()
	{
		this->angle=0;
	}

	void resetSpeed()
	{
		this->time=0.07;
	}

	void blink()
	{
		_ball.setFillColor(sf::Color(rand()%255+1,rand()%255+1,rand()%255+1));
	}

	void increaseSpeed()
	{
		this->time+=0.01;
	}

	void decreaseSpeed()
	{
		if(this->time > 0.01) this->time-=0.01;
	}

	void resetColor()
	{
		_ball.setFillColor(sf::Color::White);
	}

	void draw(sf::RenderWindow &window)
	{
		window.draw(_ball);
	}

	void saveBallToFile()
	{
		std::ofstream file("ball_save.txt");

		file << getX() << " " << getY() << " " << original_speed << " " << speed << " " << angle << " " << time << "\n";

		file.close();
	}


	void loadBallFromFile()
	{
		std::ifstream file("ball_save.txt");

		int loadedX, loadedY;
		short loadedOriginalSpeed, loadedSpeed;
		double loadedAngle;
		float loadedTime;

		if (file >> loadedX >> loadedY >> loadedOriginalSpeed >> loadedSpeed >> loadedAngle >> loadedTime)
		{
			setPosition(loadedX, loadedY);
			original_speed = loadedOriginalSpeed;
			speed = loadedSpeed;
			angle = loadedAngle;
			time = loadedTime;
		}

		file.close();
	}

private:
	short original_speed;
	short speed=0;
	double angle=0.00;
	float time=0.07;
	sf::CircleShape _ball;
};
