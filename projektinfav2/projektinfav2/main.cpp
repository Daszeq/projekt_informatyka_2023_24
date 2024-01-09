#include <SFML/Graphics.hpp> 
#include <iostream>
#include <ctime> 
#include <math.h> 
#include <string.h> 
#include <stdio.h> 
#include <fstream>
#include <sstream>
#include "player.h" 
#include "ball.h" 
#include "brick.h" 
#include "wall.h" 
#include "powerup.h"
#include "buttons.h"
#include "results.h"

#define WIDTH 600 
#define HEIGHT 600 

bool moveL=false;
bool moveR=false;

int player_score=0; 
short player_lives=3; 

bool start=false;
bool win=false;
bool loose=false;
bool helpi = false;
bool ex_it = false;
bool inmenu = true;
bool rec_saving = false;
bool toexit = false;
bool intop = false;
bool settings = false;

int powersswitch=0;
int compactionswitch=0;
int sizeswitch=0;

sf::Clock chrono;
sf::RectangleShape bg(sf::Vector2f(540, 250));
sf::RectangleShape bg2(sf::Vector2f(345, 35));

int tot_bricks=0;
short power_type=0;

std::vector<std::string> attributes;


void load(std::vector<std::string> &attributes,std::vector<brick> &bricks,std::string lv)
{
	int x=0;
	int y=0;
	int resistance=0;

	std::ifstream loader(lv);
	std::string line;
	std::string delimiter= "," ;
	char* current;

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

void saveGameProgress(int score, short lives, short power) {
	std::ofstream saveFile("stats.txt");
	if (saveFile.is_open()) {
		saveFile << score << "\n";
		saveFile << lives << "\n";
		saveFile << power << "\n";
		saveFile.close();
	}
}

void loadGameProgress(int& score, short& lives, short& power) {
	std::ifstream loadFile("stats.txt");
	if (loadFile.is_open()) {
		loadFile >> score;
		loadFile >> lives;
		loadFile >> power;
		loadFile.close();
	}
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

	sf::Text save_msg;
	save_msg.setFont(atari);
	save_msg.setPosition(WIDTH / 2 - 150, HEIGHT / 2 - 250);
	save_msg.setCharacterSize(35);
	save_msg.setFillColor(sf::Color::White);

	sf::Text pause;
	pause.setFont(atari);
	pause.setString("Pauza");
	pause.setPosition(WIDTH/2-25,HEIGHT/2-200);
	pause.setFillColor(sf::Color::White);

	sf::Text help;
	help.setFont(atari);
	help.setString("Pomoc:\nF1 - Pomoc\nP - pauza\nSPACE - wznow\nTRZALKI - sterowanie platforma\nESC - wyjscie");
	help.setPosition(WIDTH / 2 - 100, HEIGHT / 2 - 170);
	help.setFillColor(sf::Color::White);

	sf::Text exitconf;
	exitconf.setFont(atari);
	exitconf.setString("Czy na pewno chcesz wyjsc?");
	exitconf.setPosition(WIDTH / 2 - 200, HEIGHT / 2 - 80);
	exitconf.setFillColor(sf::Color::White);

	sf::Text nick;
	nick.setFont(atari);
	nick.setString("");
	nick.setPosition(WIDTH / 2 - 250, HEIGHT / 2 - 130);
	nick.setFillColor(sf::Color::White);

	sf::Text results_list;
	results_list.setFont(atari);
	results_list.setCharacterSize(20);
	results_list.setPosition(WIDTH / 2 - 250, HEIGHT / 2 - 80);
	results_list.setFillColor(sf::Color::White);

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

	score_txt.setString("WYNIK:");
	score_txt.setPosition(5,5);
	score_txt.setCharacterSize(25);
	score_txt.setFillColor(sf::Color::Cyan);

	score.setPosition(28,28);
	score.setCharacterSize(20);
	score.setFillColor(sf::Color::White);

	lives_txt.setString("ZYCIA:");
	lives_txt.setPosition(WIDTH-100,5);
	lives_txt.setCharacterSize(25);
	lives_txt.setFillColor(sf::Color::Red);

	lives.setPosition(WIDTH-75,28);
	lives.setCharacterSize(20);
	lives.setFillColor(sf::Color::White);


	end_msg.setPosition(WIDTH/2-75,HEIGHT/2-250);
	end_msg.setCharacterSize(35);
	end_msg.setFillColor(sf::Color::White);

	press_space.setPosition(WIDTH/2-125,HEIGHT/2+200);
	press_space.setCharacterSize(35);
	press_space.setFillColor(sf::Color::Red);

	std::vector<powerup> powers;

	button ExitButton(50, 300, 200, 50, "Wyjdz", atari);
	button ExitButton2(200, 500, 200, 50, "Wyjdz", atari);
	button CancleButton(350, 300, 200, 50, "Anuluj", atari);
	button StartButton(200, 200, 200, 50, "Nowa Gra", atari);
	button StartButton2(200, 350, 200, 50, "Start", atari);
	button MenuButton(200, 375, 200, 50, "Menu", atari);
	button SaveButton(200, 425, 200, 50, "Zapisz", atari);
	button NSaveButton(200, 475, 200, 50, "Nie zapisuj", atari);
	button TopScoreButton(200, 400, 200, 50, "Tablica Wynikow", atari);
	button ReturnButton(200, 450, 200, 50, "Powrot", atari);
	button LoadButton(200, 300, 200, 50, "Wczytaj", atari);

	button PowersSwitch(200, 350, 200, 50, "On", atari);
	button CompactionSwitch(200, 350, 200, 50, "On", atari);
	button SizeSwitch(200, 350, 200, 50, "On", atari);

	player p1(70,10,WIDTH/2,HEIGHT-20);
	ball palla(5,WIDTH/2,(HEIGHT/2)+50,4);
	wall theWall;
	theWall.generateLevel();

	 


	 while (window.isOpen())
	 {
		 if (inmenu && !intop && !settings)
		 {
			 end_msg.setString("ARCANOID");
			 sf::Event event;
			 while (window.pollEvent(event))
			 {
				 if (event.type == sf::Event::Closed) ex_it=true;
				 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					 ex_it = true;
				 }
				 if (StartButton.isClicked(window))
				 {
					 settings = true;
				 }
				 if (LoadButton.isClicked(window))
				 {
					 inmenu = false;
					 loadGameProgress(player_score, player_lives, power_type);
					 theWall.loadBricksFromFile();
					 p1.loadPlayerFromFile();
					 palla.loadBallFromFile();
					 start = false;

				 }
				 if (ExitButton2.isClicked(window))
				 {
					 ex_it = true;
				 }
				 if (TopScoreButton.isClicked(window))
				 {
					 intop = true;
				 }
			 }
			 window.clear();
			 window.draw(end_msg);
			 ExitButton2.draw(window);
			 StartButton.draw(window);
			 TopScoreButton.draw(window);
			 LoadButton.draw(window);
			 if (ex_it)
			 {
				 window.draw(bg);
				 window.draw(exitconf);
				 ExitButton.draw(window);
				 CancleButton.draw(window);
			 }
			 window.display();
		 }
			 tot_bricks = theWall.get_total_bricks();

			 if (player_lives == 0) loose = true;
			 if (tot_bricks == 0) win = true;

			 if (start)generatePowers(powers, pow1_texture, pow2_texture, pow3_texture, pow4_texture, pow5_texture, pow6_texture, pow7_texture, pow8_texture, pow9_texture);

			 if (chrono.getElapsedTime().asSeconds() < 5)
			 {
				 if (power_type == 1)
				 {
					 palla.blink();
				 }

				 if (power_type == 2)
				 {
					 p1.grow();
					 power_type = 0;
					 palla.resetColor();
				 }

				 if (power_type == 3)
				 {
					 p1.shrink();
					 power_type = 0;
					 palla.resetColor();
				 }

				 if (power_type == 4)
				 {
					 palla.increaseSpeed();
					 palla.resetColor();
					 power_type = 0;
				 }

				 if (power_type == 5)
				 {
					 palla.decreaseSpeed();
					 palla.resetColor();
					 power_type = 0;
				 }

				 if (power_type == 6)
				 {
					 player_lives += 1;
					 palla.resetColor();
					 power_type = 0;
				 }

				 if (power_type == 7)
				 {
					 player_lives -= 1;
					 palla.resetColor();
					 power_type = 0;
				 }

				 if (power_type == 8)
				 {
					 p1.increaseSpeed();
					 palla.resetColor();
					 power_type = 0;
				 }

				 if (power_type == 9)
				 {
					 p1.decreaseSpeed();
					 palla.resetColor();
					 power_type = 0;
				 }
			 }

			 else
			 {
				 power_type = 0;
				 palla.resetColor();
			 }


			 if (ex_it)
			 {
				 start = false;
				 helpi = false;
				 bg.setPosition(30, 200);
				 bg.setFillColor(sf::Color::Black);
				 bg.setOutlineThickness(2);
				 bg.setOutlineColor(sf::Color::Blue);
				 if (ExitButton.isClicked(window)) 
				 {
					 saveGameProgress(player_score, player_lives, power_type);
					 theWall.saveBricksToFile();
					 p1.savePlayerToFile();
					 palla.saveBallToFile();
					 window.close();
				 }
				 if (CancleButton.isClicked(window))
					 ex_it = false;
				 if (MenuButton.isClicked(window))
				 {
					 ex_it = false;
					 inmenu = true;
					 saveGameProgress(player_score, player_lives, power_type);
				     theWall.saveBricksToFile();
					 p1.savePlayerToFile();
					 palla.saveBallToFile();
				 }

			 }
			 if (!loose && !win && !inmenu && !rec_saving)
			 {
				 score.setString(std::to_string(player_score));
				 lives.setString(std::to_string(player_lives));
				 score.setPosition(28, 28);
				 score.setCharacterSize(20);
				 score_txt.setPosition(5, 5);
				 score_txt.setCharacterSize(25);

				 sf::Event event;

				 while (window.pollEvent(event))
				 {
					 if (event.type == sf::Event::Closed) ex_it = true;

					 if (event.type == sf::Event::KeyReleased)
					 {
						 if (sf::Keyboard::Left) moveL = false;
						 if (sf::Keyboard::Right) moveR = false;
					 }

					 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) moveL = true;
					 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) moveR = true;
					 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					 {
						 start = true;
						 helpi = false;
					 }
					 if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) start = false;
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

				 if (start) palla.move();

				 theWall.checkCollisions(palla, power_type);
				 theWall.removeDestroyed(player_score);

				 for (auto power = powers.begin(); power != powers.end(); ++power)
				 {
					 if ((*power).isTake())
					 {
						 powers.erase(power);
						 --power;
					 }
				 }


				 for (auto& power : powers)
				 {
					 if (power.getGlobalBounds().intersects(p1.getGlobalBounds()))
					 {
						 chrono.restart();
						 power.take();
						 power_type = power.getType();
					 }
				 }


				 if (palla.getX() <= 0 || palla.getX() >= WIDTH - 20) palla.wall_bounce();
				 if (palla.getY() <= 0) { palla.bounce(); }

				 if (palla.getGlobalBounds().intersects(p1.getGlobalBounds())) palla.bounce();
				 if (palla.getY() > HEIGHT)
				 {
					 player_lives -= 1;
					 restart(start, palla);
				 }

				 if (moveL && p1.getX() > 0 && start) p1.moveLeft();
				 if (moveR && p1.getX() < WIDTH - p1.getW() && start) p1.moveRight();


				 window.clear();

				 window.draw(score_txt);
				 window.draw(score);
				 window.draw(lives_txt);
				 window.draw(lives);
				 theWall.draw(window);
				 for (auto& power : powers) power.draw(window);
				 p1.draw(window);
				 palla.draw(window);
				 if (!start) window.draw(pause);
				 if (helpi) window.draw(help);
				 if (ex_it)
				 {
					 window.draw(bg);
					 window.draw(exitconf);
					 ExitButton.draw(window);
					 CancleButton.draw(window);
					 MenuButton.draw(window);
				 }
				 if (start) for (auto& power : powers) power.move();

				 window.display();

			 }

			 if (loose && !inmenu && !rec_saving)
			 {
				 end_msg.setString("PRZEGRANA");
				 score.setPosition(WIDTH / 2, 100);
				 score.setCharacterSize(24);
				 score_txt.setPosition(WIDTH / 2 - 80, 100);
				 score_txt.setCharacterSize(24);

				 sf::Event event;
				 while (window.pollEvent(event))
				 {
					 if (event.type == sf::Event::Closed) ex_it = true;
					 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
						 start = false;
						 ex_it = true;
					 }
					 if (SaveButton.isClicked(window))
						 rec_saving = true;
					 if (NSaveButton.isClicked(window))
					 {
						 player_lives = 3;
						 player_score = 0;
						 loose = false;
						 theWall.clear();
						 powers.clear();
						 theWall.reset_total_bricks();
						 power_type = 0;
						 p1.reset_w();
						 p1.resetPosition();
						 p1.resetSpeed();
						 theWall.generateLevel();
						 restart(start, palla);
						 inmenu = true;
					 }
				 }

				 window.clear();
				 window.draw(end_msg);
				 window.draw(score_txt);
				 window.draw(score);
				 SaveButton.draw(window);
				 NSaveButton.draw(window);
				 if (ex_it)
				 {
					 window.draw(bg);
					 window.draw(exitconf);
					 ExitButton.draw(window);
					 CancleButton.draw(window);
					 MenuButton.draw(window);
				 }
				 window.display();


			 }

			 if (win && !inmenu && !rec_saving)
			 {
				 end_msg.setString("WYGRALES");
				 press_space.setString("NACISNIJ SPACJE");
				 score.setPosition(WIDTH / 2, 100);
				 score.setCharacterSize(24);
				 score_txt.setPosition(WIDTH / 2 - 80, 100);
				 score_txt.setCharacterSize(24);

				 sf::Event event;
				 while (window.pollEvent(event))
				 {
					 if (event.type == sf::Event::Closed) ex_it = true;

					 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					 {
						 win = false;
						 theWall.clear();
						 powers.clear();
						 theWall.reset_total_bricks();
						 theWall.generateLevel();
						 p1.reset_w();
						 p1.resetPosition();
						 p1.resetSpeed();
						 power_type = 0;
						 restart(start, palla);
					 }
					 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
						 start = false;
						 ex_it = true;
					 }

				 }

				 window.clear();
				 window.draw(end_msg);
				 window.draw(score_txt);
				 window.draw(score);
				 if (chrono.getElapsedTime().asSeconds() > 1) window.draw(press_space);
				 if (chrono.getElapsedTime().asSeconds() > 2) chrono.restart();
				 if (ex_it)
				 {
					 window.draw(bg);
					 window.draw(exitconf);
					 ExitButton.draw(window);
					 CancleButton.draw(window);
					 MenuButton.draw(window);
				 }
				 
				 window.display();
			 }
			 if (intop)
			 {
				 end_msg.setString("NAJLEPSI GRACZE");

				 std::vector<Result> results = loadResults();
				 results_list.setString(displayResults(results));

				 sf::Event event;
				 while (window.pollEvent(event))
				 {
					 if (event.type == sf::Event::Closed) ex_it = true;


					 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
						 ex_it = true;
					 }
					 if (ReturnButton.isClicked(window))
					 {
						 intop = false;
					 }

				 }

				 window.clear();
				 window.draw(end_msg);
				 window.draw(results_list);
				 ReturnButton.draw(window);
				 if (ex_it)
				 {
					 window.draw(bg);
					 window.draw(exitconf);
					 ExitButton.draw(window);
					 CancleButton.draw(window);
					 MenuButton.draw(window);
				 }

				 window.display();
			 }
			 if (settings)
			 {
				 end_msg.setString("USTAWIENIA GRY");

				 sf::Event event;
				 while (window.pollEvent(event))
				 {
					 if (event.type == sf::Event::Closed) ex_it = true;


					 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
						 ex_it = true;
					 }
					 if (ReturnButton.isClicked(window))
					 {
						 settings = false;
					 }
					 if (StartButton2.isClicked(window))
					 {
						 settings = false;
						 inmenu = false;
						 player_lives = 3;
						 player_score = 0;
						 theWall.clear();
						 powers.clear();
						 theWall.reset_total_bricks();
						 power_type = 0;
						 p1.reset_w();
						 p1.resetPosition();
						 p1.resetSpeed();
						 theWall.generateLevel();
						 restart(start, palla);
					 }

				 }

				 window.clear();
				 window.draw(end_msg);
				 StartButton2.draw(window);
				 ReturnButton.draw(window);
				 if (ex_it)
				 {
					 window.draw(bg);
					 window.draw(exitconf);
					 ExitButton.draw(window);
					 CancleButton.draw(window);
					 MenuButton.draw(window);
				 }

				 window.display();
			 }
			 if (rec_saving)
			 {
				 save_msg.setString("ZAPISZ SWOJ NICK");
				 press_space.setString("NACISNIJ ENTER");
				 score.setPosition(WIDTH / 2, 100);
				 score.setCharacterSize(24);
				 score_txt.setPosition(WIDTH / 2 - 80, 100);
				 score_txt.setCharacterSize(24);
				 bg2.setPosition(30, 170);
				 bg2.setFillColor(sf::Color::Black);
				 bg2.setOutlineThickness(2);
				 bg2.setOutlineColor(sf::Color::Blue);

				 sf::Event event;
				 sf::Uint32 unicode = 0;
				 std::vector<Result> results = loadResults();
				 results_list.setString(displayResults(results));

				 while (window.pollEvent(event))
				 {
					 if (event.type == sf::Event::Closed) ex_it = true;
					 if (event.type == sf::Event::TextEntered)
						 if (event.text.unicode == 8 && !nick.getString().isEmpty())
						 {
							 sf::String str = nick.getString();
							 str.erase(str.getSize() - 1);
							 nick.setString(str);
						 }
						 else if (event.text.unicode == 13)
						 {
							 std::string str = nick.getString().toAnsiString();

							 results.push_back({ str, player_score });
							 std::sort(results.begin(), results.end());
							 if (results.size() > 5)
							 {
								 results.resize(5);
							 }
							 saveResults(results);

							 nick.setString("");
							 rec_saving = false;
							 player_lives = 3;
							 player_score = 0;
							 loose = false;
							 theWall.clear();
							 powers.clear();
							 theWall.reset_total_bricks();
							 power_type = 0;
							 p1.reset_w();
							 p1.resetPosition();
							 p1.resetSpeed();
							 theWall.generateLevel();
							 restart(start, palla);
							 if (toexit)
								 window.close();
							 else
								inmenu = true;
						 }
						 else if (event.text.unicode >= 33 && event.text.unicode <= 122)
						 {
							 if (nick.getString().getSize() < 20)
							 {
								 unicode = event.text.unicode;
							 }
						 }
					 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
						 start = false;
						 ex_it = true;
					 }
					 
				 }
				 if (unicode)
				 {
					 sf::String str = nick.getString();
					 str += unicode;
					 nick.setString(str);
				 }
				 window.clear();
				 window.draw(save_msg);
				 window.draw(bg2);
				 window.draw(nick);
				 window.draw(score_txt);
				 window.draw(score);
				 if (chrono.getElapsedTime().asSeconds() > 1) window.draw(press_space);
				 if (chrono.getElapsedTime().asSeconds() > 2) chrono.restart();
				 window.draw(results_list);
				 if (ex_it)
				 {
					 window.draw(bg);
					 window.draw(exitconf);
					 ExitButton.draw(window);
					 CancleButton.draw(window);
				 }
				 window.display();


			 }
	 }
	return 0;
}
