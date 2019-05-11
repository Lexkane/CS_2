#include<iostream>
#include<fstream>
#include<algorithm>
#include<set>
#include<map>
#include<string>
#include<iterator>
#include<list>
using namespace std;

class VNZ
{
private:
	string name;
	string tgn;
	int count;
	string spec;
public:
	VNZ(string _name, string _tgn, int _count, string _spec) :
		name(_name),
		tgn(_tgn),
		count(_count),
		spec(_spec)
	{
	}

	VNZ()
	{
	}

	string getName()const
	{
		return name;
	}
	string getTGN()const
	{
		return tgn;
	}
	int getCount()const
	{
		return count;
	}
	string getSpec()const
	{
		return spec;
	}

	friend ostream& operator<<(ostream& os,const VNZ& a)
	{
		os << a.name << " " << a.tgn << " " << a.count << " " << a.spec << endl;
		return os;
	}
	friend istream& operator>>(istream& is, VNZ& a)
	{
		is >> a.name >> a.tgn >> a.count >> a.spec;
		return is;
	}

	friend bool operator<(const VNZ& a, const VNZ& b)
	{
		return a.getName() < b.getName();
	}
};


void main()
{
	multimap<string, VNZ> univer;
	ostream_iterator<string> out(cout, " ");
	ifstream in("input.txt");
	string temp;
	VNZ tmp;
	while (!in.eof())
	{
		in >> temp;
		in >> tmp;
		univer.insert(make_pair(temp, tmp));
	}
	cout << "Input data:" << endl;
	for (multimap<string, VNZ>::iterator i = univer.begin(); i != univer.end(); ++i)
	{
		cout << i->first << " " << i->second;
	}
	cout << endl;

	cout << "Facultes for every univer:" << endl;
	map<string, multiset<VNZ>> fac;
	for (multimap<string, VNZ>::iterator i = univer.begin(); i != univer.end(); ++i)
	{
		multiset<VNZ> temp;
		if (!fac[i->first].empty())
		{
			temp = fac[i->first];
		}
		temp.insert(i->second);
		fac[i->first] = temp;
	}

	for (auto i = fac.begin(); i != fac.end(); ++i)
	{
		cout << i->first << ": " << endl;
		for (auto j = i->second.begin(); j != i->second.end(); ++j)
		{
			cout << *j << endl;
		}
		cout << endl;
	}

	list<string> ls;//task 1
	string spec;
	cout << "input spec:" << endl;
	cin >> spec;
	for (auto i = univer.begin(); i != univer.end(); ++i)
	{
		if (spec == i->second.getSpec())
		{
			ls.push_back(i->first);
		}
	}
	cout << "\nUniversities with such spec:" << endl;
	copy(ls.begin(), ls.end(), out);
	cout << "\nTekh TGN:" << endl;
	multimap<string, VNZ> lst;//task 2
	string tempo = "tekh";
	for (auto i = univer.begin(); i != univer.end(); ++i)
	{
		if (tempo == i->second.getTGN())
		{
			cout << i->second;
		}
	}

	cout << "\nCount by universities:" << endl;
	map<string, int> res;//task 3
	for (auto i = univer.begin(); i != univer.end(); ++i)
	{
		res[i->first] = 0;
	}
	for (auto i = univer.begin(); i != univer.end(); ++i)
	{
		res[i->first] += i->second.getCount();
	}
	for (auto i = res.begin(); i != res.end(); ++i)
	{
		cout << i->first << " " << i->second << endl;
	}

	cout << "\nSame faculty for all universities:" << endl;
	multiset<VNZ> in_every = fac.begin()->second;
	for (auto i = next(fac.begin()); i != fac.end(); ++i)//task 4
	{
		multiset<VNZ> temp;
		set_intersection(in_every.begin(), in_every.end(), i->second.begin(), i->second.end(), inserter(temp, temp.begin()));
		in_every.clear();
		in_every = temp;
	}
	for (auto i = in_every.begin(); i != in_every.end(); ++i)
	{
		cout << *i << endl;
	}

	cout << "Tehks and gums sorted by name:" << endl;
	set<VNZ> tekhos;
	set<VNZ> gums;
	for (auto i = univer.begin(); i != univer.end(); ++i)
	{
		if (i->second.getTGN() == "tekh")
		{
			tekhos.insert(i->second);
		}
		else if (i->second.getTGN() == "gum")
		{
			gums.insert(i->second);
		}
	}
	cout << "TEHS::::::" << endl;
	for (auto i = tekhos.begin(); i != tekhos.end(); ++i)
	{
		cout << *i << endl;
	}
	cout << endl;
	cout << "GUMS::::::" << endl;
	for (auto i = gums.begin(); i != gums.end(); ++i)
	{
		cout << *i << endl;
	}
	system("pause");
}