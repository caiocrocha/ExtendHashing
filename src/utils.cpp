#include <iostream>
#include <string>

#include "../include/utils.hpp"

size_t hash(const std::string& pseudoKey, size_t n)
{
	return std::strtoul(pseudoKey.substr(0, n).c_str(), nullptr, 2);
}
