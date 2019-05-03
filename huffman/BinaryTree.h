#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#include <iostream>
#include <iomanip>
#include "BinaryHeap.h"

using namespace std;

class BinaryTree
{
	public:
	int count;
	char Letter;
	bool tree;
	string coding = "";
	
	BinaryTree* leftchild;	
	BinaryTree* rightchild;
	
	bool operator==(const BinaryTree& other) const{
		if(this->count == other.count)
			return true;
		else
			return false;
	}
	
	bool operator<(const BinaryTree& other) const{
		if(this->count < other.count)
			return true;
		else
			return false;
	}
	
	bool operator>(const BinaryTree& other) const{
		if(this->count > other.count)
			return true;
		else
			return false;
	}
	
	void insert(BinaryTree* tree_to_insert);
	void printinorder() const;
};

void BinaryTree::insert(BinaryTree* tree_to_insert){
	if(this->count==0){			
		//this = *tree_to_insert;
	}
	else{
		if((tree_to_insert->count)<(this->count)){
			(this->leftchild)->insert(tree_to_insert);
		}
		else if((tree_to_insert->count)<(this->count)){
			(this->rightchild)->insert(tree_to_insert);
		}
	}
}

void BinaryTree::printinorder() const{
	if(tree == false){
		cout << Letter << setw(5) << count << " " << coding << endl;
	}
	else{
		leftchild->coding = coding + '0';
		leftchild->printinorder();
		rightchild->coding = coding + '1';
		rightchild->printinorder();
	}
}

#endif
