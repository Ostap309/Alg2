#pragma once
#include <vector>
#include <sstream>
template<class T>
class Command {
public:
    Command(const std::string &name, const T& arg) : command_name_(name), arg_(arg) {}
private:
    std::string command_name_;
    T arg_;
};
class Parser {
public:
    friend class Emulator;
    Parser() = default;
    Parser(const std::string &in);
    std::string GetCommand(size_t line);
    size_t GetSize() const;
    size_t FindLabel(const std::string &label) const;
    template<class T>
    std::pair<std::string, T> GetLine(size_t line) {
        std::stringstream ss(list_[line]);
        std::string com;
        ss >> com;
        T arg;
        ss >> arg;
        return std::make_pair(com, arg);
    }
    template<class T>
    T GetArgument(size_t line) {
        std::stringstream ss(list_[line]);
        std::string com;
        ss >> com;
        T arg;
        ss >> arg;
        return arg;
    }
private:
    std::vector<std::string> list_;
};