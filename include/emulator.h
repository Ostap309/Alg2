#pragma once
#include "stack.h"
#include "parser.h"
#include <map>
#include <iostream>
#include <fstream>
class Emulator {
public:
    void Run(const std::string &code, std::istream &in, std::ostream &out);
    ~Emulator();
    std::string last_out;
private:
    friend class CommandWrap;
    void Execute(std::istream &, std::ostream &);
    using ValueType = int;
    void Begin();
    void End();
    void Push(int value0);
    void Pop();
    void PushR(const std::string &reg0);
    void PopR(const std::string &reg0);
    void Add();
    void Sub();
    void Mul();
    void Div();
    void Out(std::ostream &);
    void In(std::istream &);
    void Jmp(const std::string &label);
    void Jeq(const std::string &label);
    void Jne(const std::string &label);
    void Call(const std::string &label);
    void Ret();

    Stack<ValueType> stack_;
    std::map<std::string, ValueType> reg_;
    Parser parser_;
    bool start_ = false;
    size_t line;
    Stack<size_t> stack_calls_;
    const static std::array<std::string, 3> commands;
};