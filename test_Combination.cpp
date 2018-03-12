#include <iostream>
#include <vector>
#include "Combination.hpp"

int main(int argc, char const* argv[])
{
	std::vector<double> A = {1,2,3};
	std::vector<double> B = {4,5,6};

	Combination table;
	table.add(A);
	table.add(B);

	std::cout << "[size()]\t\t" << table.size() << std::endl;
	std::cout << "[get_index(1,4)]\t" << table.get_index({1.0,4.0}) << std::endl;
	
	std::cout << "[get_elem(1)]\t\t";
	for (auto&& e : table.get_elem(1)){
		std::cout << e << ',';
	}
	std::cout << std::endl;

	auto result = table.get_combination_table();
	std::cout << "[get_combination_table]\t" << std::endl;
	for(auto&& vec : result){
		for(auto&& elem : vec){
			std::cout << elem << ',';
		}
		std::cout << std::endl;
	}
	return 0;
}
