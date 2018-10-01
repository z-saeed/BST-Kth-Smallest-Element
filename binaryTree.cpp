#include <iostream>
#include <math.h>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

//Struct for Binary Search Tree Node
struct BstNode {
	int data;
	BstNode* left;
	BstNode* right;
};

//Create a new Node Function
BstNode* CreateNewNode(int data) {
	BstNode* newNode = new BstNode();
	newNode->data = data;
	newNode->left = NULL; //set left pointer to null
	newNode->right = NULL; //set right pointer to null

	return newNode;
}

BstNode* Insert(BstNode* root, vector<int> vect) {
	int midPoint = floor(vect.size()/2); //Get midpoint of vector
	vector<int> left(&vect[0],&vect[midPoint]); //new vector from 0 to midpoint of initial vector
	vector<int> right(&vect[midPoint + 1],&vect[vect.size()]); //new vector from midpoint to end of initial vector

	if (vect.size() == 1) { //if vector has only one element in it
		root = CreateNewNode(vect[0]); //add the node of that element
	} else {
		root = CreateNewNode(vect[midPoint]); //create node of midpoint
		root->left = Insert(root, left); //Go through insertion function with left vector
		root->right = Insert(root, right); //Go through insertion function with left vector
	}
	return root; //return node;
}

BstNode* kthSearch(BstNode* root, int k) {
	stack <BstNode*> st; //initialize stack
	BstNode* bst = root; //set new bst node equal to root
	BstNode* result = new BstNode(); //initial result node

	while (!st.empty() || bst != NULL) { //while the stack isnt empty OR bst node isnt null
		if (bst != NULL) { //if node isnt null
			st.push(bst); //push node into stack
			bst = bst->left; //move node down the left branch
		} else { //if node is null
			BstNode* temp = st.top(); //set temp node to the top node in stack
			st.pop(); //pop the top node in stack
			k--; //decrement k
			if (k == 0) { //if k is equal to 0
				result = temp; //result node equals temp node
			}
			bst = temp->right; //move bst node to right branch of temp node
		}
	}
	return result; //return result
}

void PrintTree(BstNode* root) {
	queue <BstNode*> q1; //initialize 2 queues
	queue <BstNode*> q2; //initialize 2 queues

	q1.push(root); //push root node to first queue

	while(!q1.empty() || !q2.empty()) { //while queue 1 isnt empty OR queue 2 isnt empty
		while(!q1.empty()) { //while queue 1 isnt empty
			root = q1.front(); //root node is equal to the node in the front of queue 1
			q1.pop(); //pop the node in the front of queue 1
			cout << root->data << " "; //print node value
			if (root->left != NULL) { //if the node's left branch isnt null
				q2.push(root->left); //push the node's left branch into queue 2
			}
			if (root->right != NULL) { //if the node's right branch isnt null
				q2.push(root->right); //push the node's right branch into queue 2
			}
		}
		cout << endl; //print a line break

		while(!q2.empty()) { //while queue 2 isnt empty
			root = q2.front(); //root node is equal to the node in the front of queue 2
			q2.pop(); //pop the node in the front of queue 2
			cout << root->data << " "; //print node value
			if (root->left != NULL) { //if the node's left branch isnt null
				q1.push(root->left); //push the node's left branch into queue 1
			}
			if (root->right != NULL) { //if the node's right branch isnt null
				q1.push(root->right); //push the node's right branch into queue 1
			}
		}
		cout << endl;//print a line break
	}
}  

int main() {

	int inputs [] = {6,17,20,41,45,52,57,65,71,76,79,87,92,95,99};
	int size = *(&inputs + 1) - inputs;
	
	vector<int> data(inputs, inputs + size);	

	BstNode* root = CreateNewNode(65);
	root = Insert(root,data);

	int answer;
	cout << "Enter k value: ";
	cin >> answer;
	
	BstNode* kthNode = kthSearch(root, answer);
	cout <<  "The kth smallest value is: " <<kthNode->data << endl;

	cout << "The printed tree: \n";
	PrintTree(root);

	return 0;
}