#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Visitor;

class Component
{
private:
	string name;
public:
	Component(string _name) :
		name(_name)
	{
	}

	virtual void accept(Visitor& vis)=0;

	string getName() const
	{
		return name;
	}
};

class Detail : public Component
{
private:
	string type;
	int weight;
public:
	Detail(string _name, string _type, int _weight) :
		Component(_name),
		type(_type),
		weight(_weight)
	{
	}

	string getType() const
	{
		return type;
	}

	int getWeight() const
	{
		return weight;
	}

	void accept(Visitor& vis);
};

class Composite : public Component
{
private:
	vector<Component*> components;
public:
	Composite(string _name) :
		Component(_name)
	{
	}

	void add(Component* elem)
	{
		components.push_back(elem);
	}

	vector<Component*> getComponents()
	{
		return components;
	}

	void accept(Visitor& vis);
};

class Visitor
{
public:
	virtual void visit(Detail* detail) = 0;
	virtual void visit(Composite* comp) = 0;
	virtual void showResult(ostream& stream=cout){}
};

class Task1 : public Visitor
{
private:
	map<string, int> counts;
public:
	void visit(Detail* detail)
	{
		counts[detail->getName()]+=1;
	}

	void visit(Composite* comp)
	{
		for (auto i : comp->getComponents())
		{
			i->accept(*this);
		}
	}

	void showResult(ostream& stream = cout)
	{
		stream << "Details and its counts:" << endl;
		for (auto i = counts.begin(); i != counts.end(); ++i)
		{
			stream << i->first << "\t" << i->second << endl;
		}
		stream << endl;
	}
};

class Task2 : public Visitor
{
private:
	int sum;
public:
	Task2() :
		sum(0)
	{
	}

	void visit(Detail* detail)
	{
		if (detail->getType() == "gold" || detail->getType() == "silver" || detail->getType() == "platina")
		{
			sum += detail->getWeight();
		}
	}

	void visit(Composite* comp)
	{
		for (auto i : comp->getComponents())
		{
			i->accept(*this);
		}
	}

	void showResult(ostream& stream = cout)
	{
		stream << "Sum weight of gold, platina and silver:" << endl;
		stream << "sum=" << sum << endl;
	}
};

class Task3 : public Visitor
{
private:
	int quantity;
public:
	Task3() :
		quantity(0)
	{
	}

	void visit(Detail* detail)
	{
		if (detail->getType() == "plastic")
		{
			++quantity;
		}
	}

	void visit(Composite* comp)
	{
		for (auto i : comp->getComponents())
		{
			i->accept(*this);
		}
	}

	void showResult(ostream& stream = cout)
	{
		stream << "Quantity of plastic details:" << endl;
		stream << "quantity=" << quantity << endl;
	}
};

class Task4 : public Visitor
{
private:
	int indent;
	ostream& stream;
public:
	Task4(ostream& _stream=cout):
		indent(0),
		stream(_stream)
	{
	}

	void visit(Detail* detail)
	{
		for (int i = 0; i < indent; ++i)
		{
			stream << " ";
		}
		stream << detail->getName() << endl;
	}

	void visit(Composite* comp)
	{
		for (int i = 0; i < indent; ++i)
		{
			stream << " ";
		}
		indent += 4;
		stream << "(" << comp->getName() << ")" << endl;
		for (auto i : comp->getComponents())
		{
			i->accept(*this);
		}
		indent -= 4;
	}
};

void Detail::accept(Visitor& vis)
{
	vis.visit(this);
}

void Composite::accept(Visitor& vis)
{
	vis.visit(this);
}

Composite* createComputer()
{
	Composite* computer = new Composite("Computer");
	Composite*  SysBlock = new Composite("SysBlock");

	Detail* motherBoard = new Detail("Mother Board", "gold", 20);
	Detail* processor = new Detail("Processor", "platina", 50);
	Detail* box = new Detail("Box", "plastic", 60);
	Detail* monitor = new Detail("Monitor", "gold", 70);
	Detail* keyboard = new Detail("Keyboard", "plastic", 50);
	Detail* mouse = new Detail("Mouse", "platina", 30);

	SysBlock->add(motherBoard);
	SysBlock->add(motherBoard);
	SysBlock->add(processor);

	computer->add(SysBlock);
	computer->add(monitor);
	computer->add(mouse);
	computer->add(keyboard);
	return computer;
}

Composite* createRoom()
{
	Composite* room = new Composite("Room");
	Composite* bed = new Composite("Bed");

	Detail* wall = new Detail("Wall", "gold", 20);
	Detail* carpet = new Detail("Carpet","silver", 40);
	Detail* box = new Detail("Box", "plastic", 60);

	Detail* mattress = new Detail("Mattress","platina", 20);
	Detail* blanket = new Detail("Blanket","gold", 15);
	Detail* pillow = new Detail("Pillow","plastic", 25);

	bed->add(mattress);
	bed->add(blanket);
	bed->add(pillow);

	room->add(wall);
	room->add(carpet);
	room->add(bed);
	room->add(box);
	return room;
}


void visitList(vector<Composite*>& vec, Visitor& vis)
{
	for (auto i : vec)
	{
		i->accept(vis);
	}
	vis.showResult();
}

void main()
{
	vector<Composite*> products;

	products.push_back(createComputer());
	products.push_back(createRoom());
		
	Task1 visitor1;
	visitList(products, visitor1);
	Task2 visitor2;
	visitList(products, visitor2);
	Task3 visitor3;
	visitList(products, visitor3);

	cout << "All details and categories:" << endl;
	Task4 visitor4;
	products[0]->accept(visitor4);
	cout << endl;
	products[1]->accept(visitor4);
	system("pause");
}