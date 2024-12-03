#include <iostream>
#include <fstream>
#include <regex>

int main(int argc, char* argv[])
{
	std::ifstream infile("input.txt");

	std::string arg1;
	std::string ignore;
	std::string arg2;
	std::regex re(R"mul\(\d{1,3},\d{1,3}\)");

	while(infile >> arg1)
	{
		std::cout << arg1  << std::endl << std::endl; 
	
	}

	return 0;
}
