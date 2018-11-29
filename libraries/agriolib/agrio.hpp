/**
 *  @file
 *  @copyright defined in agr/LICENSE.txt
 */
#pragma once
#include <agriolib/action.hpp>
#include <agriolib/print.hpp>
#include <agriolib/multi_index.hpp>
#include <agriolib/dispatcher.hpp>
#include <agriolib/contract.hpp>

/**
 * Helper macros to reduce the verbosity for common contracts
 */
#define CONTRACT class [[agrio::contract]]
#define ACTION   [[agrio::action]] void
#define TABLE struct [[agrio::table]]
