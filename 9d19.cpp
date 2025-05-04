
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// AVL Tree Node
struct TreeNode {
    string key;
    string meaning;
    TreeNode* left;
    TreeNode* right;
    int height;

    TreeNode(string k, string m) : key(k), meaning(m), left(nullptr), right(nullptr), height(1) {}
};

// AVL Tree class
class AVLTree {
private:
    TreeNode* root;

    // Get height of the tree node
    int height(TreeNode* node) {
        return node ? node->height : 0;
    }

    // Update height of the node
    void updateHeight(TreeNode* node) {
        node->height = max(height(node->left), height(node->right)) + 1;
    }

    // Get balance factor of the node
    int getBalanceFactor(TreeNode* node) {
        return height(node->left) - height(node->right);
    }

    // Right rotate
    TreeNode* rightRotate(TreeNode* y) {
        TreeNode* x = y->left;
        TreeNode* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        updateHeight(y);
        updateHeight(x);

        return x;
    }

    // Left rotate
    TreeNode* leftRotate(TreeNode* x) {
        TreeNode* y = x->right;
        TreeNode* T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        updateHeight(x);
        updateHeight(y);

        return y;
    }

    // Rebalance the tree
    TreeNode* rebalance(TreeNode* node) {
        updateHeight(node);

        int balance = getBalanceFactor(node);

        // Left heavy case
        if (balance > 1) {
            if (getBalanceFactor(node->left) < 0) {
                node->left = leftRotate(node->left);
            }
            return rightRotate(node);
        }

        // Right heavy case
        if (balance < -1) {
            if (getBalanceFactor(node->right) > 0) {
                node->right = rightRotate(node->right);
            }
            return leftRotate(node);
        }

        return node;
    }

    // Insert a new key into the AVL tree
    TreeNode* insert(TreeNode* node, const string& key, const string& meaning) {
        if (!node) return new TreeNode(key, meaning);

        if (key < node->key) {
            node->left = insert(node->left, key, meaning);
        } else if (key > node->key) {
            node->right = insert(node->right, key, meaning);
        } else {
            node->meaning = meaning;  // Update the meaning if key exists
            return node;
        }

        return rebalance(node);
    }

    // Find the node with the minimum key
    TreeNode* getMinNode(TreeNode* node) {
        TreeNode* current = node;
        while (current && current->left) {
            current = current->left;
        }
        return current;
    }

    // Delete a node with the given key
    TreeNode* deleteNode(TreeNode* root, const string& key) {
        if (!root) return root;

        if (key < root->key) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->key) {
            root->right = deleteNode(root->right, key);
        } else {
            if (!root->left || !root->right) {
                TreeNode* temp = root->left ? root->left : root->right;
                delete root;
                return temp;
            } else {
                TreeNode* temp = getMinNode(root->right);
                root->key = temp->key;
                root->meaning = temp->meaning;
                root->right = deleteNode(root->right, temp->key);
            }
        }

        return rebalance(root);
    }

    // In-order traversal for ascending order display
    void inorder(TreeNode* node) {
        if (node) {
            inorder(node->left);
            cout << node->key << " : " << node->meaning << endl;
            inorder(node->right);
        }
    }

    // Reverse in-order traversal for descending order display
    void reverseInorder(TreeNode* node) {
        if (node) {
            reverseInorder(node->right);
            cout << node->key << " : " << node->meaning << endl;
            reverseInorder(node->left);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    // Insert a new keyword-meaning pair
    void insert(const string& key, const string& meaning) {
        root = insert(root, key, meaning);
    }

    // Delete a keyword from the dictionary
    void deleteKeyword(const string& key) {
        root = deleteNode(root, key);
    }

    // Update the meaning of a keyword
    void updateMeaning(const string& key, const string& newMeaning) {
        root = insert(root, key, newMeaning);
    }

    // Display the dictionary in ascending order
    void displayAscending() {
        inorder(root);
    }

    // Display the dictionary in descending order
    void displayDescending() {
        reverseInorder(root);
    }

    // Find maximum comparisons for keyword lookup (O(log n))
    int findMaxComparisons() {
        return height(root);
    }

    // Search for a keyword and return its meaning
    string search(const string& key) {
        TreeNode* current = root;
        while (current) {
            if (key < current->key) {
                current = current->left;
            } else if (key > current->key) {
                current = current->right;
            } else {
                return current->meaning;  // Found the keyword
            }
        }
        return "Keyword not found";
    }
};

// Main function for testing
int main() {
    AVLTree dictionary;
    string key, meaning, newMeaning;
    int choice;

    while (true) {
        cout << "\nDictionary Menu:\n";
        cout << "1. Insert a new keyword\n";
        cout << "2. Delete a keyword\n";
        cout << "3. Update meaning of a keyword\n";
        cout << "4. Search for a keyword\n";
        cout << "5. Display dictionary (Ascending Order)\n";
        cout << "6. Display dictionary (Descending Order)\n";
        cout << "7. Find maximum comparisons needed for lookup\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // To clear the newline character from the input buffer

        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                getline(cin, key);
                cout << "Enter meaning: ";
                getline(cin, meaning);
                dictionary.insert(key, meaning);
                break;
            case 2:
                cout << "Enter keyword to delete: ";
                getline(cin, key);
                dictionary.deleteKeyword(key);
                break;
            case 3:
                cout << "Enter keyword to update: ";
                getline(cin, key);
                cout << "Enter new meaning: ";
                getline(cin, newMeaning);
                dictionary.updateMeaning(key, newMeaning);
                break;
            case 4:
                cout << "Enter keyword to search: ";
                getline(cin, key);
                cout << "Meaning: " << dictionary.search(key) << endl;
                break;
            case 5:
                cout << "Dictionary in Ascending Order:\n";
                dictionary.displayAscending();
                break;
            case 6:
                cout << "Dictionary in Descending Order:\n";
                dictionary.displayDescending();
                break;
            case 7:
                cout << "Maximum comparisons needed for lookup: " << dictionary.findMaxComparisons() << endl;
                break;
            case 8:
                cout << "Exiting the program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
