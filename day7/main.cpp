#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <tuple>
#include <sstream>

enum class Type 
{
	HIGH_CARD,
	ONE_PAIR,
	TWO_PAIR,
	TREE_OF_KIND,
	FULL_HOUSE,
	FOUR_OF_A_KIND,
	FIVE_OF_A_KIND
};

std::string type2String(Type arg)
{
	switch(arg)
	{
		case Type::HIGH_CARD:
			return "HIGHT_CARD";
		case Type::ONE_PAIR:
			return "ONE_PAIR";
		case Type::TWO_PAIR:
			return "TWO_PAIR";
		case Type::TREE_OF_KIND:
			return "TREE_OF_KIND";
		case Type::FULL_HOUSE:
			return "FULL_HOUSE";
		case Type::FOUR_OF_A_KIND:
			return "FOUR_OF_A_KIND";
		case Type::FIVE_OF_A_KIND:
			return "FIVE_OF_A_KIND";
	}
	return "UNKNOWN";
}

class Hand
{
	public:
	Hand(std::string arg, unsigned int a_bid)
		: bid{a_bid}
	{
		for(char card:arg)
		{
			switch (card)
			{
			  case 'T':
				cards.push_back(10);
			     break;
			  case 'J':
				cards.push_back(11);
			     break;
			  case 'Q':
				cards.push_back(12);
			     break;
			  case 'K':
				cards.push_back(13);
			     break;
			  case 'A':
				cards.push_back(14);
			     break;
			  default:
			       cards.push_back(card - '0');
			}
		}	
		std::set<unsigned int> tmp_set(cards.begin(), cards.end());
		if(tmp_set.size() == 1) type = Type::FIVE_OF_A_KIND;
		else if(tmp_set.size() == 5) type = Type::HIGH_CARD;
		else if(tmp_set.size() == 4) type = Type::ONE_PAIR;
		else if(tmp_set.size() == 3) 
		{
			if(std::any_of(tmp_set.begin(), tmp_set.end(), [this](unsigned int cr)
					{return std::count(this->cards.begin(), this->cards.end(), cr) == 3;}))
			{
				type = Type::TREE_OF_KIND;

			}else type = Type::TWO_PAIR;
		}else
		{
			if(std::any_of(tmp_set.begin(), tmp_set.end(), [this](unsigned int cr)
					{return std::count(this->cards.begin(), this->cards.end(), cr) == 4;}))
			{
				type = Type::FOUR_OF_A_KIND;

			}else type = Type::FULL_HOUSE;
		}

	}
	bool operator<(const Hand& rhs)
	{
		return std::tie(this->type, this->cards[0], this->cards[1], this->cards[2], this->cards[4], this->cards[5])
		     < std::tie(rhs.type, rhs.cards[0], rhs.cards[1], rhs.cards[2], rhs.cards[4], rhs.cards[5]);

	}

	std::string print()
	{
		std::stringstream ss;
		ss << "Card: " << cards[0] << ", "
				      << cards[1] << ", "
				      << cards[2] << ", "
				      << cards[3] << ", "
				      << cards[4] << "\t" 
				      << type2String(type)
				      << "\t" << bid; 
		return ss.str();
	}
	
	//private:
		unsigned int bid;
		std::vector<int> cards;
		Type type;


};


int main(int argc, char* argv[])
{
	std::ifstream infile("input.txt");
	
	std::string cards;
	std::string bid;
	std::vector<Hand> hands;

	while(infile >> cards >> bid)
	{
		hands.push_back(Hand(cards, stoi(bid)));
	}

	std::sort(hands.begin(), hands.end());
	for(auto hand:hands)
	{
		//hand.print();
	}

	unsigned long int sum {0};
	unsigned long int current_rank{1};

	for(auto hand:hands)
	{
		sum+=(current_rank*hand.bid);	
		std::cout << hand.print() << "\t" << sum << "\t" <<  current_rank << "\t" << current_rank*hand.bid << std::endl;
		++current_rank;
	}
	std::cout << "Sol A: " << sum << std::endl;

	return 0;
}
