#ifndef _CUPANDNODE_H_
#define _CUPANDNODE_H_

#include <vector>
#include <string>

using std::string;
using std::to_string;
using std::vector;
using uint = unsigned int;

enum Owner { A, B };

class Cup {
public:
	Owner owner;
	uint capacity;
	uint fill;

	string toString();
	bool empty();
	uint tillFull();
	void fillCup(Cup& other);

	bool operator==(const Cup& other) const;
	bool operator!=(const Cup& other) const;

	Cup(Owner o, uint c, uint f);
};
class Node {
private:
	vector<Cup> cups;
public:
	Node* parent;
	vector<Node> children;

	string toString();
	bool equalFluid();
	bool hasParent();
	void getChildren();

	bool operator==(const Node& other) const;
	bool operator!=(const Node& other) const;

	Node(vector<Cup> c);
	Node(vector<Cup> c, Node* p);
};
#endif