/**
 *  @file
 *  @copyright defined in agrio.cdt/LICENSE.txt
 */

#include <agrio/agrio.hpp>
#include <agrio/rope.hpp>
#include <agrio/tester.hpp>
#include <string>

using namespace agrio::native;

AGRIO_TEST_BEGIN(rope_test)
   silence_output(false);
   agrio::rope r("test string 0");
   r += ", test string 1";
   r += ", test string 2";
   r += ", test string 3";
   r += ", test string 4";
   r += ", test string 5";
   r += ", test string 6";
   r += ", test string 7";
   
   std::string s("test string 0");
   s += ", test string 1";
   s += ", test string 2";
   s += ", test string 3";
   s += ", test string 4";
   s += ", test string 5";
   s += ", test string 6";
   s += ", test string 7";

   agrio::rope r2 = r + agrio::rope("lhs") + agrio::rope("rhs") + "some string";
   std::string s2 = s + std::string("lhs") + std::string("rhs") + "some string";

   r2 += agrio::rope("rvalue +=");
   s2 += std::string("rvalue +=");

   r2 = r2 + r2;   
   s2 = s2 + s2;

   r2 += "the end";
   s2 += "the end";
   
   agrio::rope r3(r2);
   std::string s3(s2);

   REQUIRE_EQUAL(s.compare(std::string(r.c_str())), 0);
   REQUIRE_EQUAL(s2.compare(std::string(r2.c_str())), 0);
   REQUIRE_EQUAL(s3.compare(std::string(r3.c_str())), 0);
   
   REQUIRE_EQUAL(s.length(),  r.length()); 
   REQUIRE_EQUAL(s2.length(), r2.length()); 
   REQUIRE_EQUAL(s3.length(), r3.length()); 
   
   for (int i=0; i < s.length(); i++) {
      REQUIRE_EQUAL(s[i], r[i]);
   }

   for (int i=0; i < s2.length(); i++) {
      REQUIRE_EQUAL(s2[i], r2[i]);
   }

   for (int i=0; i < s3.length(); i++) {
      REQUIRE_EQUAL(s3[i], r3[i]);
   }

   silence_output(false);
AGRIO_TEST_END

int main(int argc, char** argv) {
   AGRIO_TEST(rope_test);
   return has_failed();
}
