#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <queue>
#include <array>
#include <math.h>

using namespace std;

// The node class will contain member variables that contain the state of the node, the path-cost up to that node from the root node, and the path up to that node from the root node.  
class Node {
public:
	Node(vector<vector<int>> state) : state(state), pathCost(0), path({}) {}
	Node(vector<vector<int>> state, int pathCost, vector<char> path) : state(state), pathCost(pathCost), path(path) {}

	void displayState() const {
		string stringstate;
		for (size_t i = 0; i < state.size(); i++) {
			for (size_t j = 0; j < state[i].size(); j++) {
				stringstate += to_string(state[i][j]) + ' ';
			}
			stringstate += '\n';
		}
		cout << "State: \n" << stringstate << endl;
	}
	void displayPathCost() const {
		cout << "Path cost: " << pathCost << endl;
	}
	void displayPath() const {
		string strpath;
		for (size_t i = 0; i < path.size(); i++) {
				strpath += path[i];
		}
		cout << "Path: " << strpath << endl;
	
	}

	int getPathCost() const {
		return pathCost;
	}

	vector<char> getPath() const {
		return path;
	}

	vector<vector<int>> getState() const {
		return state;
	}

private: 
	vector<vector<int>> state;
	int pathCost;
	vector<char> path;

};

// This function defines the comparison operator that is used in a min-heap with the user defined type, node. 
class cmpFunction {
	public:
		int operator()(const Node& a, const Node& b) {
			return (a.getPathCost() > b.getPathCost());
		}
};

// This function creates the output file and writes to the file in the format specified in the project problem once the solution node has been found
void solution(const Node* node, const vector<vector<int>>& initialState, const vector<vector<int>>& goalState) {
	ofstream outputFile;
	outputFile.open("Output1.txt");
	string fstring;
	for (size_t i = 0; i < initialState.size(); i++) {
		for (size_t j = 0; j < initialState[i].size(); j++) {
			fstring += to_string(initialState[i][j]) + " ";
		}
		fstring += '\n';
	}
	fstring += '\n';
	for (size_t i = 0; i < goalState.size(); i++) {
		for (size_t j = 0; j < goalState[i].size(); j++) {
			fstring += to_string(goalState[i][j]) + " ";
		}
		fstring += '\n';
	}
	fstring += '\n';
	vector<char> path = node->getPath();
	fstring += to_string(path.size()) + '\n';
	fstring += "N\n";
	for (size_t i = 0; i < path.size(); i++) {
			fstring += path[i] + " ";
	}
	outputFile << fstring;
	outputFile.close();
}

// This function returns the manhattan distance of one tile from its goal position
int tileDist(int tile, const vector<vector<int>>& currState, const vector<vector<int>>& goalState) {
	
	vector<int> stateCoor;
	vector<int> goalCoor;
	for (size_t i = 0; i < currState.size(); i++) {
		for (size_t j = 0; j < currState[i].size(); j++) {
			if (currState[i][j] == tile) {
				stateCoor.push_back(i);
				stateCoor.push_back(j);
			}
			if (goalState[i][j] == tile) {
				goalCoor.push_back(i);
				goalCoor.push_back(j);
			}
		}
	}

	int xdiff = abs(stateCoor[0] - goalCoor[0]);
	int ydiff = abs(stateCoor[1] - goalCoor[1]);

	int tileDist = xdiff + ydiff;
	return tileDist;

}

// This function returns the sum of Manhattan distances of all tiles (except blank) from their goal position
int heuristic(const vector<vector<int>>& currState, const vector<vector<int>>& goalState) {
	int sumDist = 0;
	for (int i = 1; i < 9; i++) {
		sumDist += tileDist(i, currState, goalState);
	}
	return sumDist;
}

// This function returns true if the state is equivalent to the goal state. It is equivalent when the sum of Manhattan distances of the tiles from their goal position is equal to 0. It returns false otherwise.
bool goalTest(const vector<vector<int>>& state, const vector<vector<int>>& goal) {
	return heuristic(state, goal) == 0;
}

// This function returns a vector containing all possible actions doable from a given state
vector<char> actions(const vector<vector<int>>& state) {
	// enum position {
	// 	TOP_RIGHT
	// }

	vector<char> vecActions;
	vector<int> coors;
	for (size_t i = 0; i < state.size(); i++) {
		for (size_t j = 0; j < state[i].size(); j++) {
			if (state[i][j] == 0) {
				coors.push_back(i);
				coors.push_back(j);
			}
		}
	}

	if (coors[0] == 0) {
		vecActions.push_back('D');
	}
	else if (coors[0] == 1) {
		vecActions.push_back('D');
		vecActions.push_back('U');
	}
	else {
		vecActions.push_back('U');
	}

		
	if (coors[1] == 0) {
		vecActions.push_back('R');
	}
	else if (coors[1] == 1) {
		vecActions.push_back('R');
		vecActions.push_back('L');
	}
	else {
		vecActions.push_back('L');
	}

	return vecActions;	
}

// remove the node with the lowest pathCost from the frontier and return the pointer
Node* pop(vector<Node*>& frontier) {
	int minCost = 100;
	int minIndex = 0;
	for (size_t i = 0; i < frontier.size(); i++) {
		int pathCost = frontier[i]->getPathCost();
		if (pathCost < minCost) {
			minCost = pathCost;
			minIndex = i;
		}
	}
	Node* nodeptr = frontier[minIndex];
	frontier.erase((frontier.begin()+minIndex));
	return nodeptr;
}

