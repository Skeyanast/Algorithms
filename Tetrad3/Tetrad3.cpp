#include <iostream>
#include <ctime>
#include <stack>

using namespace std;

class kucha
{
private:
	int key = -1;
	kucha* R = nullptr;
	kucha* L = nullptr;

	void setkey(string way, int data)
	{
		if (way.size() == 1)
		{
			if (way == "L") L->key = data;
			else R->key = data;
		}
		else
		{
			if (way[0] == 'L') return setkey(L, way.substr(1, way.size() - 1), data);
			else return setkey(R, way.substr(1, way.size() - 1), data);
		}
	}

	void setkey(kucha* curr, string way, int data)
	{
		if (way.size() == 1)
		{
			if (way == "L") curr->L->key = data;
			else curr->R->key = data;
		}
		else
			if (way[0] == 'L')
			{
				return setkey(curr->L, way.substr(1, way.size() - 1), data);
			}
			else
			{
				return setkey(curr->R, way.substr(1, way.size() - 1), data);
			}
	}

	kucha* get_node(string way)
	{
		if (way.size() == 1)
		{
			if (way == "L") return L;
			else return R;
		}
		else
		{
			if (way[0] == 'L') return get_node(L, way.substr(1, way.size() - 1));
			else return get_node(R, way.substr(1, way.size() - 1));
		}
	}

	kucha* get_node(kucha* curr, string way)
	{
		if (way.size() == 1)
		{
			if (way == "L") return curr->L;
			else return curr->R;
		}
		if (way[0] == 'L')
		{
			return get_node(curr->L, way.substr(1, way.size() - 1));
		}
		else
		{
			return get_node(curr->R, way.substr(1, way.size() - 1));
		}
	}

	bool is_node_exs(string way)
	{
		if (way.size() == 1)
		{
			if (way == "L") return L != nullptr;
			else return R != nullptr;
		}
		else
		{
			if (way[0] == 'L') return is_node_exs(L, way.substr(1, way.size() - 1));
			else return is_node_exs(R, way.substr(1, way.size() - 1));
		}
	}

	bool is_node_exs(kucha* curr, string way)
	{
		if (way.size() == 1)
		{
			if (way == "L") return curr->L != nullptr;
			else return curr->R != nullptr;
		}
		if (way[0] == 'L')
		{
			if (curr->L != nullptr) return get_node(curr->L, way.substr(1, way.size() - 1));
			else return false;
		}
		else
		{
			if (curr->R != nullptr) return get_node(curr->R, way.substr(1, way.size() - 1));
			else return false;
		}
	}

	void upbuild_node(string way)
	{
		if (way.size() == 1)
		{
			if (way == "L") L = new kucha;
			else R = new kucha;
		}
		else
			if (way[0] == 'L')
			{
				if (L != nullptr) upbuild_node(L, way.substr(1, way.size() - 1));
				else { L = new kucha; upbuild_node(L, way.substr(1, way.size() - 1)); }
			}
			else
			{
				if (R != nullptr) upbuild_node(R, way.substr(1, way.size() - 1));
				else { R = new kucha; upbuild_node(R, way.substr(1, way.size() - 1)); }
			}
	}

	void upbuild_node(kucha* curr, string way)
	{
		if (way.size() == 1)
		{
			if (way == "L") curr->L = new kucha;
			else curr->R = new kucha;
		}
		else
			if (way[0] == 'L')
			{
				if (curr->L != nullptr) upbuild_node(curr->L, way.substr(1, way.size() - 1));
				else { curr->L = new kucha; upbuild_node(curr->L, way.substr(1, way.size() - 1)); }
			}
			else
			{
				if (curr->R != nullptr) upbuild_node(curr->R, way.substr(1, way.size() - 1));
				else { curr->R = new kucha; upbuild_node(curr->R, way.substr(1, way.size() - 1)); }
			}
	}

	string bulid_way(int level, int pos)
	{
		if (level == 0) return "";

		//cout << pos << " " << pow(2, level - 1) << "\n";
		if (pos >= pow(2, level - 1)) return bulid_way(level - 1, pos - pow(2, level - 1)) + "R";
		else return bulid_way(level - 1, pos) + "L";

	}

	string* build_all_ways(int size)
	{
		string* ways = new string[size];
		int level;
		for (int i = 1; i < size + 1; i++)
		{
			level = 0;
			while (true)
			{
				if (pow(2, level) > i) break;
				else level += 1;
			}
			ways[i - 1] = bulid_way(level - 1, i - pow(2, level - 1));
		}

		return ways;
	}

