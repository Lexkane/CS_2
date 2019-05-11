#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>
#include <vector>
#include <iterator>
using namespace std;

class Mean
{
	int size;
	int sum;
	int pos;
public:
	Mean() :
		sum(0),
		size(0),
		pos(0)
	{
	}

	void operator()(int& elem)
	{
		if (pos == 1 && elem > 0)
		{
			sum += elem;
			++size;
			pos = 0;
		}
		else
		{
			++pos;
		}
	}

	friend ostream& operator<<(ostream& stream, Mean& b)
	{
		stream << (double)b.sum / b.size;
		return stream;
	}
};

class CountPred
{
private:
	int number;
public:
	CountPred(int _number) :
		number(_number)
	{
	}

	bool operator()(int & elem)
	{
		return elem<0 && abs(elem)>number;
	}
};

class MinPred
{
private:
	int separator;
	int pos;
	int minElem;
public:
	MinPred(int _separator) :
		separator(_separator),
		pos(1),
		minElem(INT_MAX)
	{
	}

	void operator()(int & elem)
	{
		if (pos%separator == 0)
		{
			pos = 1;
			if (elem < minElem)
			{
				minElem = elem;
			}
		}
		else
		{
			++pos;
		}
	}

	friend ostream& operator<<(ostream& stream, MinPred& el)
	{
		stream << el.minElem;
		return stream;
	}
};

class Deleter
{
private:
	int num;
public:
	Deleter(int _num) :
		num(_num)
	{
	}

	bool operator()(int& elem)
	{
		return elem > (num*num);
	}
};

class Generator
{
private:
	double x;
	int n;
	double prev;
public:
	Generator(const double _x) :
		x(_x),
		n(0),
		prev(1)
	{
	}

	double operator()()
	{
		double result = prev;
		prev *= (double)-(x*x) / ((2 * n + 1)*(2 * n + 2));
		++n;
		return result;
	}
};


class Sumator
{
private:
	double sum;
public:
	Sumator() :
		sum(0)
	{
	}
	void operator()(double& elem)
	{
		sum += elem;
	}

	friend ostream& operator<<(ostream& stream, Sumator& el)
	{
		stream << el.sum;
		return stream;
	}
};

void main()
{
	list<int> lst;
	ifstream in("input.txt");
	istream_iterator<int> beg(in), end;
	lst.assign(beg, end);
	ostream_iterator<int> out(cout, " ");

	cout << "input data------" << endl;
	copy(lst.begin(), lst.end(), out);
	cout << endl;

	cout << "1)ar mean=" << for_each(lst.begin(), lst.end(), Mean()) << endl;

	cout << "input number="; int number; cin >> number;
	cout << "2)count=" << count_if(lst.begin(), lst.end(), CountPred(number)) << endl;

	cout << "input position separator="; int separator; cin >> separator;
	cout << "3)min elem=" << for_each(lst.begin(), lst.end(), MinPred(separator)) << endl;

	cout << "input number="; int num; cin >> num;
	cout << "4)after removing-----" << endl;
	list<int>::iterator remove_pos = remove_if(lst.begin(), lst.end(), Deleter(num));
	lst.erase(remove_pos, lst.end());
	copy(lst.begin(), lst.end(), out);
	cout << endl;

	cout << "5) cosx------------------" << endl;
	cout << "input n="; int n; cin >> n;
	cout << "input x="; double x; cin >> x;
	list<double> result(n);
	ostream_iterator<double> res_out(cout, " ");
	generate_n(result.begin(), n, Generator(x));
	copy(result.begin(), result.end(), res_out);
	cout << endl;
	cout << "sum=" << for_each(result.begin(), result.end(), Sumator()) << endl;
	cout << "cox(x)=" << cos(x) << endl;
	cout << endl;

	system("pause");
}