#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp> 
#include <iostream>
#include <ctime> 
#include <math.h> 
#include <string.h> 
#include <stdio.h> 
#include <fstream> 
#include "player.h" 
#include "ball.h" 
#include "brick.h" 
#include "wall.h" 
#include "powerup.h" 
#include "menu.h" 
#include "menu2.h" 
//#include "test.cpp" 
#define WIDTH 600 
#define HEIGHT 600 

bool moveL=false;
bool moveR=false;

unsigned int player_score=0; 
short player_lives=3; 

bool start=false;
bool pause=false;
bool win=false;
bool loose=false;
bool fortune_stat=false;
bool helpi = false;
bool ex_it = false;
bool closing = false;

sf::Clock chrono;
sf::Texture fortune_texture;
sf::Sprite fortune;



int tot_bricks=0;
short power_type=0;

std::vector<std::string> attributes;


std::string highScoreIO(std::string hscore,unsigned int score=0,bool mode=0)
{
	std::string Hscore;

	std::fstream fhandler;

	fhandler.open(hscore,std::ios::out | std::ios::in);

	if(!mode)
	{
		getline(fhandler,Hscore);
		return Hscore;
	}
	if(mode) fhandler << score;

	fhandler.close();

}

void load(std::vector<std::string> &attributes,std::vector<brick> &bricks,std::string lv)
{
	int x=0;
	int y=0;
	int resistance=0;

	std::ifstream loader(lv);
	std::string line;
	std::string delimiter= "," ;
	char* current;

	while(getline(loader,line))
	{
		current=strtok((char*)line.c_str(),delimiter.c_str());
		while(current != NULL)
		{
			attributes.push_back(current);
			current=strtok(NULL,delimiter.c_str());
		}
	}

	loader.close();

	for(auto attribute=attributes.begin(); attribute != attributes.end(); ++attribute)
	{
		x=stoi(*attribute);
		attribute++;
		y=stoi(*attribute);
		attribute++;
		resistance=stoi(*attribute);

		brick b(40,10,x,y,resistance);
		bricks.push_back(b);
	}

}

void restart(bool &start,ball &palla)
{
	start=false;
	palla.setPosition(WIDTH/2,HEIGHT/2-50);
	palla.resetAngle();
	palla.resetSpeed();
}

void generatePowers(std::vector<powerup> &powers,
sf::Texture &texture1,
sf::Texture &texture2,
sf::Texture &texture3,
sf::Texture &texture4,
sf::Texture &texture5,
sf::Texture &texture6,
sf::Texture &texture7,
sf::Texture &texture8,
sf::Texture &texture9)
{
	if(rand()%100000 == 0)
	{
		powerup pow(texture1,1); 
		pow.setPosition(rand()%(WIDTH-50)+1,rand()%HEIGHT/2+1); 
		powers.push_back(pow); 
	}

	if(rand()%100000 == 1)
	{
		powerup pow(texture2,2); 
		pow.setPosition(rand()%(WIDTH-50)+1,rand()%HEIGHT/2+1); 
		powers.push_back(pow); 
	}

	if(rand()%100000 == 2)
	{
		powerup pow(texture3,3); 
		pow.setPosition(rand()%(WIDTH-50)+1,rand()%HEIGHT/2+1); 
		powers.push_back(pow); 
	}

	if(rand()%100000 == 3)
	{
		powerup pow(texture4,4);
		pow.setPosition(rand()%(WIDTH-50)+1,rand()%HEIGHT/2+1);
		powers.push_back(pow);
	}

	if(rand()%100000 == 4)
	{
		powerup pow(texture5,5);
		pow.setPosition(rand()%(WIDTH-50)+1,rand()%HEIGHT/2+1);
		powers.push_back(pow);
	}

	if(rand()%100000 == 5)
	{
		powerup pow(texture6,6);
		pow.setPosition(rand()%(WIDTH-50)+1,rand()%HEIGHT/2+1);
		powers.push_back(pow);
	}

	if(rand()%500000 == 6)
	{
		powerup pow(texture7,7);
		pow.setPosition(rand()%(WIDTH-50)+1,rand()%HEIGHT/2+1);
		powers.push_back(pow);
	}

	if(rand()%100000 == 7)
	{
		powerup pow(texture8,8);
		pow.setPosition(rand()%(WIDTH-50)+1,rand()%HEIGHT/2+1);
		powers.push_back(pow);
	}

	if(rand()%100000 == 8)
	{
		powerup pow(texture9,9);
		pow.setPosition(rand()%(WIDTH-50)+1,rand()%HEIGHT/2+1);
		powers.push_back(pow);
	}

}

