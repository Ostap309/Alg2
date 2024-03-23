#include "../include/emulator.h"


//const std::array<std::string, 3> Emulator::commands = {"END", "PUSH", "POP"};


void Emulator::Execute(std::istream &in, std::ostream &out) {
    std::string command = parser_.GetCommand(line);
    if (command == "BEGIN") {
        Begin();
        return;
    }
    if (!start_) {
        return;
    }
    /*
    switch (std::find(commands.begin(), commands.end(), command) - commands.begin()) {
        case 0: End(); break; //
        case 1: Push(parser_.GetArgument<float>(line)); break;
        case 2: Pop(); break;
        case 3: PushR(parser_.GetArgument<std::string>(line)); break;
        case 4: PopR(parser_.GetArgument<std::string>(line)); break;
        case 5: Add(); break;

    }
    */

    if (command == "END") {
        End();
    } else if (command == "PUSH") {
        float value0 = parser_.GetArgument<float>(line);
        Push(value0);
    } else if (command == "POP") {
        Pop();
    } else if (command == "PUSHR") {
        std::string reg0 = parser_.GetArgument<std::string>(line);
        PushR(reg0);
    } else if (command == "POPR") {
        std::string reg0 = parser_.GetArgument<std::string>(line);
        PopR(reg0);
    } else if (command == "ADD") {
        Add();
    } else if (command == "SUB") {
        Sub();
    } else if (command == "MUL") {
        Mul();
    } else if (command == "DIV") {
        Div();
    } else if (command == "OUT") {
        Out(out);
    } else if (command == "IN") {
        In(in);
    } else if (command == "JMP") {
        auto label = parser_.GetArgument<std::string>(line);
        Jmp(label);
    } else if (command == "JEQ") {
        std::string label = parser_.GetArgument<std::string>(line);
        Jeq(label);
    } else if (command == "JNE") {
        std::string label = parser_.GetArgument<std::string>(line);
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

void Emulator::Out(std::ostream &out) {
    out << stack_.Top() << "\n";
    last_out = std::to_string(stack_.Top());
}

void Emulator::In(std::istream &in) {
    ValueType x;
    in >> x;
    std::cout << "x = " << x << "\n";
    stack_.Push(x);
}

void Emulator::Run(const std::string &code, std::istream &in, std::ostream &out) {
    reg_.clear();
    stack_.Clear();
    stack_calls_.Clear();
    parser_ = Parser(code);
    line = parser_.FindLabel("BEGIN");
    start_ = true;
    while (start_ && line < parser_.GetSize()) {
        Execute(in, out);
        line++;
    }
}

void Emulator::Jmp(const std::string &label) {
    line = parser_.FindLabel(label);
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


class CommandWrap {
public:
    virtual void Execute(Emulator* em);
    template<class T>
    static T GetLineArg(Emulator* em) {
        return em->parser_.GetArgument<T>(em->line);
    }
};

class CommandPush : public CommandWrap {
public:
    void Execute(Emulator* em) {
        float value = GetLineArg<float>(em);
        em->stack_.Push(value);
    }
};

class CommandPop : public CommandWrap {
public:
    void Execute(Emulator* em) {
        if (em->stack_.Empty()) {
            return;
        }
        em->stack_.Pop();
    }
};


class CommandPushR : public CommandWrap {
public:
    void Execute(Emulator* em) {
        std::string reg0 = GetLineArg<std::string>(em);
        em->stack_.Push(em->reg_[reg0]);
    }
};

class CommandPopR : public CommandWrap {
public:
    void Execute(Emulator* em) {
        std::string reg0 = GetLineArg<std::string>(em);
        em->reg_[reg0] = em->stack_.Top();
        em->stack_.Pop();

    }
};

class CommandAdd : public CommandWrap {
public:
    void Execute(Emulator* em) {
        ValueType value0 = em->stack_.Top(), value1;
        em->stack_.Pop();
        value1 = em->stack_.Top();
        em->stack_.Push(value0);
        em->stack_.Push(value0 + value1);
    }
};

class CommandSub : public CommandWrap {
public:
    void Execute(Emulator* em) {
        ValueType value0 = em->stack_.Top(), value1;
        em->stack_.Pop();
        value1 = em->stack_.Top();
        em->stack_.Push(value0);
        em->stack_.Push(value0 - value1);
    }
};

class CommandMul : public CommandWrap {
public:
    void Execute(Emulator* em) {
        ValueType value0 = em->stack_.Top(), value1;
        em->stack_.Pop();
        value1 = em->stack_.Top();
        em->stack_.Push(value0);
        em->stack_.Push(value0 * value1);
    }
};

class CommandDiv : public CommandWrap {
public:
    void Execute(Emulator* em) {
        ValueType value0 = em->stack_.Top(), value1;
        em->stack_.Pop();
        value1 = em->stack_.Top();
        em->stack_.Push(value0);
        em->stack_.Push(value0 / value1);
    }
};

class CommandOut : public CommandWrap {
public:
    void Execute(Emulator* em) {
        std::ostream out = 
        // ...
    }
};

class CommandIn : public CommandWrap {
public:
    void Execute(Emulator* em) {
        // ...
    }
};

//...