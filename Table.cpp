#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "Table.hpp"

/**
 * @brief コンストラクタ 1 of 2
 *
 * デフォルトコンストラクタ
 * 後で，Table::initialize(int state_number, int aciotn_number)
 * によりstate_numberとaction_numberを指定する必要がある
 */
Table::Table(){
}

/**
 * @brief コンストラクタ 2 of 2
 *
 * 引数のstate_number x action_numberの２次元配列を作成する
 *
 * @param state_number 状態数
 * @param action_number 可能な行動の数
 */
Table::Table(const unsigned int state_number, const unsigned int action_number){

	this->initialize(state_number, action_number);
}

/**
 * @brief エラーを装飾する関数
 *
 * 自動的に関数名と引数の型を表示する
 *
 * @param error_content 表示したいエラー内容
 */
void Table::error_display(std::string error_content){
	std::cout << "||| error Table " << __PRETTY_FUNCTION__ 
		      << " " << error_content << std::endl;
}

/**
 * @brief Tableクラスを指定したパラメータで初期化する
 *
 * @param state_number 状態数
 * @param action_number 可能な行動の数
 */
void Table::initialize(const unsigned int state_number, const unsigned int action_number){

	//引数が正の数かどうかチェックする
	if (state_number == 0) {
		this->error_display("state_number argument must be positive");
		std::exit(0);
	}
	if (action_number == 0) {
		this->error_display("action_number argument must be positive");
		std::exit(0);
	}

	//テーブルを作成する
	for (unsigned int i = 0; i < state_number; i++) {
		this->data.emplace_back(std::vector<double>(action_number, 0));
	}

	//set row and collumn from state number and action number.
	this->col = state_number;
	this->row = action_number;
}

/**
 * @brief ある行でテーブルをスライスし，その行を取り出す．
 *
 * @param row_number 何行目を取り出すかを指定する引数
 *
 * @return とり出された行
 */
std::vector<double> Table::slice_row(int row_number){
	return this->data[row_number];
}

/**
 * @brief ある列でテーブルをスライスし，その列を取り出す．
 *
 * @param col_number 何列目を取り出すかを指定する引数
 *
 * @return とり出された列
 */
std::vector<double> Table::slice_col(int col_number){
	std::vector<double> vec;

	for (int i = 0; i < (int)this->data.size(); i++) {
		vec.push_back(this->data[i][col_number]);
	}

	return vec;
}

/**
 * @brief 引数で指定された行の最大値を返す
 *
 * @param row_number 列を指定する
 *
 * @return row_numberで指定した行の最大値
 */
double Table::get_max_row_value(int row_number){
	return *std::max_element(this->data[row_number].begin(), this->data[row_number].end());
}

/**
 * @brief 引数で指定された列の最大値を返す
 *
 * @param colmun_number 行を指定する
 *
 * @return colmun_numberで指定した列の最大値
 */
double Table::get_max_col_value(int colmun_number){
	auto vec = this->slice_col(colmun_number);
	return *std::max_element(vec.begin(), vec.end());
}

/**
 * @brief 全ての要素を引数で与えられた数にする
 *
 * @param value 要素に指定したい数
 */
void Table::reset_all(double value){
	for (auto&& vec : this->data){
		for (auto&& elem : vec){
			elem = value;
		}
	}
}

/**
 * @brief 指定した行における最大値の添字を得る
 *
 * @param row_number 最大値の添字を得たい行数
 *
 * @return 指定した行における最大値の添字
 */
int Table::get_max_row_index(int row_number){
	auto max_itr = std::max_element(this->data[row_number].begin(), this->data[row_number].end());
	return (int)std::distance(this->data[row_number].begin(), max_itr);
}

/**
 * @brief 指定した列における最大値の添字を得る
 *
 * @param column_number 最大値の添字を得たい列数
 *
 * @return 指定した列における最大値の添字
 */
int Table::get_max_col_index(int colmun_number){
	std::vector<double> vec = this->slice_col(colmun_number);
	auto max_itr = std::max_element(vec.begin(), vec.end());
	return (int)std::distance(vec.begin(), max_itr);
}

