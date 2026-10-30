#ifndef AVLTREE_HPP
#define AVLTREE_HPP
#include <vector>
#include <iostream>

class AVLTree {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;
        int height;
        Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
    };
    Node* root;

    int height(Node* n) const;
    int getBalance(Node* n) const;
    void updateHeight(Node* n);
    Node* balance(Node* node);
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
    Node* insert(Node* node, int key);
    Node* deleteNode(Node* root, int key);
    Node* minValueNode(Node* node);
    bool search(Node* root, int key) const;
    void inorder(Node* root) const;
    void clear(Node* root);
    void toVector(Node* root, std::vector<int>& v) const;
    
    // Новый вспомогательный метод для рисования
    void printTreeRec(Node* node, int space) const; 

public:
    AVLTree();
    ~AVLTree();
    void insert(int key);
    void remove(int key);
    bool find(int key) const;
    
    void print() const;       // Старый вывод (просто числа: 10 20 30)
    void printTree() const;   // НОВЫЙ вывод (красивая ёлочка)
    
    std::vector<int> getData() const;
    void setData(const std::vector<int>& d);
};
#endif
