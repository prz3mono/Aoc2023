#include <iostream>
#include <fstream>
#include <algorithm>
#include <array>
#include <limits>
#include <exception>
#include <iterator>

class MyException: public std::exception
{
	public:
	MyException(std::string a_msg)
		:msg{a_msg}
	{}
	const char* what()
	{
		return msg.c_str();
	}

	private:
	std::string msg;
};

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
	throw MyException("Wrong digit string");
}

int main(int argc, char* argv[])
{
	std::ifstream infile("input.txt");
	std::string line;
	int sum{0};
	int sum_part2{0};

	while(infile >> line)
	{
		auto firstDigit = std::find_if(line.begin(), line.end(), [](const char& leter){return leter <= '9';});
		auto lastDigit = std::find_if(line.rbegin(), line.rend(), [](const char& leter){return leter <= '9';});
		int number = std::stoi(std::string{*firstDigit} + *lastDigit);
		sum+=number;
//part 2
//------------------------------------------------------------------------------------------------------------------------------

		unsigned int firstDigtVal = std::stoi(std::string{*firstDigit});
		unsigned int lastDigtVal = std::stoi(std::string{*lastDigit});

		size_t firstDigitDistance = findFirstDigitName(line);
		if (( not (firstDigitDistance == std::string::npos)) and firstDigitDistance < std::distance(line.begin(), firstDigit))
		{
				firstDigtVal = digit2I(line.substr(firstDigitDistance));
		}

		size_t lastDigitDistance = findLastDigitName(line);
		if (( not (lastDigitDistance == std::string::npos)) and (lastDigitDistance > (std::distance(line.begin(),lastDigit.base()) - 1)))
		{
			lastDigtVal = digit2I(line.substr(lastDigitDistance));
		}

		int val = firstDigtVal*10 + lastDigtVal;

		sum_part2+=val;


	}

	std::cout << "SumValue: " << sum << std::endl;
	std::cout << "SumValue part2: " << sum_part2 << std::endl;
	return 0;
}
