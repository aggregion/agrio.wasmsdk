#include <agriolib/agrio.hpp>

using namespace agrio;

/* you can use this method of declaration */
//class [[agrio::contract]] multi_index_example : public contract {
/* or this method of declaration if you don't want to use the c++ class name */
//class [[agrio::contract("<some contract name>")]] multi_index_example : public contract {
CONTRACT multi_index_example : public contract {
  public:
      using contract::contract;
      multi_index_example( name receiver, name code, datastream<const char*> ds )
         : contract(receiver, code, ds), testtab(receiver, receiver.value) {}

//      [[agrio::action]]
//      void set( name user ) {
      ACTION set(name user) {
         auto itr = testtab.find(user.value);
         if ( itr == testtab.end() ) {
            testtab.emplace( _self, [&]( auto& u ) {
                  u.test_primary = user;
                  u.secondary = "second"_n;
                  u.datum = 0;
            });
         }
      }
      
//      [[agrio::action]]
//      void print( name user ) {
      ACTION print( name user ) {
         auto itr = testtab.find(user.value);
         agrio_assert( itr != testtab.end(), "test table not set" );
         agrio::print_f("Test Table : {%, %, %}\n", itr->test_primary, itr->secondary, itr->datum);
      }

//      [[agrio::action]]
//      void bysec( name user ) {
      ACTION bysec( name secid ) {
         auto idx = testtab.get_index<"secid"_n>();
         for ( auto itr = idx.begin(); itr != idx.end(); itr++ ) {
            print( itr->test_primary );
         }
      }

//      [[agrio::action]]
//      void mod( name user, uint32_t n ) {
      ACTION mod( name user, uint32_t n ) {
         auto itr = testtab.find(user.value);
         agrio_assert( itr != testtab.end(), "test table not set" );
         testtab.modify( itr, _self, [&]( auto& row ) {
            row.secondary = user;
            row.datum = n;
         });
      }

//      struct [[agrio::table]] test_table {
      TABLE test_table {
         name test_primary;
         name secondary;
         uint64_t datum;
         uint64_t primary_key()const { return test_primary.value; }
         uint64_t by_secondary()const { return secondary.value; }
      };

      typedef agrio::multi_index<"testtaba"_n, test_table, agrio::indexed_by<"secid"_n, agrio::const_mem_fun<test_table, uint64_t, &test_table::by_secondary>>> test_tables;

      using set_action   = action_wrapper<"set"_n, &multi_index_example::set>;
      using print_action = action_wrapper<"print"_n, &multi_index_example::print>;
      using bysec_action = action_wrapper<"bysec"_n, &multi_index_example::bysec>;
      using mod_action   = action_wrapper<"mod"_n, &multi_index_example::mod>;
  private:
      test_tables testtab;
};

AGRIO_DISPATCH( multi_index_example, (set)(print)(mod)(bysec) )
