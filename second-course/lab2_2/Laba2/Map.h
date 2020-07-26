#pragma once
#include <iostream>
#include "List.h"
#include <windows.h>

using namespace std;

enum Color { BLACK, RED, };

template <typename TKey, typename TValue1, class TValue2>
class Node
{
private:
	Color color;
	Node<TKey, TValue1, TValue2>* left, * right, * parent;
	TKey key;
	TValue1 value1;
	TValue2 value2;
public:
	Node() : color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
	Node(TKey key, TValue1 value1) : color(RED), left(nullptr), right(nullptr), parent(nullptr), key(key), value1(value1) {}
	Node(TKey key, TValue1 value1, TValue2 value2) : color(RED), left(nullptr), right(nullptr), parent(nullptr), key(key), value1(value1), value2(value2) {}
	bool isOnLeft() { return this == parent->getLeft(); }
	Node<TKey, TValue1, TValue2>* sibling()
	{
		if (parent == nullptr)
			return nullptr;

		if (isOnLeft())
			return parent->right;

		return parent->left;
	}

	bool hasRedChild()
	{
		return (left != nullptr && left->getColor() == RED) || (right != nullptr && right->getColor() == RED);
	}

	void setColor(Color color)
	{
		this->color = color;
	}

	Color getColor()
	{
		if (this == nullptr)
			return BLACK;
		return color;
	}

	void setLeft(Node* ptr)
	{
		left = ptr;
	}

	Node* getLeft()
	{
		return left;
	}

	void setRight(Node* ptr)
	{
		right = ptr;
	}

	Node* getRight()
	{
		return right;
	}

	void setParent(Node* parent)
	{
		this->parent = parent;
	}

	Node* getParent()
	{
		return parent;
	}

	void setKey(TKey key)
	{
		this->key = key;
	}

	TKey getKey()
	{
		return key;
	}

	void setValue1(TValue1 value)
	{
		this->value1 = value;
	}

	TValue1 getValue1()
	{
		return value1;
	}

	void setValue2(TValue2 value)
	{
		value2.push_front(value);
	}

	TValue2 getValue2()
	{
		return value2;
	}
};
#pragma endregion

