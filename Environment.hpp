#include <iostream>
#include <tuple>

namespace rein {
namespace environment {
class Rock_Scissors_Paper {
	
	public:
		Rock_Scissors_Paper();
		Rock_Scissors_Paper(double rock_probability, double scissors_probability, double paper_probability);
		void initialize(double rock_probability, double scissors_probability, double paper_probability);
		std::tuple<int, int> battle(const int action_index);
		int get_current_state();
		int get_state_number();
		int get_action_number();
		double get_reward();
		void show_all_info();

	private:
		int is_win(int agent_action, int environment_action);
		double rock_probability = 1/3;
		double scissors_probability = 1/3;
		double paper_probability = 1/3;
		int current_state = 0;
		bool is_rock_chosed = false;
		bool is_scissors_chosed = false;
		bool is_paper_chosed = false;

};
	enum Action {
		ROCK = 0,
		SCISSORS = 1,
		PAPER = 2
	};
}
}
