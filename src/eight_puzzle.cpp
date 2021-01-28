#include "eight_puzzle.hpp"

ostream &operator<<(ostream &stream, const State &state)
{
	stream << "( ";
	for (int i = 0; i < 9; i++)
	{
		stream << state.board[i] << " ";
	}
	stream << ") " << state.r << ", " << state.c;
	return stream;
}

ostream &operator<<(ostream &stream, const Node &node)
{
	stream << "(" << *(node.state) << ") ";
	stream << node.path_cost;
	return stream;
}

shared_ptr<State> initial_state()
{
	return make_shared<State>(array<int, 9>({7, 2, 4, 5, 0, 6, 8, 3, 1}), 1, 1);
}

bool is_goal(shared_ptr<State> state)
{
	return state->hash == 12345678;
}

bool is_valid(int r, int c)
{
	return (r >= 0) and (r <= 2) and (c >= 0) and (c <= 2);
}

shared_ptr<State> move_blank(shared_ptr<State> state, int new_r, int new_c)
{
	auto new_board = array<int, 9>(state->board);
	new_board[3 * state->r + state->c] = new_board[3 * new_r + new_c];
	new_board[3 * new_r + new_c] = 0;
	return make_shared<State>(new_board, new_r, new_c);
}

vector<tuple<shared_ptr<State>, int>> successors(shared_ptr<State> state)
{
	int r = state->r;
	int c = state->c;
	int new_r, new_c;

	vector<tuple<shared_ptr<State>, int>> result;

	new_r = r - 1;
	new_c = c;
	if (is_valid(new_r, new_c))
	{
		result.push_back(make_tuple(move_blank(state, new_r, new_c), 1));
	}
	new_r = r + 1;
	new_c = c;
	if (is_valid(new_r, new_c))
	{
		result.push_back(make_tuple(move_blank(state, new_r, new_c), 1));
	}
	new_r = r;
	new_c = c - 1;
	if (is_valid(new_r, new_c))
	{
		result.push_back(make_tuple(move_blank(state, new_r, new_c), 1));
	}
	new_r = r;
	new_c = c + 1;
	if (is_valid(new_r, new_c))
	{
		result.push_back(make_tuple(move_blank(state, new_r, new_c), 1));
	}
	return result;
}