#pragma region CLASS_MAP
template <typename TKey, typename TValue1, class TValue2>
class map
{
private:
	Node<TKey, TValue1, TValue2>* root;
	void SetColor(int text, int background)
	{
		HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleHandle, (WORD)((background << 4) | text));
	}

	void fixInsertion(Node<TKey, TValue1, TValue2>*& node)
	{
		if (root == node) {
			node->setColor(BLACK);
			return;
		}
		Color c;
		Node<TKey, TValue1, TValue2>* parent = nullptr, * grandparent = nullptr, * uncle = nullptr;
		//Проверка правил красно чёрного дерева (в случае если родитель красного цвета)
		while (node != root && node->getParent()->getColor() == RED)
		{
			parent = node->getParent();
			grandparent = parent->getParent();
			//В случае если родитель "левый" ребёнок
			if (parent == grandparent->getLeft())
			{
				uncle = grandparent->getRight();
				//В случае если дядя тоже "красный" нам достаточно перекрасить деда, папу и дядю
				if (uncle->getColor() == RED)
				{
					parent->setColor(BLACK);
					grandparent->setColor(RED);
					uncle->setColor(BLACK);
					node = grandparent;
				}
				else
				{
					//Если дядя "чёрный", и наш узел "правый" ребёнок, то нужно сделать его "левым"
					if (node == parent->getRight())
					{
						leftRotate(parent);
						node = parent;
						parent = node->getParent();
					}
					//Также необходимо перекрасить папу и деда, а также вызвать поворот для деда
					rightRotate(grandparent);
					c = parent->getColor();
					parent->setColor(grandparent->getColor());
					grandparent->setColor(c);
					node = parent;
				}
			}
			else
			{
				//Зеркально отражаем код для другого расположения папы и дяди
				uncle = grandparent->getLeft();
				if (uncle->getColor() == RED)
				{
					parent->setColor(BLACK);
					grandparent->setColor(RED);
					uncle->setColor(BLACK);
					node = grandparent;
				}
				else
				{
					if (node == parent->getLeft())
					{
						rightRotate(parent);
						node = parent;
						parent = node->getParent();
					}
					leftRotate(grandparent);
					c = parent->getColor();
					parent->setColor(grandparent->getColor());
					grandparent->setColor(c);
					node = parent;
				}
			}
		}
		root->setColor(BLACK);
	}

	Node<TKey, TValue1, TValue2>* minValueNode(Node<TKey, TValue1, TValue2>* node) {

		Node<TKey, TValue1, TValue2>* ptr = node;

		while (ptr->getLeft() != nullptr)
			ptr = ptr->getLeft();

		return ptr;
	}

	void leftRotate(Node<TKey, TValue1, TValue2>* node)
	{
		Node<TKey, TValue1, TValue2>* right_child = node->getRight();
		node->setRight(right_child->getLeft());

		if (node->getRight() != nullptr)
			node->getRight()->setParent(node);

		right_child->setParent(node->getParent());

		if (node->getParent() == nullptr)
			root = right_child;
		else if (node == node->getParent()->getLeft())
			node->getParent()->setLeft(right_child);
		else
			node->getParent()->setRight(right_child);

		right_child->setLeft(node);
		node->setParent(right_child);
	}

	void rightRotate(Node<TKey, TValue1, TValue2>* node)
	{
		Node<TKey, TValue1, TValue2>* left_child = node->getLeft();
		node->setLeft(left_child->getRight());

		if (node->getLeft() != nullptr)
			node->getLeft()->setParent(node);

		left_child->setParent(node->getParent());

		if (node->getParent() == nullptr)
			root = left_child;
		else if (node == node->getParent()->getLeft())
			node->getParent()->setLeft(left_child);
		else
			node->getParent()->setRight(left_child);

		left_child->setRight(node);
		node->setParent(left_child);
	}

	void deleteSubTree(Node<TKey, TValue1, TValue2>* node)
	{
		while (node != nullptr) {
			deleteSubTree(node->getLeft());
			deleteSubTree(node->getRight());
			delete node;
			node = nullptr;
		}
		root = nullptr;
	}

	void setKeys(List<TKey>& list, Node<TKey, TValue1, TValue2>* node)
	{
		while (node)
		{
			setKeys(list, node->getLeft());
			list.push_back(node->getKey());
			setKeys(list, node->getRight());
			return;
		}
	}

	void setValues1(List<TValue1>& list, Node<TKey, TValue1, TValue2>* node)
	{
		while (node)
		{
			setValues1(list, node->getLeft());
			list.push_back(node->getValue1());
			setValues1(list, node->getRight());
			return;
		}
	}

	void setValues2(List<TValue2>& list, Node<TKey, TValue1, TValue2>* node)
	{
		while (node)
		{
			setValues2(list, node->getLeft());
			list.push_back(node->getValue2());
			setValues2(list, node->getRight());
			return;
		}
	}
	// возвращает указатель на элемент с помощью ключа
	Node<TKey, TValue1, TValue2>* search(TKey key)
	{
		Node<TKey, TValue1, TValue2>* temp = root;
		while (temp != NULL && key != temp->getKey())
		{
			if (key < temp->getKey()) {
				temp = temp->getLeft();
			}
			else {
				temp = temp->getRight();
			}
		}
		return temp;
	}

