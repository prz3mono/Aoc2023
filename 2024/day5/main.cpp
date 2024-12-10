#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

bool isCorrect(const std::vector<unsigned int>& order, const std::vector<std::pair<unsigned int, unsigned int>> rules)
{
	for(auto rule: rules)
	{
		auto it_f = std::find(order.begin(), order.end(), rule.first);
		if(it_f == order.end()) continue; 
		auto it_s = std::find(order.begin(), it_f, rule.second);
		if(it_s != it_f) return false;
	}

	return true;
}

int main(int argc, char* argv[])
{
	//std::ifstream infile("input.txt");
	std::ifstream infile("example.txt");
	std::string line;
	std::vector <std::pair<unsigned int, unsigned int> > rules;
	std::vector<std::vector<unsigned int> > page_orders;

	infile >> line;
	while(line.size() == 5)
	{
		unsigned int a = stoi(line);
		unsigned int b = stoi(line.substr(line.find('|') + 1));
		rules.push_back(std::pair(a,b));
		infile >> line;
	}
	for (auto el: rules) std::cout << el.first << "|" << el.second << std::endl;

	do	
	{
		std::vector<unsigned int> page_order;		
		std::string page;
		std::stringstream s_line(line);
		while(std::getline(s_line, page, ','))	
		{
			page_order.push_back(stoi(page));
		}
		page_orders.push_back(page_order);
	}while(infile >> line);
	
	std::cout << "Pages----------------------------------" << std::endl;
	for (auto el: page_orders)
	{
		for (auto el2: el) std::cout << el2 << ",";
		std::cout << std::endl;
	}
	
	//----------------------------------------------------------------------
	std::vector<std::vector<unsigned int> > correct_page_orders;
	for (auto page_order: page_orders)
	{	
		std::cout << "Is correct: " << isCorrect(page_order, rules) << std::endl;
		if(isCorrect(page_order, rules)) correct_page_orders.push_back(page_order);
	}
	
	unsigned int sum{0};
	for(auto order: correct_page_orders)
	{
		sum+=order[order.size()/2];
	}

	std::cout << "Sum: " << sum << std::endl;

	return 0;
}

