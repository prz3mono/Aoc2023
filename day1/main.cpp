#include <iostream>
#include <fstream>
#include <algorithm>
#include <array>
#include <limits>
#include <exception>

const std::array<std::string, 9> DIGIT_NAMES{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

size_t findFirstDigitName(std::string arg)
{
	size_t result = std::numeric_limits<size_t>::max(); 
	bool found{false};

	for(std::string name: DIGIT_NAMES)
	{
		size_t poz = arg.find(name);
		if (poz == std::string::npos) continue;
		found = true;
		result = poz < result ? poz:result;
	}
	if (not found) return std::string::npos;
	return result;
}

size_t findLastDigitName(std::string arg)
{
	size_t result{0}; 
	bool found = false;

	for(std::string name: DIGIT_NAMES)
	{
		size_t poz = arg.rfind(name);
		if (poz == std::string::npos)
		{
		       	continue;
		}
		found = true;
		result = poz > result ? poz:result;
	}

	if (not found) return std::string::npos;
	return result;
}


unsigned short int digit2I(std::string arg)
{
	for (int i = 0; i < DIGIT_NAMES.size() ; ++i) 
	{
		if(arg.substr(0, DIGIT_NAMES[i].size()) == DIGIT_NAMES[i]) return i + 1;
	}
	throw std::exception("Wrong digit string");
}

int main(int argc, char* argv[])
{
	std::ifstream infile("input2.txt");
	std::string line;
	int sum{0};
/*
	while(infile >> line)
	{
		auto firstDigit = std::find_if(line.begin(), line.end(), [](const char& leter){return leter <= '9';});
		auto lastDigit = std::find_if(line.rbegin(), line.rend(), [](const char& leter){return leter <= '9';});
		int number = std::stoi(std::string{*firstDigit} + *lastDigit);
		std::cout << line << " :" << number << std::endl;
		sum+=number;
	}
	std::cout << "SumValue: " << sum << std::endl;
*/

	while(infile >> line)
	{
		auto firstDigit = std::find_if(line.begin(), line.end(), [](const char& leter){return leter <= '9';});
		auto lastDigit = std::find_if(line.rbegin(), line.rend(), [](const char& leter){return leter <= '9';});
		int number = std::stoi(std::string{*firstDigit} + *lastDigit);
		//std::cout << line << " :" << number << std::endl;
		unsigned int sFirstDigit;
		size_t sFirstDigitPoz = findFirstDigtName(line);
		if(sFirstDigitPoz != std::string:npos)
		{
			if (std::distatnce(line.begin(), firstDigit) > sFirstDigitPoz)
			{
				//sFirstDigit = digit2I(


			}
		}

		std::cout << "First :" << findFirstDigitName(line) <<  "   Last: " << findLastDigitName(line) << std::endl; 
		sum+=number;
	}

	std::cout << "SumValue: " << sum << std::endl;
	return 0;
}
