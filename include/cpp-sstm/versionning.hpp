#pragma once

#include <cstdint>
#include <shared_mutex>

namespace cpp_sstm {

/// internal usage
std::uint64_t get_monotonic_value();

struct Versionning {
  std::uint64_t version_ = 0;
  std::uint64_t id_ = get_monotonic_value();
};

struct LockedVersionning : Versionning {
  LockedVersionning() = default;
  LockedVersionning(const LockedVersionning & ) = delete;
  LockedVersionning(LockedVersionning && other ) noexcept : lock_(), Versionning(other) {
  }
  ~LockedVersionning() = default;

  LockedVersionning &operator=(const LockedVersionning & ) = delete;
  LockedVersionning &operator=(LockedVersionning && other){
    if(this != &other){
        static_cast<Versionning &>(*this) = static_cast<Versionning &>(other);
    }
    return *this;
  }


  std::shared_mutex lock_;
};


} // namespace cpp_sstm