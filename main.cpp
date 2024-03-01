#include "stack.h"
#include <iostream>
int test_constructor() {
    {
        Stack<int> stack;
        if (!stack.Empty()) {
            return 1;
        }
        std::cout << "OK\n";
    }
    {
        Stack<int> stack({1, 2, 4});
        std::cout << "OK\n";
        Stack<int> stack2 = stack;
        std::cout << "OK\n";
        if (stack2.Size() != stack.Size()) {
            return 1;
        }
        std::cout << "OK\n";
        while (!stack.Empty()) {
            if (stack2.Top() != stack.Top()) {
                return 1;
            }
            stack.Pop();
            stack2.Pop();
        }
        std::cout << "OK\n";
    }
    {
        Stack<int> stack({1, 2, 4});
        Stack<int> stack2(stack);
        if (stack2.Size() != stack.Size()) {
            return 1;
        }
        while (!stack.Empty()) {
            if (stack2.Top() != stack.Top()) {
                return 1;
            }
            stack.Pop();
            stack2.Pop();
        }
    }
    return 0;
}
int test_change() {
    {
        Stack<int> stack;
        stack.Push(1);
        stack.Push(2);
        stack.Push(4);
        if (stack.Size() != 3 || stack.Top() != 4) {
            return 1;
        }
    }
    return 0;
}
int main() {
    if (test_constructor()) {
        return 1;
    }
    if (test_change()) {
        return 1;
    }
}