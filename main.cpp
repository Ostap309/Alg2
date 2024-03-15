#include "emulator.h"
#include <fstream>
#include "googletest/googletest/include/gtest/gtest.h"
#include "googletest/googlemock/include/gmock/gmock.h"
void fibonachi(int n, Emulator& em) {
    std::string n_string = std::to_string(n);
    std::string code = "BEGIN\nPUSH ";
    code += n_string;
    code += "\n";
    code+= "POPR eax\n" // eax = n
                       "PUSH 2\n"
                       "POPR ecx\n" // ecx = 2
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
    em.Run(code);
}
TEST(Fibonachi, Subset1) {
    Emulator em;
    fibonachi(5, em);
    ASSERT_TRUE(em.last_out == "3");
}
TEST(Fibonachi, Subset2) {
    Emulator em;
    fibonachi(3, em);
    ASSERT_TRUE(em.last_out == "1");
}

int main(int argc, char** argv) { /// argc = 5, argv = ["./stack", "a", "b", "c", "d"]
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}