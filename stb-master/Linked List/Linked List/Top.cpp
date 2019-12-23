#include <vector>
#include <iostream>

using namespace std;


class Node
{
public:
	int Value;
	Node* next;

public:

};

class Linked_List 
{
private:
	Node* Head;

public:
	Linked_List();
	~Linked_List();

	void Insert_first(int data)
	{
		Node* N1 = new Node ;
		N1->Value = data;
		N1->next = Head;
	}

	void Insert_positional(int data , int Position)
	{
		Node* temp;
		Node* N1;
		for(int i=0;i<=(Position-1);i++)
		{
		temp = temp->next;
		}
		N1 = temp;
		N1->Value = data;
		N1->next = Head;
	}
	void Delete(int data)
	{
		for(int i=0; i<=4; i++)
		{

		}

	}
	void Display()
	{
		Node* temp = NULL;
		temp->next = Head;
		for(int i=0;i<=5;i++)
		{
			cout << temp << " -> " ;
			temp = temp->next;
		}
	}

};



Linked_List::Linked_List(void)
{
}


Linked_List::~Linked_List(void)
{
}

void main()
{
	Linked_List Link;
	int Data;
	int Position;
	cout << "Insert your Data" << endl;
	cin >> Data;
	Link.Insert_first(Data);
	cout << "Insert your Data and position" << endl;
	cin >> Data >> Position ;
	Link.Insert_first(Data);
	Link.Display();


}

