#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <cmath>
#include <limits>
#include <map>
#include <ctime>


using namespace std;

class Solver
{
	
	int puzzle[3][3];			//Initializes puzzle
	int final;					// h(n) + g(n)

	public:
		int depth;				// Current depth in the tree
		int h;					// Stores type of heuristic
		int prev;				// The last move the puzzle made
		pair<int, int> space;	// Location of zero, updated at all points

		Solver()
		{
			space = make_pair(2, 2);
			depth = 0;
			final = numeric_limits<int>::max();
		};
		
		// Prints 3x3 puzzle
		void print() 
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					
					cout << puzzle[i][j] << " ";
				}
				cout << endl;
			}
		}
		
		// Sets initial state by input from user
		void set_Puzzle()		
		{	
			int input;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					cin >> input; 
					puzzle[i][j] = input;
					if (input == 0)
					{
						space = make_pair(j, i) ;	// j is x, i is y
					}
				}
			}
		}
		
		// Sets initial state by default
		void default_Puzzle()	
		{
			 puzzle[0][0] = 1;  puzzle[0][1] = 2;  puzzle[0][2] = 3;
			 puzzle[1][0] = 4;  puzzle[1][1] = 0;  puzzle[1][2] = 6;
			 puzzle[2][0] = 7;  puzzle[2][1] = 5;  puzzle[2][2] = 8;
			 
			 space = make_pair(1, 1);
		}
		
		// Set puzzle to Goal
		void set_Goal() 
		{
			 puzzle[0][0] = 1;  puzzle[0][1] = 2;  puzzle[0][2] = 3;
			 puzzle[1][0] = 4;  puzzle[1][1] = 5;  puzzle[1][2] = 6;
			 puzzle[2][0] = 7;  puzzle[2][1] = 8;  puzzle[2][2] = 0;
		}
		
		// Chooses whether to use default puzzle or user input for initial state
		void choose_Puzzle(int choice)
		{
			if (choice == 1)
			{
				default_Puzzle();
			}
			else 
			{
				cout << "Enter your puzzle, use a zero to represent the blank" << endl;
				cout << "Enter the first, second, and third rows with a space or tabs between numbers:" << endl;;
				set_Puzzle();
			}
		}
		
		// Compares current state to goal state
		bool isGoal(Solver X) 
		{ // might be too simple	

			if ((puzzle[0][0] == X.puzzle[0][0]) && (puzzle[0][1] == X.puzzle[0][1]) && (puzzle[0][2] == X.puzzle[0][2])
				&& (puzzle[1][0] == X.puzzle[1][0]) && (puzzle[1][1] == X.puzzle[1][1]) && (puzzle[1][2] == X.puzzle[1][2])
				&& (puzzle[2][0] == X.puzzle[2][0]) && (puzzle[2][1] == X.puzzle[2][1]) && (puzzle[2][2] == X.puzzle[2][2]))
			{
				return true;
			}
			return false;
		}

		/* 
		    Operator functions
			"first" represents x-axis and "second" represents y-axis. 
			Basically keeps track of the location of the zero
			-RIGHT
			-LEFT
			-UP
			-DOWN
		*/
		
		void move_RIGHT() 
		{
			if (space.first >= 2)
			{
				// Out of bounds
				return;
			}
			else 
			{
				int temp = puzzle[space.second][space.first + 1];
				puzzle[space.second][space.first] = temp;
				puzzle[space.second][space.first + 1] = 0;
				space = make_pair(space.first + 1, space.second);
				return;
			}
		}
		
		void move_LEFT() 
		{
			if (space.first <= 0){
				// Out of bounds
				return;
			}
			else 
			{
				int temp = puzzle[space.second][space.first - 1];
				puzzle[space.second][space.first] = temp;
				puzzle[space.second][space.first - 1] = 0;
				space = make_pair(space.first - 1, space.second);
				return;
			}
		}
		
		/*
			since we go y[0] , move up actually
						y[1] moves down and
						y[2] down moves up
		*/
		
		void move_UP() 
		{
			if (space.second <= 0){
				// Out of bounds
				return;
			}
			else 
			{
				int temp = puzzle[space.second - 1][space.first];
				puzzle[space.second][space.first] = temp;
				puzzle[space.second - 1][space.first] = 0;
				space = make_pair(space.first, space.second - 1);
				return;
			}
		}
		
		void move_DOWN() 
		{
			if (space.second >= 2){
				// Out of bounds
				return;
			}
			else 
			{
				int temp = puzzle[space.second + 1][space.first];
				puzzle[space.second][space.first] = temp;
				puzzle[space.second + 1][space.first] = 0;
				space = make_pair(space.first, space.second + 1);
				return;
			}
		}

		int get_final() 
		{
			return final;
		}
		
		// Calculates h(n) + g(n)
		// Sets total weight based on the desired heuristic
		void set_final_val() 
		{
			if (h == 1) 
			{
				final = depth;
				h_moves.push_back(0);
			}
			else if (h == 2) 
			{
				final = misplaced() + depth;
				h_moves.push_back(final - depth);
			}
			else 
			{
				final = manhattan() + depth;
				h_moves.push_back(final - depth);
			}
		}
		
		// Calculates and returns the Manhattan Distance for a given problem
		int manhattan() 
		{
			int total = 0, row, col, num;
		
			for (int y = 0; y < 3; y++)
			{
				for (int x = 0; x < 3; x++)
				{			
					if ((num = puzzle[x][y]) != 0) {	// Don't include blank space in calculation
						row = (num - 1) / 3;			// Gives the original x value of each number in the puzzle
						col = (num - 1) % 3;			// Gives the original y-value of each numner in the puzzle 
		
						total += abs(row - x) + abs(col - y);	// Adds distance from origin to total
					}
				}
			}
			return total;
		}
		
		// Calculates and returns the Misplaced Tiles value for a given map
		int misplaced() 
		{
			return ((puzzle[0][0] != 1) + (puzzle[0][1] != 2) + (puzzle[0][2] != 3)	
				+ (puzzle[1][0] != 4) + (puzzle[1][1] != 5) + (puzzle[1][2] != 6)		
				+ (puzzle[2][0] != 7) + (puzzle[2][1] != 8));
		}
		
		Solver a_star();		// Runs the algorithm
		vector<int> moves;		// vector of moves made
		vector<int> h_moves;	// vector of h(n) (estimated cost from n to goal) at move location
		vector<int> g_moves;	// vector of g(n) (path cost from intial state to n) at move location

};