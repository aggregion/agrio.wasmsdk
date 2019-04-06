#include <agrio/agrio.hpp>
#include <agrio/tester.hpp>

using namespace agrio::native;

AGRIO_TEST_BEGIN(print_test)
   silence_output(false);
   CHECK_PRINT("27", [](){ agrio::print((uint8_t)27); });
   CHECK_PRINT("34", [](){ agrio::print((int)34); });
   CHECK_PRINT([](std::string s){return s[0] == 'a';},  [](){ agrio::print((char)'a'); });
   CHECK_PRINT([](std::string s){return s[0] == 'b';},  [](){ agrio::print((int8_t)'b'); });
   CHECK_PRINT("202", [](){ agrio::print((unsigned int)202); });
   CHECK_PRINT("-202", [](){ agrio::print((int)-202); });
   CHECK_PRINT("707", [](){ agrio::print((unsigned long)707); });
   CHECK_PRINT("-707", [](){ agrio::print((long)-707); });
   CHECK_PRINT("909", [](){ agrio::print((unsigned long long)909); });
   CHECK_PRINT("-909", [](){ agrio::print((long long)-909); });
   CHECK_PRINT("404", [](){ agrio::print((uint32_t)404); });
   CHECK_PRINT("-404", [](){ agrio::print((int32_t)-404); });
   CHECK_PRINT("404000000", [](){ agrio::print((uint64_t)404000000); });
   CHECK_PRINT("-404000000", [](){ agrio::print((int64_t)-404000000); });
   CHECK_PRINT("0x0066000000000000", [](){ agrio::print((uint128_t)102); });
   CHECK_PRINT("0xffffff9affffffffffffffffffffffff", [](){ agrio::print((int128_t)-102); });
   silence_output(false);
AGRIO_TEST_END

int main(int argc, char** argv) {
   AGRIO_TEST(print_test);
   return has_failed();
}
