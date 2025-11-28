/// @file tvar.hpp
/// @brief Defines the TVar class, a transactional variable for use in STM.
#pragma once

#include <cassert>
#include <cstdint>
#include <limits>
#include <mutex>
#include <shared_mutex>

#include "transaction.hpp"
#include "value_container.hpp"

namespace cpp_sstm {

/// @brief A constant representing an invalid TVar ID.
constexpr std::uint64_t invalid_id = std::numeric_limits<std::uint64_t>::max();

/// internal usage
std::uint64_t get_monotonic_value();

/// @class TVar
/// @brief A transactional variable (TVar) that encapsulates a value of type T.
///
/// TVars are the fundamental building blocks of the STM system. They manage
/// a value that can be read from and written to within a transaction.
/// The STM system ensures that all operations on TVars within a transaction
/// are atomic, consistent, and isolated.
///
/// @tparam T The type of the value to be stored.
template <typename T> class TVar {
public:
  /// @brief Constructs a new TVar with an initial value.
  /// @param value The initial value to store in the TVar.
  explicit TVar(T &&value)
      : versionning_(), value_(std::move(value)) {}

  /// @brief Deleted copy constructor. TVars cannot be copied.
  TVar(const TVar &value) = delete;

  /// @brief Move constructor.
  /// @param other The TVar to move from.
  /// @warning Moving a TVar during an associated transaction is undefined
  /// behaviour
  TVar(TVar &&other) noexcept = default;

  /// @brief Default destructor.
  ~TVar() = default;

  /// @brief Deleted copy assignment operator. TVars cannot be copied.
  TVar &operator=(const TVar &other) = delete;

  /// @brief Move assignment operator.
  /// @param other The TVar to move from.
  /// @return A reference to this TVar.
  /// @warning Moving a TVar during an associated transaction is undefined
  /// behaviour
  TVar &operator=(TVar &&other) noexcept = default;

  T read_unversioned() {
    std::shared_lock lock(versionning_.lock_);
    return value_;
  }

  T read(Transaction &ts) {
    assert(false);
    // TODO : implement
  }

  void write(Transaction &ts, T &&value) {
    assert(false);
    // TODO : implement
  }

private:
  /// @brief Versioning data for the TVar.
  LockedVersionning versionning_;

  /// @brief The actual value stored in the TVar.
  std::unique_ptr<ValueChain> value_;
};

} // namespace cpp_sstm