	bool balance_node_min(kucha* curr)
	{
		bool has_moved = false;
		if (curr->L != nullptr)
		{
			if (curr->L->key < curr->key)
			{
				int b = curr->L->key;
				curr->L->key = curr->key;
				curr->key = b;
				has_moved = true;
			}
		}
		if (curr->R != nullptr)
		{
			if (curr->R->key < curr->key)
			{
				int b = curr->R->key;
				curr->R->key = curr->key;
				curr->key = b;
				has_moved = true;
			}
		}
		return has_moved;
	}

	bool balance_node_max(kucha* curr)
	{
		bool has_moved = false;
		if (curr->L != nullptr)
		{
			if (curr->L->key > curr->key)
			{
				int b = curr->L->key;
				curr->L->key = curr->key;
				curr->key = b;
				has_moved = true;
			}
		}
		if (curr->R != nullptr)
		{
			if (curr->R->key > curr->key)
			{
				int b = curr->R->key;
				curr->R->key = curr->key;
				curr->key = b;
				has_moved = true;
			}
		}
		return has_moved;
	}

	int* sized_arr(int* old_arr, int old_size, int new_size)
	{
		int* new_arr = new int[new_size];
		for (int i = 0; i < new_size; i++)
		{
			if (i >= old_size) new_arr[i] = -1;
			else new_arr[i] = old_arr[i];
		}
		return new_arr;
	}

public:
	void balance_all_min(int size)
	{
		string* ways = new string[size];
		ways = build_all_ways(size);
		bool F = true;

		while (F)
		{
			//cout << "*";
			F = false;
			for (int i = 0; i < size - 1; i++)
			{
				F = F || balance_node_min(get_node(ways[size - i - 1]));
			}

			if (L != nullptr)
			{
				if (L->key < key)
				{
					int b = L->key;
					L->key = key;
					key = b;
					F = true;
				}
			}
			if (R != nullptr)
			{
				if (R->key < key)
				{
					int b = R->key;
					R->key = key;
					key = b;
					F = true;
				}
			}
		}
	}

	void balance_all_max(int size)
	{
		string* ways = new string[size];
		ways = build_all_ways(size);
		bool F = true;

		while (F)
		{
			//cout << "*";
			F = false;
			for (int i = 0; i < size - 1; i++)
			{
				F = F || balance_node_max(get_node(ways[size - i - 1]));
			}

			if (L != nullptr)
			{
				if (L->key > key)
				{
					int b = L->key;
					L->key = key;
					key = b;
					F = true;
				}
			}
			if (R != nullptr)
			{
				if (R->key > key)
				{
					int b = R->key;
					R->key = key;
					key = b;
					F = true;
				}
			}
		}
	}

	kucha()
	{

	}

	kucha(int* A, int size)
	{
		string* ways = new string[size];
		ways = build_all_ways(size);

		key = A[0];

		for (int i = 1; i < size; i++)
		{
			//cout << ways[i] << " " << A[i] << "|\n";
			upbuild_node(ways[i]);
			setkey(ways[i], A[i]);
		}
	}

	void build(int* A, int size)
	{
		key = -1;
		L = nullptr;
		R = nullptr;

		string* ways = new string[size];
		ways = build_all_ways(size);

		key = A[0];

		for (int i = 1; i < size; i++)
		{
			//cout << ways[i] << " " << A[i] << "|\n";
			upbuild_node(ways[i]);
			setkey(ways[i], A[i]);
		}
	}

	void print(int size)
	{
		string* ways = new string[size];
		ways = build_all_ways(size);

		cout << key << "|\n";
		for (int i = 1; i < size; i++)
		{
			cout << ways[i] << " " << get_node(ways[i])->key << "|\n";
		}
	}

	int find_max(int size)
	{
		string* ways = new string[size];
		ways = build_all_ways(size);

		int max = key;
		int t;

		for (int i = 1; i < size; i++)
		{
			//cout << ways[i] << " " << A[i] << "|\n";
			t = get_node(ways[i])->key;
			if (t > max) max = t;
		}
		return max;
	}

	int find_min(int size)
	{
		string* ways = new string[size];
		ways = build_all_ways(size);

		int min = key;
		int t;

		for (int i = 1; i < size; i++)
		{
			//cout << ways[i] << " " << A[i] << "|\n";
			t = get_node(ways[i])->key;
			if (t < min) min = t;
		}
		return min;
	}

