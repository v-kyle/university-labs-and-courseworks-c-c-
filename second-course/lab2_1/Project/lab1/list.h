template <typename TValue>
class List
{
private:
	class Node
	{
	public:
		Node* next = nullptr;
		TValue data;
	};
	Node* tail = nullptr;
	Node* head = nullptr;
public:
	void push_back(TValue element)
	{
		if (!tail)
		{
			tail = head = new Node;
			tail->data = element;
		}
		else
		{
			tail->next = new Node;
			tail = tail->next;
			tail->data = element;
		}
	}
	TValue next()
	{
		TValue value = head->data;
		head = head->next;
		return value;
	}
	bool isEmpty()
	{
		if (!head) return true;
		else return false;
	}
};
