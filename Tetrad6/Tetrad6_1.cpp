#include <iostream>
#include <string>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	float** A = new float* [6];
	for (int i = 0; i < 6; i++)
		A[i] = new float[6];

	A[0][0] = A[1][1] = A[2][2] = A[3][3] = A[4][4] = A[5][5] = -1;

	A[1][0] = A[0][1] = 1.97;
	A[2][0] = A[0][2] = 21.6;
	A[3][0] = A[0][3] = 10.7;
	A[4][0] = A[0][4] = 22.3;
	A[5][0] = A[0][5] = 10.4;

	A[2][1] = A[1][2] = 22.3;
	A[3][1] = A[1][3] = 11.4;
	A[4][1] = A[1][4] = 23.0;
	A[5][1] = A[1][5] = 11.1;

	A[3][2] = A[2][3] = 11.5;
	A[4][2] = A[2][4] = 5.2;
	A[5][2] = A[2][5] = 12.0;

	A[4][3] = A[3][4] = 13.4;
	A[5][3] = A[3][5] = 0.68;

	A[5][4] = A[4][5] = 13.8;

	float** ways = new float* [5];
	for (int i = 0; i < 5; i++)
		ways[i] = new float[2];

	int point1 = rand() % 6, point2;
	float min = 1024;
	for (int i = 0; i < 6; i++)
	{
		if (A[point1][i] < min && i != point1)
		{
			min = A[point1][i];
			point2 = i;
		}
	}

	ways[4][0] = point1;
	ways[4][1] = point2;

	int* used = new int[6];
	used[0] = used[1] = used[2] = used[3] = used[4] = used[5] = false;
	used[point1] = used[point2] = true;
	float summ = A[point1][point2];
	int curr, c1, c2;

	for (int k = 0; k < 6; k++)
	{
		min = 1024;
		bool F = false;
		for (int l = 0; l < 6; l++)
		{
			F = F || not(used[l]);
		}
		if (not(F)) break;
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				if (i != j && ((used[i] && not(used[j])) || (used[j] && not(used[i]))))
				{
					if (A[i][j] < min)
					{
						c1 = i; c2 = j;
						min = A[i][j];
					}
				}
			}
		}
		ways[k][0] = c1;
		ways[k][1] = c2;

		summ += min;
		used[c1] = true;
		used[c2] = true;
	}

	for (int i = 0; i < 5; i++)
	{
		cout << ways[i][0] << " <-> " << ways[i][1] << endl;
	}
	cout << endl;
	cout << summ;

	return 0;
}