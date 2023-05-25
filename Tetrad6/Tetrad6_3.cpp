#include <iostream>
#include <string>
#include <ctime>

using namespace std;

int AS = 7;
string way;

string normalaze(string S)
{
	string C = "";
	string bl;
	for (int i = 0; i < S.size(); i++)
	{
		if (S[i] == '0') C += "A";
		if (S[i] == '1') C += "B";
		if (S[i] == '2') C += "C";
		if (S[i] == '3') C += "D";
		if (S[i] == '4') C += "E";
		if (S[i] == '5') C += "F";
		if (S[i] == '6') C += "G";
	}
	return C;
}

int find_cicle(float** G)
{
	bool* used = new bool[AS];
	for (int i = 0; i < AS; i++) used[i] = true;
	used[0] = false;
	float dist = 0;
	int curr = 0, start = 0;
	way = " ";

	while (true)
	{
		bool F = false;
		for (int i = 0; i < AS; i++)
		{
			F = F || used[i];
		}
		if (!F)
		{
			cout << normalaze(way + to_string(start)) << "|";
			return dist + G[curr][start];
		}

		float min = 9999;
		int mini = -1;
		for (int i = 0; i < AS; i++)
		{
			if (used[i] && i != curr)
			{
				if (G[i][curr] < min)
				{
					min = G[i][curr];
					mini = i;
				}
			}
		}
		used[mini] = false;
		dist += min;
		curr = mini;
		way += to_string(mini);
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	srand(time(NULL));

	float** A = new float* [AS];
	for (int i = 0; i < AS; i++)
		A[i] = new float[AS];

	for (int i = 0; i < AS; i++)
		for (int j = 0; j < AS; j++)
		{
			if (i != j)
			{
				if (1) A[i][j] = A[j][i] = (rand() % 10 + 1);
				else A[i][j] = 9999;
			}
			else
			{
				A[i][j] = 9999;
			}
		}

	for (int i = 0; i < AS; i++)
	{
		for (int j = 0; j < AS; j++)
		{
			if (A[i][j] == 9999) A[i][j] = -1;
		}
	}

	string tre[16] = { "A", "B", "C",  "D", "E", "F",  "G" };
	cout << "  A  B  C  D  E  F  G" << endl;
	for (int i = 0; i < AS; i++)
	{
		cout << tre[i] << " ";
		for (int j = 0; j < AS; j++)
		{
			if (A[i][j] == 10 || A[i][j] == -1) cout << A[i][j] << " ";
			else cout << A[i][j] << "  ";
		}
		cout << endl;
	}

	cout << find_cicle(A) << " ";

	return 0;
}