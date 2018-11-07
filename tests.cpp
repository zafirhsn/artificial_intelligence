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
	solution("test.txt", &test, initialState, goalState, 4);

	cout << "======================" << endl;
	cout << "======================" << endl;
	cout << endl;