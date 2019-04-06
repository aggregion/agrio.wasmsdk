/**
 *  @file
 *  @copyright defined in agrio.cdt/LICENSE.txt
 */

#include <agrio/tester.hpp>
#include <agrio/crypto.hpp>

using agrio::public_key;
using agrio::signature;

// Definitions in `agrio.cdt/libraries/agrio/crypto.hpp`
AGRIO_TEST_BEGIN(public_key_type_test)
   silence_output(true);

   // -----------------------------------------------------
   // bool operator==(const public_key&, const public_key&)
   CHECK_EQUAL( (public_key{0, std::array<char, 33>{}}  == public_key{0, std::array<char, 33>{}}), true  )
   CHECK_EQUAL( (public_key{0, std::array<char, 33>{1}} == public_key{0, std::array<char, 33>{}}), false )

   // -----------------------------------------------------
   // bool operator!=(const public_key&, const public_key&)
   CHECK_EQUAL( (public_key{0, std::array<char, 33>{}}  != public_key{0, std::array<char, 33>{}}), false )
   CHECK_EQUAL( (public_key{0, std::array<char, 33>{1}} != public_key{0, std::array<char, 33>{}}), true  )
   
   silence_output(false);
AGRIO_TEST_END

// Definitions in `agrio.cdt/libraries/agrio/crypto.hpp`
AGRIO_TEST_BEGIN(signature_type_test)
   silence_output(true);

   // ---------------------------------------------------
   // bool operator==(const signature&, const signature&)
   CHECK_EQUAL( (signature{0, std::array<char, 65>{}}  == signature{0, std::array<char, 65>{}}), true  )
   CHECK_EQUAL( (signature{0, std::array<char, 65>{1}} == signature{0, std::array<char, 65>{}}), false )

   // ---------------------------------------------------
   // bool operator!=(const signature&, const signature&)
   CHECK_EQUAL( (signature{0, std::array<char, 65>{1}} != signature{0, std::array<char, 65>{}}), true  )
   CHECK_EQUAL( (signature{0, std::array<char, 65>{}}  != signature{0, std::array<char, 65>{}}), false )
   
   silence_output(false);
AGRIO_TEST_END

int main(int argc, char* argv[]) {
   AGRIO_TEST(public_key_type_test)
   AGRIO_TEST(signature_type_test)
   return has_failed();
}
