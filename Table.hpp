#pragma once

#include <iostream>
#include <string>
#include <vector>

class Table {
	public:
		Table(int state_number, int action_number);
		std::vector<double> slice_row(int row_number);
		std::vector<double> slice_col(int column_number);
		double get_max_row_value(int row_number);
		double get_max_col_value(int column_number);
		int get_max_row_index(int row_number);
		int get_max_col_index(int colmun_number);
		void reset_all(double value);
		void show();
		void save_as_dat(const std::string file_name);
		void save_as_csv(const std::string file_name);
		void load_csv(const std::string csv_file);
		void load_dat(const std::string dat_file);

		//２次元配列のテーブル本体
		std::vector<std::vector<double>> data;

	private:
		void error_display(std::string error_content);
		std::vector<std::string> split_str(const std::string data, const char delim);
		std::vector<double> convert_str_to_double(const std::vector<std::string> str_vector);
};
