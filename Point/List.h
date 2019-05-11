#include "main.h"
#include "main.h"
#include "Point.h"

struct PointLink
{
public:
	Point data;
	PointLink* next;

	PointLink(): next(NULL) {}
	PointLink(const Point& _data): next(NULL)
	{
		data = _data;
	}
	virtual ~PointLink() {}
};

class List
{
protected:
	PointLink* head;
	
public:
	List();

	void push(PointLink*);
	PointLink* remove(PointLink* = NULL);
	PointLink* search(PointLink* = NULL);
};

List::List(): head(NULL)
{}

void List::push(PointLink* node)
{
	if (!head) head = node;
	else
	{
		node->next = head;
		head = node;
	}
}

PointLink* List::remove(PointLink* node)
{
	PointLink* temp = head;
	PointLink* prev = NULL;

	if ( head == node )
	{
		head = head->next;
		node->next = 0;

		return node;
	}
	
	while(temp)
	{
		if ( temp == node )
		{
			prev->next = temp->next;
			node->next = 0;
			return node;
		}

		prev = temp;
		temp = temp->next;
	}

	return 0;
}

PointLink* List::search(PointLink* offset)
{
	PointLink* start = head;
	
	if ( offset )
	{
		while(offset != start)
		{
			if (start->next)
				start = start->next;
			else
				return NULL;
		}

		if (start->next)
			start = start->next;
		else
			return NULL;
	}

	while( start && start->next && start->next->next )
	{
		if ( start->data.isCorrect(start->next->data, start->next->next->data) ) 
			return start;

		if ( start->next )
			start = start->next;
		else
			return NULL;
	}
	
	return NULL;	
}