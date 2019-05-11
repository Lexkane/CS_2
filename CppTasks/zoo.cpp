#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <iterator>
#include <list>
#include <algorithm>
using namespace std;

class Zoo
{
private:
	string name;
	int price;
	int visiting;
public:
	Zoo(){}
	Zoo(string _name, int _price, int _visiting) :
		name(_name),
		price(_price),
		visiting(_visiting)
	{
	}

	string getName() const
	{
		return name;
	}

	int getPrice() const
	{
		return price;
	}

	int getVisit() const
	{
		return visiting;
	}

	friend istream& operator>>(istream& st, Zoo& el)
	{
		st >> el.name >> el.price >> el.visiting;
		return st;
	}

	friend ostream& operator<<(ostream& st,const Zoo& el)
	{
		st << el.name << " " << el.price << " " << el.visiting;
		return st;
	}

	friend bool operator<(const Zoo& a, const Zoo& b)
	{
		return a.getName() < b.getName();
	}
};

class Animal
{
private:
	string name;
	int count;
	bool red;
public:
	Animal(){}
	Animal(string _name, int _count, bool _red) :
		name(_name),
		count(_count),
		red(_red)
	{
	}

	string getName() const
	{
		return name;
	}

	int getCount() const
	{
		return count;
	}

	bool getRed() const
	{
		return red;
	}

	friend istream& operator>>(istream& st, Animal& el)
	{
		st >> el.name >> el.count >> el.red;
		return st;
	}

	friend ostream& operator<<(ostream& st,const Animal& el)
	{
		st << el.name << " " << el.count << " " << el.red;
		return st;
	}

	friend bool operator<(const Animal& a, const Animal& b)
	{
		return a.getName() < b.getName();
	}
};

bool compare(const Zoo& a, const Zoo& b)
{
	return a.getVisit() < b.getVisit();
}

bool uniqueCompare(const Animal& a, const Animal& b)
{
	return a.getName() == b.getName();
}


void main()
{
	multimap<Zoo, Animal> zooes;
	ifstream in("input.txt");
	Zoo z; Animal an;
	while (!in.eof())
	{
		in >> z >> an;
		zooes.insert(make_pair(z, an));
	}
	cout << "Input data:" << endl;
	for (auto i = zooes.begin(); i != zooes.end(); ++i)
	{
		cout << i->first << " " << i->second << endl;
	}
	cout << "Zooes and their animals:" << endl;
	map<Zoo, multiset<Animal>> animals;
	for (auto i = zooes.begin(); i != zooes.end(); ++i)
	{
		multiset<Animal> _st;
		if (!animals[i->first].empty())
		{
			_st = animals[i->first];
		}
		_st.insert(i->second);
		animals[i->first] = _st;
	}
	for (auto i = animals.begin(); i != animals.end(); ++i)
	{
		cout << i->first << ":" << endl;
		for (auto j = i->second.begin(); j != i->second.end(); ++j)
		{
			cout << *j << endl;
		}
		cout << endl;
	}
	cout << "Animals in red book:" << endl;
	map<Zoo, int> redBook;
	for (auto i = animals.begin(); i != animals.end(); ++i)
	{
		redBook[i->first] = 0;
	}

	for (auto i = zooes.begin(); i != zooes.end(); ++i)
	{
		if (i->second.getRed() == true)
		{
			redBook[i->first]++;
		}
	}

	for (auto i = redBook.begin(); i != redBook.end(); ++i)
	{
		cout << i->first << ": " << i->second << endl;
	}
	cout << "Zooes with input animal:" << endl;
	string name;
	cout << "input name="; cin >> name;
	list<Zoo> lst;
	for (auto i = zooes.begin(); i != zooes.end(); ++i)
	{
		if (i->second.getName() == name)
		{
			lst.push_back(i->first);
		}
	}
	lst.sort(compare);
	ostream_iterator<Zoo> out(cout, "\n");
	copy(lst.begin(), lst.end(), out);
	cout << endl;

	cout << "Amimals that are in every zoo:" << endl;
	multiset<Animal> in_every = animals.begin()->second;
	for (auto i = next(animals.begin()); i != animals.end(); ++i)
	{
		multiset<Animal> temp;
		set_intersection(in_every.begin(), in_every.end(), i->second.begin(), i->second.end(),inserter(temp,temp.begin()));
		in_every.clear();
		in_every = temp;
	}
	for (auto i = in_every.begin(); i != in_every.end(); ++i)
	{
		cout << *i << endl;
	}

	cout << "Animals that are not in red Book:" << endl;
	list<Animal> unq;
	for (auto i = zooes.begin(); i != zooes.end(); ++i)
	{
		if (i->second.getRed() == false)
		{
			unq.push_back(i->second);
		}
	}
	unq.unique(uniqueCompare);
	ostream_iterator<Animal> out1(cout, "\n");
	copy(unq.begin(), unq.end(), out1);

	cout << "After deleting animals from zooes that are more than count:" << endl;
	int count;
	cout << "input count="; cin >> count;
	map<Animal, int> counts;
	for (auto i = zooes.begin(); i != zooes.end(); ++i)
	{
		counts[i->second] = count_if(zooes.begin(), zooes.end(), [=](pair<const Zoo, Animal>& pr)
		{
			return pr.second.getName() == i->second.getName();
		});
	}
	for (auto i = zooes.begin(); i != zooes.end();)
	{
		if (counts[i->second] >= count)
		{
			i = zooes.erase(i);
		}
		else
		{
			++i;
		}
	}
	for (auto i = zooes.begin(); i != zooes.end(); ++i)
	{
		cout << i->first << " " << i->second << endl;
	}
	system("pause");
}