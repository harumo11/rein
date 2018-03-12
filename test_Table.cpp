#include <iostream>
#include "Table.hpp"

int main(int argc, char const* argv[])
{
	
	rein::Table t(3, 2);
	auto v1 = t.slice_col(1);
	auto v2 = t.slice_row(0);

	for (int i = 0; i < (int)v1.size(); i++) {
		std::cout << v1[i];
	}

	std::cout << std::endl;

	for (int i = 0; i < (int)v2.size(); i++) {
		std::cout << v2[i];
	}
	std::cout << std::endl;

	std::cout << "max row value = " << t.get_max_col_value(0) << std::endl;
	std::cout << "max col value = " << t.get_max_row_value(0) << std::endl;

	t.reset_all(2);
	t.show();
	t.save_as_dat("table.dat");
	t.save_as_csv("table.csv");

	std::vector<std::vector<double>> t1 = {{1,2,3},{4,5,6}};
	t.data = t1;
	std::cout << "get max row = " << t.get_max_row_value(0) << std::endl;
	std::cout << "get max row index = " << t.get_max_row_index(0) << std::endl;
	std::cout << "get max col = " << t.get_max_col_value(1) << std::endl;
	std::cout << "get max col index = " << t.get_max_col_index(1) << std::endl;
	t.show();

	t.load_csv("test.csv");
	t.show();
	t.load_dat("test.dat");
	t.show();

	return 0;
}
