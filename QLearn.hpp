#pragma once

#include "Table.hpp"

class QLearn {
	public:
		QLearn();
		QLearn(int state_number, int action_number, int initial_state, double alpha_param = 0.7, double gamma_param = 0.7);
		bool initialize(int state_number, int action_number, int initial_state, double alpha_param = 0.7, double gamma_param = 0.7);
		int action();
		double update(int state_dash, double reward);
		bool set_epsilon_param(const double param_epsilon);
		bool set_alpha_param(const double param_alpha);
		bool set_gamma_param(const double param_gamma);
		std::tuple<double, double, double> get_params();

		Table q_table;

	private:
		double alpha = 0.7;
		double gamma = 0.7;
		double epsilon = 0.2;
		double q_value;
		double q_value_dash;
		int state_index;
		int state_dash_index;
		int action_index;

		int epsilon_greedy(Table q_table, int state, double epsilon_param);
};


