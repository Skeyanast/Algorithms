#include <iostream>
#include <string>
#include <ctime>

using namespace std;

int AS = 7;

int* get_neight(int** G, int point)
{
	int* arr = new int[AS];
	for (int i = 0; i < AS; i++)
		arr[i] = G[i][point];
	arr[point] = 0;
	return arr;
}

int find_dist(int** G, int start, int end, int dist, bool* used)
{
	bool F = false;
	for (int i = 0; i < AS; i++)
	{
		F = F || (used[i]);
	}
	if (!F) return -9999;

	//cout << "*/";
	for (int i = 0; i < AS; i++)
	{
		//cout << used[i] << " ";
	}
	//cout << " " << start << " " << end << " " << dist << " | ";
	int* arr = get_neight(G, start);
	for (int i = 0; i < AS; i++)
	{
		if (i == end && arr[i]) return dist + 1;
	}
	//cout << "\n";

	int min = 9999, b;
	for (int i = 0; i < AS; i++)
	{
		if ((used[i]) && arr[i])
		{
			bool* du = new bool[AS];
			for (int k = 0; k < AS; k++)
			{
				if (k == i) du[k] = false;
				else du[k] = used[k];
			}
			b = find_dist(G, i, end, dist + 1, du);
			if (b < min)
			{
				min = b;
			}
		}
	}
	return min;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	srand(time(NULL));

	int** A = new int* [AS];
	for (int i = 0; i < AS; i++)
		A[i] = new int[AS];

	float** B = new float* [AS];
	for (int i = 0; i < AS; i++)
		B[i] = new float[AS];

	for (int i = 0; i < AS; i++)
		for (int j = 0; j < AS; j++)
		{
			if (i != j)
			{
				if (rand() % 2 == 0) A[i][j] = 1;
				else A[i][j] = 0;
			}
			else
			{
				A[i][j] = 0;
			}
		}

	string tre[16] = { "A", "B", "C",  "D", "E", "F",  "G" };
	cout << "  A B C D E F G\n";
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

	for (int i = 0; i < AS; i++)
	{
		for (int j = 0; j < AS; j++)
		{
			bool* du = new bool[AS];
			for (int k = 0; k < AS; k++)
			{
				if (k == j) du[k] = false;
				else du[k] = true;
			}
			B[i][j] = find_dist(A, i, j, 0, du);
		}
	}

	cout << "  A B C D E F G\n";
	for (int i = 0; i < AS; i++)
	{
		cout << tre[i] << " ";
		for (int j = 0; j < AS; j++)
		{
			if (B[j][i] == -9999 || B[j][i] == 9999) cout << "0 ";
			else cout << B[j][i] << " ";
		}
		cout << endl;
	}

	return 0;
}