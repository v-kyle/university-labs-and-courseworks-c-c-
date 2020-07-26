#pragma once
#include <stdexcept>
#include <iostream>
using namespace std;

template<typename T>
class List
{
private:
	class Node
	{
	public:
		T data;
		Node* next, * prev;
	public:
		Node() : next(NULL), prev(NULL) {};
		Node(T data)
		{
			this->data = data;
			next = NULL;
			prev = NULL;
		}

		~Node()
		{
			next = NULL;
			prev = NULL;
		}

		void set_data(T data)
		{
			this->data = data;
		}

		T get_data()
		{
			return data;
		}

		Node* get_next()
		{
			return next;
		}

		Node* get_prev()
		{
			return prev;
		}

		void set_next(Node* Elem)
		{
			next = Elem;
		}

		void set_prev(Node* Elem)
		{
			prev = Elem;
		}
	};
	Node* head, * tail;

	Node* get_Elem(size_t index)
	{
		if (isEmpty() || (index > get_size() - 1))
		{
			throw out_of_range("Invalid argument");
		}
		else if (index == get_size() - 1)
			return tail;
		else if (index == 0)
			return head;
		else
		{
			Node* temp = head;
			while ((temp) && (index--))
			{
				temp = temp->get_next();
			}
			return temp;
		}
	}
public:
	List() : head(NULL), tail(NULL) {}
	List(int size, int value)
	{
		while (size--)
		{
			push_back(value);
		}
	}

	List(const List<T>& list)
	{
		head = NULL;
		tail = NULL;
		Node* temp = list.head;
		while (temp)
		{
			push_back(temp->get_data());
			temp = temp->get_next();
		}
	}

	~List()
	{
		while (head)
		{
			tail = head->get_next();
			delete head;
			head = tail;
		}
		head = NULL;
	}

	void push_back(T data)
	{
		Node* temp = new Node;
		temp->set_data(data);
		if (head)
		{
			temp->set_prev(tail);
			tail->set_next(temp);
			tail = temp;
		}
		else
		{
			head = temp;
			tail = head;
		}
	}

	void push_front(T data)
	{
		Node* temp = new Node;
		temp->set_data(data);
		if (head)
		{
			temp->set_next(head);
			head->set_prev(temp);
			head = temp;
		}
		else
		{
			head = temp;
			tail = head;
		}
	}

	void push_back(List<bool> list)
	{
		Node* temp = list.head;
		size_t length = list.get_size();
		while ((temp) && (length--))
		{
			push_back(temp->get_data());
			temp = temp->get_next();
		}
	}

	void push_front(List& list)
	{
		Node* temp = list.tail;
		size_t length = list.get_size();
		while ((temp) && (length--))
		{
			push_front(temp->get_data());
			temp = temp->get_prev();
		}
	}

	void pop_back()
	{
		if (head != tail)
		{
			Node* temp = tail;
			tail = tail->get_prev();
			tail->set_next(NULL);
			delete temp;
		}
		else if (!isEmpty())
		{
			Node* temp = tail;
			tail = head = NULL;
			delete temp;
		}
		else
			throw out_of_range("Список пуст!!!");
	}

	void pop_front()
	{
		if (head != tail)
		{
			Node* temp = head;
			head = head->get_next();
			head->set_prev(NULL);
			delete temp;
		}
		else if (!isEmpty())
		{
			Node* temp = head;
			head = tail = NULL;
			delete temp;
		}
		else
			throw out_of_range("Список пуст!!!");
	}

	void insert(size_t index, T data)
	{
		Node* temp;
		temp = get_Elem(index);
		if (temp == head)
			push_front(data);
		else
		{
			Node* newElem = new Node;
			newElem->set_data(data);
			temp->get_prev()->set_next(newElem);
			newElem->set_prev(temp->get_prev());
			newElem->set_next(temp);
			temp->set_prev(newElem);
		}
	}

	T at(size_t index)
	{
		Node* temp;
		temp = get_Elem(index);
		return temp->get_data();
	}

	void remove(size_t index)
	{
		Node* temp;
		temp = get_Elem(index);
		if (temp == head)
			pop_front();
		else if (temp == tail)
			pop_back();
		else
		{
			temp->get_prev()->set_next(temp->get_next());
			temp->get_next()->set_prev(temp->get_prev());
			delete temp;
		}
	}

	void remove(T data)
	{
		Node* temp = head;
		while (temp && temp->get_data() != data)
			temp = temp->get_next();
		if (!temp)
			throw out_of_range("Недопустимый аргумент!!!");
		if (temp == head)
			pop_front();
		else if (temp == tail)
			pop_back();
		else
		{
			temp->get_prev()->set_next(temp->get_next());
			temp->get_next()->set_prev(temp->get_prev());
			delete temp;
		}
	}

	size_t get_size()
	{
		Node* temp = head;
		size_t length = 0;
		while (temp)
		{
			length++;
			temp = temp->get_next();
		}
		return length;
	}

	void print_to_console()
	{
		Node* temp = head;
		while (temp)
		{
			cout << temp->get_data();
			temp = temp->get_next();
		}
	}

	void clear()
	{
		while (head)
		{
			tail = head->get_next();
			delete head;
			head = tail;
		}
	}

	void set(size_t index, T data)
	{
		Node* temp;
		temp = get_Elem(index);
		temp->set_data(data);
	}

	bool isEmpty()
	{
		if (!head)
			return true;
		else
			return false;
	}

	bool compare(List<T> list)
	{
		if (get_size() != list.get_size())
			return false;
		for (int i = 0; i < get_size(); i++) {
			if (at(i) != list.at(i))
				return false;
		}
		return true;
	}

	bool contains(List<char>& list)
	{
		Node* temp = head;
		while (temp) {
			if (temp->get_data().compare(list))
				return true;
			temp = temp->get_next();
		}
		return false;
	}

	void nullify()
	{
		head = NULL;
		tail = NULL;
	}

	int get_price(size_t vertex1, size_t vertex2)
	{
		Node* temp = head;
		while (temp)
		{
			if (temp->get_data().vertex1 == vertex1 && temp->get_data().vertex2 == vertex2)
				return temp->get_data().cost;
			temp = temp->get_next();
		}
		throw invalid_argument("Некорректный аргумент!!!");
	}

	void insert_with_sorting(char data1, float data2)
	{
		if (!head || head->data.second < data2)
		{
			push_front(pair<char, float>(data1, data2));
			return;
		}
		Node* newElem = new Node;
		newElem->data = pair<char, float>(data1, data2);
		int i = 0;
		Node* temp = head;
		while (temp)
		{
			if (temp->data.second < data2)
			{
				temp->get_prev()->set_next(newElem);
				newElem->set_prev(temp->get_prev());
				temp->set_prev(newElem);
				newElem->set_next(temp);
				return;
			}
			if (temp->data.first == data1 && temp->data.second == data2) {
				delete newElem;
				return;
			}
			i++;
			temp = temp->get_next();
		}
		delete newElem;
		push_back(pair<char, float>(data1, data2));
	}
};