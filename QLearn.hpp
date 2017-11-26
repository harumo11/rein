#pragma once

#include "Table.hpp"

class QLearn {
	public:
		QLearn();
		QLearn(int state_number, int action_number, int initial_state, double alpha_param = 0.7, double gamma_param = 0.7);
		bool initialize(int state_number, int action_number, int initial_state, double alpha_param = 0.7, double gamma_param = 0.7);
		int action();
		double update(int state_dash, double reward);

	private:
		double alpha;
		double gamma;
		double q_value;
		double q_value_dash;
		int state_index;
		int state_dash_index;
		int action_index;
		int state_number;
		int action_number;
		Table q_table;
};