int main(int argc, char** argv)
{

	sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT),"ARKANOID");
	srand(time(NULL));

	sf::Font atari;
	atari.loadFromFile("font/AtariST8x16SystemFont.ttf");

	sf::Text hscore_ui;
	hscore_ui.setFont(atari);

	sf::Text hscore_txt;
	hscore_txt.setFont(atari);

	sf::Text score_txt;
	score_txt.setFont(atari);

	sf::Text score;
	score.setFont(atari);

	sf::Text lives_txt;
	lives_txt.setFont(atari);

	sf::Text lives;
	lives.setFont(atari);

	sf::Text end_msg;
	end_msg.setFont(atari);

	sf::Text press_space;
	press_space.setFont(atari);

	sf::Text pause;
	pause.setFont(atari);
	pause.setString("Pauza");
	pause.setPosition(WIDTH/2-25,HEIGHT/2-200);
	pause.setFillColor(sf::Color::White);

	sf::Text help;
	help.setFont(atari);
	help.setString("Pomoc:\nF1 - Pomoc\nSPACE - wznów");
	help.setPosition(WIDTH / 2 - 100, HEIGHT / 2 - 170);
	help.setFillColor(sf::Color::White);

	sf::Texture pow1_texture;
	pow1_texture.loadFromFile("powers/power1.png");

	sf::Texture pow2_texture;
	pow2_texture.loadFromFile("powers/power2.png");

	sf::Texture pow3_texture;
	pow3_texture.loadFromFile("powers/power3.png");

	sf::Texture pow4_texture;
	pow4_texture.loadFromFile("powers/power4.png");

	sf::Texture pow5_texture;
	pow5_texture.loadFromFile("powers/power5.png");

	sf::Texture pow6_texture;
	pow6_texture.loadFromFile("powers/power6.png");

	sf::Texture pow7_texture;
	pow7_texture.loadFromFile("powers/power7.png");

	sf::Texture pow8_texture;
	pow8_texture.loadFromFile("powers/power8.png");

	sf::Texture pow9_texture;
	pow9_texture.loadFromFile("powers/power9.png");


	hscore_txt.setString("H-SCORE");
	hscore_txt.setPosition(10,5);
	hscore_txt.setCharacterSize(25);
	hscore_txt.setFillColor(sf::Color::Yellow);

	hscore_ui.setPosition(35,28);
	hscore_ui.setFillColor(sf::Color::Red);
	hscore_ui.setCharacterSize(20);
	hscore_ui.setString(highScoreIO("HSCORE"));

	score_txt.setString("SCORE");
	score_txt.setPosition(WIDTH/2,5);
	score_txt.setCharacterSize(25);
	score_txt.setFillColor(sf::Color::White);

	score.setPosition(WIDTH/2+25,28);
	score.setCharacterSize(20);
	score.setFillColor(sf::Color::White);

	lives_txt.setString("PLAYER");
	lives_txt.setPosition(WIDTH-100,5);
	lives_txt.setCharacterSize(25);
	lives_txt.setFillColor(sf::Color::White);

	lives.setPosition(WIDTH-100,28);
	lives.setCharacterSize(20);
	lives.setFillColor(sf::Color::White);


	end_msg.setPosition(WIDTH/2-75,HEIGHT/2-100);
	end_msg.setCharacterSize(35);
	end_msg.setFillColor(sf::Color::White);

	press_space.setPosition(WIDTH/2-200,HEIGHT/2);
	press_space.setCharacterSize(35);
	press_space.setFillColor(sf::Color::Red);

	std::vector<powerup> powers;

	player p1(70,10,WIDTH/2,HEIGHT-20);
	ball palla(5,WIDTH/2,(HEIGHT/2)+50,4);
	wall theWall;
	 theWall.generateLevel();


	while(window.isOpen())
	{
		tot_bricks=theWall.get_total_bricks();

		if(player_lives == 0) loose=true;
		if(tot_bricks == 0) win=true;

		if(start)generatePowers(powers,pow1_texture,pow2_texture,pow3_texture, pow4_texture,pow5_texture,pow6_texture,pow7_texture,pow8_texture,pow9_texture);

		if(chrono.getElapsedTime().asSeconds() < 5)
		{
			if(power_type == 1)
			{
				palla.blink();
			}

			if(power_type == 2)
			{
				p1.grow();
				power_type=0;
				palla.resetColor();
			}

			if(power_type == 3)
			{
				p1.shrink();
				power_type=0;
				palla.resetColor();
			}

			if(power_type == 4)
			{
				palla.increaseSpeed();
				palla.resetColor();
				power_type=0;
			}

			if(power_type == 5)
			{
				palla.decreaseSpeed();
				palla.resetColor();
				power_type=0;
			}

			if(power_type == 6)
			{
				player_lives+=1;
				palla.resetColor();
				power_type=0;
			}

			if(power_type == 7)
			{
				player_lives-=1;
				palla.resetColor();
				power_type=0;
			}

			if(power_type == 8)
			{
				p1.increaseSpeed();
				palla.resetColor();
				power_type=0;
			}

			if(power_type == 9)
			{
				p1.decreaseSpeed();
				palla.resetColor();
				power_type=0;
			}
		}

		else
		{
			power_type=0;
			palla.resetColor();
		}



		if(!loose && !win)
		{
			score.setString(std::to_string(player_score));
			lives.setString(std::to_string(player_lives));


			sf::Event event;

			while(window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed) closing = true;

				if(event.type == sf::Event::KeyReleased)
				{
					if(sf::Keyboard::Left) moveL=false;
					if(sf::Keyboard::Right) moveR=false;
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) moveL=true;
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) moveR=true;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
				{
					start = true;
					helpi = false;
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)) start=false;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
				{
					start = false;
					helpi = true;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					start = false;
					ex_it = true;

				} 
			}

			if(start) palla.move();

			theWall.checkCollisions(palla,power_type);
			theWall.removeDestroyed(player_score,fortune_stat);

			for (auto power=powers.begin(); power != powers.end(); ++power)
			{
				if((*power).isTake())
				{
					powers.erase(power);
					--power;
				}
			}


			for(auto &power : powers)
			{
				if(power.getGlobalBounds().intersects(p1.getGlobalBounds()))
				{
					chrono.restart();
					power.take();
					power_type=power.getType();
				}
			}


			if(palla.getX() <= 0 || palla.getX() >= WIDTH-20) palla.wall_bounce();
			if(palla.getY() <= 0) {palla.bounce();}

			if(palla.getGlobalBounds().intersects(p1.getGlobalBounds())) palla.bounce();
			if(palla.getY() > HEIGHT)
			{
				 player_lives-=1;
				 restart(start,palla);
			}

			if(moveL && p1.getX() > 0 && start) p1.moveLeft();
			if(moveR && p1.getX() < WIDTH-p1.getW() && start ) p1.moveRight();


			window.clear();

			if(fortune_stat) window.draw(fortune);
			window.draw(hscore_txt);
			window.draw(hscore_ui);
			window.draw(score_txt);
			window.draw(score);
			window.draw(lives_txt);
			window.draw(lives);
			theWall.draw(window);
			for(auto &power : powers) power.draw(window);
			p1.draw(window);
			palla.draw(window);
			if(!start) window.draw(pause);
			if (helpi) window.draw(help);

			if (ex_it)
			{
				window.clear();
				//closing = true;

			}
			if (closing)
			{
				if (player_score > std::stoi(highScoreIO("HSCORE"))) highScoreIO("HSCORE", player_score, 1);
				window.close();
			}
			if (start) for (auto& power : powers) power.move();

			window.display();

		}

		if(loose)
		{
			end_msg.setString("PRZEGRANA");
			press_space.setString("NACIŒNIJ SPACJÊ, ABY ZRESTARTOWAÆ");

			if(player_score > std::stoi(highScoreIO("HSCORE"))) highScoreIO("HSCORE",player_score,1);

			sf::Event event;
			while(window.pollEvent(event))
			{
				if(event.type == sf::Event::Closed) window.close();
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					 player_lives=3;
					 player_score=0;
					 hscore_ui.setString(highScoreIO("HSCORE"));
					 loose=false;
					 fortune_stat=false;
					 theWall.clear();
					 powers.clear();
					 theWall.reset_total_bricks();
					 power_type=0;
					 p1.reset_w();
					 p1.resetPosition();
					 p1.resetSpeed();
					 theWall.generateLevel();
					 restart(start,palla);

				}
			}

			window.clear();
			window.draw(end_msg);
			if(chrono.getElapsedTime().asSeconds() > 1) window.draw(press_space);
			if(chrono.getElapsedTime().asSeconds() > 2) chrono.restart();
			window.display();

		}

		if(win)
		{
			end_msg.setString("WYGRA£EŒ");
			press_space.setString("NACIŒNIJ SPACJÊ, ABY KONTYNUOWAÆ");

			sf::Event event;
			while(window.pollEvent(event))
			{
				if(event.type == sf::Event::Closed) window.close();

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					win=false;
					fortune_stat=false;
					theWall.clear();
					powers.clear();
					theWall.reset_total_bricks();
					theWall.generateLevel();
					p1.reset_w();
					p1.resetPosition();
					p1.resetSpeed();
					power_type=0;
					restart(start,palla);
				}

			}

			window.clear();
			window.draw(end_msg);
			window.draw(press_space);
			window.display();

		}
	}
	return 0;
}
