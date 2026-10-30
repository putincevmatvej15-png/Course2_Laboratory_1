#include "MyStack.hpp"
#include <stdexcept>

void MyStack::push(const std::string& val) { push_back(val); }

std::string MyStack::pop() {
    if (size == 0) throw std::runtime_error("Stack is empty");
    std::string v = data[size - 1];
    remove_at(size - 1);
    return v;
}

void MyStack::print() const {
    for (int i = size - 1; i >= 0; --i) std::cout << data[i] << " ";
}
