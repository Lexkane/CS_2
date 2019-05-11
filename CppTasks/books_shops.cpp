#include<iostream>
#include<fstream>
#include<map>
#include<set>
#include<list>
#include<string>
#include<iterator>
#include<algorithm>
using namespace std;

class Book
{
private:
	string name;
	string category;
	int price;
	int count;
public:
	Book(string _n, string _ca, int _p, int _co) :
		name(_n),
		category(_ca),
		price(_p),
		count(_co)
	{
	}

	Book() 
	{
	}
	string getName()const
	{
		return name;
	}
	string getCategory()const
	{
		return category;
	}
	int getPrice()const
	{
		return price;
	}
	int getCount()const
	{
		return count;
	}

	friend istream& operator>>(istream& is, Book& b)
	{
		is >> b.name >> b.category >> b.price >> b.count;
		return is;
	}
	friend ostream& operator<<(ostream& os, const Book& b)
	{
		os << b.name << " " << b.category << " " << b.price << " " << b.count << endl;
		return os;
	}

	friend bool operator<(const Book& a, const Book b)
	{
		return a.getName() < b.getName();
	}
};

bool compare(const Book& a, const Book& b)
{
	return a.getCount() < b.getCount();
}

void main()
{
	multimap<string, Book> books;
	ifstream in("book.txt");
	string tmp1;
	Book tmp2;
	while (!in.eof())
	{
		in >> tmp1;
		in >> tmp2;
		books.insert(make_pair(tmp1, tmp2));
	}
	cout << "Input data:" << endl;
	for (auto i = books.begin(); i != books.end(); ++i)
	{
		cout << i->first << " " << i->second;
	}
	cout << endl;

	cout << "Shop and their books sorted by count:" << endl;;
	map<string, multiset<Book>> sort;
	for (auto i = books.begin(); i != books.end(); ++i)
	{
		multiset<Book> st;
		if (!sort[i->first].empty())
		{
			st = sort[i->first];
		}
		st.insert(i->second);
		sort[i->first] = st;
	}

	map<string, list<Book>> sort2;
	for (auto i = books.begin(); i != books.end(); ++i)
	{
		list<Book> st;
		if (!sort2[i->first].empty())
		{
			st = sort2[i->first];
		}
		st.push_back(i->second);
		st.sort(compare);
		sort2[i->first] = st;
	}

	for (auto i = sort2.begin(); i != sort2.end(); ++i)
	{
		cout << i->first << ": ";
		for (auto j = i->second.begin(); j != i->second.end(); ++j)
		{
			cout << *j << " ";
		}
		cout << endl;
	}

	cout << "Sum price for each magazine: " << endl;
	map<string, int> sumprice;
	for (auto i = books.begin(); i != books.end(); ++i)
	{
		sumprice[i->first] = 0;
	}
	for (auto i = books.begin(); i != books.end(); ++i)
	{
		sumprice[i->first] += i->second.getPrice();
	}
	for (auto i = sumprice.begin(); i != sumprice.end(); ++i)
	{
		cout << i->first << " " << i->second << endl;
	}

	cout << "Shops with inputed book:" << endl;
	list<string> lst;
	string name;
	cout << "input name="; 
	cin >> name;
	for (auto i = books.begin(); i != books.end(); ++i)
	{
		if (name == i->second.getName())
		{
			lst.push_back(i->first);
		}
	}
	lst.unique();
	lst.sort();
	copy(lst.begin(), lst.end(), ostream_iterator<string>(cout, " "));

	cout <<endl<< "Books that are in every shop:" << endl;
	multiset<Book> in_every = sort.begin()->second;
	for (auto i = next(sort.begin()); i != sort.end(); ++i)
	{
		multiset<Book> temp;
		set_intersection(in_every.begin(), in_every.end(), i->second.begin(), i->second.end(), inserter(temp, temp.begin()));
		in_every.clear();
		in_every = temp;
	}
	set<Book> every(in_every.begin(), in_every.end());
	for (auto i = every.begin(); i != every.end(); ++i)
	{
		cout << *i;
	}

	cout << endl << "Tekh books sorted by name:" << endl;
	set<Book> tehnLit;
	for (auto i = books.begin(); i != books.end(); ++i)
	{
		if (i->second.getCategory() == "tekh")
		{
			tehnLit.insert(i->second);
		}
	}
	for (auto i = tehnLit.begin(); i != tehnLit.end(); ++i)
	{
		cout << *i;
	}
	system("pause");
}