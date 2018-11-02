#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <math.h>

class Node {
public:
// void displayState() {
// 	for (size_t i = 0; i < (sizeOf(state[0]) / sizeof(*state[0])); i++) {
// 		std::cout << "This is the " + i + " row" << std::endl;
// 	}
// }

int state[3][3];
// Node* parent;
// Node* child;
// int heuristic;
// char action;

};

void graphSearchA(std::string file) {
	// vector<char> path;
	// int initialState[3][3];
	// int goalState[3][3];
	// std::vector<Node*> frontier;
	// std::vector<Node*> explored; 
	// 

}

int main() {
	std::cout << "Hello, world" << std::endl;

	int state[3][3];
	state[0][2] = 100;
	std::cout << sizeof(state) / sizeof(*state) << std::endl;
	std::cout << *(state)[2] << std::endl;
	std::cout << std::endl;

	int test[10];
	
	test[0] = 5;
	test[9] = 40;
	test[4] = 100;
	//  print test[0] = 5
	std::cout << *test << std::endl;
	//  print test[9] 
	std::cout << *(test+9) << std::endl;
	//  print test[4]

}