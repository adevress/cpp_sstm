/// @file tvar.hpp
/// @brief Defines the TVar class, a transactional variable for use in STM.
#pragma once

#include <cstdint>
#include <limits>
#include <mutex>
#include <shared_mutex>

#include "transaction.hpp"

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
      : lock_(), version_(0), id_(get_monotonic_value()),
        value_(std::move(value)) {}

  /// @brief Deleted copy constructor. TVars cannot be copied.
  TVar(const TVar &value) = delete;

  /// @brief Move constructor.
  /// @param other The TVar to move from.
  /// @warning Moving a TVar during an associated transaction is undefined
  /// behaviour
  TVar(TVar &&other) noexcept : lock_() {
    version_ = other.version_;
    id_ = other.id_;
    value_ = std::move(other.value_);

    // Invalidate the other TVar
    other.version_ = 0;
    other.id_ = invalid_id;
  }

  /// @brief Default destructor.
  ~TVar() = default;

  /// @brief Deleted copy assignment operator. TVars cannot be copied.
  TVar &operator=(const TVar &other) = delete;

  /// @brief Move assignment operator.
  /// @param other The TVar to move from.
  /// @return A reference to this TVar.
  /// @warning Moving a TVar during an associated transaction is undefined
  /// behaviour
  TVar &operator=(TVar &&other) noexcept {
    if (this != &other) {

      // move the data
      lock_ = {};
      version_ = other.version_;
      id_ = other.id_;
      value_ = std::move(other.value_);

      // Invalidate the other TVar
      other.version_ = 0;
      other.id_ = invalid_id;
    }
    return *this;
  }

  T read_unversionned() {
    std::shared_lock lock(lock_);
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
  /// @brief Mutex to protect access to the TVar's data.
  /// A shared_mutex is used to allow multiple concurrent readers.
  std::shared_mutex lock_;

  /// @brief The version number of the data. Incremented on each write.
  std::uint64_t version_;

  /// @brief A unique identifier for this TVar instance.
  std::uint64_t id_;

  /// @brief The actual value stored in the TVar.
  T value_;
};

} // namespace cpp_sstm
