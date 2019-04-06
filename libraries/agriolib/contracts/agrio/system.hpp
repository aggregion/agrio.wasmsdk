/**
 *  @file
 *  @copyright defined in agr/LICENSE
 */
#pragma once
#include "../../core/agrio/time.hpp"
#include "../../core/agrio/check.hpp"

namespace agrio {
  namespace internal_use_do_not_use {
    extern "C" {
      __attribute__((agrio_wasm_import, noreturn))
      void agrio_exit( int32_t code );
    }
  }

  /**
   *  @addtogroup system System
   *  @ingroup contracts
   *  @brief Defines time related functions and agrio_exit
   */

   /**
    *  This method will abort execution of wasm without failing the contract. This is used to bypass all cleanup / destructors that would normally be called.
    *
    *  @ingroup system
    *  @param code - the exit code
    *  Example:
    *
    *  @code
    *  agrio_exit(0);
    *  agrio_exit(1);
    *  agrio_exit(2);
    *  agrio_exit(3);
    *  @endcode
    */
   inline void agrio_exit( int32_t code ) {
     internal_use_do_not_use::agrio_exit(code);
   }

   /**
   *  Returns the time in microseconds from 1970 of the current block as a time_point
   *
   *  @ingroup system
   *  @return time in microseconds from 1970 of the current block as a time_point
   */
   time_point current_time_point();

   /**
   *  Returns the time in microseconds from 1970 of the current block as a block_timestamp
   *
   *  @ingroup system
   *  @return time in microseconds from 1970 of the current block as a block_timestamp
   */
   block_timestamp current_block_time();
}