/**
 * @brief 全データを表示する関数
 *
 * テーブルが大きい場合には，はみ出るため，おすすめしない．
 */
void Table::show(){
	std::cout << "----------------Table--------------" << std::endl;
	for (auto&& vec : this->data){
		for (auto&& elem : vec){
			std::cout << elem << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "----------------Table--------------" << std::endl;
}

/**
 * @brief dat形式でTableの中身を保存する関数
 *
 * gnuplotなどでTableの中身を見るときに使用する
 *
 * @param file_name 保存するファイル名(e.g. table.dat)
 */
void Table::save_as_dat(const std::string file_name){
	std::ofstream file;
	file.open(file_name);

	if (file.is_open()) {
		for (auto&& vec : this->data){
			for (auto&& elem : vec){
				file << elem << " ";
			}
			file << std::endl;
		}
		file.close();
	}
	else {
		this->error_display("Can't open the file to save as dat");
	}
}

/**
 * @brief csv形式でTableの中身歩を保存する関数
 *
 * 表計算ソフトでTableの中身を見るときに使用する
 *
 * @param file_name 保存するファイル名(e.g. table.csv)
 */
void Table::save_as_csv(const std::string file_name){
	std::ofstream file;
	file.open(file_name);

	if (file.is_open()) {
		for (auto&& vec : this->data){
			for (auto&& elem : vec){
				file << elem << ',';
			}
			file << std::endl;
		}
		file.close();
	}
	else {
		this->error_display("Can't open the file to save as csv");
	}

}

/**
 * @brief std::vector<std::string>をstd::vector<double>に変換する関数
 *
 * @param str_vector 変換したいstd::vector<std::string>
 *
 * @return 変換されたstd::vector<double>
 */
std::vector<double> Table::convert_str_to_double(const std::vector<std::string> str_vector){

	std::vector<double> result;
	for (auto&& word : str_vector){
		result.push_back(std::stod(word));
	}

	return result;
}

/**
 * @brief 読み込んだstd::stringをdelimごとに分割する関数
 *
 * @param data 分割される対象となる文字列.delimを含む．
 * @param delim 文字列を分割する区切りとなる文字
 *
 * @return 分割された文字がstd::vector<std::string>に詰められたもの
 */
std::vector<std::string> Table::split_str(const std::string data, const char delim){

	std::stringstream line(data);
	std::string word;
	std::vector<std::string> result;

	while (std::getline(line, word, delim)) {
		result.push_back(word);
	}

	return result;
}

/**
 * @brief csvファイルに記述されたTable情報を読みだす
 *
 * @param csv_file Table情報が書かれたcsvファイルの名前
 */
void Table::load_csv(const std::string csv_file){

	std::ifstream load_file(csv_file);
	std::string line;

	//dataを初期化
	this->data.clear();

	if (load_file.is_open()) {
		while (std::getline(load_file, line)) {
			//','で分解する
			auto word_vector = this->split_str(line, ',');
			//stringをdoubleに変換する
			auto num_vector  = this->convert_str_to_double(word_vector);
			//Tableのdataに格納する
			this->data.push_back(num_vector);
		}
	}
	else {
		this->error_display("Can't load file. Dose it exist?");
	}
}

void Table::load_dat(const std::string dat_file){

	std::ifstream load_file(dat_file);
	std::string line;

	//dataを初期化
	this->data.clear();

	if (load_file.is_open()) {
		while (std::getline(load_file, line)) {
			//','で分解する
			auto word_vector = this->split_str(line, ' ');
			//stringをdoubleに変換する
			auto num_vector  = this->convert_str_to_double(word_vector);
			//Tableのdataに格納する
			this->data.push_back(num_vector);
		}
	}
	else {
		this->error_display("Can't load file. Dose it exist?");
	}

}

/*
 * @brief Tableの行の数を返す
 *
 */
int Table::cols(){
	return this->col;
}

/*
 * @brief Tableの列の数を返す
 */
int Table::rows(){
	return this->row;
}
