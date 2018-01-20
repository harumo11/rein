#include <random>
#include "QLearn.hpp"

/**
 * @brief コンストラクタ 1 of 2
 *
 * パラメータを設定しないバージョンのコンストラクタ
 * 後でQLearn::initialize()によって各パラメータを設定する必要がある
 *
 */
QLearn::QLearn()
{
}

QLearn::QLearn(int state_number, int action_number, int initial_state, double alpha, double gamma) 
{
	this->initialize(state_number, action_number, initial_state, alpha, gamma);
}

bool QLearn::initialize(int state_number, int action_number, int initial_state, double alpha, double gamma) 
{
	//パラメータが正の値かどうかチェック
	if ((state_number > 0) && (action_number > 0) && (initial_state > 0) && (alpha > 0) && (gamma > 0)) {
		this->q_table.initialize(state_number, action_number); 
		this->state_index = initial_state;
		this->alpha = alpha;
		this->gamma = gamma;

		return true;
	}
	else {
		return false;
	}
}

/**
 * @brief epsilonの値を変更する
 *
 * epilon-greedy法で使用されるepsilonの値を変更する．
 * 小さな確率epsilonでランダムな行動が選択される．
 *
 * @return 設定変更の成否
 *
 * true -> epilon設定変更
 * false -> epsilonの設定はそのまま(param_epsilonが負の場合)
 */

bool QLearn::set_epsilon_param(const double param_epsilon){

	if (param_epsilon >= 0) {
		this->epsilon = param_epsilon;
		return true;
	}
	else {
		return false;
	}
}

/**
 * @brief　行動（の添字）を返す関数．
 *
 * epsilon-greedy方で行動を選択する
 * \TODO 他の方法も実装する
 *
 * @return 次に行う行動（の添字）
 */
int QLearn::action()
{
	return this->epsilon_greedy(this->q_table, this->state_index, this->epsilon);
}

/**
 * @brief epsilon-greedy方で次に行う行動を決定する関数
 *
 * @param q_table Qテーブル
 * @param greedy_probability greedyな選択を行う確率
 *
 * @return 次に行う行動（のインデックス）
 */
int QLearn::epsilon_greedy(Table q_table, int state, double epsilon_param){

	//乱数生成器を作成する
	std::random_device rand_generater;
	//生成する乱数の範囲を[0,1]に設定
	std::uniform_real_distribution<> rand_real_range(0, 1.0);

	int action;
	if (rand_real_range(rand_generater) > epsilon_param) {
		//greedyな選択
		action = q_table.get_max_row_index(state);
	}
	else {
		//randomな選択
		//行動の中からランダムに１つインデックスを選択する
		std::uniform_int_distribution<> rand_int_range(0, q_table.rows()-1);
		action = rand_int_range(rand_generater);
	}
	
	return action;
}
