#pragma once
#include"List.h"

using namespace std;

enum Color
{
	RED, BLACK
};

template<typename TypeKey, typename TypeValue>
class Map {
public:
	class Node
	{
	public:
		Node(bool color = RED, TypeKey key = TypeKey(), Node* parent = NULL, Node* left = NULL, Node* right = NULL, TypeValue value = TypeValue()) :color(color), key(key), parent(parent), left(left), right(right), value(value) {}
		TypeKey key;
		TypeValue value;
		bool color;
		Node* parent;
		Node* left;
		Node* right;
	};

	~Map()
	{
		if (this->Root != NULL)
			this->clear();
		Root = NULL;
		delete TNULL;
		TNULL = NULL;
	}

	Map(Node* Root = NULL, Node* TNULL = new Node(0)) :Root(TNULL), TNULL(TNULL) {}

	void printTree()
	{
		if (Root)
		{
			print_helper(this->Root, "", true);
		}
		else throw std::out_of_range("Tree is empty!");
	}

	void  insert(TypeKey key, TypeValue value)
	{
		if (this->Root != TNULL)
		{
			Node* node = NULL;
			Node* parent = NULL;
			/* Search leaf for new element */
			for (node = this->Root; node != TNULL; )
			{
				parent = node;
				if (key < node->key)
					node = node->left;
				else if (key > node->key)
					node = node->right;
				else if (key == node->key)
					throw std::out_of_range("key is repeated");
			}

			node = new Node(RED, key, TNULL, TNULL, TNULL, value);
			node->parent = parent;


			if (parent != TNULL)
			{
				if (key < parent->key)
					parent->left = node;
				else
					parent->right = node;
			}
			insert_fix(node);
		}
		else
		{
			this->Root = new Node(BLACK, key, TNULL, TNULL, TNULL, value);
		}
	}

	List<TypeKey>* get_keys() {
		List<TypeKey>* list = new List<TypeKey>();
		this->ListKey(Root, list);
		return list;
	}
	List<TypeValue>* get_values() {
		List<TypeValue>* list = new List<TypeValue>();
		this->ListValue(Root, list);
		return list;
	}

	TypeValue find(TypeKey key)
	{
		Node* node = Root;
		while (node != TNULL && node->key != key)
		{
			if (node->key > key)
				node = node->left;
			else
				if (node->key < key)
					node = node->right;
		}
		if (node != TNULL)
			return node->value;
		else
			throw std::out_of_range("Key is missing");
	}

	void remove(TypeKey key)
	{
		this->delete_node(this->find_key(key));
	}

	void clear()
	{
		this->clear_tree(this->Root);
		this->Root = NULL;
	}

	bool find_is(TypeKey key) {
		Node* node = Root;

		while (node != TNULL && node->key != key) {
			if (node->key > key)
				node = node->left;
			else
				if (node->key < key)
					node = node->right;
		}
		if (node != TNULL)
			return true;
		else
			return false;
	}
	void increment_value(TypeKey key) {
		Node* cur = this->find_value(key);
		cur->value++;
	}
private:
	Node* Root;
	Node* TNULL;

	//delete functions

	void delete_node(Node* find_node)
	{
		Node* node_with_fix, * cur_for_change;
		cur_for_change = find_node;
		bool cur_for_change_original_color = cur_for_change->color;
		if (find_node->left == TNULL)
		{
			node_with_fix = find_node->right;
			transplant(find_node, find_node->right);
		}
		else if (find_node->right == TNULL)
		{
			node_with_fix = find_node->left;
			transplant(find_node, find_node->left);
		}
		else
		{
			cur_for_change = minimum(find_node->right);
			cur_for_change_original_color = cur_for_change->color;
			node_with_fix = cur_for_change->right;
			if (cur_for_change->parent == find_node)
			{
				node_with_fix->parent = cur_for_change;
			}
			else
			{
				transplant(cur_for_change, cur_for_change->right);
				cur_for_change->right = find_node->right;
				cur_for_change->right->parent = cur_for_change;
			}
			transplant(find_node, cur_for_change);
			cur_for_change->left = find_node->left;
			cur_for_change->left->parent = cur_for_change;
			cur_for_change->color = find_node->color;
		}
		delete find_node;
		if (cur_for_change_original_color == RED)
		{
			this->delete_fix(node_with_fix);
		}
	}

