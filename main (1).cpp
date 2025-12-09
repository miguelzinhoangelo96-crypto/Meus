#include <bits/stdc++.h>
using namespace std;

/*
 AVL Tree implementation (template)
 Supports:
  - insert(value)
  - remove(value)
  - find(value)
  - traversals: inorder, preorder, postorder
  - printTree (simple ascii sideways)
 Complexity:
  - Insert/Delete/Search: O(log n) average and guaranteed for AVL
*/

template<typename T>
struct AVLNode {
    T key;
    AVLNode* left;
    AVLNode* right;
    int height;
    AVLNode(const T& k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

template<typename T>
class AVLTree {
private:
    AVLNode<T>* root;

    int height(AVLNode<T>* node) const {
        return node ? node->height : 0;
    }

    int balanceFactor(AVLNode<T>* node) const {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void updateHeight(AVLNode<T>* node) {
        if (node) node->height = 1 + max(height(node->left), height(node->right));
    }

    AVLNode<T>* rotateRight(AVLNode<T>* y) {
        AVLNode<T>* x = y->left;
        AVLNode<T>* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);
        return x;
    }

    AVLNode<T>* rotateLeft(AVLNode<T>* x) {
        AVLNode<T>* y = x->right;
        AVLNode<T>* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);
        return y;
    }

    AVLNode<T>* rebalance(AVLNode<T>* node) {
        if (!node) return node;
        updateHeight(node);
        int bf = balanceFactor(node);

        // Left heavy
        if (bf > 1) {
            if (balanceFactor(node->left) < 0) {
                // Left-Right case
                node->left = rotateLeft(node->left);
            }
            // Left-Left
            return rotateRight(node);
        }
        // Right heavy
        if (bf < -1) {
            if (balanceFactor(node->right) > 0) {
                // Right-Left case
                node->right = rotateRight(node->right);
            }
            // Right-Right
            return rotateLeft(node);
        }
        return node;
    }

    AVLNode<T>* insertNode(AVLNode<T>* node, const T& key) {
        if (!node) return new AVLNode<T>(key);
        if (key < node->key) node->left = insertNode(node->left, key);
        else if (key > node->key) node->right = insertNode(node->right, key);
        else return node; // duplicate keys ignored (could be adjusted)

        return rebalance(node);
    }

    AVLNode<T>* findMin(AVLNode<T>* node) const {
        AVLNode<T>* cur = node;
        while (cur && cur->left) cur = cur->left;
        return cur;
    }

    AVLNode<T>* removeNode(AVLNode<T>* node, const T& key) {
        if (!node) return node;

        if (key < node->key) {
            node->left = removeNode(node->left, key);
        } else if (key > node->key) {
            node->right = removeNode(node->right, key);
        } else {
            // node to be deleted
            if (!node->left || !node->right) {
                AVLNode<T>* temp = node->left ? node->left : node->right;
                if (!temp) {
                    // no children
                    temp = node;
                    node = nullptr;
                } else {
                    // one child
                    *node = *temp; // copy contents (pointer-shallow copy of children ok)
                }
                delete temp;
            } else {
                // two children: replace with inorder successor (min in right subtree)
                AVLNode<T>* temp = findMin(node->right);
                node->key = temp->key;
                node->right = removeNode(node->right, temp->key);
            }
        }

        if (!node) return node;
        return rebalance(node);
    }

    bool contains(AVLNode<T>* node, const T& key) const {
        if (!node) return false;
        if (key == node->key) return true;
        if (key < node->key) return contains(node->left, key);
        return contains(node->right, key);
    }

    void inorderRec(AVLNode<T>* node, vector<T>& out) const {
        if (!node) return;
        inorderRec(node->left, out);
        out.push_back(node->key);
        inorderRec(node->right, out);
    }

    void preorderRec(AVLNode<T>* node, vector<T>& out) const {
        if (!node) return;
        out.push_back(node->key);
        preorderRec(node->left, out);
        preorderRec(node->right, out);
    }

    void postorderRec(AVLNode<T>* node, vector<T>& out) const {
        if (!node) return;
        postorderRec(node->left, out);
        postorderRec(node->right, out);
        out.push_back(node->key);
    }

    void deleteAll(AVLNode<T>* node) {
        if (!node) return;
        deleteAll(node->left);
        deleteAll(node->right);
        delete node;
    }

    // Pretty-print tree sideways (root on left)
    void printTreeRec(AVLNode<T>* node, string prefix, bool isLeft) const {
        if (!node) return;
        if (node->right) {
            printTreeRec(node->right, prefix + (isLeft ? "│   " : "    "), false);
        }
        cout << prefix;
        cout << (isLeft ? "└── " : "┌── ");
        cout << node->key << " (h=" << node->height << ")\n";
        if (node->left) {
            printTreeRec(node->left, prefix + (isLeft ? "    " : "│   "), true);
        }
    }

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { deleteAll(root); }

    void insert(const T& key) {
        root = insertNode(root, key);
    }

    void remove(const T& key) {
        root = removeNode(root, key);
    }

    bool find(const T& key) const {
        return contains(root, key);
    }

    vector<T> inorder() const {
        vector<T> out;
        inorderRec(root, out);
        return out;
    }

    vector<T> preorder() const {
        vector<T> out;
        preorderRec(root, out);
        return out;
    }

    vector<T> postorder() const {
        vector<T> out;
        postorderRec(root, out);
        return out;
    }

    void printTree() const {
        if (!root) {
            cout << "(empty tree)\n";
            return;
        }
        printTreeRec(root, "", false);
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    AVLTree<int> tree;

    // Example operations
    vector<int> vals = {30, 20, 40, 10, 25, 35, 50, 5, 15, 27, 45};
    cout << "Insert sequence: ";
    for (int v : vals) cout << v << " ";
    cout << "\n\n";

    for (int v : vals) {
        tree.insert(v);
    }

    cout << "Tree after insertions:\n";
    tree.printTree();
    cout << "\nInorder (sorted): ";
    for (int x : tree.inorder()) cout << x << " ";
    cout << "\n\n";

    // Test finds
    cout << "Find 25? " << (tree.find(25) ? "Yes" : "No") << "\n";
    cout << "Find 100? " << (tree.find(100) ? "Yes" : "No") << "\n\n";

    // Remove a leaf
    cout << "Removing 5 (leaf) ...\n";
    tree.remove(5);
    tree.printTree();
    cout << "\n\n";

    // Remove node with one child / two children
    cout << "Removing 40 (has two children) ...\n";
    tree.remove(40);
    tree.printTree();
    cout << "\n\n";

    cout << "Final inorder: ";
    for (int x : tree.inorder()) cout << x << " ";
    cout << "\n";

    return 0;    return 0;
}
