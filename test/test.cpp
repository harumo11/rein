#include <iostream>
#include <rein/all.hpp>

int main(int argc, char const* argv[])
{
	rein::QLearn agent;
	agent.initialize(3, 3, 0);
	agent.q_table.show();
	std::cout << agent.q_table.cols() << std::endl;
	std::cout << agent.q_table.rows() << std::endl;
	return 0;
}
