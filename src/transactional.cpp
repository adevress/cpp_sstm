#include <cpp-sstm/sstm.hpp>

#include <atomic>

namespace cpp_sstm {


std::uint64_t get_monotonic_value(){
    static std::atomic<std::uint64_t> value = 1;
    return value.fetch_add(1);
}


} // namespace cpp_sstm
