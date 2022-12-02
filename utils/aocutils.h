#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> get_lines();
std::string strip_str(std::string str);
bool string_is_whitespace(std::string str);
std::vector<std::string> split_str(std::string inp, std::string delim, bool ignore_empty = false);