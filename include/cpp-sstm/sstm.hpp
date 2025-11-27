#pragma once

#include <concepts>
#include <cstdint>
#include <expected>
#include <variant>

#include "transaction.hpp"
#include "tvar.hpp"

namespace cpp_sstm {

struct TransactionOptions {
  std::uint32_t max_read_var = 64;
  std::uint32_t max_write_var = 64;

  std::uint32_t auto_retries = std::numeric_limits<std::uint32_t>::max();
};

/// @concept TransactionCallback
/// @brief Ensures a type is a callable that can be invoked with a Transaction
/// lvalue reference.
///
/// This concept is used to constrain the callback parameter of
/// `execute_transaction`. It checks if a given type `C` can be called with a
/// `Transaction&` as its only argument.
template <typename C>
concept TransactionCallback = std::invocable<C, Transaction &>;

inline std::expected<void, TransactionError>
execute_transaction(TransactionCallback auto &&callback,
                    const TransactionOptions &options = TransactionOptions{}) {

  Transaction state{};
  // TODO: internal stack configuration

  std::uint32_t retries = 0;
  do {
    callback(state);

    auto &err = state.error();
    if (err.has_value()) {
      return std::unexpected(err.value());
    } else {
      return {};
    }
    retries += 1;
  } while (retries < options.auto_retries);

  return std::unexpected(RetryError{});
}

} // namespace cpp_sstm
