#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <queue>
#include <array>
#include <math.h>

using namespace std;

class Node {
public:
	Node(vector<vector<int>> state) : state(state), pathCost(0), path({}) {}
	Node(vector<vector<int>> state, int pathCost, vector<string> path) : state(state), pathCost(pathCost), path(path) {}

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

	vector<string> getPath() const {
		return path;
	}

private: 
	vector<vector<int>> state;
	int pathCost;
	vector<string> path;

};

class cmpFunction {
	public:
		int operator()(const Node& a, const Node& b) {
			return (a.getPathCost() > b.getPathCost());
		}

};

void solution(const Node& node) {

}

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

	int tileDist = max(xdiff, ydiff);
	return tileDist;

}

int heuristic(const vector<vector<int>>& currState, const vector<vector<int>>& goalState) {
	int sumDist = 0;
	for (int i = 1; i < 9; i++) {
		sumDist += tileDist(i, currState, goalState);
	}
	return sumDist;
}

bool goalTest(const vector<vector<int>>& state, const vector<vector<int>>& goal) {
	return heuristic(state, goal) == 0;
}

vector<char> actions(const vector<vector<int>>& state) {
	enum position {
		TOP_RIGHT
	}

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
		if (coors[1] == 0) {
			vecActions.push_back('R');
		}
		else if (coors[1] == 1) {
			vecActions.push_back('R');
			vecActions.push_back('L');
		}
		else if (coors[1] == 2) {
			vecActions.push_back('L');
			vecActions.push_back('D');
		}
	}
	else if (coors[0] == 1) {
		vecActions.push_back('D');
		vecActions.push_back('U');
		if (coors[1] == 1) {
			vecActions.push_back('L');
			vecActions.push_back('R');
		}
		else if (coors[1] == 0) {
			vecActions.push_back('R');
		}
		else {
			vecActions.push_back('L');
		}
	}
	else {
		vecActions.push_back('U');
	}
	

}

Node child-node(const Node& currNode, const char action) {

}

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

	// cout << initialState[3][2] << endl;
	
	int i = 0;
	int j = 0;
	while (ifs >> tile) {
		if (i < 3) {
			initialState[i].push_back(tile);
			// cout << i << endl;
			// cout << tile << endl;
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

	// cout << "The tile distance for 2 is: " << 
	int chessDest = tileDist(2, initialState, goalState); 
	// << endl: 
	cout << "The tile distance for 2 is: " << chessDest << endl;

	int sumDist = heuristic(initialState, goalState);
	cout << "The sum of all chessboard distances is: " << sumDist << endl;

	Node root(initialState);
	root.displayState();
	root.displayPath();
	root.displayPathCost();

	Node goal(goalState, -6, {});




	// string line;
	// while (getline(ifs, line)) {
	// 	for (size_t i = 0; i < line.length(); i++) {
	// 		if (line[i] != '\0' && line[i] != ' ' && line[i] != '\n') {
	// 			initialState
	// 		}
	// 	}
	// }

	priority_queue<Node, vector<Node>, cmpFunction > frontier;
	vector<Node*> explored;

	frontier.push(root);
	frontier.push(goal);

	Node n = frontier.top();
	n.displayState();
	// cout << frontier.top() << endl;



	// vector<char> path;
	// int initialState[3][3];
	// int goalState[3][3];
	// vector<Node*> frontier;
	// vector<Node*> explored; 
	// 

}

int main() {
	cout << "Hello, world" << endl;

	// int state[3][3];
	// state[0][2] = 100;
	// cout << sizeof(state) / sizeof(*state) << endl;
	// cout << *(state)[2] << endl;
	// cout << endl;

	// int test[10];
	
	// test[0] = 5;
	// test[9] = 40;
	// test[4] = 100;
	// //  print test[0] = 5
	// cout << *test << endl;
	// //  print test[9] 
	// cout << *(test+9) << endl;
	// //  print test[4]


	graphSearchA("Input1.txt");

	// vector< vector<int> > multivec = {{1,2,3}, {4, 5, 6}, {7, 8, 9}};
	// vector<string> path(1);
	
	// Node root(multivec, 0, path); 
	// root.displayState();
	// root.displayPathCost(); 
	// root.displayPath();


	// vector<int> vec = {2, 3, 4, 5, 6, 7};
	// cout << vec[4] << endl;


}