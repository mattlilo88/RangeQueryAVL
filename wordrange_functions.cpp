#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <cstdlib>
#include "wordrange.h"

using namespace std;


void AVL :: insert(string val){
	Node *new_insert = new Node(val);
	if(root == NULL){
		root = new_insert;
	}
	else{
		insert(root, new_insert);
	}
}

void AVL :: insert(Node* start, Node* new_insert){
	if(start == NULL){
		return;
	}
	start->substree_sizes += 1;
	if(new_insert->key < start->key){
		if(start->left == NULL){
			start->left = new_insert;
			new_insert->parent = start;
			balanceTree(start, new_insert);
			
			return;
		}
		else{
			insert(start->left, new_insert);
			return;
		}
	}
	else if(new_insert->key > start->key){
		if(start->right == NULL){
			start->right = new_insert;
			new_insert->parent = start;
			balanceTree(start, new_insert);
			
			return;
		}
		else{
			insert(start->right, new_insert);
			return;
		}
	}
	decrementSubtree(root, new_insert);
	delete(new_insert);

}

void AVL :: decrementSubtree(Node* start, Node* new_insert){
	if(start == NULL){
		return;
	}
	start->substree_sizes -= 1;
	if(new_insert->key < start->key){
		decrementSubtree(start->left, new_insert);
	}
	else if(new_insert->key > start->key){
		decrementSubtree(start->right, new_insert);
	}
}

void AVL :: balanceTree(Node* start, Node* new_insert){
	if(start == NULL){
		return;
	}
	
	
	start->height = max(height(start->left), height(start->right)) + 1;
	
	int bf = (height(start->left)) - (height(start->right));


	if(bf < -1 && new_insert->key > start->right->key){

		start = leftRotate(start);
	
		if(start->parent == NULL){
			root = start;
		}
		else{
			if(start->parent->key > start->key){
				start->parent->left = start;
			}
			else{
				start->parent->right = start;
			}
			
		}
		balanceTree(start->parent, new_insert);
	}
	else if(bf > 1 && new_insert->key < start->left->key){
		
		start = rightRotate(start);
	

		if(start->parent == NULL){
			root = start;
		}
		else{
			if(start->parent->key > start->key){
				start->parent->left = start;
			}
			else{
				start->parent->right = start;
			}
			
		}
		balanceTree(start->parent, new_insert);
	}
	else if(bf < -1 && new_insert->key < start->right->key){
		start->right = rightRotate(start->right);
		
		start = leftRotate(start);

		if(start->parent == NULL){
			root = start;
		}
		else{
			
			if(start->parent->key > start->key){
				start->parent->left = start;
			}
			else{
				start->parent->right = start;
			}
			
		}
		balanceTree(start->parent, new_insert);
	}
	else if(bf > 1 && new_insert->key > start->left->key){
		
		start->left = leftRotate(start->left);
		start = rightRotate(start);
	
		if(start->parent == NULL){
			root = start;
		}
		else{
	
			if(start->parent->key > start->key){
				start->parent->left = start;
			}
			else{
				start->parent->right = start;
			}
		
		}
		balanceTree(start->parent, new_insert);
	}
	else{
		balanceTree(start->parent, new_insert);
	}
	return;
}

int AVL :: height(Node* start){
	if(start == NULL){
		return 0;
	}
	return start->height;
}

int AVL :: substree_sizes(Node* start){
	if(start == NULL){
		return 0;
	}
	return start->substree_sizes + 1;
}

Node* AVL :: rightRotate(Node* start){
	Node* start_parent = start->parent;
	Node* x = start->left;
	Node* x_child = x->right;
	
	

	start->left = x_child;
	if(x_child != NULL){
		x_child->parent = start;
	}
	x->right = start;
	x->parent = start_parent;
	start->parent = x;

	start->height = max(height(start->left), height(start->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;
	start->substree_sizes = substree_sizes(start->left) + substree_sizes(start->right);
	x->substree_sizes = substree_sizes(x->left) + substree_sizes(x->right);

	return x;
}

Node* AVL :: leftRotate(Node* start){
	Node* start_parent = start->parent;
	Node* x = start->right;
	Node* x_child = x->left;



	start->right = x_child;
	if(x_child != NULL){
		x_child->parent = start;
	}
	x->left = start;
	x->parent = start_parent;
	start->parent = x;

	start->height = max(height(start->left), height(start->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	start->substree_sizes = substree_sizes(start->left) + substree_sizes(start->right);
	x->substree_sizes = substree_sizes(x->left) + substree_sizes(x->right);


	return x;
}


string AVL :: printInOrder(){
	return printInOrder(root);
}

string AVL :: printInOrder(Node* start){
	if(start == NULL){
		return "";
	}
	string leftpart = printInOrder(start->left);
	string rightpart = printInOrder(start->right);
	string output = start->key;
	if(leftpart.length() != 0){
		output = leftpart + " " + output;
	}
	if(rightpart.length() != 0){
		output = output + " " + rightpart;
	}
	return output;
}


Node* AVL :: lca(string str1, string str2){
	return lca(root, str1, str2);
}

Node* AVL :: lca(Node* start, string str1, string str2){
	if(start == NULL){
		return NULL;
	}
	if(str1 < start->key && str2 < start->key){
		return lca(start->left, str1, str2);
	}
	if(str1 > start->key && str2 > start->key){
		return lca(start->right, str1, str2);
	}
	if(start->key == str1 || start->key == str2){
		return start;
	}
	if((start->key > str1 && start->key < str2) || (start->key < str1 && start->key > str2)){
		return start;
	}
}

int AVL :: range(string str1, string str2){
	Node* lca_node = lca(str1, str2);
	if(lca_node == NULL){
		return 0;
	}
	int total = 0;
	total += rangeLeft(lca_node->left, str1, str2);
	total += rangeRight(lca_node->right, str1, str2);
	return total + 1;
}

int AVL :: rangeLeft(Node* start, string str1, string str2){
	if(!start){
		return 0;
	}
	if(start->key < str1){
		return rangeLeft(start->right, str1, str2);
	}
	else if(start->key >= str1){
		int current_total = substree_sizes(start->right) + 1;
		return current_total + rangeLeft(start->left, str1, str2);
	}
}

int AVL :: rangeRight(Node* start, string str1, string str2){
	if(!start){
		return 0;
	}
	if(start->key > str2){
		return rangeRight(start->left, str1, str2);
	}
	else if(start->key <= str2){
		int current_total = substree_sizes(start->left) + 1;
		return current_total + rangeRight(start->right, str1, str2);
	}
}