#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

class SingleTransformer
{
	public:
	SingleTransformer(unsigned long int destination, unsigned long int source, unsigned long int rang)
		:source_min{source}, 
		source_max{source + rang - 1},
		destination_min{destination},
		destination_max{destination + rang - 1},
		transform_factor{destination-source}
	{}
	unsigned long int transform(unsigned long int arg)
	{
		return arg+transform_factor;	
	}

	unsigned long int reverseTransform(unsigned long int arg)
	{
		return arg-transform_factor;	
	}

	bool isInRange(unsigned long int arg)
	{
		if ((arg < source_min) or ( arg > source_max)) return false;
		return true;
	}

	bool isInReverseRange(unsigned long int arg)
	{
		if ((arg < destination_min) or ( arg > destination_max)) return false;
		return true;
	}


	private:
		unsigned long int source_min;
		unsigned long int source_max;
		unsigned long int destination_min;
		unsigned long int destination_max;
		long int transform_factor;


};

class Transformer
{
	public:
	Transformer(std::vector<SingleTransformer> a_transformers)
		:transformers{a_transformers}
	{}

	unsigned long int transform(unsigned long int arg)
	{
		for( auto& transformer:transformers)
		{
			if(transformer.isInRange(arg)) return transformer.transform(arg);
		}
		return arg;
	}

	unsigned long int reverseTransform(unsigned long int arg)
	{
		for( auto& transformer:transformers)
		{
			if(transformer.isInReverseRange(arg)) return transformer.reverseTransform(arg);
		}
		return arg;
	}
	std::vector<SingleTransformer> transformers;


};




int main(int argc, char* argv[])
{
	std::ifstream infile("input.txt");

	std::string line;
	std::string ignore;

	getline(infile,line);
	std::stringstream ss (line);
	ss >> ignore;

	std::vector<unsigned long int> seeds;
	std::string seed_number;

	while(ss >> seed_number) seeds.push_back(stoul(seed_number));

	std::vector<Transformer> transformers;


	getline(infile,line);
	getline(infile,line);

	std::vector<SingleTransformer> single_transformers;
	std::vector<unsigned long int> potential_seeds2;
	while(getline(infile,line))
	{
		if(line.compare("") == 0)
		{
			transformers.push_back(Transformer(single_transformers));
			single_transformers.clear();
			getline(infile,line);
			continue;
		}

		std::stringstream ss{line};
		std::string buff;

		ss >> buff;
		unsigned long int destination{stoul(buff)}; 

		ss >> buff;
		unsigned long int source{stoul(buff)};

		ss >> buff;
		unsigned long int range{stoul(buff)};

		single_transformers.push_back(SingleTransformer(destination, source, range));

		potential_seeds2.push_back(source);
		if (source > 0) potential_seeds2.push_back(source - 1);

		potential_seeds2.push_back(source + range);
		potential_seeds2.push_back(source + range - 1);

		potential_seeds2.push_back(destination);
		if (destination > 0) potential_seeds2.push_back(destination - 1);

		potential_seeds2.push_back(destination + range);
		potential_seeds2.push_back(destination + range - 1);

		
	}

		transformers.push_back(Transformer(single_transformers));
		//std::cout << "Transforems: " << transformers.size() << std::endl;


		std::vector<unsigned long int> humidity;

		for (auto seed:seeds)
		{
			for(auto transformer: transformers)
			{
				seed = transformer.transform(seed);
			}
			std::cout << seed << std::endl;
			humidity.push_back(seed);
		}

		std::cout << "Solution " << *(std::min_element(humidity.begin(), humidity.end())) << std::endl;
		//--------------------------------------------------------------------------------------------------

		std::vector<std::pair<unsigned long int, unsigned long int> > input_ranges;
                for (auto it = seeds.begin(); it < seeds.end(); std::advance(it, 2))
                {
                        input_ranges.push_back(std::pair(*it, (*it) + (*std::next(it)) - 1));
                }

		for(auto re:input_ranges)
		{
			std::cout << "Input range: (" << re.first << ", " << re.second << ")" << std::endl;

		}


		unsigned long int humidity2{0};
		unsigned long int seed2{0};
		for(;;++humidity2)
		{
			seed2 = humidity2;;
			for(auto it=transformers.rbegin(); it < transformers.rend(); std::advance(it,1))
			{
				seed2 = it->reverseTransform(seed2);
				
			}	
			if(std::any_of(input_ranges.begin(), input_ranges.end(), [seed2](std::pair<unsigned long int, unsigned long int> in_range)
										{return ((in_range.first <= seed2) and (seed2 <= in_range.second));}))
			{
				break;
			}
		}



		std::cout << "Solution2 " << humidity2 << std::endl;

	return 0;
}
