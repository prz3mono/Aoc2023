#include <iostream>
#include <fstream>
#include <vector>


struct Point
{
	Point(unsigned int a_x, unsigned int a_y)
	: x{a_x}, y{a_y}
	{}
	unsigned int x;
	unsigned int y;
};


Point GetStartPoint(std::vector<std::string> map)
{
	for(unsigned int y = 0; y < map.size(); ++y)
	{
		for(unsigned int x = 0; x < map[y].size(); ++x)
		{
			if (map[y][x] == '^') return Point(x,y);
		}
	}
}

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
}

bool Step(Point point, Direction direction; std::vector<std::string>& map, std::vector<std::string>& visited_map)
{
	switch (direction)
	{
		case: UP
		{
			if((point.y - 1) < 0) return false;
			if((map[point.y - 1][point.x]  == '#') direction = RIGHT;
			else point.y = point.y - 1;
		} 



	}
	visited_map[point.y, point.x] = true;
}

int main(int argc, char* argv[])
{
	//std::ifstream infile("input.txt");
	std::ifstream infile("example.txt");
	std::vector<std::string> map;
	std::string line;

	while(infile >> line)
	{
		map.push_back(line);
	}


	for (auto el: map)
	{
		std::cout << el << std::endl;
	}	
	
	std::cout << map[0].size() << std::endl;
	std::vector<std::vector<bool>> visited_map(map.size(), std::vector<bool>(map[0].size(), false)); 

	for (auto el: visited_map)
	{
		for (auto el2: el)
		{
			if(el2 == false) std::cout << ".";	
			if(el2 == true) std::cout << "X";	
		}
		std::cout << std::endl;
	}

	Point start_point = GetStartPoint(map);
	std::cout << "Start point: " << start_point.x << ", " << start_point.y << std::endl;
	
	Direction dircetion = UP;
	Point point = start_point;
	visited_map[point.y, point.x] == true;



	
	
	return 0;
}
