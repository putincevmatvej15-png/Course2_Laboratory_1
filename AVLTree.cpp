#include "AVLTree.hpp"
#include <algorithm>
#include <stdexcept>
#include <iostream>

AVLTree::AVLTree() : root(nullptr) {}
AVLTree::~AVLTree() { clear(root); }

void AVLTree::clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

int AVLTree::height(Node* node) const { return node ? node->height : 0; }

void AVLTree::updateHeight(Node* node) {
    if (node) node->height = 1 + std::max(height(node->left), height(node->right));
}

int AVLTree::getBalance(Node* node) const {
    if (!node) return 0;
    return height(node->left) - height(node->right);
}

AVLTree::Node* AVLTree::rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

AVLTree::Node* AVLTree::leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

AVLTree::Node* AVLTree::balance(Node* node) {
    if (!node) return node;
    updateHeight(node);
    int bf = getBalance(node);

    if (bf > 1 && getBalance(node->left) >= 0) return rightRotate(node);
    if (bf < -1 && getBalance(node->right) <= 0) return leftRotate(node);
    if (bf > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (bf < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

AVLTree::Node* AVLTree::insert(Node* node, int key) {
    if (!node) return new Node(key);
    if (key < node->key) node->left = insert(node->left, key);
    else if (key > node->key) node->right = insert(node->right, key);
    else return node;
    return balance(node);
}

AVLTree::Node* AVLTree::minValueNode(Node* node) {
    Node* cur = node;
    while (cur->left) cur = cur->left;
    return cur;
}

AVLTree::Node* AVLTree::deleteNode(Node* root, int key) {
    if (!root) return root;
    if (key < root->key) root->left = deleteNode(root->left, key);
    else if (key > root->key) root->right = deleteNode(root->right, key);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp) { temp = root; root = nullptr; }
            else *root = *temp;
            delete temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }
    if (!root) return root;
    return balance(root);
}

bool AVLTree::search(Node* node, int key) const {
    if (!node) return false;
    if (node->key == key) return true;
    if (key < node->key) return search(node->left, key);
    return search(node->right, key);
}

void AVLTree::inorder(Node* node) const {
    if (!node) return;
    inorder(node->left);
    std::cout << node->key << " ";
    inorder(node->right);
}

void AVLTree::toVector(Node* node, std::vector<int>& v) const {
    if (!node) return;
    toVector(node->left, v);
    v.push_back(node->key);
    toVector(node->right, v);
}

void AVLTree::insert(int key) { root = insert(root, key); }
void AVLTree::remove(int key) { root = deleteNode(root, key); }
bool AVLTree::find(int key) const { return search(root, key); }

void AVLTree::print() const {
    inorder(root);
}

// НОВЫЕ МЕТОДЫ ДЛЯ КРАСИВОГО ВЫВОДА
void AVLTree::printTreeRec(Node* node, int space) const {
    if (node == nullptr) return;

    space += 5;

    // Сначала правое поддерево
    printTreeRec(node->right, space);

    // Печатаем узел
    std::cout << "\n";
    for (int i = 5; i < space; i++) std::cout << " ";
    std::cout << node->key << "(h:" << node->height << ")";

    // Потом левое
    printTreeRec(node->left, space);
}

void AVLTree::printTree() const {
    if (!root) {
        std::cout << "(empty tree)";
        return;
    }
    printTreeRec(root, 0);
}

std::vector<int> AVLTree::getData() const {
    std::vector<int> res;
    toVector(root, res);
    return res;
}

void AVLTree::setData(const std::vector<int>& d) {
    clear(root);
    root = nullptr;
    for (int v : d) root = insert(root, v);
}
