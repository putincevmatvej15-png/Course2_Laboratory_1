#ifndef MYSTACK_HPP
#define MYSTACK_HPP
#include "MyArray.hpp"

class MyStack : public MyArray {
public:
    void push(const std::string& val);
    std::string pop();
    void print() const;
};
#endif
