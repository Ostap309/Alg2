#include "../include/emulator.h"
#include <istream>
#include "../googletest/googletest/include/gtest/gtest.h"
#include "../googletest/googlemock/include/gmock/gmock.h"
void fibonachi(int n, Emulator& em, std::ofstream &file_out) {
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
    file_out.close();
}
TEST(Fibonachi, Subset1) {
    std::ofstream file_out("./output.txt");
    Emulator em;
    fibonachi(5, em, file_out);
    ASSERT_TRUE(em.last_out == "3");
    fibonachi(3, em, file_out);
    ASSERT_TRUE(em.last_out == "1");
}
TEST(Fibonachi, Subset2) {
    std::stringstream out;
    out << 4;
    Emulator em;
    std::string code = "BEGIN\nIN\nOUT\nEND\n";
    em.Run(code, out, std::cout);
}