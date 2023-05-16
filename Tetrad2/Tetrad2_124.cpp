#include <iostream>
#include <string>

using namespace std;

class BST {
	struct Node {
		int value;
		int height;
		Node* left;
		Node* right;
	};

	Node* root;

    // main methods

    void makeEmpty(Node* t)
    {
        if (t == nullptr) return;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }

    Node* insert(int x, Node* t)
    {
        if (t == nullptr)
        {
            t = new Node;
            t->value = x;
            t->height = 0;
            t->left = t->right = nullptr;
        }
        else if (x < t->value)
        {
            t->left = insert(x, t->left);
            if (height(t->left) - height(t->right) == 2)
            {
                if (x < t->left->value)
                    t = singleRightRotate(t);
                else
                    t = doubleRightRotate(t);
            }
        }
        else if (x > t->value)
        {
            t->right = insert(x, t->right);
            if (height(t->right) - height(t->left) == 2)
            {
                if (x > t->right->value)
                    t = singleLeftRotate(t);
                else
                    t = doubleLeftRotate(t);
            }
        }

        t->height = max(height(t->left), height(t->right)) + 1;
        return t;
    }

    Node* singleRightRotate(Node*& t)
    {
        if (t->left != nullptr) {
            Node* u = t->left;
            t->left = u->right;
            u->right = t;
            t->height = max(height(t->left), height(t->right)) + 1;
            u->height = max(height(u->left), t->height) + 1;
            return u;
        }
        return t;
    }

    Node* singleLeftRotate(Node*& t)
    {
        if (t->right != nullptr)
        {
            Node* u = t->right;
            t->right = u->left;
            u->left = t;
            t->height = max(height(t->left), height(t->right)) + 1;
            u->height = max(height(t->right), t->height) + 1;
            return u;
        }
        return t;
    }

    Node* doubleLeftRotate(Node*& t)
    {
        t->right = singleRightRotate(t->right);
        return singleLeftRotate(t);
    }

    Node* doubleRightRotate(Node*& t)
    {
        t->left = singleLeftRotate(t->left);
        return singleRightRotate(t);
    }

    Node* findMin(Node* t)
    {
        if (t == nullptr)
            return nullptr;
        else if (t->left == nullptr)
            return t;
        else
            return findMin(t->left);
    }

    Node* findMax(Node* t)
    {
        if (t == nullptr)
            return nullptr;
        else if (t->right == nullptr)
            return t;
        else
            return findMax(t->right);
    }

    Node* remove(int x, Node* t)
    {
        Node* temp;

        // Element not found
        if (t == nullptr)
            return nullptr;

        // Searching for element
        else if (x < t->value)
            t->left = remove(x, t->left);
        else if (x > t->value)
            t->right = remove(x, t->right);

        // Element found
        // With 2 children
        else if (t->left && t->right)
        {
            temp = findMin(t->right);
            t->value = temp->value;
            t->right = remove(t->value, t->right);
        }
        // With one or zero child
        else
        {
            temp = t;
            if (t->left == nullptr)
                t = t->right;
            else if (t->right == nullptr)
                t = t->left;
            delete temp;
        }
        if (t == nullptr)
            return t;

        t->height = max(height(t->left), height(t->right)) + 1;

        // If node is unbalanced
        // If left node is deleted, right case
        if (height(t->left) - height(t->right) == 2)
        {
            // right right case
            if (height(t->left->left) - height(t->left->right) == 1)
                return singleLeftRotate(t);
            // right left case
            else
                return doubleLeftRotate(t);
        }
        // If right node is deleted, left case
        else if (height(t->right) - height(t->left) == 2)
        {
            // left left case
            if (height(t->right->right) - height(t->right->left) == 1)
                return singleRightRotate(t);
            // left right case
            else
                return doubleRightRotate(t);
        }
        return t;
    }

    int height(Node* t)
    {
        return (t == nullptr ? -1 : t->height);
    }

    int getBalance(Node* t)
    {
        if (t == nullptr)
            return 0;
        else
            return height(t->left) - height(t->right);
    }

    void inorder(Node* t)
    {
        if (t == nullptr) return;
        inorder(t->left);
        cout << t->value << "(" << t->height << ")" << " ";
        inorder(t->right);
    }

    // methods for visual output

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
		    cout << top->value << "(" << getBalance(top) << ")" << endl;
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

    // function for checking RBtree properties

    bool checkingRBtree(Node* root, int& rootMax)
    {
        if (root == nullptr) {
            return true;
        }
        int leftMax = 0, rightMax = 0;
        if (checkingRBtree(root->left, leftMax) &&
            checkingRBtree(root->right, rightMax))
        {
            int rootMin = min(leftMax, rightMax) + 1;
            rootMax = max(leftMax, rightMax) + 1;

            return (rootMax <= 2 * rootMin);
        }
        return false;
    }

public:
    BST()
    {
        root = nullptr;
    }

    void insert(int x)
    {
        root = insert(x, root);
    }

    void remove(int x)
    {
        root = remove(x, root);
    }

    void display()
    {
        inorder(root);
        cout << endl;
    }

    void visualoutput()
    {
        visualprintTree(root);
        cout << endl;
    }

    void isRBtree()
    {
        Node* r = root;
        int rMax = 0;
        if (checkingRBtree(r, rMax)) cout << "Like a RB tree";
        else cout << "Not like a RB tree";
    }
};

int main()
{
	setlocale(LC_ALL, "Russian");

    BST t;
    
    t.insert(5);
    t.insert(3);
    t.insert(7);
    t.insert(10);
    t.insert(12);

    t.display();

    t.visualoutput();

    t.remove(5);

    t.visualoutput();

    t.isRBtree();

	return 0;
}