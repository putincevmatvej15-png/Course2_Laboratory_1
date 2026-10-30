#ifndef MYQUEUE_HPP
#define MYQUEUE_HPP
#include "MyArray.hpp"

class MyQueue : public MyArray {
public:
    void push(const std::string& val);
    std::string pop();
    void print() const;
};
#endif
