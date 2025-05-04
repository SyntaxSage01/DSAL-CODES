#include <iostream>
#include <cstring>
using namespace std;

struct node
{
    char data;
    node *left;
    node *right;
};

class tree
{
    char prefix[20];

public:
    node *top;
    void expression(char[]);
    void display(node *);
    void non_rec_postorder(node *);
    void del(node *);
};

class stack1
{
    node *data[30];
    int top;

public:
    stack1()
    {
        top = -1;
    }
    int empty()
    {
        if (top == -1)
            return 1;
        return 0;
    }
    void push(node *p)
    {
        data[++top] = p;
    }
    node *pop()
    {
        return (data[top--]);
    }
};

void tree::expression(char prefix[])
{
    char c;
    stack1 s;
    node *t1, *t2;
    int len, i;
    len = strlen(prefix);

    for (i = len - 1; i >= 0; i--)
    {
        node *newNode = new node; // Create a new node here
        newNode->left = NULL;
        newNode->right = NULL;

        if (isalpha(prefix[i]))
        {
            newNode->data = prefix[i];
            s.push(newNode);
        }
        else if (prefix[i] == '+' || prefix[i] == '*' || prefix[i] == '-' || prefix[i] == '/')
        {
            t2 = s.pop();
            t1 = s.pop();
            newNode->data = prefix[i];
            newNode->left = t2;
            newNode->right = t1;
            s.push(newNode);
        }
    }

    top = s.pop(); // Final tree root is stored in top
}

void tree::display(node *root)
{
    if (root != NULL)
    {
        cout << root->data;
        display(root->left);
        display(root->right);
    }
}

void tree::non_rec_postorder(node *top)
{
    stack1 s1, s2; // stack s1 is for traversal; s2 for reverse post-order
    node *T = top;
    cout << "\n";
    s1.push(T);

    while (!s1.empty())
    {
        T = s1.pop();
        s2.push(T);

        if (T->left != NULL)
            s1.push(T->left);
        if (T->right != NULL)
            s1.push(T->right);
    }

    while (!s2.empty())
    {
        top = s2.pop();
        cout << top->data;
    }
}

void tree::del(node *node)
{
    if (node == NULL)
        return;
   
    // First delete both subtrees
    del(node->left);
    del(node->right);
   
    // Then delete the node
    cout << "\nDeleting node : " << node->data << endl;
    delete node; // Use delete for objects created with new
}

void menu()
{
    cout << "\n----- MENU -----\n";
    cout << "1. Construct Expression Tree from Prefix Expression\n";
    cout << "2. Display Tree in Pre-order\n";
    cout << "3. Perform Post-order Traversal\n";
    cout << "4. Delete Tree\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main()
{
    char expr[20];
    tree t;
    int choice;

    do
    {
        menu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter prefix Expression: ";
            cin >> expr;
            cout << "Prefix Expression: " << expr << endl;
            t.expression(expr);
            break;

        case 2:
            cout << "\nTree in Pre-order: ";
            t.display(t.top);
            cout << endl;
            break;

        case 3:
            cout << "\nPost-order Traversal: ";
            t.non_rec_postorder(t.top);
            cout << endl;
            break;

        case 4:
            t.del(t.top); // Delete the entire tree
            break;

        case 5:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
