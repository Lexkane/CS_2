#include<iostream>
#include<vector>
#include<iterator>
#include<algorithm>
#include<fstream>
using namespace std;

class Remover
{
private:
	int pos;
	int count;
public:
	Remover(int _pos) :
		pos(_pos),
		count(1)
	{}

	bool operator ()(int& elem)
	{
		if (count%pos == 0)
		{
			count = 1;
			return true;
		}
		else
		{
			count++;
			return false;
		}
	}
};

void main()
{
	vector<int> vec;
	ifstream ifs("Text.txt");
	istream_iterator<int> iter1(ifs);
	istream_iterator<int> iter2;
	vec.assign(iter1, iter2);
	ostream_iterator<int> out(cout, " ");
	copy(vec.begin(), vec.end(), out);
	int pos;
	cin >> pos;
	remove_if(vec.begin(), vec.end(), Remover(pos));
	copy(vec.begin(), vec.end(), out);
	system("pause");
}