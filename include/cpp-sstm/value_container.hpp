#pragma once

#include <cstdint>
#include <memory>

namespace cpp_sstm {


template<typename T>
struct VValueContainer {
    std::uint32_t version;

    std::shared_ptr<const ValueContainer<T>> next;
    
    T value;
};


template<typename T>
struct ValueChain{
    std::uint64_t id() const{
        // compute a unique id for this value out of the memory address
        return static_cast<std::uint64_t>(this);
    }

    std::atomic<std::shared_ptr<const VValueContainer<T>>> head;
};

} // namespace cpp_sstm