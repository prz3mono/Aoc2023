#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <algorithm>
#include <cmath>
#include <optional>

class Card
{
	public:
		Card(unsigned int a_ID, unsigned int a_nMathes)
			: ID{a_ID}, nMathes{a_nMathes}, score()
		{}
	unsigned int ID;
	unsigned int nMathes;
	std::optional<unsigned int> score;
};

unsigned int calcScore(Card& card, std::vector<Card>& cards)
{
	if(card.nMathes == 0) return 1;
	if(card.score.has_value()) return *(card.score);

	card.score=0;
	for(unsigned int i = 1; i<=card.nMathes; ++i)
	{
		card.score = *(card.score) + calcScore(cards[card.ID + i - 1], cards);
	}
	card.score = *(card.score) + 1;
	return  (*(card.score));
}


int main(int argc, char* argv[])
{
	std::ifstream infile("input.txt");
	std::string ignore;
	unsigned int sum{0};
	infile >> ignore;
	unsigned int i{1};
	std::vector<Card> cards;

	while(infile >> ignore)
	{
		std::vector<unsigned int> winningNumbers;
		std::vector<unsigned int> myNumbers;
		std::string buff;

		while(infile >> buff)
		{
			if(buff.compare("|") == 0) break;
			winningNumbers.push_back(stoi(buff));
		}
			
		while(infile >> buff)
		{
			if(buff.compare("Card") == 0) break;
			myNumbers.push_back(stoi(buff));
		}

		std::sort(winningNumbers.begin(), winningNumbers.end());
		std::sort(myNumbers.begin(), myNumbers.end());

		std::vector<unsigned int> intersection;
		std::set_intersection(winningNumbers.begin(), winningNumbers.end(), myNumbers.begin(), myNumbers.end(), std::back_inserter(intersection));

		unsigned int size = intersection.size();
		if(size > 0) sum+= std::pow(2, size-1);
		cards.push_back(Card(i,size));

		++i;
	}



	unsigned int sum2{0};
	for (auto & card: cards)
	{
		sum2+=calcScore(card,cards); 
	}
	std::cout << "Part A : " << sum << std::endl;
	std::cout << "Part B : " << sum2 << std::endl;

	return 0;
}
