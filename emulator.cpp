#include "emulator.h"
void Emulator::Execute() {
        const std::string& command_line = history_[line];
        std::stringstream ss(command_line);
        std::string command;
        ss >> command;

        if (command == "BEGIN") {
            Begin();
            return;
        }

        if (!start_) {
            return;
        }

        if (command == "END") {
            End();
        }
        
        else if (command == "PUSH") {
            float value0;
            ss >> value0;
            Push(value0);
        }
        
        else if (command == "POP") {
            Pop();
        }
        
        else if (command == "PUSHR") {
            std::string reg0;
            ss >> reg0;
            PushR(reg0);
        }
        
        else if (command == "POPR") {
            std::string reg0;
            ss >> reg0;
            PopR(reg0);
        }
        
        else if (command == "ADD") {
            Add();
        }
        
        else if (command == "SUB") {
            Sub();
        }
        
        else if (command == "MUL") {
            Mul();
        }
        
        else if (command == "DIV") {
            Div();
        }
        
        else if (command == "OUT") {
            Out();
        }
        
        else if (command == "IN") {
            In();
        }
        
        else if (command == "JMP") {
            std::string label;
            ss >> label;
            Jmp(label);
        }
        
        else if (command == "JEQ") {
            std::string label;
            ss >> label;
            Jeq(label);
        }
        
        else if (command == "JNE") {
            std::string label;
            ss >> label;
            Jne(label);
        }
}
void Emulator::Begin() {
        start_ = true;
    }

    void Emulator::End() {
        start_ = false;
    }

    void Emulator::Push(ValueType value0) {
        stack_.Push(value0);
    }

    void Emulator::Pop() {
        if (stack_.Empty()) {
            return;
        }
        stack_.Pop();
    }

    void Emulator::PushR(const std::string &reg0) {
        stack_.Push(reg_[reg0]);
    }

    void Emulator::PopR(const std::string &reg0) {
        reg_[reg0] = stack_.Top();
        stack_.Pop();
    }

    void Emulator::Add() {
        ValueType value0 = stack_.Top(), value1;
        stack_.Pop();
        value1 = stack_.Top();
        stack_.Push(value0);
        stack_.Push(value0 + value1);
    }

    void Emulator::Sub() {
        ValueType value0 = stack_.Top(), value1;
        stack_.Pop();
        value1 = stack_.Top();
        stack_.Push(value0);
        stack_.Push(value0 - value1);
    }

    void Emulator::Mul() {
        ValueType value0 = stack_.Top(), value1;
        stack_.Pop();
        value1 = stack_.Top();
        stack_.Push(value0);
        stack_.Push(value0 * value1);
    }

    void Emulator::Div() {
        ValueType value0 = stack_.Top(), value1;
        stack_.Pop();
        value1 = stack_.Top();
        stack_.Push(value0);
        stack_.Push(value0 / value1);
    }

    void Emulator::Out() {
        std::cout << stack_.Top() << "\n";
        last_out = std::to_string(stack_.Top());
    }

    void Emulator::In() {
        ValueType x;
        std::cin >> x;
        stack_.Push(x);
    }

    Emulator::~Emulator() {
        if (start_) {
            std::cout << "Emulator is still running!\n";
        }
    }

void Emulator::Run(const std::string &code) {
    std::string line_string;
    for (int i = 0; i < code.size(); ++i) {
        if (code[i] == '\n') {
            history_.push_back(line_string);
            line_string.clear();
            continue;
        }
        line_string += code[i];
    }
    line = std::find(history_.begin(), history_.end(), "BEGIN") - history_.begin();
    start_ = true;
    while (start_ && line < history_.size()) {
        Execute();
        line++;
    }
}

void Emulator::Jmp(const std::string& label) {
    auto it = std::find(history_.begin(), history_.end(), label);
    if (it == history_.end()) {
        std::cout << "No such label\n";
    }
    line = it - history_.begin();
}

void Emulator::Jeq(const std::string &label) {
    ValueType top_value = stack_.Top();
    stack_.Pop();
    ValueType second_value = stack_.Top();
    stack_.Push(top_value);
    if (top_value == second_value) {
        Jmp(label);
    }
}

void Emulator::Jne(const std::string &label) {
    ValueType top_value = stack_.Top();
    stack_.Pop();
    ValueType second_value = stack_.Top();
    stack_.Push(top_value);
    if (top_value != second_value) {
        Jmp(label);
    }
}

void Emulator::Call(const std::string &label) {
    stack_calls_.Push(line);
    Jmp(label);
}

void Emulator::Ret() {
    line = stack_calls_.Top();
    stack_calls_.Pop();
}