public:
	map() : root(nullptr) {}
	~map() {
		deleteSubTree(root);
	}

	//Вставка ноды
	void insert(TKey key, TValue1 value1, TValue1 value2)
	{
		Node<TKey, TValue1, TValue2>* temp = new Node<TKey, TValue1, TValue2>(key, value1);
		if (!root)
		{
			root = temp;
		}
		else
		{
			Node<TKey, TValue1, TValue2>* temp1 = root;
			Node<TKey, TValue1, TValue2>* temp2 = nullptr;
			while (temp1 != nullptr)
			{
				temp2 = temp1;
				if (temp1->getKey() < temp->getKey())
				{
					temp1 = temp1->getRight();
				}
				else if (temp1->getKey() == temp->getKey()) //Если такой символ уже есть, то нужно просто увеличить его количество
				{
					delete temp;
					temp1->setValue1(temp1->getValue1() + value2);
					return;
				}
				else
				{
					temp1 = temp1->getLeft();
				}
			}
			temp->setParent(temp2);
			if (temp2->getKey() <= temp->getKey())
			{
				temp2->setRight(temp);
			}
			else {
				temp2->setLeft(temp);
			}
		}
		fixInsertion(temp);
	}

	//Возвращает значение, используя ключ
	TValue1 find_value1(TKey key)
	{
		if (!root)
			throw invalid_argument("Мапа пуста!!!");
		Node<TKey, TValue1, TValue2>* temp = root;
		while (temp && temp->getKey() != key)
		{
			if (temp->getKey() < key)
				temp = temp->getRight();
			else
				temp = temp->getLeft();
		}
		if (!temp)
			throw invalid_argument("Такого значения нет в мапе!!!");
		return temp->getValue1();
	}

	TValue2 find_value2(TKey key)
	{
		if (!root)
			throw invalid_argument("Мапа пуста!!!");
		Node<TKey, TValue1, TValue2>* temp = root;
		while (temp && temp->getKey() != key)
		{
			if (temp->getKey() < key)
				temp = temp->getRight();
			else
				temp = temp->getLeft();
		}
		if (!temp)
			throw invalid_argument("Такого значения нет в мапе!!!");
		return temp->getValue2();
	}

	//Очистка мапы
	void clear() {
		if (root == nullptr)
			throw runtime_error("Мапа пуста!!!");
		deleteSubTree(root);
	}

	//Возвращает копию списка, содержащую ключи мапы
	List<TKey> get_keys()
	{
		List<TKey> list;
		setKeys(list, root);
		return list;
	}

	//Возвращает копию списка, содержащую значение мапы
	List<TValue1> get_values1()
	{
		List<TValue1> list;
		setValues1(list, root);
		return list;
	}

	List<TValue2> get_values2()
	{
		List<TValue2> list;
		setValues2(list, root);
		return list;
	}

	void value1_increase(TKey key, TValue1 value)
	{
		Node<TKey, TValue1, TValue2>* temp = search(key);
		temp->setValue1(temp->getValue1() + value);
	}

	void set_value2(TKey key, TValue2& value)
	{
		Node<TKey, TValue1, TValue2>* temp = search(key);
		temp->setValue2(value);
	}

	TKey find_key(TValue2 code_symbols)
	{
		TKey key = NULL;
		bool is_found = false;
		additional_find_key(root, code_symbols, key, is_found);
		return key;
	}

	bool code(TValue2 code_symbols)
	{
		bool is_found = false;
		return additional_code(root, code_symbols, is_found);
	}
	//Вспомогательная (рекурсивная) функция нахождения ключа
	void additional_find_key(Node<TKey, TValue1, TValue2>* node, TValue2 code_symbols, TKey& key, bool& is_found)
	{
		if (node)
		{
			if (node->getValue2().compare(code_symbols))
			{
				key = node->getKey();
				is_found = true;
				return;
			}
			else
			{
				additional_find_key(node->getLeft(), code_symbols, key, is_found);
				if (is_found)
					return;
				additional_find_key(node->getRight(), code_symbols, key, is_found);
			}
		}
	}

	bool additional_code(Node<TKey, TValue1, TValue2>* node, TValue2 code_symbols, bool& is_found)
	{
		if (node) {
			if (node->getValue2().compare(code_symbols))
			{
				is_found = true;
				return true;
			}
			else
			{
				additional_code(node->getLeft(), code_symbols, is_found);
				if (is_found)
					return true;
				additional_code(node->getRight(), code_symbols, is_found);
				return is_found;
			}
		}
	}

};