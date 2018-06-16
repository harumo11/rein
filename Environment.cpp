#include <random>
#include "Environment.hpp"


/**
 * @brief コンストラクタ 1 of 2
 *
 * グー・チョキ・パーが出される確率はそれぞれ1/3に設定される．
 */
rein::Rock_Scissors_Paper::Rock_Scissors_Paper(){
}

/**
 * @brief コンストラクタ 2 of 2
 *
 * @param rock_probability		グーを出す確率
 * @param scissors_probability  チョキを出す確率
 * @param paper_probability		パーを出す確率
 *
 * (例)
 * Rock_Scissors_Paper(0.1, 0.1, 0.8)
 */
rein::Rock_Scissors_Paper::Rock_Scissors_Paper(double rock_probability,
											   double scissors_probability,
										   	   double paper_probability){
	this->initialize(rock_probability, scissors_probability, paper_probability);
}

void rein::Rock_Scissors_Paper::initialize(double rock_probability, double scissors_probability, double paper_probability){

	//引数の合計が1でなかった時のために，正規化を行う
	double sum = rock_probability + scissors_probability + paper_probability;
	this->rock_probability = rock_probability / sum;
	this->scissors_probability = scissors_probability / sum;
	this->paper_probability = paper_probability / sum;
}

/**
 * @brief じゃんけんをする関数
 *
 * 引数で入力した手でじゃんけんを行い．
 * 勝ち負けと，Environmentが出したを返す．
 *
 * @param action_index
 *
 * @return int 勝ち・負け・あいこ, int Environmentが繰り出した手
 *
 * |int|result      |
 * |----|------------|
 * |1|you win     |
 * |-1|you lose   |
 * |0 | win-win   |
 *
 * |int| action|enum|
 * |---|-------|----|
 * |0  |Rock   |Action::ROCK|
 * |1  |Scissors|Action::SCISSORS|
 * |2  |Paper   |Action::PAPER|
 *
 */
std::tuple<int, int> rein::Rock_Scissors_Paper::battle(const int action_index){

	//action_numberが負の値だった時，falseを返して終わる
	if (action_index < 0) {
		return std::forward_as_tuple(-1, -1);
	}

	std::random_device rand_dev;
	std::uniform_real_distribution<> rand_dist(0,1);
	double probability = rand_dist(rand_dev);

	if (probability < this->rock_probability) {
		this->is_rock_chosed = true;
		this->current_state = rein::ROCK;
	}
	else if (probability < this->scissors_probability){
		this->is_scissors_chosed = true;
		this->current_state = rein::SCISSORS;
	}
	else {
		this->is_paper_chosed = true;
		this->current_state = rein::PAPER;
	}
}

/**
 * @brief 勝ち・負け・アイコをagentとEnvironmentの手によって
 * 判断する関数．
 *
 * @param agent_action agentの手を表す．[0,1,2]
 * @param environment_action Environmentの手を表す.[0,1,2]
 *
 * @return 勝ち・負け・アイコ
 *
 * |win|lose|win-win|
 * |---|----|-------|
 * |+1 |-1  |0      |
 *
 * 判定は下記のように行う.
 * |Agent                       |
 * |--------|----|--------|-----|
 * |/       |rock|scissors|paper|
 * |rock    | 0  |-1      |1    |
 * |scissors|+1   | 0      |-1   |
 * |paper   |-1  |+1      |0    |
 */
int rein::Rock_Scissors_Paper::is_win(int agent_action, int environment_action){
}