	int* get_arr(int size)
	{
		string* ways = new string[size];
		ways = build_all_ways(size);

		int* arr = new int[size];
		arr[0] = key;

		for (int i = 1; i < size; i++)
		{
			//cout << ways[i] << " " << A[i] << "|\n";
			arr[i] = get_node(ways[i])->key;
		}
		return arr;
	}

	int* unite_arr(int* A, int* B, int size_A, int size_B)
	{
		int* new_arr = new int[size_A + size_B];
		for (int i = 0; i < size_A; i++)
		{
			new_arr[i] = A[i];
		}
		for (int i = 0; i < size_B; i++)
		{
			new_arr[i + size_A] = B[i];
		}
		return new_arr;
	}

	void insert(int size, int data)
	{
		int* arr = get_arr(size);
		arr = sized_arr(arr, size, size + 1);
		arr[size] = data;

		build(arr, size + 1);
	}

	void remove(int size, int data)
	{
		int* arr = get_arr(size);
		for (int i = 0; i < size; i++)
		{
			if (arr[i] == data)
			{
				arr[i] = arr[size - 1];
				arr[size - 1] = -1;
				break;
			}
		}
		arr = sized_arr(arr, size, size - 1);

		build(arr, size - 1);
	}

	void unite_kucha(int* A, int* B, int size_A, int size_B)
	{
		int* arr = unite_arr(A, B, size_A, size_B);
		build(arr, size_A + size_B);
	}

	int solve_wipes(int* A, int size)
	{
		int summ = 0;
		int f1, f2;
		int* fnline = new int[size];
		build(A, size);
		balance_all_min(size);
		while (true)
		{
			if (L == nullptr && R != nullptr && R->L == nullptr && R->R == nullptr)
			{
				return summ + key + R->key;
			}
			if (R == nullptr && L != nullptr && L->L == nullptr && L->R == nullptr)
			{
				return summ + key + L->key;
			}

			f1 = find_min(size);
			remove(size, f1);
			f2 = find_min(size - 1);
			remove(size - 1, f2);

			summ += f1 + f2;

			insert(size - 2, f1 + f2);
			size -= 1;
		}
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");

	srand(time(NULL));

	int size = 5;
	int* P = new int[size];
	for (int i = 0; i < size; i++)
	{
		P[i] = rand() % 99 + 1;
	}
	kucha T(P, size);
	cout << endl << "Неотсортированная куча" << endl;
	T.print(size);
	T.balance_all_min(size);
	cout << endl << "Min-куча" << endl;
	T.print(size);
	T.balance_all_max(size);
	cout << endl << "Max-куча" << endl;
	T.print(size);
	cout << endl << "Минимум - " << T.find_min(size);
	cout << endl << "Максимум - " << T.find_max(size);
	cout << endl << endl << "Удаление" << endl;
	T.remove(size, T.get_arr(size)[rand() % size]);
	T.balance_all_max(size - 1);
	T.print(size - 1);
	T.insert(size - 1, rand() % 99 + 1);
	T.balance_all_max(size);
	cout << endl << "Вставка" << endl;
	T.print(size);

	int sizeA = 6;
	int* PA = new int[sizeA];
	for (int i = 0; i < sizeA; i++)
	{
		PA[i] = rand() % 99 + 1;
	}
	int sizeB = 4;
	int* PB = new int[sizeB];
	for (int i = 0; i < sizeB; i++)
	{
		PB[i] = rand() % 99 + 1;
	}

	cout << endl << "Куча 1" << endl;
	T.build(PA, sizeA);
	T.balance_all_max(sizeA);
	T.print(sizeA);

	cout << endl << "Куча 2" << endl;
	T.build(PB, sizeB);
	T.balance_all_max(sizeB);
	T.print(sizeB);

	cout << endl << "Слияние двух куч" << endl;
	T.unite_kucha(PA, PB, sizeA, sizeB);
	T.balance_all_max(sizeA + sizeB);
	T.print(sizeA + sizeB);

	int sizeC = 4;
	int* PC = new int[sizeC];
	for (int i = 0; i < sizeC; i++)
	{
		PC[i] = rand() % 99 + 1;
	}
	PC[0] = 5;
	PC[1] = 4;
	PC[2] = 2;
	PC[3] = 8;
	cout << endl << "Задача о канатах" << endl;
	T.build(PC, sizeC);
	T.balance_all_max(sizeC);
	T.print(sizeC);

	cout << endl << "Ответ -> " << T.solve_wipes(PC, sizeC);

	return 0;
}