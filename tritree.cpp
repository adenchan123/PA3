/**
 * @file tritree.cpp
 * @author CPSC 221
 * @description TriTree class implementation, CPSC 221 PA3
 *
 * This file must be submitted for grading.
 *
**/

#include "tritree.h"

TriTree::TriTree(PNG& imIn) {
	// REPLACE THE LINEs BELOW WITH YOUR CODE
	width = imIn.width();
	height = imIn.height();
	root = BuildNode(imIn, {0,0}, width, height);
}

void TriTree::Clear() {
	// YOUR CODE HERE
}

void TriTree::Copy(const TriTree& other) {
	// YOUR CODE HERE
}

PNG TriTree::Render() const {
	// REPLACE THE LINE BELOW WITH YOUR CODE
	return PNG();
}

void TriTree::Transpose() {
	// YOUR CODE HERE
}

void TriTree::Prune(double tol) {
	// YOUR CODE HERE
}

int TriTree::NumLeaves(Node* node) const {
	if(node == nullptr) {
		return 0;
	}
	
	if(node->A == nullptr && node->B == nullptr && node->C == nullptr) {
		return 1;
	}

	return NumLeaves(node->A) + NumLeaves(node->B) + NumLeaves(node->C);
}

int TriTree::NumLeaves() const {
	return NumLeaves(root);
}

Node* TriTree::BuildNode(PNG& im, pair<int, int> ul, int w, int h) {

	//create root node
	Node* root = new Node(ul, w, h);

	//final case, one pixel, leaf node
	if (h == 1 && w == 1) {
		return root;
	}

	//decide to split along width or height

	//vert split
	if (h > w) {
		//height is long side
		int rem = h % 3;

		if (rem == 0) {
			//increment y by h/3
			root->A = BuildNode(im, ul, w, h/3);
			root->B = BuildNode(im, {ul.first, ul.second + h/3}, w, h/3);
			root->C = BuildNode(im, {ul.first, ul.second + 2*h/3}, w, h/3);
		} else if (rem == 1) {
			root->A = BuildNode(im, ul, w, (h-1)/3);
			root->B = BuildNode(im, {ul.first, ul.second + (h-1)/3}, w, (h-1)/3 + 1);
			root->C = BuildNode(im, {ul.first, ul.second + 2*(h-1)/3 + 1}, w, (h-1)/3);
		} else {
			root->A = BuildNode(im, ul, w, (h-2)/3 + 1);
			root->B = BuildNode(im, {ul.first, ul.second + (h-2)/3 + 1}, w, (h-2)/3);
			root->C = BuildNode(im, {ul.first, ul.second + 2*(h-2)/3 + 1}, w, (h-2)/3 + 1);
		}
	} 
	
	//horiz split (includes square case)
	else {
		//height is long side
		int rem = w % 3;

		if (rem == 0) {
			//increment y by h/3
			root->A = BuildNode(im, ul, w/3, h);
			root->B = BuildNode(im, {ul.first + w/3, ul.second}, w/3, h);
			root->C = BuildNode(im, {ul.first + 2 *w/3, ul.second }, w/3, h);
		} else if (rem == 1) {
			root->A = BuildNode(im, ul, (w-1)/3, h);
			root->B = BuildNode(im, {ul.first + (w-1)/3, ul.second}, (w-1)/3 + 1, h);
			root->C = BuildNode(im, {ul.first + 2*(w-1)/3 + 1, ul.second}, (w-1)/3, h);
		} else {
			root->A = BuildNode(im, ul, (w-2)/3 + 1, h);
			root->B = BuildNode(im, {ul.first + (w-2)/3 + 1, ul.second}, (w-2)/3, h);
			root->C = BuildNode(im, {ul.first + 2*(w-2)/3 + 1, ul.second}, (w-2)/3 + 1, h);
		}
	}

	// REPLACE THE LINE BELOW WITH YOUR CODE

	//return root node
	return root;
}

/*==== ALSO IMPLEMENT ANY PRIVATE FUNCTIONS YOU HAVE DECLARED ====*/