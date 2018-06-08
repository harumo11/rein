#include <iostream>
#include "all.hpp"

int main(void)
{

	rein::Rock_Scissors_Paper env;
	rein::QLearn agent(env.get_state_number(), env.get_action_number(), env.get_current_state());

	for (int i = 0; i < 200; i++) {
		env.set_action(agent.action());
		agent.update(env.get_current_state(), env.get_reward());
	}

	return 0;
}