// This function creates a child node using the state of the current node, a legal action, and the goal state for the problem
Node* childNode(const Node* currNode, const char action, const vector<vector<int>>& goalState) {
	vector<vector<int>> childState = currNode->getState();

	vector<char> path = currNode->getPath(); 
	path.push_back(action);

	int fcost = currNode->getPathCost() - heuristic(currNode->getState(), goalState) + 1;

	int temp;
	for (size_t i = 0; i < childState.size(); i++) {
		for (size_t j = 0; j < childState[i].size(); j++) {
			if (childState[i][j] == 0) {
				if (action == 'U') {
					temp = childState[i-1][j];
					childState[i-1][j] = 0;
				}
				else if (action == 'D') {
					temp = childState[i+1][j];
					childState[i+1][j] = 0;
				}
				else if (action == 'L') {
					temp = childState[i][j-1];
					childState[i][j-1] = 0;
				}
				else {
					temp = childState[i][j+1];
					childState[i][j+1] = 0;
				}
				childState[i][j] = temp;
			}
		}
	}

	int pathCost = heuristic(childState, goalState) + fcost;
	Node* child = new Node(childState, pathCost, path);
	return child;
}


bool equals(const vector<vector<int>>& s, const vector<vector<int>>& t) {
	for (size_t i = 0; i < s.size(); i++) {
		for (size_t j = 0; j < s[i].size(); j++) {
			if (s[i][j] != t[i][j]) {
				return false;
			}
		}
	}
	return true;
}

// Check if a state is inside frontier or explored
bool contains(const vector<vector<int>>& state, const vector<Node*>& nodevec) {

	for (size_t i = 0; i < nodevec.size(); i++) {
		// vector<vector<int>> currState = nodevec[i]->getState();
		if(equals(state, nodevec[i]->getState())) {
			return true;
		}
	}
	return false;
}




// GRAPH-SEARCH A* using Sum of Manhattan distances of tiles from their goal position as heuristic. 
void graphSearchA(string file) {
	ifstream ifs(file);
	if (!ifs) {
		cerr << "Could not open the file.\n";
		exit(1);
	}
	else {
		cout << "File has been opened successfully" << endl;
	}

	int tile;
	int counter = 0;
	vector< vector<int> > initialState(3);
	vector< vector<int> > goalState(3);
	
	int i = 0;
	int j = 0;
	while (ifs >> tile) {
		if (i < 3) {
			initialState[i].push_back(tile);
		}
		else {
			goalState[i-3].push_back(tile);
		}
		j++;
		if (j % 3 == 0) {
			i++;
		}
	}
	ifs.close();


	// Node class TESTS
	cout << "Node class tests: " << endl;
	Node test(initialState, heuristic(initialState, goalState), {});
	test.displayState();
	test.displayPath();
	test.displayPathCost();

	// tileDist TESTS
	int manDist2 = tileDist(3, initialState, goalState); 
	cout << "The tile distance for 3 is: " << manDist2 << endl;
	int manDist8 = tileDist(8, initialState, goalState);
	cout << "The tile distance for 8 is: " << manDist8 << endl;

	// heuristic TESTS
	int sumDist = heuristic(initialState, goalState);
	cout << "The sum of all Manhattan distances is: " << sumDist << endl;

	// goaltest TESTS
	cout << "Goal Test" << endl;
	cout << goalTest(initialState, goalState) << endl;

	// actions TESTS 

	vector<char> vecActions = actions(test.getState());
	cout << "These are the actions for this state" << endl;	 
	for (size_t i = 0; i < vecActions.size(); i++) {
		cout << vecActions[i] << endl;
	}

	// childNode TESTS
	cout << "Child node test: " << endl;
	Node* testptr = &test;
	Node* child = childNode(testptr, 'U', goalState);
	child->displayState();
	child->displayPathCost();
	child->displayPath();

	// frontier TESTS
	cout << "Frontier test: " << endl;
	// Node goal(goalState, 6, {});
	// priority_queue<Node, vector<Node>, cmpFunction > frontier;
	// vector<Node*> explored;

	// frontier.push(root);
	// frontier.push(goal);

	// Node n = frontier.top();
	// n.displayState();
	// cout << frontier.top() << endl;


	// soultion TESTS
	cout << "This is a solution test: " << endl;
	solution(&test, initialState, goalState);

	cout << "======================" << endl;
	cout << "======================" << endl;
	cout << endl;


	Node* root = new Node(initialState, heuristic(initialState, goalState), {});
	vector<Node*> frontier; 
	frontier.push_back(root);
	vector<Node*> explored;

	while(true) {
		if (frontier.empty()) { 
			cerr << "Search has failed" << endl;
			exit(1);
		}
		Node* n = pop(frontier);
		cout << "Popped frontier" << endl;
		n->displayState();
		n->displayPath();
		n->displayPathCost();

		if (goalTest(n->getState(), goalState)) {
			return solution(n, initialState, goalState);
		}

		explored.push_back(n);
		vector<char> possActions = actions(n->getState());
		for (size_t i = 0; i < possActions.size(); i++) {
			cout << possActions[i] << " " << endl;
			Node* child = childNode(n, possActions[i], goalState);
			cout << "Created child" << endl;
			if (!(contains(child->getState(), frontier)) || !(contains(child->getState(), explored))) {
				frontier.push_back(child);
			}
			// else if (child->getState() in frontier with lower pathCost {
			// 	replace that node in frontier
			// }
		}
		cout << frontier.size() << endl;
	}

}

int main() {
	cout << "Hello, world" << endl;

	graphSearchA("Input1.txt");


}