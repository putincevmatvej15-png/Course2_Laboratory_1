#ifndef DATABASE_HPP
#define DATABASE_HPP
#include <string>
#include <map>
#include "MyArray.hpp"
#include "ForwardList.hpp"
#include "DoublyList.hpp"
#include "MyStack.hpp"
#include "MyQueue.hpp"
#include "AVLTree.hpp"

struct Database {
    std::map<std::string, MyArray> arrays;
    std::map<std::string, ForwardList> fLists;
    std::map<std::string, DoublyList> dLists;
    std::map<std::string, MyStack> stacks;
    std::map<std::string, MyQueue> queues;
    std::map<std::string, AVLTree> trees;

    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
};
#endif
