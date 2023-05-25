#include <iostream>
#include <string>

using namespace std;

class hesh {
private:
	int size = 1;
	string* arr = new string[size];
	string* dat = new string[size];

	int hesh_funcion(string S)
	{
		int tr, summ = 0;
		for (int i = 0; i < S.size(); i++)
		{
			tr = (int)(S[i]);
			summ += tr;
		}
		return summ % size;
	}

public:
	hesh(int HS)
	{
		size = HS;
		arr = new string[HS];
		dat = new string[HS];
		for (int i = 0; i < HS; i++)
		{
			arr[i] = "";
			dat[i] = "";
		}
	}

	void insert(string key, string data)
	{
		int pos = hesh_funcion(key);
		//cout << pos << "*";
		while (true)
		{
			if (arr[pos] == "")
			{
				arr[pos] = data;
				dat[pos] = key;
				break;
			}
			else
			{
				pos = (pos + 1) % size;
			}
		}
	}

	void remove(string key)
	{
		int pos = hesh_funcion(key);
		while (true)
		{
			if (dat[pos] == key)
			{
				arr[pos] = "";
				dat[pos] = "";
				break;
			}
			else pos = (pos + 1) % size;
		}
	}

	string get(string key)
	{
		int pos = hesh_funcion(key);
		while (true)
		{
			if (dat[pos] == key) return arr[pos];
			else pos = (pos + 1) % size;
		}
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");

	string S, key;
	cin >> S >> key;

	cout << endl;

	hesh T(S.size());
	for (int i = 0; i < S.size(); i++)
	{
		T.insert(key.substr(i, 1), S.substr(i, 1));
	}

	for (int i = 0; i < S.size(); i++)
	{
		cout << key.substr(i, 1) << " -> " << T.get(key.substr(i, 1)) << "\n";
	}

	cout << endl;

	hesh tab(5);
	tab.insert("aaa", "1234567");
	tab.insert("who is", "i am");
	tab.insert("lol", "yep");
	tab.insert("aaslkfj", "stop feeding");
	tab.insert("666", "okay");

	cout << tab.get("aaa") << endl;
	cout << tab.get("who is") << endl;
	cout << tab.get("lol") << endl;
	cout << tab.get("aaslkfj") << endl;
	cout << tab.get("666") << endl;

	return 0;
}