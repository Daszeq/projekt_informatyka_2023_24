
class powerup
{
public:
	powerup(sf::Texture &texture,int type)
	{
		_power.setScale(_power.getScale().x/20,_power.getScale().y/20);
		_power.setTexture(texture);
		this->type=type;
	}

	void setPosition(int x, int y)
	{
		_power.setPosition(x,y);
	}

	void move()
	{
		_power.move(0,0+2*0.09);
	}

	int getType()
	{
		return this->type;
	}

	sf::FloatRect getGlobalBounds()
	{
		return _power.getGlobalBounds();
	}

	void take()
	{
		this->_take=1;
	}

	bool isTake()
	{
		return this->_take;
	}

	void draw(sf::RenderWindow &window)
	{
		window.draw(_power);
	}

private:
	int type=0;
	bool _take=0;
	sf::Sprite _power;
};
