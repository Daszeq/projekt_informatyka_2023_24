//#include <SFML/Graphics.hpp> 
//#include <ctime> 
//#include <math.h> 
//#include <string.h> 
//#include <stdio.h> 
//#include <fstream> 
//#include "player.h" 
//#include "ball.h" 
//#include "brick.h" 
//#include "wall.h" 
//#include "powerup.h" 
//
//#define WIDTH 600 
//#define HEIGHT 600
//void generatePowers(std::vector<powerup>& powers,
//	sf::Texture& texture1,
//	sf::Texture& texture2,
//	sf::Texture& texture3,
//	sf::Texture& texture4,
//	sf::Texture& texture5,
//	sf::Texture& texture6,
//	sf::Texture& texture7,
//	sf::Texture& texture8,
//	sf::Texture& texture9)
//{
//	if (rand() % 100000 == 0)
//	{
//		powerup pow(texture1, 1);
//		pow.setPosition(rand() % (WIDTH - 50) + 1, rand() % HEIGHT / 2 + 1);
//		powers.push_back(pow);
//	}
//
//	if (rand() % 100000 == 1)
//	{
//		powerup pow(texture2, 2);
//		pow.setPosition(rand() % (WIDTH - 50) + 1, rand() % HEIGHT / 2 + 1);
//		powers.push_back(pow);
//	}
//
//	if (rand() % 100000 == 2)
//	{
//		powerup pow(texture3, 3);
//		pow.setPosition(rand() % (WIDTH - 50) + 1, rand() % HEIGHT / 2 + 1);
//		powers.push_back(pow);
//	}
//
//	if (rand() % 100000 == 3)
//	{
//		powerup pow(texture4, 4);
//		pow.setPosition(rand() % (WIDTH - 50) + 1, rand() % HEIGHT / 2 + 1);
//		powers.push_back(pow);
//	}
//
//	if (rand() % 100000 == 4)
//	{
//		powerup pow(texture5, 5);
//		pow.setPosition(rand() % (WIDTH - 50) + 1, rand() % HEIGHT / 2 + 1);
//		powers.push_back(pow);
//	}
//
//	if (rand() % 100000 == 5)
//	{
//		powerup pow(texture6, 6);
//		pow.setPosition(rand() % (WIDTH - 50) + 1, rand() % HEIGHT / 2 + 1);
//		powers.push_back(pow);
//	}
//
//	if (rand() % 500000 == 6)
//	{
//		powerup pow(texture7, 7);
//		pow.setPosition(rand() % (WIDTH - 50) + 1, rand() % HEIGHT / 2 + 1);
//		powers.push_back(pow);
//	}
//
//	if (rand() % 100000 == 7)
//	{
//		powerup pow(texture8, 8);
//		pow.setPosition(rand() % (WIDTH - 50) + 1, rand() % HEIGHT / 2 + 1);
//		powers.push_back(pow);
//	}
//
//	if (rand() % 100000 == 8)
//	{
//		powerup pow(texture9, 9);
//		pow.setPosition(rand() % (WIDTH - 50) + 1, rand() % HEIGHT / 2 + 1);
//		powers.push_back(pow);
//	}
//
//}