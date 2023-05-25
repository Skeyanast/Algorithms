#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	int input[7] = { 86, 90, 27, 29, 38, 30, 40 };

	int hash[7] = { -1,-1,-1,-1,-1,-1,-1 };

	int curr;
	for (int i = 0; i < 7; i++)
	{
		curr = input[i] % 7;
		while (true)
		{
			if (hash[curr] == -1)
			{
				hash[curr] = input[i];
				break;
			}
			else
			{
				curr = (curr + 1) % 7;
			}
		}
	}

	for (int i = 0; i < 7; i++)
	{
		cout << hash[i] << " ";
	}

	return 0;
}