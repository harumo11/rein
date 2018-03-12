#include <random>
#include <tuple>
#include "../include/rein/QLearn.hpp"

namespace rein {

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


/**
 * @brief コンストラクタ 2 of 2
 *
 * パラメータを設定するバージョンのコンストラクタ
 * 
 * @param state_number 状態sの数
 * @param action_number 可能な行動aの数
 * @param initial_state 最初の状態s
 * @param alpha \f$ \alpha \f$ of following equation
 * @param gamma \f$ \gamma \f$ of following equation
 *
 * \f[
 *		Q_(s_t,a) \gets Q_(s_t,a) + \alpha \Bigl[ r_{t+1} + \gamma \max_{a} Q(s_{t+1},a) -Q(s_t,a) \Bigr]
 * \f]
 */
QLearn::QLearn(int state_number, int action_number, int initial_state, double alpha, double gamma) 
{
	this->initialize(state_number, action_number, initial_state, alpha, gamma);
}

/**
 * @brief 初期化関数，イニシャライザー
 *
 * @param state_number 状態sの数
 * @param action_number 可能な行動aの数
 * @param initial_state 最初の状態s
 * @param initial_state 最初の状態s
 * @param alpha \f$ \alpha \f$ of following equation
 * @param gamma \f$ \gamma \f$ of following equation
 *
 * @return パラメータの設定が成功したかどうか(成功->true, 失敗->false)
 * パラメータが府の値の場合失敗する
 */
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
	this->action_index =  this->epsilon_greedy(this->q_table, this->state_index, this->epsilon);
	return this->action_index;
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

double QLearn::update(int state_dash_index, double reward){

	this->state_dash_index = state_dash_index;

	double modified_q_value = this->q_table.data[this->state_index][this->action_index];
	double sigma = reward + this->gamma * this->q_table.get_max_row_value(this->state_dash_index)
		        - this->q_table.data[this->state_index][this->action_index];
	modified_q_value += this->alpha * sigma;

	//更新則によって計算された値でq_tableを更新
	this->q_table.data[this->state_index][action_index] = modified_q_value;

	//使用したQ(s,a)とmaxQ(s',a')を変数に格納（参照用）
	this->q_value_dash = this->q_table.get_max_row_value(this->state_dash_index);
	this->q_value = modified_q_value;

	//state_indexをstate_dash_indexに更新する
	this->state_index = this->state_dash_index;

	return modified_q_value;
}

/**
 * @brief 現在設定されているパラメータを返す関数
 *
 * @return \f$ \alpha, \gamma, \epsilon \f$ 
 *
 * |Order|Parameter|
 * |:---:|:-------:|
 * |0    |\f$ \alpha   \f$ |
 * |1    |\f$ \gamma   \f$ |
 * |2    |\f$ \epsilon \f$ |
 *
 * How to get params
 *
 * \code{.cpp}
 * double a;
 * double g;
 * double e;
 *
 * QLearn agent;
 * ...
 * ...
 * std::tie(a,g,e) = agent.get_params();
 *
 * std::tie(std::ignore,g,e) = agent.get_params();
 *
 * \endcode
 */
std::tuple<double, double, double> QLearn::get_params(){
	return std::forward_as_tuple(this->alpha, this->gamma, this->epsilon);
}

/**
 * @brief パラメータ\f$ \alpha \f$を設定する関数
 *
 * @param param_alpha 設定したい値
 *
 * @return 設定変更が成功->true, 失敗->false
 * param_alphaが負の場合失敗する
 */
bool QLearn::set_alpha_param(const double param_alpha){

	if (param_alpha > 0) {
		this->alpha = param_alpha;
		return true;
	}
	else {
		return false;
	}
}

/**
 * @brief パラメータ\f$ \gamma \f$を設定する関数
 *
 * @param param_gamma 設定したい値
 *
 * @return 設定変更が成功->true, 失敗->false
 * param_gammaが負の場合失敗する
 */
bool QLearn::set_gamma_param(const double param_gamma){

	if (param_gamma > 0) {
		this->gamma = param_gamma;
		return true;
	}
	else {
		return false;
	}
}

}
