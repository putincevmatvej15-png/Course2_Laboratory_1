#include "Database.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>

std::vector<std::string> tokenize(const std::string& s) {
    std::vector<std::string> tokens;
    std::stringstream ss(s);
    std::string t;
    while (ss >> t) tokens.push_back(t);
    return tokens;
}

int main(int argc, char* argv[]) {
    std::string filename = "data.json";
    std::string query;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) filename = argv[++i];
        else if (arg == "--query" && i + 1 < argc) query = argv[++i];
    }

    Database db;
    db.loadFromFile(filename);
    if (query.empty()) return 0;

    auto tokens = tokenize(query);
    if (tokens.empty()) return 0;

    std::string cmd = tokens[0];
    std::string name = tokens.size() > 1 ? tokens[1] : "";
    std::string val = tokens.size() > 2 ? tokens[2] : "";
    std::string val2 = tokens.size() > 3 ? tokens[3] : "";

    try {
        if (cmd == "PRINT") {
            bool found = false;
            if (db.arrays.count(name)) { std::cout << name << ": "; db.arrays[name].print(); std::cout << "\n"; found = true; }
            if (db.fLists.count(name)) { std::cout << name << ": "; db.fLists[name].print(); std::cout << "\n"; found = true; }
            if (db.dLists.count(name)) { std::cout << name << ": "; db.dLists[name].print(); std::cout << "\n"; found = true; }
            if (db.stacks.count(name)) { std::cout << name << ": "; db.stacks[name].print(); std::cout << "\n"; found = true; }
            if (db.queues.count(name)) { std::cout << name << ": "; db.queues[name].print(); std::cout << "\n"; found = true; }
            if (db.trees.count(name))  { std::cout << "Tree '" << name << "':\n"; db.trees[name].printTree(); std::cout << "\n"; found = true; }
            if (!found) std::cerr << "Error: Container '" << name << "' not found\n";
        }
        // МАССИВ
        else if (cmd == "MPUSH") { db.arrays[name].push_back(val); db.saveToFile(filename); }
        else if (cmd == "MINSERT") { db.arrays[name].insert_at(std::stoi(val), val2); db.saveToFile(filename); }
        else if (cmd == "MGET") { std::cout << db.arrays[name].get(std::stoi(val)) << "\n"; }
        else if (cmd == "MUPDATE") { db.arrays[name].update_at(std::stoi(val), val2); db.saveToFile(filename); }
        else if (cmd == "MDEL_AT") { db.arrays[name].remove_at(std::stoi(val)); db.saveToFile(filename); }
        else if (cmd == "MDEL_VALUE") { db.arrays[name].remove_by_value(val); db.saveToFile(filename); }
        else if (cmd == "MLEN") { std::cout << db.arrays[name].length() << "\n"; }
        
        // ОДНОСВЯЗНЫЙ СПИСОК
        else if (cmd == "FPUSH_FRONT") { db.fLists[name].push_front(val); db.saveToFile(filename); }
        else if (cmd == "FPUSH_BACK") { db.fLists[name].push_back(val); db.saveToFile(filename); }
        else if (cmd == "FINSERT_BEFORE_AT") { db.fLists[name].insert_before_at(std::stoi(val), val2); db.saveToFile(filename); }
        else if (cmd == "FINSERT_AFTER_AT") { db.fLists[name].insert_after_at(std::stoi(val), val2); db.saveToFile(filename); }
        else if (cmd == "FINSERT_BEFORE_VAL") { db.fLists[name].insert_before_value(val, val2); db.saveToFile(filename); }
        else if (cmd == "FINSERT_AFTER_VAL") { db.fLists[name].insert_after_value(val, val2); db.saveToFile(filename); }
        else if (cmd == "FPOP_FRONT") { db.fLists[name].pop_front(); db.saveToFile(filename); }
        else if (cmd == "FPOP_BACK") { db.fLists[name].pop_back(); db.saveToFile(filename); }
        else if (cmd == "FDEL_AT") { db.fLists[name].remove_at(std::stoi(val)); db.saveToFile(filename); }
        else if (cmd == "FDEL_VALUE") { db.fLists[name].remove_by_value(val); db.saveToFile(filename); }
        else if (cmd == "FDEL_ALL") { db.fLists[name].remove_all_by_value(val); db.saveToFile(filename); }
        else if (cmd == "FDEL_BEFORE") { db.fLists[name].remove_before_value(val); db.saveToFile(filename); }
        else if (cmd == "FDEL_AFTER") { db.fLists[name].remove_after_value(val); db.saveToFile(filename); }
        else if (cmd == "FGET") { std::cout << (db.fLists[name].find(val) ? "TRUE" : "FALSE") << "\n"; }

        // ДВУСВЯЗНЫЙ СПИСОК
        else if (cmd == "LPUSH_FRONT") { db.dLists[name].push_front(val); db.saveToFile(filename); }
        else if (cmd == "LPUSH_BACK") { db.dLists[name].push_back(val); db.saveToFile(filename); }
        else if (cmd == "LINSERT_BEFORE_AT") { db.dLists[name].insert_before_at(std::stoi(val), val2); db.saveToFile(filename); }
        else if (cmd == "LINSERT_AFTER_AT") { db.dLists[name].insert_after_at(std::stoi(val), val2); db.saveToFile(filename); }
        else if (cmd == "LINSERT_BEFORE_VAL") { db.dLists[name].insert_before_value(val, val2); db.saveToFile(filename); }
        else if (cmd == "LINSERT_AFTER_VAL") { db.dLists[name].insert_after_value(val, val2); db.saveToFile(filename); }
        else if (cmd == "LPOP_FRONT") { db.dLists[name].pop_front(); db.saveToFile(filename); }
        else if (cmd == "LPOP_BACK") { db.dLists[name].pop_back(); db.saveToFile(filename); }
        else if (cmd == "LDEL_AT") { db.dLists[name].remove_at(std::stoi(val)); db.saveToFile(filename); }
        else if (cmd == "LDEL_VALUE") { db.dLists[name].remove_by_value(val); db.saveToFile(filename); }
        else if (cmd == "LDEL_ALL") { db.dLists[name].remove_all_by_value(val); db.saveToFile(filename); }
        else if (cmd == "LDEL_BEFORE") { db.dLists[name].remove_before_value(val); db.saveToFile(filename); }
        else if (cmd == "LDEL_AFTER") { db.dLists[name].remove_after_value(val); db.saveToFile(filename); }
        else if (cmd == "LGET") { std::cout << (db.dLists[name].find(val) ? "TRUE" : "FALSE") << "\n"; }

        // СТЕК / ОЧЕРЕДЬ / ДЕРЕВО
        else if (cmd == "SPUSH") { db.stacks[name].push(val); db.saveToFile(filename); }
        else if (cmd == "SPOP") { std::cout << db.stacks[name].pop() << "\n"; db.saveToFile(filename); }
        else if (cmd == "QPUSH") { db.queues[name].push(val); db.saveToFile(filename); }
        else if (cmd == "QPOP") { std::cout << db.queues[name].pop() << "\n"; db.saveToFile(filename); }
        else if (cmd == "TINSERT") { db.trees[name].insert(std::stoi(val)); db.saveToFile(filename); }
        else if (cmd == "TDEL") { db.trees[name].remove(std::stoi(val)); db.saveToFile(filename); }
        else if (cmd == "TGET") { std::cout << (db.trees[name].find(std::stoi(val)) ? "TRUE" : "FALSE") << "\n"; }
        
        else { std::cerr << "Unknown command\n"; }

    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}