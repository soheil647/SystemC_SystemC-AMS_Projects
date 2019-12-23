#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<math.h>
int a[100], c = 0;
using namespace std;
struct node
{
	int data;
	struct node *next;
	struct node *prev;
}*start;

class linked_list
{
public:
	void create_list(int value)
	{
		struct node *s, *temp;
		temp = new(struct node);
		temp->data = value;
		temp->next = NULL;
		if (start == NULL)
		{
			temp->prev = NULL;
			start = temp;
		}
		else
		{
			s = start;
			while (s->next != NULL)
				s = s->next;
			s->next = temp;
			temp->prev = s;
		}
	}
	void Insert_first(int value)
	{
		if (start == NULL)
		{
			cout << "Create the list at first :))" << endl;
			return;
		}
		struct node *temp;
		temp = new(struct node);
		temp->prev = NULL;
		temp->data = value;
		temp->next = start;
		start->prev = temp;
		start = temp;
		cout << "Element has been inserted :))" << endl;
	}
	void Insert_positional(int value, int pos)
	{
		if (start == NULL)
		{
			cout << "Creat the list :)) " << endl;
			return;
		}
		struct node *tmp, *q;
		int i;
		q = start;
		for (i = 0; i < pos - 1; i++)
		{
			q = q->next;
			if (q == NULL)
			{
				cout << "Elements count are less than list length :)) ";
				cout << pos << " elements " << endl;
				return;
			}
		}
		tmp = new(struct node);
		tmp->data = value;
		if (q->next == NULL)
		{
			q->next = tmp;
			tmp->next = NULL;
			tmp->prev = q;
		}
		else
		{
			tmp->next = q->next;
			tmp->next->prev = tmp;
			q->next = tmp;
			tmp->prev = q;
		}
		cout << "Element Inserted" << endl;
	}
	void Delete(int value)
	{
		struct node *tmp, *q;
		/*first element deletion*/
		if (start->data == value)
		{
			tmp = start;
			start = start->next;
			start->prev = NULL;
			cout << "Element Deleted" << endl;
			free(tmp);
			return;
		}
		q = start;
		while (q->next->next != NULL)
		{
			/*Element deleted in between*/
			if (q->next->data == value)
			{
				tmp = q->next;
				q->next = tmp->next;
				tmp->next->prev = q;
				cout << "Element Deleted" << endl;
				free(tmp);
				return;
			}
			q = q->next;
		}
		/*last element deleted*/
		if (q->next->data == value)
		{
			tmp = q->next;
			free(tmp);
			q->next = NULL;
			cout << "Element has been deleted :))" << endl;
			return;
		}
		cout << "Element " << value << " not found" << endl;
	}
	void Display()
	{
		struct node *q;
		if (start == NULL)
		{
			cout << "List is empty :))" << endl;
			return;
		}
		q = start;
		cout << "The List after changes is : :))" << endl;
		while (q != NULL)
		{
			cout << q->data << " -> ";
			a[c] = q->data;
			c++;
			q = q->next;
		}
		cout << "NULL" << endl;
	}
};


int main()
{
	int choice, element, position;
	linked_list input_list;
	input_list.create_list(1);
	input_list.Insert_positional(2, 1);
	input_list.Insert_positional(3, 2);
	input_list.Insert_positional(1, 3);
	input_list.Display();
	cout << "\n\n";
	input_list.Delete(2);
	input_list.Display();
	return 0;
}