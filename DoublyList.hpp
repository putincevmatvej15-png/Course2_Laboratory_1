#ifndef DOUBLYLIST_HPP
#define DOUBLYLIST_HPP
#include <string>
#include <vector>
#include <iostream>

class DoublyList {
private:
    struct Node {
        std::string data;
        Node* prev;
        Node* next;
        Node(const std::string& val) : data(val), prev(nullptr), next(nullptr) {}
    };
    Node* head;
    Node* tail;
    int size;

public:
    DoublyList();
    ~DoublyList();

    void push_front(const std::string& val);
    void push_back(const std::string& val);
    void insert_before_at(int index, const std::string& val);
    void insert_after_at(int index, const std::string& val);
    
    // НОВЫЕ
    void insert_before_value(const std::string& target, const std::string& val);
    void insert_after_value(const std::string& target, const std::string& val);
    
    void pop_front();
    void pop_back();
    void remove_at(int index);
    void remove_by_value(const std::string& val);
    
    // НОВЫЕ
    void remove_all_by_value(const std::string& val);
    void remove_before_value(const std::string& target);
    void remove_after_value(const std::string& target);
    
    bool find(const std::string& val) const;
    int getSize() const;
    void print() const;

    std::vector<std::string> getData() const;
    void setData(const std::vector<std::string>& d);
};
#endif