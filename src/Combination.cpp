#include <iostream>
#include <algorithm>
#include "Combination.hpp"

namespace rein {

/**
 * @brief element_vectorをCombination::uncombination_tableに加える関数
 *
 * @param element_vector 組み合わせを考えたい要素
 *
 * 例えば，
 * - 状態sの一部
 * - 可能な行動aの一部
 *
 * \f[
 *	A \times B
 * \f]
 *
 * で定義される直積（デカルト積）のベクトルA，もしくはＢ
 */
void Combination::add(std::vector<double> element_vector){

	this->uncombination_table.emplace_back(element_vector);

}

/**
 * @brief 全通りの組み合わせを計算した後,いくつ組み合わせの種類ができたかを返す関数
 *
 * @return 組み合わせの種類の数
 *
 * もし，Combination::cart_product()が実行されていなければ
 * cart_product()を実行し，組み合わせの種類の数を得る．
 */
int Combination::size(){
	
	if (!this->did_cart_product) {
		this->cart_product();
	}
	return this->combination_table.size();
}

/**
 * @brief elementsを要素に持つcombination_tableのindexを調べ，そのindexを返す．
 *
 * @param elements Combination::combination_table[index]の要素
 *
 * @return もし，発見できれば，そのインデックスを返す．見つからなければ-1を返す． 
 */
int Combination::get_index(std::vector<double> elements){
	
	//catr_product()が実行されているか確認．
	//実行されていなければ，cart_product()をすぐに実行する．
	if (this->did_cart_product == false) {
		this->cart_product();
	}

	//combination_tableに要素が追加されていない場合のエラー処理
	if (this->combination_table.empty()) {
		std::cout << "[ error ] Combination::get_index() | No data is added. Please add data using Combination::add()" << std::endl;
		return -1;
	}
	else {
		//elementsの該当インデックスを探す
		auto itr = std::find(this->combination_table.begin(), this->combination_table.end(), elements);
		//もし，発見できなければエラーを起こす
		if (itr == this->combination_table.end()) {
			std::cout << "[ error ] Combination::get_index() | Could not find those elemens " << std::endl;
			return -1;
		}
		else {
			//発見できれば，そのインデックスを返す
			std::size_t index = std::distance(this->combination_table.begin(), itr);
			return (int)index;
		}
	}
}

/**
 * @brief 添字indexから，combination_table[index]を返す
 *
 * @param index combination_tableの添字．combination_table[index]
 *
 * @return indexが適切な値であれば，combination_table[index]を返す．そうでなければ空のstd::vectorを返す．
 * 
 * index+1 <= combination_table.size()であるならばindexは妥当
 * そうでないならば，indexは不適当でエラーを起こし，空のstd::vectorを返す．
 */
std::vector<double> Combination::get_elem(unsigned int index){

	//indexが要素数以下かどうか検証する
	if (index+1 <= (unsigned int)this->combination_table.size()) {
		return this->combination_table[index];
	}
	else {
		std::cout << "[ error ] Combination::get_elem() | index is not valid. index > size()" << std::endl;
		return {};
	}
}

/**
 * @brief 直積(デカルト積)を行う関数
 *
 * uncombination_table(計算される要素) -> combination_table(計算結果)
 * 実行後，combination_tableから全通りの組み合わせに関する情報を得ることが可能となる．
 */
void Combination::cart_product(){

	//cart_product()が既に実行されていなければ，実行する
	if (!this->did_cart_product) {
		std::vector<std::vector<double>> s = {{}};
		for(const auto& u : this->uncombination_table){
			std::vector<std::vector<double>> r;
			for(const auto& x : s){
				for(const auto& y : u){
					r.push_back(x);
					r.back().push_back(y);
				}
			}
			s = std::move(r);
		}
		//フラグを実行済みに変更
		this->did_cart_product = true;
		//計算結果をcombination_tableに移動
		this->combination_table = std::move(s);
	}
}

/**
 * @brief cart_product()を実行済みのcombination_tableを返す関数
 *
 * @return combination_table 
 *
 * 全通りの組み合わせの要素が格納された2次元std::vectorを返す．
 * cart_product()が以前に実行されていない場合，この関数内で実行される．
 */
std::vector<std::vector<double>> Combination::get_combination_table(){

	if (!this->did_cart_product) {
		this->cart_product();
	}
	
	return this->combination_table;
}

}
