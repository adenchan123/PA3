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
	width = 0;
	height = 0;
	root = nullptr;
}

void TriTree::Clear(Node* node) {
	if(node == nullptr) {
		return;
	} 

	Clear(node->A);
	Clear(node->B);
	Clear(node->C);

	delete node;
}

void TriTree::Clear() {
	Clear(root);
}

void TriTree::Copy(const TriTree& other) {
	// YOUR CODE HERE
}

void TriTree::GetLeafNodes(Node* node, vector<Node*> &nodes) const {
	if(node == nullptr) {
		return;
	}
	if(node->A == nullptr && node->B == nullptr && node->C == nullptr) {
		nodes.push_back(node);
	} else {
		GetLeafNodes(node->A, nodes);
		GetLeafNodes(node->B, nodes);
		GetLeafNodes(node->C, nodes);
	}
}

PNG TriTree::Render() const {
	vector<Node*> nodes;
	GetLeafNodes(root, nodes);

	PNG img(width, height);
	for(Node* node: nodes) {
		pair<int, int> upperleft = node->upperleft;
		int upper_x = upperleft.first;
		int upper_y = upperleft.second;

		int w = node->width;
		int h = node->height;
		RGBAPixel avg_color = node->avg;

		// Draw pixels in img block with the avg color in node
		for(int pix_x = upper_x; pix_x < upper_x + w; pix_x++) {
			for(int pix_y = upper_y; pix_y < upper_y + h; pix_y++) {
				RGBAPixel *curr_pix = img.getPixel(pix_x, pix_y);
				*curr_pix = avg_color;
			}
		}
	}
	
	return img;
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
	// REPLACE THE LINE BELOW WITH YOUR CODE
	return nullptr;
}

/*==== ALSO IMPLEMENT ANY PRIVATE FUNCTIONS YOU HAVE DECLARED ====*/