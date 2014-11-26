#include "cupandnode.h"
/// CUP definition
string Cup::toString() {
	return string("[") + to_string(fill) + "|" + to_string(capacity) + "]";
}
bool Cup::empty() {
	return fill == 0;
}
uint Cup::tillFull() {
	return capacity - fill;
}
void Cup::fillCup(Cup& other) {
	if (other.tillFull() == 0) return;

	if (fill >= other.tillFull()) {
		fill -= other.tillFull();
		other.fill = other.capacity;
	}
	else if(fill < other.tillFull()) {
		other.fill += fill;
		fill = 0;
	}
}

bool Cup::operator==(const Cup& other) const {
	return capacity == other.capacity && fill == other.fill;
}
bool Cup::operator!=(const Cup& other) const {
	return !(*this == other);
}

Cup::Cup(Owner o, uint c, uint f) : owner(o), capacity(c), fill(f) { }


/// Node definition
string Node::toString() {
	string str("");
	for (auto& cup : cups) {
		str += cup.toString();
	}
	return str;
}
bool Node::equalFluid() {
	int i = 0;
	for (auto const& cup : cups) {
		if (cup.owner == A) i += cup.fill;
		else i -= cup.fill;
	}
	return i == 0;
}
bool Node::hasParent() {
	return parent != NULL;
}
void Node::getChildren() {
	//cout << "ha";
	for (int i = 0; i < cups.size(); ++i) {
		for (int j = 0; j < cups.size(); ++j) {
			if (i == j || 
				cups[i].empty() || 
				cups[j].tillFull() == 0) continue;

			vector<Cup> newcups = cups;
			newcups[i].fillCup(newcups[j]);

			// ERROR: runs without end (ONLY: when in constructor)
			children.push_back(Node(newcups, this));
		}
	}
}

bool Node::operator==(const Node& other) const {
	for (int i = 0; i < cups.size(); ++i) {
		if (cups[i] != other.cups[i]) {
			return false;
		}
	}
	return true;
}
bool Node::operator!=(const Node& other) const {
	return !(*this == other);
}

Node::Node(vector<Cup> c)          : cups(c), parent(NULL) { }
Node::Node(vector<Cup> c, Node* p) : cups(c), parent(p) { }