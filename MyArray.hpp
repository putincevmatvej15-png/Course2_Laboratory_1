#ifndef MYARRAY_HPP
#define MYARRAY_HPP
#include <string>
#include <iostream>

class MyArray {
protected:
    std::string* data;
    int size;
    int capacity;
    void resize(int new_capacity);

public:
    MyArray();
    ~MyArray();

    void push_back(const std::string& val);
    void insert_at(int index, const std::string& val);
    void remove_at(int index);
    void remove_by_value(const std::string& val);
    void update_at(int index, const std::string& val);
    std::string get(int index) const;
    int length() const;
    void print() const;
    
    std::string* get_raw_data() const { return data; }
    void set_from_array(const std::string* arr, int count);
};
#endif
