### Building your first smart contract
```c++
#include <agrio/agrio.hpp>
#include <agrio/name.hpp>

class [[agrio::contract]] hello : public agrio::contract {
   public:
      using agrio::contract::contract;

      [[agrio::action]]
      void hi(agrio::name nm) {
         agrio::print_f("Hello, %\n", nm);
      }
};
```

- Navigate to the hello folder in examples (./examples/hello).
- You should then see the hello.cpp file
- Now run the compiler
```sh
$ agrio-cpp -abigen hello.cpp -o hello.wasm
```
- Or with CMake
```sh
$ mkdir build
$ cd build
$ cmake ..
$ make
```
This will generate two files:
* The compiled binary wasm (hello.wasm)
* The generated ABI file (hello.abi)
