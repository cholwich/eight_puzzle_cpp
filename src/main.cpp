#include "eight_puzzle.hpp"

int main()
{
	/*
	auto s0 = initial_state();
	cout << *s0 << endl;
	cout << is_goal(s0) << endl;

	auto s1 = move_blank(s0, 0, 1);
	cout << *s1 << endl;

	auto pairs = successors(s0);
	for(auto p : pairs) {
		auto succ = get<0>(p);
		auto cost = get<1>(p);
		cout << *succ << endl;
	}
	*/

	shared_ptr<Node> goal_node;
	int n_visits;
	tie(goal_node, n_visits) = uniform_cost_graph_search();
	if (goal_node != nullptr)
	{
		print_solution(goal_node);
		cout << "=====" << endl;
		cout << "Number of Visited States = " << n_visits << endl;
	}
}