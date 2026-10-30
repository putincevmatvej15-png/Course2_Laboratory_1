#include "DoublyList.hpp"
#include <stdexcept>

DoublyList::DoublyList() : head(nullptr), tail(nullptr), size(0) {}
DoublyList::~DoublyList() {
    while (head) { Node* t = head; head = head->next; delete t; }
}

void DoublyList::push_front(const std::string& val) {
    Node* n = new Node(val);
    if (!head) { head = tail = n; }
    else { n->next = head; head->prev = n; head = n; }
    size++;
}

void DoublyList::push_back(const std::string& val) {
    Node* n = new Node(val);
    if (!tail) { head = tail = n; }
    else { n->prev = tail; tail->next = n; tail = n; }
    size++;
}

void DoublyList::insert_before_at(int index, const std::string& val) {
    if (index < 0 || index > size) throw std::out_of_range("Index out of range");
    if (index == 0) { push_front(val); return; }
    Node* cur = head;
    for (int i = 0; i < index; ++i) cur = cur->next;
    Node* n = new Node(val);
    n->prev = cur->prev; n->next = cur;
    cur->prev->next = n; cur->prev = n; size++;
}

void DoublyList::insert_after_at(int index, const std::string& val) {
    if (index < 0 || index >= size) throw std::out_of_range("Index out of range");
    if (index == size - 1) { push_back(val); return; }
    Node* cur = head;
    for (int i = 0; i < index; ++i) cur = cur->next;
    Node* n = new Node(val);
    n->next = cur->next; n->prev = cur;
    cur->next->prev = n; cur->next = n; size++;
}

void DoublyList::insert_before_value(const std::string& target, const std::string& val) {
    Node* cur = head;
    while (cur && cur->data != target) cur = cur->next;
    if (!cur) return;
    if (cur == head) { push_front(val); return; }
    Node* n = new Node(val);
    n->prev = cur->prev; n->next = cur;
    cur->prev->next = n; cur->prev = n; size++;
}

void DoublyList::insert_after_value(const std::string& target, const std::string& val) {
    Node* cur = head;
    while (cur && cur->data != target) cur = cur->next;
    if (!cur) return;
    if (cur == tail) { push_back(val); return; }
    Node* n = new Node(val);
    n->next = cur->next; n->prev = cur;
    cur->next->prev = n; cur->next = n; size++;
}

void DoublyList::pop_front() {
    if (!head) return;
    Node* t = head; head = head->next;
    if (head) head->prev = nullptr; else tail = nullptr;
    delete t; size--;
}

void DoublyList::pop_back() {
    if (!tail) return;
    Node* t = tail; tail = tail->prev;
    if (tail) tail->next = nullptr; else head = nullptr;
    delete t; size--;
}

void DoublyList::remove_at(int index) {
    if (index < 0 || index >= size) throw std::out_of_range("Index out of range");
    if (index == 0) { pop_front(); return; }
    if (index == size - 1) { pop_back(); return; }
    Node* cur = head;
    for (int i = 0; i < index; ++i) cur = cur->next;
    cur->prev->next = cur->next; cur->next->prev = cur->prev;
    delete cur; size--;
}

void DoublyList::remove_by_value(const std::string& val) {
    Node* cur = head;
    while (cur && cur->data != val) cur = cur->next;
    if (!cur) return;
    if (cur == head) { pop_front(); return; }
    if (cur == tail) { pop_back(); return; }
    cur->prev->next = cur->next; cur->next->prev = cur->prev;
    delete cur; size--;
}

void DoublyList::remove_all_by_value(const std::string& val) {
    Node* cur = head;
    while (cur) {
        if (cur->data == val) {
            Node* next = cur->next;
            if (cur == head) { pop_front(); }
            else if (cur == tail) { pop_back(); }
            else {
                cur->prev->next = cur->next;
                cur->next->prev = cur->prev;
                delete cur; size--;
            }
            cur = next;
        } else {
            cur = cur->next;
        }
    }
}

void DoublyList::remove_before_value(const std::string& target) {
    Node* cur = head;
    while (cur && cur->data != target) cur = cur->next;
    if (!cur || !cur->prev) return;
    Node* t = cur->prev;
    if (t->prev) t->prev->next = cur; else head = cur;
    cur->prev = t->prev;
    delete t; size--;
}
void DoublyList::remove_after_value(const std::string& target) {
    Node* cur = head;
    while (cur && cur->data != target) cur = cur->next;
    if (!cur || !cur->next) return;
    Node* t = cur->next;
    if (t->next) t->next->prev = cur; else tail = cur;
    cur->next = t->next;
    delete t; size--;
}

bool DoublyList::find(const std::string& val) const {
    Node* cur = head;
    while (cur) { if (cur->data == val) return true; cur = cur->next; }
    return false;
}

int DoublyList::getSize() const { return size; }

void DoublyList::print() const {
    Node* cur = head;
    while (cur) { std::cout << cur->data << " <-> "; cur = cur->next; }
    std::cout << "NULL";
}

std::vector<std::string> DoublyList::getData() const {
    std::vector<std::string> res; Node* cur = head;
    while (cur) { res.push_back(cur->data); cur = cur->next; }
    return res;
}

void DoublyList::setData(const std::vector<std::string>& d) {
    while (head) { Node* t = head; head = head->next; delete t; }
    head = tail = nullptr; size = 0;
    for (const auto& v : d) push_back(v);
}