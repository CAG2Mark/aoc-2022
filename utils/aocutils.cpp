#include "aocutils.h"

std::vector<std::string> get_lines(std::string filename) {
    std::ifstream f(filename);
    std::string line;

    std::vector<std::string> ret;

    while (getline(f, line)) {
        ret.push_back(line);
    }

    return ret;
}

std::string strip_str(std::string str) {
    int i = 0;
    int j = str.length() - 1;
    for (; i < str.length() && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'); ++i);
    for (; j >= 0 && (str[j] == ' ' || str[j] == '\t' || str[j] == '\n'); --j);

    return str.substr(i, j - i + 1);
}

bool string_is_whitespace(std::string str) {
    return strip_str(str).length() == 0;
}

std::vector<std::string> split_str(std::string inp, std::string delim, bool ignore_empty) {
    std::vector<std::string> ret;

    int pos = 0;
    while (pos < inp.length()) {
        std::string token = inp.substr(pos, inp.find(delim, pos) - pos);

        if (!ignore_empty || !string_is_whitespace(token))
            ret.push_back(token);

        pos += token.length() + delim.length();
    }
    return ret;
}
