#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include "pair.hpp"
#include <iostream>

#define RED 'r'
#define BLACK 'b'

// template<class T>
// class Node {

// public:

// 	typedef T	value_type;

// 	value_type	val;
// 	Node*		left;
// 	Node*		right;
// 	Node*		parent;
// 	char		color;

// }; // node

template<class T, class Alloc = std::allocator<T> >
class RB_tree {

public:

	typedef T												value_type;

	class Node {
		public:

			value_type	val;
			Node*		left;
			Node*		right;
			Node*		parent;
			char		color;

			Node& operator++(void) {
				if (this->right != null_leaf)
					return getLeftMost(this->right);
				while (this->parent != null_leaf && *this == this->parent->right)
					this = this->parent;
				return this->parent;
			}

			Node& operator--(void) {

			}

	}; // node


	typedef typename Alloc::template rebind<Node>::other	allocator_type;

	Node* 			root;
	Node* 			null_leaf;
	allocator_type	alloc;

		/*********************************/
		/*							     */
		/*  CONSTRUCTORS AND DESTRUCTORS */
		/*								 */
		/*********************************/

	RB_tree(allocator_type const& alloc = allocator_type()) {
		this->alloc = alloc;
		null_leaf = this->alloc.allocate(1);
		null_leaf->left = nullptr;
		null_leaf->right = nullptr;
		null_leaf->parent = nullptr;
		null_leaf->color = BLACK;
		root = null_leaf;
	}

	~RB_tree() {
		this->clean_tree(this->root);
		this->alloc.deallocate(this->null_leaf, 1);
	}

		/*********************************/
		/*							     */
		/*			  ROTATIONS 		 */
		/*								 */
		/*********************************/

	void left_rotate(Node* nod) {
		Node* n = nod->right;
		nod->right = n->left;
		if (n->left != null_leaf)
			n->left->parent = nod;
		n->parent = nod->parent;
		if (nod->parent == null_leaf) // nod = root
			this->root = n;
		else if (nod == nod->parent->left) // nod == left child
			nod->parent->left = n;
		else
			nod->parent->right = n;
		n->left = nod;
		nod->parent = n;
	}

	void right_rotate(Node* nod) {
		Node* n = nod->left;
		nod->left = n->right;
		if (n->right != null_leaf)
			n->right->parent = nod;
		n->parent = nod->parent;
		if (nod->parent == null_leaf)
			this->root = n;
		else if (nod == nod->parent->right)
			nod->parent->right = n;
		else
			nod->parent->left = n;
		n->right = nod;
		nod->parent = n;
	}

		/*********************************/
		/*							     */
		/*			    FIXUP   		 */
		/*								 */
		/*********************************/

	// 3 CASES TO FIX :
	// node is left-child, parent is red, uncle is red
	// node is right-child, parent is red, uncle is black
	// node is left-child, parent is red, uncle is black
	// must fix them symetrically --> those cases are used if parent is left child, same logic applies if right child
	void insert_fixup(Node* nod) {
		Node* n;
		while (nod->parent->color == RED) {

			if (nod->parent == nod->parent->parent->left) { // parent is left child
				n = nod->parent->parent->right; // uncle
				if (n->color == RED) { // case 1
					nod->parent->color = BLACK;
					n->color = BLACK;
					nod->parent->parent->color = RED;
					nod = nod->parent->parent;
				} else {
					if (nod == nod->parent->right) {// case 2
						nod = nod->parent;					
						this->left_rotate(nod);
					}
					// case 3
					nod->parent->color = BLACK;
					nod->parent->parent->color = RED;
					this->right_rotate(nod->parent->parent);
				}
			} else { // parent is right child
				n = nod->parent->parent->left; // uncle
				if (n->color == RED) { // case 1
					nod->parent->color = BLACK;
					n->color = BLACK;
					nod->parent->parent->color = RED;
					nod = nod->parent->parent;
				} else {
					if (nod == nod->parent->left) { // case 2
						nod = nod->parent;
						this->right_rotate(nod);
					}
					// case 3
					nod->parent->color = BLACK;
					nod->parent->parent->color = RED;
					this->left_rotate(nod->parent->parent);
				}
			}
		}
		this->root->color = BLACK;
		this->null_leaf->parent = nullptr;
	}

	// 4 CASES THAT VIOLATES RED BLACK TREE PROPERTIES AFTER AN INSERTION
	// (w is the sibling of the new node)
	// - w is red
	// - w is black, its children are black
	// - w is black, its right child is black and left child is red
	// - w is black, its right child is red
	void delete_fixup(Node *x) {
		Node* w;
		while (x != this->root && x->color == BLACK) {
			if (x == x->parent->left) {
				w = x->parent->right;
				if (w->color == RED) { // case 1
					w->color = BLACK;
					x->parent->color = RED;
					left_rotate(x->parent);
					w = x->parent->right;
				}
				if (w->left->color == BLACK && w->right->color == BLACK) { // case 2
					w->color = RED;
					x = x->parent;
				} else {
					if (w->right->color == BLACK) { // case 3
						w->left->color = BLACK;
						w->color = RED;
						right_rotate(w);
						w = x->parent->right;
					}
					// case 4
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->right->color = BLACK;
					left_rotate(x->parent);
					x = this->root;
				}
			} else {
				w = x->parent->left;
				if (w->color == RED) {
					w->color = BLACK;
					x->parent->color = RED;
					right_rotate(x->parent);
					w = x->parent->left;
				}
				if (w->right->color == BLACK && w->left->color == BLACK) {
					w->color = RED;
					x = x->parent;
				} else {
					if (w->left->color == BLACK) {
						w->right->color = BLACK;
						w->color = RED;
						left_rotate(w);
						w = x->parent->left;
					}
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->left->color = BLACK;
					right_rotate(x->parent);
					x = this->root;
				}
			}
		}
		x->color = BLACK;
	}

