#include <iostream>

using namespace std;

struct Node {
    int value;
    Node* next;
};

Node* newNode(int input)
{
    Node* alpha = new Node;
    alpha->value = input;
    alpha->next = nullptr;
    return alpha;
}

bool isempty(Node* head)
{
    if (head == nullptr) {
        return true;
    }
    return false;
}

int lenlist(Node* head)
{
    if (isempty(head)) {
        return 0;
    }
    else {
        Node* temp = head;
        int counter = 0;
        while (temp != nullptr) {
            counter++;
            temp = temp->next;
        }
        return counter;
    }
}

void printlist(Node* head)
{
    Node* temp = head;
    if (isempty(temp)) {
        cout << "Список пуст" << endl;
        return;
    }
    else {
        while (temp != nullptr) {
            cout << temp->value << " -> ";
            temp = temp->next;
        }
        cout << "nullptr" << endl;
        return;
    }
}

int findvalue(int input, Node* head)
{
    if (isempty(head)) {
        return 0;
    }
    else {
        Node* temp = head;
        if (temp->value == input) {
            return 1;
        }
        else {
            int counter = 1;
            while (temp->next != nullptr) {
                temp = temp->next;
                counter++;
                if (temp->value == input) {
                    return counter;
                }
            }
            return 0;
        }
    }
}

Node* pushfront(int input, Node* head)
{
    if (isempty(head)) {
        return newNode(input);
    }
    else {
        Node* newhead = newNode(input);
        newhead->next = head;
        return newhead;
    }
}

Node* pushback(int input, Node* head)
{
    if (isempty(head)) {
        return newNode(input);
    }
    else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode(input);
        return head;
    }
}

Node* pushpos(int input, int pos, Node* head)
{
    if (isempty(head)) {
        return newNode(input);
    }
    else {
        if (pos <= 0) {
            return pushfront(input, head);
        }
        else if (pos >= lenlist(head)) {
            return pushback(input, head);
        }
        else {
            Node* temp = head;
            int curpos = 1;
            while (curpos != pos) {
                temp = temp->next;
                curpos++;
            }
            Node* temp1 = temp->next;
            Node* cur = newNode(input);
            temp->next = cur;
            cur->next = temp1;
            return head;
        }
    }
}

Node* delfront(Node* head)
{
    if (isempty(head)) {
        cout << "Удалять нечего" << endl;
        return head;
    }
    else if (head != nullptr && head->next == nullptr) {
        head = nullptr;
        return head;
    }
    else if (head != nullptr && head->next != nullptr) {
        head = head->next;
        return head;
    }
}

Node* delback(Node* head)
{
    if (isempty(head)) {
        cout << "Удалять нечего" << endl;
        return head;
    }
    else if (head != nullptr && head->next == nullptr) {
        head = nullptr;
        return head;
    }
    else if (head != nullptr && head->next != nullptr) {
        Node* parent = head;
        Node* temp = parent->next;
        while (temp->next != nullptr) {
            parent = temp;
            temp = temp->next;
        }
        delete temp;
        parent->next = nullptr;
        return head;
    }
}

Node* delpos(int pos, Node* head)
{
    if (isempty(head)) {
        cout << "Удалять нечего" << endl;
        return head;
    }
    else if (head != nullptr && head->next == nullptr) {
        head = nullptr;
        return head;
    }
    else if (head != nullptr && head->next != nullptr) {
        if (pos <= 1) {
            return delfront(head);
        }
        else if (pos >= lenlist(head)) {
            return delback(head);
        }
        else {
            Node* temp = head;
            int curpos = 2;
            while (curpos != pos) {
                temp = temp->next;
                curpos++;
            }
            Node* temp1 = temp->next->next;
            delete temp->next;
            temp->next = nullptr;
            temp->next = temp1;
            return head;
        }
    }
}

Node* delvalue(int input, Node* head)
{
    if (isempty(head)) {
        cout << "Удалять нечего" << endl;
        return head;
    }
    else if (head != nullptr && head->next == nullptr) {
        head = nullptr;
        return head;
    }
    else if (head != nullptr && head->next != nullptr) {
        if (findvalue(input, head) == 0) {
            cout << "Указанного элемента в списке нет" << endl;
            return head;
        }
        else {
            if (findvalue(input, head) <= 1) {
                cout << "<<" << endl;
                return delfront(head);
            }
            else if (findvalue(input, head) >= lenlist(head)) {
                cout << ">>" << endl;
                return delback(head);
            }
            else {
                Node* parent = head;
                Node* temp = parent->next;
                int pos = 2;
                while (pos != findvalue(input, head)) {
                    parent = parent->next;
                    temp = temp->next;
                    pos++;
                }
                Node* temp1 = temp->next;
                delete temp;
                parent->next = temp1;
                return head;
            }
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    Node* list1 = new Node;
    list1 = nullptr;
    printlist(list1);
    list1 = newNode(666);
    printlist(list1);
    for (int i = 0; i < 10; i++) {
        list1 = pushback(list1->value + i + 1, list1);
        printlist(list1);
    }
    list1 = pushfront(665, list1);
    printlist(list1);
    cout << lenlist(list1) << endl;
    list1 = pushpos(6661, 2, list1);
    printlist(list1);
    for (int i = 0; i < 5; i++) {
        list1 = delback(list1);
        printlist(list1);
    }
    for (int i = 0; i < 3; i++) {
        list1 = delfront(list1);
        printlist(list1);
    }
    list1 = delpos(3, list1);
    printlist(list1);
    delvalue(668, list1);
    printlist(list1);
    delete list1;
    cout << "CONGRATULATION" << endl;

    return 0;
}