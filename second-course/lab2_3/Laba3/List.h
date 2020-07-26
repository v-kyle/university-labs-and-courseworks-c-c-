#pragma once
#include<iostream>
using namespace std;

template<typename TValue>
class List
{
private:
	class Node {
	public:
		Node(TValue data = TValue(), Node* Next = NULL) {
			this->data = data;
			this->Next = Next;
		}
		Node* Next;
		TValue data;
	};

	Node* head;
	Node* tail;
	size_t size;
public:
	void push_back(TValue obj) {
		if (head != NULL) {
			this->tail->Next = new Node(obj);
			tail = tail->Next;
		}
		else {
			this->head = new Node(obj);
			this->tail = this->head;
		}
		size++;
	}
	void push_front(TValue obj) {
		if (head != NULL) {
			Node* current = new Node;
			current->data = obj;
			current->Next = this->head;
			this->head = current;
		}
		else {
			this->head = new Node(obj);
		}
		this->size++;
	}
	void pop_back() {
		if (head != NULL) {
			Node* current = head;
			while (current->Next != tail)
				current = current->Next;
			delete tail;
			tail = current;
			tail->Next = NULL;
			size--;
		}
		else throw std::out_of_range("out_of_range");
	}
	void pop_front() {
		if (head != NULL) {
			Node* current = head;
			head = head->Next;
			delete current;
			size--;
		}
		else throw std::out_of_range("out_of_range");
	}
	void insert(TValue obj, size_t index) {
		if (index >= 0 && this->size > index) {
			if (this->head != NULL) {
				if (index == 0)
					this->push_front(obj);
				else
					if (index == this->size - 1)
						this->push_back(obj);
					else
					{
						Node* current = new Node;
						Node* current1 = head;
						for (int i = 0; i < index - 1; i++) {
							current1 = current1->Next;
						}
						current->data = obj;
						current->Next = current1->Next;
						current1->Next = current;
						size++;
					}
			}
		}
		else {
			throw std::out_of_range("out_of_range");
		}
	}
	TValue at(size_t index) {
		if (this->head != NULL && index >= 0 && index <= this->size - 1) {
			if (index == 0)
				return this->head->data;
			else
				if (index == this->size - 1)
					return this->tail->data;
				else
				{
					Node* current = head;
					for (int i = 0; i < index; i++) {
						current = current->Next;
					}
					return current->data;
				}
		}
		else {
			throw std::out_of_range("out_of_range");
		}
	}
	void remove(int index) { // удаление элемента по индексу
		if (head != NULL && index >= 0 && index <= size - 1) {
			if (index == 0) this->pop_front();
			else
				if (index == this->size - 1) this->pop_back();
				else
					if (index != 0) {
						Node* current = head;
						for (int i = 0; i < index - 1; i++) {//переходим на предэлемент
							current = current->Next;
						}

						Node* current1 = current->Next;
						current->Next = current->Next->Next;
						delete current1;
						size--;
					}
		}
		else {
			throw std::out_of_range("out_of_range");
		}
	}
	size_t get_size() { // получение размера списка
		return size;
	}
	void print_to_console() { // вывод элементов списка в консоль через разделитель
		if (this->head != NULL) {
			Node* current = head;
			for (int i = 0; i < size; i++) {
				cout << current->data << ' ';
				current = current->Next;
			}
		}
	}
	void clear() { // удаление всех элементов списка
		if (head != NULL) {
			Node* current = head;
			while (head != NULL) {
				current = current->Next;
				delete head;
				head = current;
			}
			size = 0;
		}
	}
	void set(size_t index, TValue obj)  // замена элемента по индексу на передаваемый элемент 
	{
		if (this->head != NULL && this->get_size() >= index && index >= 0) {
			Node* current = head;
			for (int i = 0; i < index; i++) {
				current = current->Next;
			}
			current->data = obj;
		}
		else {
			throw std::out_of_range("out_of_range");
		}
	}
	bool isEmpty() { // проверка на пустоту списка
		return (bool)(head);
	}
	void reverse() { // меняет порядок элементов в списке
		int Counter = size;
		Node* HeadCur = NULL;
		Node* TailCur = NULL;
		for (int j = 0; j < size; j++) {
			if (HeadCur != NULL) {
				if (head != NULL && head->Next == NULL) {
					TailCur->Next = head;
					TailCur = head;
					head = NULL;
				}
				else {
					Node* cur = head;
					for (int i = 0; i < Counter - 2; i++)
						cur = cur->Next;
					TailCur->Next = cur->Next;
					TailCur = cur->Next;
					cur->Next = NULL;
					tail = cur;
					Counter--;
				}
			}
			else {
				HeadCur = tail;
				TailCur = tail;
				Node* cur = head;
				for (int i = 0; i < size - 2; i++)
					cur = cur->Next;
				tail = cur;
				tail->Next = NULL;
				Counter--;
			}
		}
		head = HeadCur;
		tail = TailCur;
	}
	List(Node* head = NULL, Node* tail = NULL, size_t size = 0) :head(head), tail(tail), size(size) {}
	~List() {
		if (head != NULL) {
			this->clear();
		}
	};
};
