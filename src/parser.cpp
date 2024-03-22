#include "../include/parser.h"
#include <string>
#include <algorithm>
Parser::Parser(const std::string &in) {
    std::stringstream ss(in);
    while (!ss.eof()) {
        std::string line;
        std::getline(ss, line);
        list_.push_back(line);
    }
}
size_t Parser::FindLabel(const std::string &label) const {
    return std::find(list_.begin(), list_.end(), label) - list_.begin();
}
std::string Parser::GetCommand(size_t line) {
    std::stringstream ss(list_[line]);
    std::string answer;
    ss >> answer;
    return answer;
}
size_t Parser::GetSize() const {
    return list_.size();
}

