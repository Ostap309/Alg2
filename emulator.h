#include "stack.h"
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
class Emulator {
public:
    void Run(const std::string &code);
    void Execute();
    ~Emulator();
    std::string last_out;

private:
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
    void Out();
    void In();
    void Jmp(const std::string &label);
    void Jeq(const std::string &label);
    void Jne(const std::string &label);
    void Call(const std::string &label);
    void Ret();

    Stack<ValueType> stack_;
    std::map<std::string, ValueType> reg_;
    std::vector<std::string> history_;
    bool start_ = false;
    size_t line;
    Stack<size_t> stack_calls_;
};