#include <bits/stdc++.h>
using namespace std;

#define Besmellah ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(0);
#define ll long long

const double PI = 3.141592653;

struct Node {
    int data;
    bool color;
    Node *left, *right, *parent;

    Node(int data) {
        this->data = data;
        this->color = true;
        left = right = parent = nullptr;
    }
};


class RBTree {
private:
    Node *root;

    // Utility function for left rotation
    void leftRotate(Node *root, Node *x) {
        Node *y = x->right;
        x->right = y->left;

        if (y->left != nullptr)
            y->left->parent = x;

        y->parent = x->parent;

        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    // Utility function for right rotation
    void rightRotate(Node *root, Node *x) {
        Node *y = x->left;
        x->left = y->right;

        if (y->right != nullptr)
            y->right->parent = x;

        y->parent = x->parent;

        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;

        y->right = x;
        x->parent = y;
    }

    // Fix Red-Black Tree after insertion
    void fixInsertion(Node *root, Node *pt) {
        Node *parent_node = nullptr;
        Node *grand_parent_node = nullptr;

        while (pt != root and pt->color == true and pt->parent->color == true) {
            parent_node = pt->parent;
            grand_parent_node = pt->parent->parent;

            // Case A: Parent is left child of grandparent
            if (parent_node == grand_parent_node->left) {
                Node *uncle_node = grand_parent_node->right;

                // Case 1: Uncle is red
                if (uncle_node != nullptr and uncle_node->color == true) {
                    grand_parent_node->color = true;
                    parent_node->color = false;
                    uncle_node->color = false;
                    pt = grand_parent_node;
                } else {
                    // Case 2: pt is right child
                    if (pt == parent_node->right) {
                        leftRotate(root, parent_node);
                        pt = parent_node;
                        parent_node = pt->parent;
                    }

                    // Case 3: pt is left child
                    rightRotate(root, grand_parent_node);
                    swap(parent_node->color, grand_parent_node->color);
                    pt = parent_node;
                }
            } else {
                // Case B: Parent is right child of grandparent
                Node *uncle_node = grand_parent_node->left;

                // Case 1: Uncle is red
                if (uncle_node != nullptr and uncle_node->color == true) {
                    grand_parent_node->color = true;
                    parent_node->color = false;
                    uncle_node->color = false;
                    pt = grand_parent_node;
                } else {
                    // Case 2: pt is left child
                    if (pt == parent_node->left) {
                        rightRotate(root, parent_node);
                        pt = parent_node;
                        parent_node = pt->parent;
                    }

                    // Case 3: pt is right child
                    leftRotate(root, grand_parent_node);
                    swap(parent_node->color, grand_parent_node->color);
                    pt = parent_node;
                }
            }
        }

        root->color = false;
    }

    // Helper for in-order traversal
    void inorderTraversal(Node *node) {
        if (node == nullptr)
            return;

        inorderTraversal(node->left);
        cout << node->data << " ";
        inorderTraversal(node->right);
    }

    // Helper for fixing Red-Black Tree after deletion
    void fixDeletion(Node *root, Node *x) {
        while (x != root and x->color == false) {
            if (x == x->parent->left) {
                Node *sibling_node = x->parent->right;

                if (sibling_node->color == true) {
                    sibling_node->color = false;
                    x->parent->color = true;
                    leftRotate(root, x->parent);
                    sibling_node = x->parent->right;
                }

                if ((sibling_node->left == nullptr or sibling_node->left->color == false) and
                    (sibling_node->right == nullptr or sibling_node->right->color == false)) {
                    sibling_node->color = true;
                    x = x->parent;
                } else {
                    if (sibling_node->right == nullptr or sibling_node->right->color == false) {
                        if (sibling_node->left != nullptr)
                            sibling_node->left->color = false;

                        sibling_node->color = true;
                        rightRotate(root, sibling_node);
                        sibling_node = x->parent->right;
                    }

                    sibling_node->color = x->parent->color;
                    x->parent->color = false;

                    if (sibling_node->right != nullptr)
                        sibling_node->right->color = false;

                    leftRotate(root, x->parent);
                    x = root;
                }
            } else {
                Node *sibling_node = x->parent->left;

                if (sibling_node->color == true) {
                    sibling_node->color = false;
                    x->parent->color = true;
                    rightRotate(root, x->parent);
                    sibling_node = x->parent->left;
                }

                if ((sibling_node->left == nullptr or sibling_node->left->color == false) and
                    (sibling_node->right == nullptr or sibling_node->right->color == false)) {
                    sibling_node->color = true;
                    x = x->parent;
                } else {
                    if (sibling_node->left == nullptr or sibling_node->left->color == false) {
                        if (sibling_node->right != nullptr)
                            sibling_node->right->color = false;

                        sibling_node->color = true;
                        leftRotate(root, sibling_node);
                        sibling_node = x->parent->left;
                    }

                    sibling_node->color = x->parent->color;
                    x->parent->color = false;

                    if (sibling_node->left != nullptr)
                        sibling_node->left->color = false;

                    rightRotate(root, x->parent);
                    x = root;
                }
            }
        }

        x->color = false;
    }

    // Helper for deleting a node
    void deleteNodeHelper(Node *root, Node *v) {
        Node *u = (v->left == nullptr or v->right == nullptr) ? v : successor(v);
        Node *child = (u->left != nullptr) ? u->left : u->right;

        if (child != nullptr)
            child->parent = u->parent;

        if (u->parent == nullptr)
            root = child;
        else if (u == u->parent->left)
            u->parent->left = child;
        else
            u->parent->right = child;

        if (u != v)
            v->data = u->data;

        if (u->color == false and child != nullptr)
            fixDeletion(root, child);

        delete u;
    }

    Node* successor(Node *x) {
        Node *curr = x->right;
        while (curr->left != nullptr)
            curr = curr->left;
        return curr;
    }

public:
    RBTree(){
        root = nullptr;
    }

    void insert(const int &data) {
        Node *pt = new Node(data);
        root = BSTInsert(root, pt);
        fixInsertion(root, pt);
    }

    Node* BSTInsert(Node *root, Node *pt) {
        if (root == nullptr)
            return pt;

        if (pt->data < root->data) {
            root->left = BSTInsert(root->left, pt);
            root->left->parent = root;
        } else if (pt->data > root->data) {
            root->right = BSTInsert(root->right, pt);
            root->right->parent = root;
        }

        return root;
    }

    void deleteNode(const int &data) {
        Node *v = search(root, data);
        if (v == nullptr) {
            cout << "Value not found in the tree.\n";
            return;
        }
        deleteNodeHelper(root, v);
    }
    
    //helps for deletion function
    Node* search(Node *root, const int &data) {
        if (root == nullptr || root->data == data)
            return root;

        if (data < root->data)
            return search(root->left, data);

        return search(root->right, data);
    }

    void PrintInOrder() {
        inorderTraversal(root);
        cout << endl;
    }
};


int main() {
    RBTree tree;
    
    
    //example from lectures slides
    tree.insert(47);
    tree.insert(32);
    tree.insert(71);
    tree.insert(93);
    tree.insert(65);
    tree.insert(82);
    tree.insert(87);
    tree.insert(51);

    tree.PrintInOrder();   cout    <<  endl;
    tree.deleteNode(32);
    tree.PrintInOrder();   cout    <<  endl;

    return 0;
}
