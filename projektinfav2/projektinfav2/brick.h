
class brick
{
public:
	brick(int width,int height,int x, int y,short resistance)
	{
		_brick.setSize(sf::Vector2f(width,height));
		_brick.setPosition(x,y);
		this->resistance=resistance;

		_brick.setOutlineColor(sf::Color::Black);
		_brick.setOutlineThickness(1);

		if(this->resistance == 0)
		{
			_brick.setFillColor(sf::Color::Black);
			_brick.setOutlineColor(sf::Color::White);
			_brick.setOutlineThickness(1);
		}

		if(this->resistance == 1)
		{
			_brick.setFillColor(sf::Color::Green);
			this->points=1;
		}
		if(this->resistance == 2)
		{
			_brick.setFillColor(sf::Color::Blue);
			this->points=2;
		}
		if(this->resistance == 3)
		{
			_brick.setFillColor(sf::Color::Red);
			this->points=3;
		}
	}

	sf::FloatRect getGlobalBounds()
	{
		return _brick.getGlobalBounds();
	}

	void hit()
	{
		this->resistance-=1;
		if(this->resistance <=0 ) this->destroyed=true;
	}

	int getX()
	{
		return _brick.getPosition().x;
	}

	int getY()
	{
		return _brick.getPosition().y;
	}

	int getSizeX()
	{
		return _brick.getSize().x;
	}

	int getSizeY()
	{
		return _brick.getSize().y;
	}

	void setResistance()
	{
		if(this->resistance <3) this->resistance+=1;
		else this->resistance=0;
	}

	void updateStatus()
	{
		if(this->resistance == 3) _brick.setFillColor(sf::Color::Red);
		if(this->resistance == 2) _brick.setFillColor(sf::Color::Blue);
		if(this->resistance == 1) _brick.setFillColor(sf::Color::Green);
		if(this->resistance == 0) {_brick.setOutlineColor(sf::Color::White);_brick.setFillColor(sf::Color::Black);_brick.setOutlineThickness(1);}
	}

	bool isDestroy()
	{
		if(this->destroyed) return true;
		if(!this->destroyed) return false;
	}

	int getResistance()
	{
		return this->resistance;
	}

	int getPoints()
	{
		return this->points;
	}

	void draw(sf::RenderWindow &window)
	{
		window.draw(_brick);
	}

private:
	short points=0;
	short resistance=0;
	bool destroyed=false;

	sf::RectangleShape _brick;
};
