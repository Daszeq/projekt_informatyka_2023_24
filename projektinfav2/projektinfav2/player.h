
class player
{
public:
	player(int w, int h,int x, int y)
	{
		this->orig_w=w;
		this->w=w;
		this->h=h;
		this->x=x;
		this->y=y;
		_player.setSize(sf::Vector2f(this->w,this->h));
		_player.setPosition(x,y);
	}

	int getX()
	{
		return _player.getPosition().x;
	}

	int getY()
	{
		return _player.getPosition().y;
	}

	int getW()
	{
		return this->w;
	}

	void moveLeft()
	{
		_player.move(0-this->vel*0.007,0);
	}

	sf::FloatRect getGlobalBounds()
	{
		return _player.getGlobalBounds();
	}

	void moveRight()
	{
		_player.move(0+this->vel*0.007,0);
	}

	void grow()
	{
		_player.setSize(sf::Vector2f(this->w+=10,this->h));
	}

	void shrink()
	{
		if(this->w > 10)_player.setSize(sf::Vector2f(this->w-=10,this->h));

	}

	void increaseSpeed()
	{
		this->vel+=10;
	}

	void decreaseSpeed()
	{
		if(this->vel > 10)this->vel-=10;
	}

	void resetSpeed()
	{
		this->vel=35;
	}

	void reset_w()
	{
		this->w=this->orig_w;
		_player.setSize(sf::Vector2f(this->w,this->h));
	}

	void resetPosition()
	{
		_player.setPosition(this->x,this->y);
	}

	void draw(sf::RenderWindow &window)
	{
		window.draw(_player);
	}

private:
	int orig_w=0;
	int w=0;
	int h=0;
	int x=0;
	int y=0;
	short vel=35;
	sf::RectangleShape _player;
};
