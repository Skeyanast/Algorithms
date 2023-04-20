﻿#include <iostream>
#include <string>

using namespace std;

struct Node {
	// Структура узла дерева
	int value;
	int count;
	Node* left;
	Node* right;
};

Node* addNode(int input, Node* top) {
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

int depthNodeSys(int input, int counter, Node* top)
{
	if (top != nullptr) {
		if (input < top->value) {
			counter++;
			return depthNodeSys(input, counter, top->left);
		}
		else if (input > top->value) {
			counter++;
			return depthNodeSys(input, counter, top->right);
		}
		else return counter;
	}
	else return 0;
}

int depthNode(int input, Node* top)
{
	int counter = 1;
	return depthNodeSys(input, counter, top);
}

void spaceprinter(int space)
{
	if (space > 1) {
		for (int i = 1; i < space; i++) {
			cout << "|   ";
		}
		cout << "|---";
	}
	else if (space == 1) {
		cout << "|---";
	}
	else return;
}

void visualprintTreeSys(Node* top, int level)
{
	if (top != nullptr) {
		if (level > 1) {
			int space = depthNodeSys(top->value, level, top) - 1;
			spaceprinter(space);
		}
		else {
			int space = depthNode(top->value, top) - 1;
			spaceprinter(space);
		}
		cout << top->value << "(" << top->count << ")" << endl;
		level++;
		visualprintTreeSys(top->left, level);
		visualprintTreeSys(top->right, level);
	}
}

void visualprintTree(Node* top)
{
	int level = 1;
	visualprintTreeSys(top, level);
}

void printTree(char method, Node* top) {
	// Пользовательская функция
	// Вход: символ выбора метода печати, название дерева
	// Выход: выбранным способом печатается дерево
	switch (method) {
	case 'p':
		if (top != nullptr) {
			cout << top->value << "(" << top->count << ")" << " ";
			printTree(method, top->left);
			printTree(method, top->right);
		}
		break;
	case 'o':
		if (top != nullptr) {
			printTree(method, top->left);
			printTree(method, top->right);
			cout << top->value << "(" << top->count << ")" << " ";
		}
		break;
	case 's':
		if (top != nullptr) {
			printTree(method, top->left);
			cout << top->value << "(" << top->count << ")" << " ";
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
		if (top->left != nullptr) delTree(top->left);
		if (top->right != nullptr) delTree(top->right);
		delete top;
	}
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

Node* findMaximumKey(Node* ptr)
{
	while (ptr->right != nullptr) {
		ptr = ptr->right;
	}
	return ptr;
}

void delNode(int input, Node* top) {
	// Пользовательская функция
	// Вход: значение удаляемого узла, название дерева
	// Выход: структура нового узла
	if (top == nullptr) {
		return;
	}

	if (input < top->value) {
		delNode(input, top->left);
	}

	else if (input > top->value) {
		delNode(input, top->right);
	}

	else {
		if (top->left == nullptr && top->right == nullptr) {
			delete top;
			top = nullptr;
		}

		else if (top->left != nullptr && top->right != nullptr) {
			Node* predecessor = findMaximumKey(top->left);
			top->value = predecessor->value;
			top->count = predecessor->count;
			delNode(predecessor->value, top->left);
		}

		else {
			Node* child = (top->left) ? top->left : top->right;
			Node* curr = top;
			top = child;
			delete curr;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	Node* root = new Node;
	root = nullptr;
	root = addNode(5000, root);
	for (int i = 27; i < 10000; i+=993) {
		root = addNode(i / 10, root);
		root = addNode(i % 10, root);
	}

	visualprintTree(root);

	return 0;
}