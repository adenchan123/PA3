/**
 * @file tritree.cpp
 * @author CPSC 221
 * @description TriTree class implementation, CPSC 221 PA3
 *
 * This file must be submitted for grading.
 *
**/

#include "tritree.h"

TriTree::TriTree(PNG& imIn) : width(imIn.width()), height(imIn.height()) {
	// REPLACE THE LINEs BELOW WITH YOUR CODE
	root = BuildNode(imIn, {0,0}, width, height);
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

void TriTree::Copy(const TriTree& other, Node* node) {
	// YOUR CODE HERE
}

void TriTree::Copy(const TriTree& other) {
	Copy(other, root);
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

void TriTree::Prune(double tol, Node* node) {
	if(node == nullptr) {
		return;
	}
	vector<Node*> nodes;
	GetLeafNodes(node, nodes);

	RGBAPixel curr_pix(node->avg);
	bool to_prune = true;
	for(Node* node_l: nodes) {
		if(curr_pix.dist(node_l->avg) > tol) {
			to_prune = false;
			break;
		}
	}

	if(to_prune) {
		Clear(node->A);
		Clear(node->B);
		Clear(node->C);

		node->A = nullptr;
		node->B = nullptr;
		node->C = nullptr;
	} else {
		Prune(tol, node->A);
		Prune(tol, node->B);
		Prune(tol, node->C);
	}
}

void TriTree::Prune(double tol) {
	Prune(tol, root);
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
	
	//printf("new node at (%d, %d), width: %d - height: %d\n", ul.first, ul.second, w, h);

	//final case, one pixel, leaf node
	if (h == 1 && w == 1) {
		//printf("getting pixel at (%d, %d)\n", ul.first, ul.second);
		RGBAPixel * p = im.getPixel(ul.first, ul.second);
		root->avg = *p;
		return root;
	} else if (h <1 || w < 1) {
		return NULL;
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

	int rsum = 0, gsum = 0, bsum = 0, n = 0;
	int total_pix = 0;

	//calculate average colour after assigning children
	if (root->A != nullptr) {
		int dimension_A = root->A->height * root->A->width;
		total_pix += dimension_A;
		rsum += root->A->avg.r * dimension_A;
		gsum += root->A->avg.g * dimension_A;
		bsum += root->A->avg.b * dimension_A;
	}

	if (root->B != nullptr) {
		int dimension_B = root->B->height * root->B->width;
		total_pix += dimension_B;
		rsum += root->B->avg.r * dimension_B;
		gsum += root->B->avg.g * dimension_B;
		bsum += root->B->avg.b * dimension_B;
	}

	if (root->C != nullptr) {
		int dimension_C = root->C->height * root->C->width;
		total_pix += dimension_C;
		rsum += root->C->avg.r * dimension_C;
		gsum += root->C->avg.g * dimension_C;
		bsum += root->C->avg.b * dimension_C;
	}

	root->avg = RGBAPixel(rsum/total_pix, gsum/total_pix, bsum/total_pix);

	// REPLACE THE LINE BELOW WITH YOUR CODE

	//return root node
	return root;
}

/*==== ALSO IMPLEMENT ANY PRIVATE FUNCTIONS YOU HAVE DECLARED ====*/
