#pragma once

#include <vector>

namespace rein{

class Combination {
	public:
		void add(std::vector<double> element_vector);
		int size();
		int get_index(std::vector<double> elements);
		std::vector<double> get_elem(unsigned int index);
		std::vector<std::vector<double>> get_combination_table();

	private:
		void cart_product();

		/**
		 * @brief デカルト積を１回のみ実行するためのフラグ
		 * デカルト積を２回実行する必要はないので，初回実行の後にこのフラグを立てる
		 */
		bool did_cart_product = false;

		/**
		 * @brief Combination::add()の引数のstd::vectorをこの変数に保存する
		 */
		std::vector<std::vector<double>> uncombination_table;

		/**
		 * @brief uncombination_tableに保存されている値を使ってデカルト積を実行し，その結果を変数に保存する
		 */
		std::vector<std::vector<double>> combination_table;
};

}
