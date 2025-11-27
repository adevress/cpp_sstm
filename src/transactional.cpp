#include <cpp-sstm/sstm.hpp>

#include <atomic>

#ifdef CPP_SSTM_TESTS
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#endif

namespace cpp_sstm {

std::uint64_t get_monotonic_value() {
  static std::atomic<std::uint64_t> value = 1;
  return value.fetch_add(1);
}

Transaction::Transaction() : erropt_(AbortError{}) {}

namespace test {

#ifdef CPP_SSTM_TESTS
TEST_CASE("Dummy test for get_monotonic_value") {
  cpp_sstm::get_monotonic_value(); // consume first value if it's 1
  auto val1 = cpp_sstm::get_monotonic_value();
  auto val2 = cpp_sstm::get_monotonic_value();
  CHECK(val2 != val1);
}

TEST_CASE("Test transaction abort") {
  TVar<std::uint64_t> counter1(0), counter2(1);

  auto res = cpp_sstm::execute_transaction([&](Transaction &state) {

  });
  CHECK(res.has_value() == false);
  CHECK(std::holds_alternative<cpp_sstm::AbortError>(res.error()));
}

#endif // CPP_SSTM_TESTS

} // namespace test

} // namespace cpp_sstm
