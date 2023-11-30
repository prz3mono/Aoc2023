#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
	std::ifstream infile("input.txt");

	std::string arg1;
	std::string ignore;
	std::string arg2;

	while(infile >> arg1 >> ignore >> arg2)
	{
		std::cout << arg1 << "->" << arg2 << std::endl;
	
	}

	return 0;
}
