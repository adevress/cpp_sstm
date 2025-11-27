/// @file transaction.hpp
/// @brief Defines the Transaction class, which represents the state of an STM
/// transaction.
#pragma once

#include <expected>
#include <optional>
#include <variant>

namespace cpp_sstm {

// Errors
struct RetryError {};
struct AbortError {};
struct TooManyValueError {};

using TransactionError =
    std::variant<RetryError, AbortError, TooManyValueError>;

/// @class Transaction
/// @brief Represents the state of a Software Transactional Memory (STM)
/// transaction. An instance of this class is passed to the transaction
/// callback.
class Transaction {
public:
  Transaction();
  ~Transaction() = default;

  Transaction(const Transaction &) = delete;
  Transaction(Transaction &&) = delete;
  Transaction &operator=(const Transaction &) = delete;
  Transaction &operator=(Transaction &&) = delete;

  inline std::optional<TransactionError> &error() { return erropt_; }

private:
  std::optional<TransactionError> erropt_;
};

} // namespace cpp_sstm