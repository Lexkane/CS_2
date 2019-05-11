#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <map>
#include <set>
#include <list>
#include <algorithm>
using namespace std;

class Car
{
private:
	string model;
	string type;
	string box;
	int quantity;
	int price;
public:
	Car()
	{
	}

	Car(string _model, string _type, string _box, int _quantity, int _price) :
		model(_model),
		type(_type),
		box(_box),
		quantity(_quantity),
		price(_price)
	{
	}

	int getPrice() const
	{
		return price;
	}

	string getType() const
	{
		return type;
	}

	string getBox() const
	{
		return box;
	}

	string getModel() const
	{
		return model;
	}

	friend bool operator<(const Car& a1, const Car& a2)
	{
		return a1.price < a2.price;
	}

	friend istream& operator>>(istream& is, Car& b)
	{
		is >> b.model >> b.type >> b.box >> b.quantity >> b.price;
		return is;
	}

	friend ostream& operator<<(ostream& os, const Car& b)
	{
		os << b.model << "\t"<< b.type << "\t" << b.box << "\t" << b.quantity << "\t" << b.price;
		return os;
	}
};


class Count
{
private:
	int a;
	int b;
public:
	Count(int _a, int _b) :
		a(_a),
		b(_b)
	{
	}

	bool operator()(const Car& el)
	{
		return el.getPrice() >= a && el.getPrice() <= b;
	}

};

class Sum
{
private:
	string type;
	int sum;
public:
	Sum(string _type) :
		type(_type),
		sum(0)
	{
	}

	void operator()(pair<const string, Car>& el)
	{
		if (el.second.getType() == type)
		{
			sum += el.second.getPrice();
		}
	}

	friend ostream& operator<<(ostream& os, Sum& b)
	{
		os << b.sum;
		return os;
	}
};

void main()
{
	ifstream in("input.txt");
	multimap<string, Car> cars;
	string name; Car car;
	while (!in.eof())
	{
		in >> name >> car;
		cars.insert(make_pair(name, car));
	}

	cout << "Cars factory and products sort by price:" << endl;
	map<string, multiset<Car>> carfactories;
	for (auto i = cars.begin(); i != cars.end(); ++i)
	{
		auto find_iter = carfactories.find(i->first);
		multiset<Car> res;
		if (find_iter != carfactories.end())
		{
			res = find_iter->second;
		}
		res.insert(i->second);
		carfactories[i->first] = res;
	}

	for (auto i = carfactories.begin(); i != carfactories.end(); ++i)
	{
		cout << left << i->first << ":" << endl;
		for (set<Car>::iterator j = i->second.begin(); j != i->second.end(); ++j)
		{
			cout << *j << endl;
		}
		cout << endl;
	}
	cout << endl;
	cout << "Quantity of carfactories with price from [a,b]:" << endl;
	int a, b;
	map<string, int> quants;
	cout << "a="; cin >> a;
	cout << "b="; cin >> b;
	for (auto i = carfactories.begin(); i != carfactories.end(); ++i)
	{
		quants[i->first] = count_if(i->second.begin(), i->second.end(), Count(a,b));
	}
	for (auto i = quants.begin(); i != quants.end(); ++i)
	{
		cout << i->first << "\t" << i->second << endl;
	}
	cout << endl;
	set<string> abx;
	cout << "Auto box and automobile type:" << endl;
	for (auto i = cars.begin(); i != cars.end(); ++i)
	{
		if (i->second.getType() == "automobile" && i->second.getBox() == "auto")
		{
			abx.insert(i->first);
		}
	}

	for (set<string>::iterator i = abx.begin(); i != abx.end(); ++i)
	{
		cout << *i << " ";
	}
	cout << endl <<endl;
	cout << "Load cars sort by name:" << endl;
	map<string, Car> rss;
	for (auto i = cars.begin(); i != cars.end(); ++i)
	{
		if (i->second.getType() == "load")
		{
			rss[i->second.getModel()] = i->second;
		}
	}
	for (auto i = rss.begin(); i != rss.end(); ++i)
	{
		cout << i->second << endl;
	}
	cout << endl;
	cout << "Deleting cars with hand box:" << endl;
	for (auto i = cars.begin(); i != cars.end();)
	{
		if (i->second.getBox() == "hand")
		{
			i = cars.erase(i);
		}
		else
		{
			++i;
		}
	}

	for (auto i = cars.begin(); i != cars.end(); ++i)
	{
		cout << left << i->first << "\t" << i->second << endl;
	}
	cout << endl;
	cout << "Sumator price of all automobile cars:" << endl;
	cout << for_each(cars.begin(), cars.end(), Sum("automobile")) << endl;
	system("pause");
}