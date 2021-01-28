#include <iostream>
#include <memory>
#include <array>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <set>
#include <tuple>
#include <deque>

using namespace std;

struct State
{
	array<int, 9> board;
	int r;
	int c;
	size_t hash;
	State(array<int, 9> b_, int r_, int c_) : board(b_), r(r_), c(c_)
	{
		hash = 0;
		for(int i=0; i<9; i++) {
			hash *= 10;
			hash += b_[i];
		}
	};
};

struct StateHash {
	size_t operator()(shared_ptr<State> const& s) const	
	{
		int h = 0;
		for(int i=0; i<9; i++) {
			h *= 10;
			h += s->board[i];
		}
		return h;
	}
};

struct StateEq {
	bool operator()(shared_ptr<State> const left, shared_ptr<State> const right) const {
		return (*left).hash == (*right).hash;
	}
};

struct StateLess {
	bool operator()(shared_ptr<State> const left, shared_ptr<State> const right) const {
		return (*left).hash < (*right).hash;
	}
};

struct Node
{
	shared_ptr<State> state;
	shared_ptr<Node> parent;
	string action;
	int path_cost;
	int depth;
	Node(shared_ptr<State> s_, shared_ptr<Node> p_,
		 string a_, int c_, int d_) : state(s_), parent(p_),
									  action(a_), path_cost(c_), depth(d_)
	{
	}
};

ostream &operator<<(ostream &stream, const State &state);
ostream &operator<<(ostream &stream, const Node &node);
shared_ptr<State> initial_state();
bool is_goal(shared_ptr<State> state);
shared_ptr<State> move_blank(shared_ptr<State> state, int new_r, int new_c);
vector<tuple<shared_ptr<State>, int>> successors(shared_ptr<State> state);
tuple<shared_ptr<Node>, int> uniform_cost_graph_search();
tuple<shared_ptr<Node>, int> uniform_cost_tree_search();
void print_solution(shared_ptr<Node> n);