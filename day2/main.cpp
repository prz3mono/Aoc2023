#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

struct GameThrow
{
	GameThrow(std::string arg)
		:red{0}, green{0}, blue{0}
	{
		std::stringstream ss{arg};
		std::string segment;
		while(std::getline(ss, segment, ','))
		{
			if(segment.find("red") != std::string::npos)
			{
				red = stoi(segment);

			}else if(segment.find("green") != std::string::npos)
			{
				green = stoi(segment);

			}else if(segment.find("blue") != std::string::npos)
			{
				blue = stoi(segment);
			}
		}

	}
	unsigned int red;
	unsigned int green;
	unsigned int blue;
};

class Game
{
public:
	constexpr static unsigned int MAX_RED{12};
	constexpr static unsigned int MAX_GREEN{13};
	constexpr static unsigned int MAX_BLUE{14};

	Game(unsigned int a_ID, std::vector<GameThrow> a_gameThrows)
		: ID{a_ID}, gameThrows{a_gameThrows}
	{}
	unsigned int getID()
	{
		return ID;
	}
	void print()
	{
		std::cout << "GAME: " << ID << std::endl;
		for (auto gameThrow : gameThrows)
		{
			std::cout << "Throw: " << " RED:" << gameThrow.red
					       << " GREEN:" << gameThrow.green
					       << " BLUE:" << gameThrow.blue
				  << std::endl;
		}
	}
	bool isPossible()
	{
		for (auto gameThrow : gameThrows)
		{
			if (gameThrow.red > MAX_RED) return false;
			if (gameThrow.green > MAX_GREEN) return false;
			if (gameThrow.blue > MAX_BLUE) return false;
		}
		return true;
	}

	unsigned int getFewestRed()
	{
		unsigned int resoult{0};
		for (auto gameThrow : gameThrows)
		{
			resoult = std::max(resoult, gameThrow.red); 
		}
		return resoult;
	}

	unsigned int getFewestGreen()
	{
		unsigned int resoult{0};
		for (auto gameThrow : gameThrows)
		{
			resoult = std::max(resoult, gameThrow.green); 
		}
		return resoult;
	}
	unsigned int getFewestBlue()
	{
		unsigned int resoult{0};
		for (auto gameThrow : gameThrows)
		{
			resoult = std::max(resoult, gameThrow.blue); 
		}
		return resoult;
	}

private:
	unsigned int ID;
	std::vector<GameThrow> gameThrows;
};

int main(int argc, char* argv[])
{
	std::ifstream infile("input.txt");
	std::string line;
	std::vector<Game> games;

	while(getline(infile, line))
	{
		std::cout << line << std::endl;
		unsigned int gameID = stoi(line.substr(4)) ;

		line = line.substr(line.find(':') + 1);
		std::stringstream ss{line};
		std::string segment;
		std::vector<GameThrow> gameThrows;

		while(std::getline(ss, segment, ';')) 
		{
			GameThrow part(segment);
			gameThrows.push_back(part);
		}
		Game game{gameID, gameThrows};
		games.push_back(game);
	}
	unsigned int sum{0};
	unsigned int sum_2{0};
	for (auto game: games)
	{
		game.print();
		std::cout << "Is posbile: " << game.isPossible() << std::endl;
		std::cout << "Fewest red: " << game.getFewestRed();
		std::cout << "Fewest green: " << game.getFewestGreen();
		std::cout << "Fewest blue: " << game.getFewestBlue();
		std::cout << std::endl;
		unsigned int power = game.getFewestRed() * game.getFewestGreen() * game.getFewestBlue();
		sum_2 += power;

		if(game.isPossible())
		{
			sum+= game.getID();
		}
	}
	std::cout << "Sum of Passible games: " << sum << std::endl;
	std::cout << "Sum of power: " << sum_2 << std::endl;

	return 0;

















}
