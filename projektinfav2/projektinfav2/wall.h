
class wall
{
public:
	void generateLevel()
	{
		for(int y=50; y< this->h; y+=20)
		{
			for(int x=20; x< this-> w; x+=60)
			{
				if(rand()%10 < 3)
				{
					brick b(40,10,x,y,rand()%3+1);
					this->bricks.push_back(b);
					this->tot_bricks+=1;
				}
			}
		}
	}
	void loadBricksFromFile()
	{
		clear();

		std::ifstream file("wall_save.txt");

		int x, y, resistance;
		while (file >> x >> y >> resistance)
		{
			brick b(40, 10, x, y, resistance);
			this->bricks.push_back(b);
			this->tot_bricks += 1;
		}

		file.close();
	}
	void saveBricksToFile()
	{
		std::ofstream file("wall_save.txt");

		for (auto& brick : this->bricks)
		{
			file << brick.getX() << " " << brick.getY() << " " << brick.getResistance() << "\n";
		}

		file.close();
	}
	void generateGrid()
	{
		for(int y=50; y< this->h; y+=20)
		{
			for(int x=20; x< this-> w; x+=60)
			{
				brick b(40,10,x,y,0);
				this->bricks.push_back(b);
			}
		}
	}

	void checkCollisions(ball &palla, int power_type)
	{
		for(auto &brick : this -> bricks) if(brick.getGlobalBounds().intersects(palla.getGlobalBounds()))
		{
			brick.hit();
			if(power_type != 1) palla.bounce();
			brick.updateStatus();
		}
	}

	void removeDestroyed( int &player_score)
	{
		for(auto brick=this->bricks.begin(); brick != bricks.end(); ++brick)
		{
			if((*brick).isDestroy())
			{
				player_score+=(*brick).getPoints();
				this->bricks.erase(brick);
				--brick;
				this->tot_bricks--;
			}
		}
	}

	std::vector<brick> getBricksVector()
	{
		return this->bricks;
	}

	int get_total_bricks()
	{
		return this-> tot_bricks;
	}

	void setBricksVector(std::vector<brick> bv)
	{
		this->bricks=bv;
	}

	void clear()
	{
		this->bricks.clear();
	}

	void count_total_bricks()
	{
		for(auto &brick : this->bricks)
		{
			if(brick.getResistance() != 0) this->tot_bricks+=1;
		}
	}

	void reset_total_bricks()
	{
		this->tot_bricks=0;
	}

	void draw(sf::RenderWindow &window)
	{
		for(auto &brick : this->bricks) brick.draw(window);
	}



private:
	int w=580;
	int h=220;
	std::vector<brick> bricks;
	short tot_bricks=0;
};