	//swap links(parent and other) for rotate
	void transplant(Node* current, Node* current1)
	{
		if (current->parent == TNULL)
		{
			Root = current1;
		}
		else if (current == current->parent->left)
		{
			current->parent->left = current1;
		}
		else
		{
			current->parent->right = current1;
		}
		current1->parent = current->parent;
	}

	void clear_tree(Node* tree)
	{
		if (tree != TNULL)
		{
			clear_tree(tree->left);
			clear_tree(tree->right);
			delete tree;
		}
	}

	//find functions

	Node* minimum(Node* node)
	{
		while (node->left != TNULL)
		{
			node = node->left;
		}
		return node;
	}

	Node* maximum(Node* node)
	{
		while (node->right != TNULL)
		{
			node = node->right;
		}
		return node;
	}

	Node* grandparent(Node* current)
	{
		if ((current != TNULL) && (current->parent != TNULL))
			return current->parent->parent;
		else
			return TNULL;
	}

	Node* uncle(Node* current)
	{
		Node* current1 = grandparent(current);
		if (current1 == TNULL)
			return TNULL; // No grandparent means no uncle
		if (current->parent == current1->left)
			return current1->right;
		else
			return current1->left;
	}

	Node* sibling(Node* n)
	{
		if (n == n->parent->left)
			return n->parent->right;
		else
			return n->parent->left;
	}

	Node* find_key(TypeKey key)
	{
		Node* node = this->Root;
		while (node != TNULL && node->key != key)
		{
			if (node->key > key)
				node = node->left;
			else
				if (node->key < key)
					node = node->right;
		}
		if (node != TNULL)
			return node;
		else
			throw std::out_of_range("Key is missing");
	}

	//all print function

	void print_helper(Node* root, string indent, bool last)
	{
		if (root != TNULL)
		{
			cout << indent;
			if (last)
			{
				cout << "R----";
				indent += "   ";
			}
			else
			{
				cout << "L----";
				indent += "|  ";
			}
			string sColor = !root->color ? "black" : "red";
			cout << root->key << " (" << sColor << ")" << endl;
			print_helper(root->left, indent, false);
			print_helper(root->right, indent, true);
		}
	}

	void list_key_or_value(int mode, List<TypeKey>* list)
	{
		if (this->Root != TNULL)
			this->key_or_value(Root, list, mode);
		else
			throw std::out_of_range("Tree empty!");
	}

	void key_or_value(Node* tree, List<TypeKey>* list, int mode)
	{
		if (tree != TNULL)
		{
			key_or_value(tree->left, list, mode);
			if (mode == 1)
				list->push_back(tree->key);
			else
				list->push_back(tree->value);
			key_or_value(tree->right, list, mode);
		}
	}

	//fix

	void insert_fix(Node* node)
	{
		Node* uncle;
		/* Current node is RED */
		while (node != this->Root && node->parent->color == RED)//
		{
			/* node in left tree of grandfather */
			if (node->parent == this->grandparent(node)->left)//
			{
				/* node in left tree of grandfather */
				uncle = this->uncle(node);
				if (uncle->color == RED)
				{
					/* Case 1 - uncle is RED */
					node->parent->color = BLACK;
					uncle->color = BLACK;
					this->grandparent(node)->color = RED;
					node = this->grandparent(node);
				}
				else {
					/* Cases 2 & 3 - uncle is BLACK */
					if (node == node->parent->right)
					{
						/*Reduce case 2 to case 3 */
						node = node->parent;
						this->left_rotate(node);
					}
					/* Case 3 */
					node->parent->color = BLACK;
					this->grandparent(node)->color = RED;
					this->right_rotate(this->grandparent(node));
				}
			}
			else {
				/* Node in right tree of grandfather */
				uncle = this->uncle(node);
				if (uncle->color == RED)
				{
					/* Uncle is RED */
					node->parent->color = BLACK;
					uncle->color = BLACK;
					this->grandparent(node)->color = RED;
					node = this->grandparent(node);
				}
				else {
					/* Uncle is BLACK */
					if (node == node->parent->left)
					{
						node = node->parent;
						this->right_rotate(node);
					}
					node->parent->color = BLACK;
					this->grandparent(node)->color = RED;
					this->left_rotate(this->grandparent(node));
				}
			}
		}
		this->Root->color = BLACK;
	}

