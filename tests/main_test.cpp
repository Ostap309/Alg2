#include "../include/emulator.h"
#include <istream>
#include <gtest/gtest.h>

//#include "../googletest/googletest/include/gtest/gtest.h"
//#include "../googletest/googlemock/include/gmock/gmock.h"
void fibonacci(int n, Emulator &em, std::ofstream &file_out) {
    std::stringstream ss;
    ss << n;
    std::string n_string = std::to_string(n);
    std::string code = "BEGIN\n"
                       "IN\n"
                       "POPR eax\n"
                       "PUSH 2\n"
                       "POPR ecx\n"
                       "PUSH 0\n"
                       "PUSH 1\n"

                       "PUSH 0\n"
                       "PUSH 0\n"

                       "LOOP\n"

                       "POP\n"
                       "POP\n"

                       "ADD\n"


                       "PUSH 1\n"
                       "PUSHR ecx\n"
                       "ADD\n"
                       "POPR ecx\n"
                       "POP\n"
                       "POP\n"


                       "PUSHR eax\n"
                       "PUSHR ecx\n"
                       "JNE LOOP\n"
                       "POP\n"
                       "POP\n"
                       "OUT\n"
                       "END\n";
    em.Run(code, ss, file_out);
}

TEST(Fibonachi, Subset1) {
    std::ofstream file_out("./output.txt");
    Emulator em;
    fibonacci(5, em, file_out);
    EXPECT_EQ(em.last_out, "3");
    fibonacci(3, em, file_out);
    EXPECT_EQ(em.last_out, "1");
}


TEST(Fibonachi, Subset2) {
    std::stringstream out;
    out << 4;
    Emulator em;
    std::string code = "BEGIN\nIN\nOUT\nEND\n";
    em.Run(code, out, std::cout);
}

TEST(StackTest, Subset1) {
    Stack<int> stack;
    ASSERT_TRUE(stack.Empty());
}

TEST(StackTest, Subset2) {
    Stack<int> stack({1, 2, 4});
    std::cout << "OK\n";
    Stack<int> stack2 = stack;
    std::cout << "OK\n";
    ASSERT_TRUE(stack2.Size() == stack.Size());
    std::cout << "OK\n";
    while (!stack.Empty()) {
        ASSERT_TRUE(stack2.Top() == stack.Top());
        stack.Pop();
        stack2.Pop();
    }
}

TEST(StackTest, Subset3) {
    Stack<int> stack({1, 2, 4});
    Stack<int> stack2(stack);
    ASSERT_TRUE(stack2.Size() == stack.Size());
    while (!stack.Empty()) {
        ASSERT_TRUE(stack2.Top() == stack.Top());
        stack.Pop();
        stack2.Pop();
    }
}

TEST(StackTest, Subset4) {
    Stack<int> stack;
    stack.Push(1);
    stack.Push(2);
    stack.Push(4);
    ASSERT_FALSE(stack.Size() != 3 || stack.Top() != 4);
}
