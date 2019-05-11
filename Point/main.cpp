#include "main.h"
#include "Point.h"
#include "List.h"

int main()
{
	List list;

	list.push(new PointLink(Point(10, 10)));
	list.push(new PointLink(Point(20, 20)));
	list.push(new PointLink(Point(30, 10)));
	list.push(new PointLink(Point(30, 40)));
	list.push(new PointLink(Point(30, 50)));
	list.push(new PointLink(Point(60, 50)));

	PointLink* node = NULL;

	while ( (node = list.search(node)) != NULL )
	{
		node->data.print();
		node->next->data.print();
		node->next->next->data.print();
		cout << endl;
	}

	return 0;
}