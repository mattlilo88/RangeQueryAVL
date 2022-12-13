#ifndef WORDRANGE_H
#define WORDRANGE_H

#include <string>

using namespace std;

class Node
{
	public:
		string key = "";
		Node *left, *right, *parent;
		int substree_sizes = 0;
		int height = 1;


		Node(){
			left = right = parent = NULL;
		}

		Node(string val){
			key = val;
			left = right = parent = NULL;
		}


};

class AVL
{
	public:
		Node *root;

		AVL(){
			root = NULL;
		}
		void insert(string);
		void insert(Node*, Node*);
		void decrementSubtree(Node*, Node*);
		void balanceTree(Node*, Node*);
		int height(Node*);
		int substree_sizes(Node*);
		Node* rightRotate(Node*);
		Node* leftRotate(Node*);
		string printInOrder();
		string printInOrder(Node*);
		Node* lca(string, string);
		Node* lca(Node*, string, string);
		int range(string, string);
		int rangeLeft(Node*, string, string);
		int rangeRight(Node*, string, string);


		
};

#endif
