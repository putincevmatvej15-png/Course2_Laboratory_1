#include "Database.hpp"
#include "json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

void Database::saveToFile(const std::string& filename) {
    json j;
    for (auto const& [name, arr] : arrays) {
        json a = json::array();
        for (int i = 0; i < arr.length(); ++i) a.push_back(arr.get(i));
        j["array"][name] = a;
    }
    for (auto const& [name, list] : fLists) j["forward_list"][name] = list.getData();
    for (auto const& [name, list] : dLists) j["doubly_list"][name] = list.getData();
    for (auto const& [name, st] : stacks) {
        json a = json::array();
        for (int i = 0; i < st.length(); ++i) a.push_back(st.get(i));
        j["stack"][name] = a;
    }
    for (auto const& [name, q] : queues) {
        json a = json::array();
        for (int i = 0; i < q.length(); ++i) a.push_back(q.get(i));
        j["queue"][name] = a;
    }
    for (auto const& [name, t] : trees) j["tree"][name] = t.getData();

    std::ofstream f(filename);
    if (f.is_open()) { f << j.dump(4); f.close(); }
}

void Database::loadFromFile(const std::string& filename) {
    std::ifstream f(filename);
    if (!f.is_open()) return;
    try {
        json j; f >> j;
        if (j.contains("array")) for (auto& el : j["array"].items()) {
            std::vector<std::string> v = el.value().get<std::vector<std::string>>();
            arrays[el.key()].set_from_array(v.data(), v.size());
        }
        if (j.contains("forward_list")) for (auto& el : j["forward_list"].items()) fLists[el.key()].setData(el.value().get<std::vector<std::string>>());
        if (j.contains("doubly_list")) for (auto& el : j["doubly_list"].items()) dLists[el.key()].setData(el.value().get<std::vector<std::string>>());
        if (j.contains("stack")) for (auto& el : j["stack"].items()) {
            std::vector<std::string> v = el.value().get<std::vector<std::string>>();
            for (auto& s : v) stacks[el.key()].push(s);
        }
        if (j.contains("queue")) for (auto& el : j["queue"].items()) {
            std::vector<std::string> v = el.value().get<std::vector<std::string>>();
            for (auto& s : v) queues[el.key()].push(s);
        }
        if (j.contains("tree")) for (auto& el : j["tree"].items()) trees[el.key()].setData(el.value().get<std::vector<int>>());
    } catch (std::exception& e) { std::cerr << "Load error: " << e.what() << std::endl; }
    f.close();
}
