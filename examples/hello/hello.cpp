#include "hello.hpp"
using namespace agrio;

ACTION hello::hi( name user ) {
   print_f( "Hello % from hello", user );
}

AGRIO_DISPATCH( hello, (hi) )
