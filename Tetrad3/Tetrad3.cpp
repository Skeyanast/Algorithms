#include <iostream> 
#include <array> 
#include <cmath> 

using namespace std;

int* creat_arr(int n) {
	int* a = new int[n];
	for (int i = 0; i < n; i++)
		cin >> a[i];
	return a;
}

int deep(int* a) {
	int size = 1;
	int degree = 0;
	while (size < sizeof(a)) {
		size *= 2;
		degree++;
	}
	return degree;
}

void print(int* a, int n) {
	for (int i = 0; i < n; i++) cout << a[i] << " ";
	cout << endl;
}

void heapify(int* a, int i, int n) {
	int max = 1;
	while (true) {
		int child = 2 * i + 1;
		if (child < n && a[child] > a[max]) max = child;
		child++;
		if (child < n && a[child] > a[max]) max = child;
		if (max == i) break;
		else {
			swap(a[max], a[i]);
			i = max;
		}
	}
}

void print_tree(int* a) {
	int width = pow(2, deep(a) - 1);
	cout << a[0] << "\n";
	int index = 1;
	for (int i = 1; i < deep(a); i++) {
		int kol = 1;
		for (kol; kol <= pow(2, i); kol++) {
			cout << a[index] << " ";
			index += 1;
			if (a[index] == a[-1]) break;
		}
		cout << "\n";
	}
}

int main() {
	setlocale(LC_ALL, "Russian");

	int n;
	cout << "Размер массива: ";
	cin >> n;

	int* a = creat_arr(n);
	cout << "Исходный массив\n";
	print(a, n);
	for (int i = n / 2; i >= 0; i--) {
		heapify(a, i, n);
	}
	cout << "Глубина дерева: " << deep(a) << "\n";
	cout << "Плоская двоичная куча\n";
	print(a, n);
	cout << "Двоичная куча\n";
	print_tree(a);
	return 0;
}