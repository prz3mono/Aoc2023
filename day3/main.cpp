#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <utility>
#include <algorithm>

constexpr unsigned int MAP_SIZE = 140;
//constexpr unsigned int MAP_SIZE = 10;

struct Point
{
	bool operator==(const Point& rhs) const
	{
		return ((line == rhs.line) and (column == rhs.column));
	}
	int line;
	int column;
};


std::vector<std::pair<Point, unsigned int> > findAllNumbers(std::string arg, unsigned int line_nr)
{
	std::vector<std::pair<Point, unsigned int > > resoult;
	auto it = arg.begin();
	while(it < arg.end() ) 
	{
		it=std::find_if(it, arg.end(), [](char a){return ('0'< a and a <='9');});
		if (it >= arg.end()) break;
		unsigned int value = stoi(arg.substr(std::distance(arg.begin(), it)));
		std::cout << "Value :" << value << std::endl;
		resoult.push_back(std::pair(Point{line_nr, std::distance(arg.begin(), it)}, value));
		//std::cout << "Distance : " << std::distance(arg.begin(), it) << std::endl;
		std::advance(it, 2);
		if(value > 99) std::advance(it, 1);
		if(value > 999) std::advance(it, 1);
		//std::cout << "Distance after advance : " << std::distance(arg.begin(), it) << std::endl;
	}
	return resoult;
}

bool isInMap(Point arg)
{
	if (arg.line < 0) return false;
	if (arg.column < 0) return false;
	if (arg.line > (MAP_SIZE - 1)) return false;
	if (arg.column > (MAP_SIZE - 1)) return false;
return true;
}


std::vector<Point> calcAdjacentPoints(std::pair<Point, unsigned int> arg)
{
	std::vector <Point> resoult;
	Point point;

	point = Point{arg.first.line - 1, arg.first.column + 1}; 
	if(isInMap(point)) resoult.push_back(point);

	point = Point{arg.first.line - 1, arg.first.column}; 
	if(isInMap(point)) resoult.push_back(point);

	point = Point{arg.first.line - 1, arg.first.column - 1}; 
	if(isInMap(point)) resoult.push_back(point);

	point = Point{arg.first.line, arg.first.column - 1}; 
	if(isInMap(point)) resoult.push_back(point);
	 
	point = Point{arg.first.line + 1, arg.first.column - 1}; 
	if(isInMap(point)) resoult.push_back(point);

	point = Point{arg.first.line + 1, arg.first.column}; 
	if(isInMap(point)) resoult.push_back(point);

	point = Point{arg.first.line + 1, arg.first.column + 1}; 
	if(isInMap(point)) resoult.push_back(point);

	if(arg.second > 9)
	{
		point = Point{arg.first.line + 1, arg.first.column + 2}; 
		if(isInMap(point)) resoult.push_back(point);

		point = Point{arg.first.line - 1 , arg.first.column + 2}; 
		if(isInMap(point)) resoult.push_back(point);
	}
	else
	{
		point = Point{arg.first.line, arg.first.column + 1}; 
		if(isInMap(point)) resoult.push_back(point);
		return resoult;
	}

	if(arg.second > 99)
	{
		point = Point{arg.first.line + 1, arg.first.column + 3}; 
		if(isInMap(point)) resoult.push_back(point);

		point = Point{arg.first.line - 1 , arg.first.column + 3}; 
		if(isInMap(point)) resoult.push_back(point);
	}
	else
	{
		point = Point{arg.first.line, arg.first.column + 2}; 
		if(isInMap(point)) resoult.push_back(point);
		return resoult;
	}

	if(arg.second > 999)
	{
		point = Point{arg.first.line + 1, arg.first.column + 4}; 
		if(isInMap(point)) resoult.push_back(point);

		point = Point{arg.first.line - 1 , arg.first.column + 4}; 
		if(isInMap(point)) resoult.push_back(point);
	}
	else
	{
		point = Point{arg.first.line, arg.first.column + 3}; 
		if(isInMap(point)) resoult.push_back(point);
		return resoult;
	}
	return resoult;
}

bool isElement(Point arg, const std::vector<std::vector <char> >& map)
{
	char field = map[arg.line][arg.column];
	if (field != '.')
	{
		if (not ('0' < field and field < '9' ))
		{
			return true;
		}
	}
	return false;
}

bool isStar(Point arg, const std::vector<std::vector <char> >& map)
{
	if(map[arg.line][arg.column] == '*') return true;
	return false;
}

int main(int argc, char* argv[])
{
	std::ifstream infile("input.txt");

	std::string line;

	std::vector<std::vector<char> > map;
	std::vector<std::pair<Point, unsigned int> > numbers; 

	for(int i = 0; infile >> line; ++i) 
	{
		map.push_back(std::vector<char>(line.begin(), line.end()));		
		auto current_numbers = findAllNumbers(line, i);
		numbers.insert(numbers.end(), current_numbers.begin(), current_numbers.end());
	
	}
	/*
	unsigned int sum = 0;
	for (auto number: numbers)
	{
		std::cout << "Number: " << number.second << "  Cords: " << number.first.line << ", " << number.first.column << std::endl;
		auto adjacent_points = calcAdjacentPoints(number);

		for ( auto point : adjacent_points)
		{
			//std::cout << "  Point: (" << point.line << ", " << point.column << "), : isE: " << isElement(point, map);
			if(isElement(point, map)) sum+=number.second;
		}
		std::cout << std::endl;

	}
	std::cout << "SUM: " << sum << std::endl;
	*/

	unsigned int sum2 = 0;
	std::vector<std::pair<Point, unsigned int>> starPoints;
	for (auto number: numbers)
	{
		auto adjacent_points = calcAdjacentPoints(number);

		for ( auto point : adjacent_points)
		{
			if(isStar(point, map)) starPoints.push_back(std::pair<Point, unsigned int>(point, number.second));
		}
		std::cout << std::endl;

	}
	for (auto starPoint : starPoints)
	{
		std::cout << "StarPoint: (" << starPoint.first.line << ", " << starPoint.first.column << ") ->" << starPoint.second << std::endl;
	}

	for(auto it = starPoints.begin(); it<starPoints.end(); std::advance(it, 1))
	{
		auto secund_occurance = std::find_if(std::next(it), starPoints.end(), [it](std::pair<Point, unsigned int> arg) {return arg.first == it->first;});
		if (secund_occurance != starPoints.end()) 
		{
			sum2+= ((it->second)*(secund_occurance->second));
		}
	}

	std::cout << "Sum2: " << sum2 << std::endl; 
	
	return 0;
}
