# 8-Puzzle Solver
Use 3 different algorithms to solve 8-Puzzle problem:
1. Uniform Cost Search
2. A* with Misplaced Tile heuristic
3. A* with Manhattan Distance heuristic

## What I Learned
* Implemented 1) Uniform Cost Search 2) A* with Misplaced Tile heuristic 3) A* with Manhattan Distance heuristic

## Usage
* Compile main.cpp file
* Enter (1) default puzzle or (2) to enter your own puzzle
* Enter your choice of algorithm (1) Uniform Cost (2) A* w/ Misplaced Tile (3) A* w/ Manhattan Distance

### Example
Trace of the Manhattan distance A* on the following problem: 

1 2 3

4 * 6 

7 5 8

The best state to expand with g(n) = 2 and h(n) = 1 is... 

1 2 3

4 5 6

7 * 8

Expanding this node...

1 2 3

4 5 6

7 8 *

Goal state is reached.
