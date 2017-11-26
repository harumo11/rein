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

int QLearn::action()
{

}
