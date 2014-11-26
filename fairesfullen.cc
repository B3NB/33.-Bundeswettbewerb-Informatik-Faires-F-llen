#include "cupandnode.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>

using std::cout; using std::cerr; using std::endl;
using std::ifstream; using std::getline;
using std::istringstream;
using std::queue;

/// MAIN ALGORITHM
vector<Node*> breadthSearch(Node& n) {
	vector<Node*> ret; // return val

	vector<Node*> checked;
	queue<Node*> que;

	checked.push_back(&n);
	que.push(&n);

	while (!que.empty()) {
		Node* currnode = que.front();
		que.pop();

		//cout << currnode->toString() << endl;

		if (currnode->equalFluid()) {
			while (currnode != NULL) {
				ret.push_back(currnode);
				currnode = currnode->parent;
			}

			// reverse ret and return
			reverse(ret.begin(), ret.end());
			return ret;
		}

		currnode->getChildren(); // only call in this function 
		for (auto& nextnode : currnode->children) {
			// for range loop will not grow eventhough checked if appends to check
			bool found = false;
			for (auto const& prevnode : checked) {
				if (nextnode == *prevnode) found = true;
			}
			
			if (!found) {
				checked.push_back(&nextnode);
				que.push(&nextnode);
			}
		}
	}
	return ret;
}

vector<vector<uint>> readInput(const char path[]) {
	ifstream file(path);
	vector<vector<uint>> ret;

	string line;
	while (getline(file, line)) {
		vector<uint> nums;

		istringstream iss(line);
		uint i;
		while (iss >> i) {
			nums.push_back(i);
		}
		ret.push_back(nums);
	}
	return ret;
}
bool validateData(vector<vector<uint>>& data) {
	bool ret = true;
	ret = ret && data.size() == 3;
	ret = ret && data[0].size() == 1;
	ret = ret && data[1].size() == data[2].size();
	uint sum = 0;
	for (const auto& i : data[2]) {
		sum += i;
	}
	ret = ret && sum % 2 == 0;
	return ret;
}
Node parseData(vector<vector<uint>>& data) {
	vector<Cup> cups;
	for (int i = 0; i < data[1].size(); ++i) {
		Owner owner = i < data[0][0] ? A : B;
		cups.push_back(Cup(owner, data[1][i], data[2][i]));
	}
	return Node(cups);
}
string nodeString(vector<Node*>& nodes) {
	string str("");
	for (const auto& node : nodes) {
		str += node->toString();
		str += '\n';
	}
	return str;
}

int main(int argc, char const *argv[]) {
	if (argc != 2) {
		cerr << "Die Eingabe ist invalid!" << endl;
		cerr << "Eingabe: fairesfullen <datei>" << endl;
		return 1;
	}
	vector<vector<uint>> data = readInput(argv[1]);
	if (!validateData(data)) {
		cerr << "Die Eingabe ist invalid!" << endl;
		cerr << "Das Format der Eingabe ist unpassend." << endl;
		return 1;
	}
	Node head = parseData(data);
	
	// for (const auto& a : data) {
	// 	cout << a.size() << ": ";
	// 	for (const auto& b : a) {
	// 		cout << b << " ";
	// 	}
	// 	cout << endl;
	// }

	vector<Node*> result = breadthSearch(head);
	if (result.empty()) {
		cout << "Das Umfüllen ist unmöglich!" << endl;
	}
	else {
		cout << "Das Umfüllen ist möglich!" << endl;
		cout << nodeString(result);
	}
	return 0;
}