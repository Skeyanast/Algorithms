#include <iostream>

using namespace std;

struct Node {
	// Структура узла дерева
	int value;
	int count;
	Node* left;
	Node* right;
};

struct Node* addNode(int input, Node* top) {
	// Пользовательская функция
	// Вход: значение узла, название дерева
	// Выход: создается структура нового узла
	if (top == nullptr) {
		top = new Node;
		top->value = input;
		top->count = 1;
		top->left = nullptr;
		top->right = nullptr;
	}
	else if (input == top->value) {
		top->count += 1;
	}
	else if (input < top->value) {
		top->left = addNode(input, top->left);
	}
	else {
		top->right = addNode(input, top->right);
	}
	return top;
}

void printTree(char method, Node* top) {
	// Пользовательская функция
	// Вход: символ выбора метода печати, название дерева
	// Выход: выбранным способом печатается дерево
	switch (method) {
	case 'p':
		if (top != nullptr) {
			cout << top->value << " ";
			printTree(method, top->left);
			printTree(method, top->right);
		}
		break;
	case 'o':
		if (top != nullptr) {
			printTree(method, top->left);
			printTree(method, top->right);
			cout << top->value << " ";
		}
		break;
	case 's':
		if (top != nullptr) {
			printTree(method, top->left);
			cout << top->value << " ";
			printTree(method, top->right);
		}
		break;
	default:
		cout << "Введен неверный символ!" << endl;
		break;
	}
}

void delTree(Node* top) {
	// Внутренняя функция
	// Вход: название дерева
	// Выход: удаление дерева
	if (top != nullptr) {
		delTree(top->left);
		delTree(top->right);
		delete top;
	}
}

int depthTreeSys(int counter, Node* top) {
	// Внутренняя функция
	// Вход: 1, название дерева
	// Выход: глубина дерева
	if (top != nullptr) {
		if (top->left == nullptr && top->right == nullptr) {
			return counter;
		}
		else if (top->left == nullptr) {
			return depthTreeSys(counter + 1, top->right);
		}
		else if (top->right == nullptr) {
			return depthTreeSys(counter + 1, top->left);
		}
		else {
			return max(depthTreeSys(counter + 1, top->left), depthTreeSys(counter + 1, top->right));
		}
	}
	else return 0;
}

int depthTree(Node* top) {
	// Пользовательская функция
	// Вход: название дерева
	// Выход: глубина дерева
	int counter = 1;
	return depthTreeSys(counter, top);
}

bool searchNode(int input, Node* top) {
	// Пользовательская функция
	// Вход: значение искомого узла
	// Выход: логическое значение
	if (top != nullptr) {
		if (input < top->value) {
			return searchNode(input, top->left);
		}
		else if (input > top->value) {
			return searchNode(input, top->right);
		}
		else return true;
	}
	else return false;
}

struct Node* parentNode(int input, Node* top) {
	// Внутренняя функция
	// Вход: значение потомка искомого элемента
	// Выход: узел родителя заданного элемента
	if (top != nullptr) {
		if ((top->left->value == input) || (top->right->value == input)) {
			return top;
		}
		else if (input < top->value) {
			return parentNode(input, top->left);
		}
		else {
			return parentNode(input, top->right);
		}
	}
}
/*
struct Node* delNode(int input, Node* top) {
	// Пользовательская функция
	// Вход: значение удаляемого узла, название дерева
	// Выход: 
	if (searchNode(input, top)) {
		Node* parent = parentNode(input, top);
		if (parent->left->value == input) {
			Node* erasable = nullptr;
			erasable = parent->left;
			if (erasable->left == nullptr && erasable->right == nullptr) {
				delete erasable;
				parent->left = nullptr;
			}
		}
		else {
			Node* erasable = nullptr;
			erasable = parent->right;
			if (erasable->left == nullptr && erasable->right == nullptr) {
				delete erasable;
				parent->right = nullptr;
			}
		}
	}
	else {
		cout << "Элемента с указанным значение не найдено!" << endl;
	}
}
*/
void WelcomeUser() {
	// Внутренняя функция
	// Вход: -
	// Выход: приветствие пользователя
	cout /*<< "Программа для работы с деревьями двоичного поиска"*/ << endl;
	cout << "Доступные функции:" << endl;
	cout << "1. Добавление элементов в дерево" << endl;
	cout << "2. Вывод дерева" << endl;
	cout << "3. Вычисление глубины дерева" << endl;
	cout << "4. Поиск элемента в дереве" << endl;
	cout << "5. Удаление элемента из дерева" << endl;
	cout << "6. Удаление дерева и завершение программы" << endl << endl;
	//cout << "Пустое дерево создано" << endl;
}

void FuncSelection(int choice, Node* tree) {
	// Внутренняя функция
	// Вход: номер функции, название дерева, с которым идет дальнейшая работа
	// Выход: вывод результата выбранной функции
	switch (choice) {
	case 1:
		cout << "Выбрано: Добавление элементов в дерево" << endl;
		cout << "Введите количество узлов: ";
		int amount;
		cin >> amount;
		for (int i = 0; i < amount; i++) {
			int temp;
			cin >> temp;
			tree = addNode(temp, tree);
		}
		cout << "Элементы успешно добавлены" << endl;
		break;
	case 2:
		cout << "Выбрано: Вывод дерева" << endl;
		cout << "Выберите метод печати ('p', 'o' или 's'): ";
		char way;
		cin >> way;
		printTree(way, tree);
		cout << endl;
		break;
	case 3:
		cout << "Выбрано: Вычисление глубины дерева" << endl;
		cout << "Глубина дерева = " << depthTree(tree) << endl;
		break;
	case 4:
		cout << "Выбрано: Поиск элемента в дереве" << endl;
		bool exist;
		cout << "Введите значение искомого узла: ";
		int val;
		cin >> val;
		exist = searchNode(val, tree);
		if (exist) {
			cout << "Искомый узел найден" << endl;
		}
		else {
			cout << "Искомый узел не найден" << endl;
		}
		break;
	case 5:
		cout << "Выбрано: Удаление элемента из дерева" << endl;
		cout << "Пока не реализовано :)" << endl;
		break;
	case 6:
		cout << "Выбрано: Удаление дерева и завершение программы" << endl;
		delTree(tree);
		cout << "Дерево удалено" << endl;
		cout << "Программа завершена." << endl;
		break;
	default:
		cout << "Введена неверная команда!" << endl;
		break;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
		
	Node* root = nullptr;
	cout << "Программа для работы с деревьями двоичного поиска" << endl;
	cout << "Задайте значение корня дерева:" << endl;
	int rtvl;
	cin >> rtvl;
	root = addNode(rtvl, root);
	
	WelcomeUser();
	
	while (true) {
		int choice;
		cout << endl << "Введите номер команды" << endl;
		cin >> choice;
		FuncSelection(choice, root);
		if (choice == 6) {
			return 0;
		}
	}
	
	return 0;
}