		/*********************************/
		/*							     */
		/*			    UTILS 	    	 */
		/*								 */
		/*********************************/

	void clean_tree(Node* nod) {
		if (nod != null_leaf) {
			clean_tree(nod->left);
			clean_tree(nod->right);
			this->alloc.deallocate(nod, 1);
		}
	}

	void transplant(Node *u, Node *v) {
		if (u->parent == null_leaf)
			this->root = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;
		v->parent = u->parent;
	}

	Node* minimum(Node *x) {
		while (x->left != null_leaf)
			x = x->left;
		return x;
	}

	int size(Node *nod) {
		if (nod == null_leaf)
			return 0;
		return 1 + size(nod->left) + size(nod->right);
	}

		/*********************************/
		/*							     */
		/*			  ITERATORS 		 */
		/*								 */
		/*********************************/

	static Node* getLeftMost(Node *n) {
		while (n->left != null_leaf)
			n = n->left;
		return n;
	}

	Node* getRightMost(Node *n) {
		while (n->right != null_leaf)
			n = n->right;
		return n;
	}

	Node* getFirst(void) {
		if (this->root == null_leaf)
			return null_leaf;
		return this->getLeftMost(this->root);
	}

	Node* getLast(void) {
		if (this->root == null_leaf)
			return null_leaf;
		return this->getRightMost(this->root);
	}

	Node* getNext(Node *n) {
		if (n->right != null_leaf)
			return getLeftMost(n->right);
		while (n->parent != null_leaf && n == n->parent->right)
			n = n->parent;
		return n->parent;
	}

	Node* getPrev(Node *n) {
		if (n->left != null_leaf)
			return getRightMost(n->left);
		while (n->parent != null_leaf && n == n->parent->left)
			n = n->parent;
		return n->parent;
	}

		/*********************************/
		/*							     */
		/*			 OPERATIONS 		 */
		/*								 */
		/*********************************/

	Node* create_node(value_type const& val) {
		Node* ret = this->alloc.allocate(1);

		ret->val = val;
		ret->left = null_leaf;
		ret->right = null_leaf;
		ret->parent = null_leaf;
		ret->color = RED;
		return ret;
	}

	void insert_node(Node* nod) {
		Node *tmp = this->root;
		Node *y = this->null_leaf;

		while (tmp != this->null_leaf) {
			y = tmp;
			if (nod->val < tmp->val)
				tmp = tmp->left;
			else
				tmp = tmp->right;
		}
		nod->parent = y;
		if (y == this->null_leaf)
			this->root = nod;
		else if (nod->val < y->val)
			y->left = nod;
		else
			y->right = nod;
		
		nod->left = this->null_leaf;
		nod->right = this->null_leaf;
		nod->color = RED;
		this->insert_fixup(nod);
	}

	void delete_nod(Node *nod) {

		Node *y = nod;
		Node *x;
		char y_color = y->color;

		if (nod->left == null_leaf) {
			x = nod->right;
			transplant(nod, nod->right);
		} else if (nod->right == null_leaf) {
			x = nod->left;
			transplant(nod, nod->left);
		} else {
			y = minimum(nod->right);
			y_color = y->color;
			x = y->right;
			if (y->parent == nod)
				x->parent = y;
			else {
				transplant(y, y->right);
				y->right = nod->right;
				y->right->parent = y;
			}
			transplant(nod, y);
			y->left = nod->left;
			y->left->parent = y;
			y->color = nod->color;
		}
		if (y_color == BLACK)
			this->delete_fixup(x);
	}

	Node *search_node(Node *nod, value_type x) {
		if (nod == null_leaf)
			return NULL;
		if (nod->val == x)
			return nod;
		else if (nod->val > x)
			return search_node(nod->left, x);
		else
			return search_node(nod->right, x);
	}

	void print_tree(Node *nod) {
		printHelper(nod, "", true);
	}

	void printHelper(Node* root, std::string indent, bool last) {
    if (root != null_leaf) {
      std::cout << indent;
      if (last) {
        std::cout << "R---- ";
        indent += "   ";
      } else {
        std::cout << "L---- ";
        indent += "|  ";
      }

      std::cout << root->val << "(" << root->color << ")" << std::endl;
      printHelper(root->left, indent, false);
      printHelper(root->right, indent, true);
    }
  }

}; // rb_tree

#endif