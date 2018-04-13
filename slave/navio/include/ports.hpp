#ifndef PORTS_H
#define PORTS_H

#include <string>
#include <unordered_map>

const std::unordered_map<std::string, int> ports = {
    /*
    {"FTL", 13}
            {"FBL", 0},
            {"FTR", 1},
            {"FBR", 2},
            {"RTL", 3},
            {"RBL", 4},
            {"RTR", 5},
            {"RBR", 6}
    */
};

int ports_at(const std::string& key) {
    auto pair = ports.find(key);
    if (pair == ports.end()) {
        return -1;
    } else {
        return pair->second;
    }
}

#endif
