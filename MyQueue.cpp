#include "MyQueue.hpp"
#include <stdexcept>

void MyQueue::push(const std::string& val) { push_back(val); }

std::string MyQueue::pop() {
    if (size == 0) throw std::runtime_error("Queue is empty");
    std::string v = data[0];
    remove_at(0);
    return v;
}

void MyQueue::print() const {
    for (int i = 0; i < size; ++i) std::cout << data[i] << " ";
}
