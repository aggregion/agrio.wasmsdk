#include <agrio/agrio.hpp>
#include <agrio/transaction.hpp>

#include "transfer.hpp" 

using namespace agrio;

class [[agrio::contract]] simple_tests : public contract {
   public:
      using contract::contract;

      [[agrio::action]] 
      void test1(name nm) {
         check(nm == "bucky"_n, "not bucky");
      }

      [[agrio::action]] 
      void test2(int arg0, std::string arg1) {
         check(arg0 == 33, "33 does not match");
         check(arg1 == "some string", "some string does not match");
      }

      [[agrio::action("test4")]] 
      void test4(name to) {
         transfer_contract::transfer_action trans("agrio.token"_n, {_self, "active"_n});
         trans.send(_self, to, asset{100, {"TST", 4}}, "memo");
      }

      [[agrio::action]] 
      void test5(name to) {
         transfer_contract::transfer_action trans("someone"_n, {_self, "active"_n});
         trans.send(_self, to, asset{100, {"TST", 4}}, "memo");
      }

      [[agrio::action]] 
      void testa(name to) {
         transfer_contract::transfer2_action trans("someone"_n, {_self, "active"_n});
         trans.send(_self, to, asset{100, {"TST", 4}}, "memo");
      }

      [[agrio::action]] 
      void testb(name to) {
         transfer_contract::transfer3_action trans("someone"_n, {_self, "active"_n});
         trans.send(_self, to, asset{100, {"TST", 4}}, "memo");
      }

      [[agrio::action]] 
      void testc(name nm) {
         check(nm == "bucky"_n, "should be bucky");
      }

      [[agrio::action]] 
      void testd(name nm) {
         transaction t;
         action act;
         act.account = "other"_n;
         act.name    = "testc"_n;
         act.authorization = {permission_level{get_self(), "active"_n}};
         std::vector<char> data = pack(nm);
         t.actions.push_back(act);
         t.send(nm.value, get_self());
      }

      [[agrio::on_notify("agrio.token::transfer")]] 
      void on_transfer(name from, name to, asset quant, std::string memo) {
         check(get_first_receiver() == "agrio.token"_n, "should be agrio.token");
         print_f("On notify : % % % %", from, to, quant, memo);
      }

      [[agrio::on_notify("*::transfer")]] 
      void on_transfer2(name from, name to, asset quant, std::string memo) {
         check(get_first_receiver() != "agrio.token"_n, "should not be agrio.token");
         print_f("On notify 2 : % % % %", from, to, quant, memo);
      }

      [[agrio::on_notify("*::transfer2")]] 
      void on_transfer3(name from, name to, asset quant, std::string memo) {
         print_f("On notify 3 : % % % %", from, to, quant, memo);
      }
};

extern "C" bool pre_dispatch(name self, name original_receiver, name action) {
   print_f("pre_dispatch : % % %\n", self, original_receiver, action);
   name nm;
   read_action_data((char*)&nm, sizeof(nm));
   if (nm == "quit"_n) {
      return false;
   }
   return true;
}

extern "C" void post_dispatch(name self, name original_receiver, name action) {
   print_f("post_dispatch : % % %\n", self, original_receiver, action);
   std::set<name> valid_actions = {"test1"_n, "test2"_n, "test4"_n, "test5"_n};
   check(valid_actions.count(action) == 0, "valid action should have dispatched");
   check(self == "agrio"_n, "should only be agrio for action failures");
}
