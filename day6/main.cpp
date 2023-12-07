#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

int main(int argc, char* argv[])
{
	//std::vector<std::pair<int,int> > input{{7,9},{15,40},{30,200}};
	//std::vector<std::pair<int,int> > input{{53,313},{89,1090},{76,1214},{98,1201}};

	
	//std::vector<std::pair<double, double> > input{{71530,940200}};
	std::vector<std::pair<double, double> > input{{53897698,313109012141201}};

	//distance=pressing_time*(total_time-pressing_time)
	//reord < -p^2 + p*T
	//0 < -p^2 +p*T - record
	
	//delta = b^2 - 4ac = T^2 + 4r 
	//x1 = (-b+sqrt(delta))/2a= (1/2)(T+sqrt(T^2 - 4r))
	//x2 = (-b-sqrt(delta))/2a= (1/2)(T-sqrt(T^2 - 4r))
	//since T,r > 0 => x1 > x2
	// solution = ceil(x1) - ceil(x2);


	int resoult{1};


	for(auto el:input)
	{
		double& time = el.first;
		double& record = el.second;
		double p1 = ((time + (std::sqrt(time*time - 4*record)))/2);
		double p2 = ((time - (std::sqrt(time*time - 4*record)))/2);


		int solution = std::floor(p1) - std::floor(p2);
		const double EPSILON = 1.0e-10;
		if((p1 - std::floor(p1) < EPSILON)  or (p2 - std::floor(p2) < EPSILON)) --solution;

		std::cout << p1 << "," << p2 << std::endl;
		std::cout << solution << std::endl;
		resoult*=solution;
	}
	std::cout << "Part A sol: " << resoult << std::endl;

	return 0;
}
