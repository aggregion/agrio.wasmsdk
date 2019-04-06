/**
 *  @file
 *  @copyright defined in agr/LICENSE
 */
#pragma once
#include "action.hpp"
#include "print.hpp"
#include "multi_index.hpp"
#include "dispatcher.hpp"
#include "contract.hpp"

#warning "<agriolib/agrio.hpp> is deprecated use <agrio/agrio.hpp>"

#ifndef AGRIO_NATIVE
static_assert( sizeof(long) == sizeof(int), "unexpected size difference" );
#endif

/**
 * Helper macros to reduce the verbosity for common contracts
 */
#define CONTRACT class [[agrio::contract]]
#define ACTION   [[agrio::action]] void
#define TABLE struct [[agrio::table]]

/**
 * @defgroup core Core API
 * @brief C++ Core API for chain-agnostic smart-contract functionality
 */

 /**
  * @defgroup contracts Contracts API
  * @brief C++ Chain API for chain-dependent smart-contract functionality
  */

/**
 * @defgroup types Types
 * @brief TODO
 */
