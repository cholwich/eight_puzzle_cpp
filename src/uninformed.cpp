#include "eight_puzzle.hpp"

bool compare_node(shared_ptr<Node> left, shared_ptr<Node> right)
{
	return left->path_cost > right->path_cost;
}

tuple<shared_ptr<Node>, int> uniform_cost_graph_search()
{
	auto initial_node = make_shared<Node>(initial_state(), nullptr, "", 0, 0);
	vector<shared_ptr<Node>> frontier;
	unordered_set<shared_ptr<State>, StateHash, StateEq> explored;
	// set<shared_ptr<State>, StateLess> explored;
	int n_visits = 0;

	frontier.push_back(initial_node);

	while (true)
	{
		if (frontier.empty())
		{
			return make_tuple(nullptr, n_visits);
		}
		else
		{
			n_visits++;
			// heappop(frontier)
			auto node = frontier.front();
			pop_heap(frontier.begin(), frontier.end(), compare_node);
			frontier.pop_back();

			explored.insert(node->state);

			// if (n_visits % 1000 == 0) {
			// 	cout << *node << endl;
			// 	cout << node->state->hash << endl;
			// 	cout << explored.size() << endl;
			// 	cout << frontier.size() << endl << endl;
			// }

			if (is_goal(node->state))
			{
				return make_tuple(node, n_visits);
			}
			else
			{
				for (auto p : successors(node->state))
				{
					auto succ = get<0>(p);
					auto cost = get<1>(p);
					auto child_cost = node->path_cost + cost;
					auto child_node = make_shared<Node>(succ, node, "", child_cost, node->depth + 1);
					if (explored.find(succ) == explored.end())
					{
						// check if succ in the frontier
						auto exist_itr = find_if(frontier.begin(), frontier.end(),
												 [succ](shared_ptr<Node> n) { return succ->hash == n->state->hash; });
						if (exist_itr == frontier.end())
						{
							// not in the frontier
							frontier.push_back(child_node);
							push_heap(frontier.begin(), frontier.end(), compare_node);
						}
						else
						{
							auto exist = *exist_itr;
							if (exist->path_cost > child_cost)
							{
								*exist_itr = child_node;
								make_heap(frontier.begin(), frontier.end(), compare_node);
							}
						}
					}
				}
			}
		}
	}
}

tuple<shared_ptr<Node>, int> uniform_cost_tree_search()
{
	auto initial_node = make_shared<Node>(initial_state(), nullptr, "", 0, 0);
	vector<shared_ptr<Node>> frontier;
	int n_visits = 0;

	frontier.push_back(initial_node);

	while (true)
	{
		if (frontier.empty())
		{
			return make_tuple(nullptr, n_visits);
		}
		else
		{
			n_visits++;
			// heappop(frontier)
			auto node = frontier.front();
			pop_heap(frontier.begin(), frontier.end(), compare_node);
			frontier.pop_back();

			if (is_goal(node->state))
			{
				return make_tuple(node, n_visits);
			}
			else
			{
				for (auto p : successors(node->state))
				{
					auto succ = get<0>(p);
					auto cost = get<1>(p);
					auto child_cost = node->path_cost + cost;
					auto child_node = make_shared<Node>(succ, node, "", child_cost, node->depth + 1);
					frontier.push_back(child_node);
					push_heap(frontier.begin(), frontier.end(), compare_node);
				}
			}
		}
	}
}

void print_solution(shared_ptr<Node> n)
{
	deque<shared_ptr<State>> states;
	while (n != nullptr)
	{
		states.push_front(n->state);
		n = n->parent;
	}
	for (auto s : states)
	{
		cout << *s << endl;
	}
}