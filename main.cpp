#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <cmath>
#include <limits>
#include <map>
#include <ctime>
#include "Solver.h"

using namespace std;

// Priority Queue comparator. Sorts by lowest g(n) + h(n) cost QQ
class Comparator
{
	public:
		bool operator() (Solver lhs, Solver rhs) 
		{
			return lhs.get_final() > rhs.get_final();
		}
};

Solver Goal;		// An instance of Solver class to store the goal state
Solver d;			// An instance of Solver class to store depth
int nodes_expanded = 0;
priority_queue<Solver, vector<Solver>, Comparator> explored_nodes;		// Priority queue
vector <Solver> closed_states;		// Vector of type solver 

// Implements search algorithm 
Solver Solver::a_star() 
{
	Solver search;
	while (true) 
	{
		search = explored_nodes.top();
		explored_nodes.pop();
		
		//If initial state equals the goal state
		if (search.isGoal(Goal)) 
		{
			d.depth = search.depth;
			return search;
		}
		else 
		{
			search.depth = search.depth + 1;		// Update costs
			search.moves.push_back(search.prev);	// Stores the last move made
			search.g_moves.push_back(search.depth);
			search.set_final_val();
			closed_states.push_back(search);

			if (search.space.first < 2)
			{	// Can move right
				search.move_RIGHT();			
				search.prev = 1;				
				explored_nodes.push(search);		// Move the map's position back after pushing it onto the
				search.move_LEFT();				// queue, else states aren't correct
				nodes_expanded++;				// Updates the total amount of nodes expanded
			}
			if (search.space.first > 0)
			{	// Can move left
				search.move_LEFT();
				search.prev = 2;
				explored_nodes.push(search);
				search.move_RIGHT();
				nodes_expanded++;
			}
			if (search.space.second > 0)
			{	// Can move up
				search.move_UP();
				search.prev = 3;
				explored_nodes.push(search);
				search.move_DOWN();
				nodes_expanded++;
			}
			if (search.space.second < 2)
			{	// Can move down
				search.move_DOWN();
				search.prev = 4;
				explored_nodes.push(search);
				search.move_UP();
				nodes_expanded++;
			}			
		}
	}
}

int main(int argc, char* argv[]) 
{
	int choice;
	cout << "Welcome to 861168896's 8-puzzle solver. \nType \"1\" to use a "; 
    cout << "default puzzle, or enter \"2\" to enter your own puzzle." << endl;
    cin >> choice;
	
	Solver start;
	Goal.set_Goal();
	start.choose_Puzzle(choice);
	
		
	cout << endl << "Enter your choice of algorithm:" << endl;
	cout << " 1. Uniform Cost\n 2. A* w/ Misplaced Tile\n 3. A* w/ Manhattan Distance\n";
	cin >> start.h;

	//clock_t begin = clock();
	explored_nodes.push(start); 			// Initializes priority queue with initial state
	Solver solution = start.a_star();		// Implements search algorithm
	//clock_t end = clock();	
	
	//double tot_time = double(end - begin) / CLOCKS_PER_SEC;
	cout << "Expanding state: " << endl;
	start.print();

	for (int i = 0; i < solution.moves.size(); i++)  // Takes moves list from
	{                                           // solution and applies it
		if (solution.moves[i] == 1)
		{					// to the start position // so that sol is viewable 
			start.move_RIGHT();
			cout << "The best state to expand with a g(n) = " << solution.g_moves[i] << " and h(n) = " << solution.h_moves[i] << " is..." << endl;
			start.print();
			cout << "Expanding this node..." << endl;
		}
		if (solution.moves[i] == 2) 
		{
			start.move_LEFT();
			cout << "The best state to expand with a g(n) = " << solution.g_moves[i] << " and h(n) = " << solution.h_moves[i] << " is..." << endl;
			start.print();
			cout << "Expanding this node..." << endl;
		}
		if (solution.moves[i] == 3) 
		{
			start.move_UP();
			cout << "The best state to expand with a g(n) = " << solution.g_moves[i] << " and h(n) = " << solution.h_moves[i] << " is..." << endl;
			start.print();
			cout << "Expanding this node..." << endl;
		}
		if (solution.moves[i] == 4) 
		{
			start.move_DOWN();
			cout << "The best state to expand with a g(n) = " << solution.g_moves[i] << " and h(n) = " << solution.h_moves[i] << " is..." << endl;
			start.print();
			cout << "Expanding this node..." << endl;
		}
		cout << endl;
	}
	solution.print();
	cout << endl << "Goal!!" << endl << endl;
	
	cout << "To solve this problem the search algorithm expanded a total of " << nodes_expanded << " nodes." << endl;
	cout << "The maximum number of nodes in the queue at any one time was " << closed_states.size() << "." << endl;
	cout << "The depth of the goal node was " << d.depth << "." << endl;
	//cout << "Puzzle solved in " << tot_time << " seconds." << endl;
}
