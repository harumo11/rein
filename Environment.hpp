#include <iostream>

namespace rein {
class Rock_Scissors_Paper {
	
	public:
		Rock_Scissors_Paper();
		Rock_Scissors_Paper(double Rock_probability, double Scissors_probability, double Paper_probability);
		void initialize(double Rock_probability, double Scissors_probability, double Paper_probability);
		bool set_action(int action_index);
		int get_current_state();
		int get_state_number();
		int get_action_number();
		double get_reward();

};

}
