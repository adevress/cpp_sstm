#pragma once

#include <expected>
#include <variant>
#include <cstdint>


#include "tvar.hpp"

namespace cpp_sstm{

class Transaction{

public:
    Transaction() = default;
    ~Transaction() = default;

    Transaction(const Transaction &) = delete;
    Transaction(Transaction &&) = delete;

    Transaction & operator=(const Transaction &) = delete;
    Transaction & operator=(Transaction &&) = delete;

};

struct RetryError{};
struct AbortError{};
struct TooManyValueError{};

using TransactionError = std::variant<RetryError, AbortError, TooManyValueError>;

struct TransactionOptions{
    std::uint32_t max_read_var = 64;
    std::uint32_t max_write_var = 64;

    std::uint32_t auto_retries = std::numeric_limits<std::uint32_t>::max();
};


std::expected<void, TransactionError> execute_transaction(auto && callback, const TransactionOptions & options = TransactionOptions{}){
    
    Transaction state{};
    // TODO: internal stack configuration

    // TODO: Auto retry logic
    callback(state);

    return {};
}


} // namespace cpp_sstm
