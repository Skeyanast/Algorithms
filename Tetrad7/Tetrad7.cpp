#include <iostream>
#include <string>

using namespace std;

int AS = 5;

int* Deixstra(int** G, int start)
{
	int* mindist = new int[AS];
	for (int i = 0; i < AS; i++) mindist[i] = 999999;
	mindist[start] = 0;

	while (true)
	{
		bool moved = false;
		for (int i = 0; i < AS; i++)
			for (int j = 0; j < AS; j++)
			{
				if (G[i][j] != 0)
				{
					if (mindist[j] + G[i][j] < mindist[i])
					{
						mindist[i] = mindist[j] + G[i][j];
						moved = true;
					}
				}
			}

		if (!moved) break;
	}

	return mindist;
}

int* Deixstra2(int** G, int start)
{
	int* mindist = new int[AS];
	for (int i = 0; i < AS; i++) mindist[i] = 999999;
	mindist[start] = 0;

	bool* used = new bool[AS];
	for (int i = 0; i < AS; i++) used[i] = true;

	int curr;
	while (true)
	{
		int min = 999999;
		for (int k = 0; k < AS; k++)
		{
			if (used[k])
			{
				if (mindist[k] < min)
				{
					curr = k;
					min = mindist[k];
				}
			}
		}

		bool moved = false;
		for (int k = 0; k < AS; k++)
		{
			if (G[curr][k] != 0 && used[k])
			{
				if (G[curr][k] + mindist[curr] < mindist[k])
				{
					mindist[k] = G[curr][k] + mindist[curr];
					moved = true;
				}
			}
		}
		if (!moved) break;
		used[curr] = false;

		bool F = false;
		for (int k = 0; k < AS; k++)
		{
			F = F || used[k];
		}
		if (!F) break;
	}

	return mindist;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	int** A = new int* [AS];
	for (int i = 0; i < AS; i++)
		A[i] = new int[AS];

	for (int i = 0; i < AS; i++)
		for (int j = 0; j < AS; j++)
		{
			if (i != j)
			{
				if (rand() % 2 == 0) A[i][j] = A[j][i] = rand() % 10;
				else A[i][j] = A[j][i] = 0;
			}
			else
			{
				A[i][j] = A[j][i] = 0;
			}
		}

	string tre[16] = { "A", "B", "C",  "D", "E", "F",  "G" , "H", "I", "J" };
	cout << "  A B C D E F G H I J" << endl;
	for (int i = 0; i < AS; i++)
	{
		cout << tre[i] << " ";
		for (int j = 0; j < AS; j++)
		{
			cout << A[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;

	int start = 0;

	int* mindist = Deixstra2(A, start);

	cout << endl;

	for (int i = 0; i < AS; i++)
	{
		if (mindist[i] == 999999)
		{
			cout << tre[i] << " " << "inf" << endl;
		}
		else
		{
			cout << tre[i] << " " << mindist[i] << endl;
		}
	}

	return 0;
}