#pragma once

#include <string>
#include <unordered_map>

const std::unordered_map<std::string, int> ports = {
	{"FTL", 13},
	{"FBL", 0},
	{"FTR", 1},
	{"FBR", 2},
	{"RTL", 3},
	{"RBL", 4},
	{"RTR", 5},
	{"RBR", 6}
};