	void delete_fix(Node* node)
	{
		Node* sibling;
		while (node != this->Root && node->color == BLACK)//
		{
			sibling = this->sibling(node);
			if (sibling != TNULL)
			{
				if (node == node->parent->left)//
				{
					if (sibling->color == BLACK)
					{
						node->parent->color = BLACK;
						sibling->color = RED;
						this->left_rotate(node->parent);
						sibling = this->sibling(node);
					}
					if (sibling->left->color == RED && sibling->right->color == RED)
					{
						sibling->color = BLACK;
						node = node->parent;
					}
					else
					{
						if (sibling->right->color == RED)
						{
							sibling->left->color = RED;
							sibling->color = BLACK;
							this->left_rotate(sibling);
							sibling = this->sibling(node);
						}
						sibling->color = node->parent->color;
						node->parent->color = RED;
						sibling->right->color = RED;
						this->left_rotate(node->parent);
						node = this->Root;
					}
				}
				else
				{
					if (sibling->color == BLACK);
					{
						sibling->color = RED;
						node->parent->color = BLACK;
						this->right_rotate(node->parent);
						sibling = this->sibling(node);
					}
					if (sibling->left->color == RED && sibling->right->color)
					{
						sibling->color = BLACK;
						node = node->parent;
					}
					else
					{
						if (sibling->left->color == RED)
						{
							sibling->right->color = RED;
							sibling->color = BLACK;
							this->left_rotate(sibling);
							sibling = this->sibling(node);
						}
						sibling->color = node->parent->color;
						node->parent->color = RED;
						sibling->left->color = RED;
						this->right_rotate(node->parent);
						node = Root;
					}
				}
			}

		}
		this->Root->color = BLACK;
	}

	//Rotates

	void left_rotate(Node* node)
	{
		Node* right = node->right;
		/* Create node->right link */
		node->right = right->left;
		if (right->left != TNULL)
			right->left->parent = node;
		/* Create right->parent link */
		if (right != TNULL)
			right->parent = node->parent;
		if (node->parent != TNULL)
		{
			if (node == node->parent->left)
				node->parent->left = right;
			else
				node->parent->right = right;
		}
		else {
			this->Root = right;
		}
		right->left = node;
		if (node != TNULL)
			node->parent = right;
	}

	void right_rotate(Node* node)
	{
		Node* left = node->left;
		/* Create node->left link */
		node->left = left->right;
		if (left->right != TNULL)
			left->right->parent = node;
		/* Create left->parent link */
		if (left != TNULL)
			left->parent = node->parent;
		if (node->parent != TNULL)
		{
			if (node == node->parent->right)
				node->parent->right = left;
			else
				node->parent->left = left;
		}
		else
		{
			this->Root = left;
		}
		left->right = node;
		if (node != TNULL)
			node->parent = left;
	}
	void ListValue(Node* tree, List<TypeValue>* list) {
		if (tree != TNULL) {
			ListValue(tree->left, list);
			list->push_back(tree->value);
			ListValue(tree->right, list);
		}
	}
	void ListKey(Node* tree, List<TypeKey>* list) {
		if (tree != TNULL) {
			ListKey(tree->left, list);
			list->push_back(tree->key);
			ListKey(tree->right, list);
		}
	}

	Node* find_value(TypeKey key) {
		Node* node = Root;

		while (node != TNULL && node->key != key) {
			if (node->key > key)
				node = node->left;
			else
				if (node->key < key)
					node = node->right;
		}
		if (node != TNULL)
			return node;

	}
};