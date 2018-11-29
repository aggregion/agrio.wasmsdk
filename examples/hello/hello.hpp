#include <agriolib/agrio.hpp>

using namespace agrio;

CONTRACT hello : public agrio::contract {
  public:
      using contract::contract;

      ACTION hi( name user );

      // accessor for external contracts to easily send inline actions to your contract
      using hi_action = action_wrapper<"hi"_n, &hello::hi>;
};
