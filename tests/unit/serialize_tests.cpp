/**
 *  @file
 *  @copyright defined in agrio.cdt/LICENSE.txt
 */

#include <algorithm>
#include <list>
#include <string>
#include <tuple>
#include <vector>

#include <agrio/tester.hpp>
#include <agrio/datastream.hpp>
#include <agrio/serialize.hpp>

using std::begin;
using std::end;
using std::fill;
using std::list;
using std::string;
using std::tie;
using std::vector;

using agrio::datastream;

struct B {
   const char c{};
   AGRLIB_SERIALIZE( B, (c) )

   friend bool operator==(const B& lhs, const B& rhs) {
         return lhs.c == rhs.c;
   }
};

struct D1 : public B {
   const int i{};
   AGRLIB_SERIALIZE_DERIVED( D1, B, (i) )

   friend bool operator==(const D1& lhs, const D1& rhs) {
      return tie(lhs.c, lhs.i) == tie(rhs.c, rhs.i);
   }
};

struct D2 : public D1 {
   const vector<double> v{};
   AGRLIB_SERIALIZE_DERIVED( D2, D1, (v) )

   friend bool operator==(const D2& lhs, const D2& rhs) {
      return tie(lhs.c, lhs.i, lhs.v) == tie(rhs.c, rhs.i, rhs.v);
   }
};

// Definitions in `agrio.cdt/libraries/agrio/serialize.hpp`
AGRIO_TEST_BEGIN(serialize_test)
   silence_output(true);

   static constexpr uint16_t buffer_size{256};
   char ds_buffer[buffer_size]{}; // Buffer for the datastream to point to
   char ds_expected_buffer[buffer_size]{}; // Buffer to compare `ds_buffer` with
   datastream<const char*> ds{ds_buffer, buffer_size};
   datastream<const char*> ds_expected{ds_expected_buffer, buffer_size};

   // Testing base structures
   static constexpr B b{'c'};
   B bb;
   ds_expected << b.c;
   ds << b;
   REQUIRE_EQUAL( memcmp( ds_buffer, ds_expected_buffer, 256), 0 )
   ds.seekp(0);
   ds >> bb;
   REQUIRE_EQUAL( b, bb )

   ds.seekp(0); // Clear all buffers
   fill(begin(ds_buffer), end(ds_buffer), 0);
   ds_expected.seekp(0);
   fill(begin(ds_expected_buffer), end(ds_expected_buffer), 0);

   // Testing derived structures
   static constexpr D1 d1{'c', 42};
   D1 dd1;
   ds_expected << d1.c << d1.i;
   ds << d1;
   REQUIRE_EQUAL( memcmp( ds_buffer, ds_expected_buffer, 256), 0 )
   
   ds.seekp(0);
   ds >> dd1;
   REQUIRE_EQUAL( d1, dd1 )

   ds.seekp(0); // Clear all buffers
   fill(begin(ds_buffer), end(ds_buffer), 0);
   ds_expected.seekp(0);
   fill(begin(ds_expected_buffer), end(ds_expected_buffer), 0);

   // Testing multiple layers of derived structures
   static const D2 d2{'c', 42, {1.1, 2.2}};
   D1 dd2;
   ds_expected << d2.c << d2.i << d2.v;
   ds << d2;
   REQUIRE_EQUAL( memcmp( ds_buffer, ds_expected_buffer, 256), 0 )
   
   ds.seekp(0);
   ds >> dd2;
   REQUIRE_EQUAL( d2, dd2 )
   
   silence_output(false);
AGRIO_TEST_END

int main(int argc, char* argv[]) {
   AGRIO_TEST(serialize_test)
   return has_failed();
}
