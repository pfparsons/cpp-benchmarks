#ifndef MG_FAKE_DATA_H
#define MG_FAKE_DATA_H
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iterator>
#include <locale>
#include <ranges>
#include <string>
#include <utility>
#include <vector>
#include <random>
#include<filesystem>
#include "spdlog/spdlog.h"
#include "fmt/core.h"
#include "tl/enumerate.hpp"
#include "tl/expected.hpp"
#include "tl/generator.hpp"
#include "tl/getlines.hpp"
#include "tl/to.hpp"
#include "type_safe/reference.hpp"

namespace mg::fake {

class FakeArray {
public:
  using container_t = std::vector<std::string>;
  using value_t = container_t::value_type;
  using vsize_t = container_t::size_type;

  explicit FakeArray(container_t data) noexcept : _data{std::move(data)} {}

  static tl::expected<FakeArray, std::string> FromFile(const std::string& filename) {
    std::string error_message;
    std::filesystem::path path{ filename };
    if ( std::filesystem::exists( path ) ) {
      auto input_stream = std::ifstream{ filename };
      if ( input_stream ) {
        auto data = tl::views::getlines(input_stream) | tl::to<std::vector>();
        input_stream.close();
        FakeArray result{ data };
        return result;
      }
    }
      return tl::make_unexpected(error_message);
  }

  [[nodiscard]] tl::generator<std::string> Get(int n = 1 ) {
    for ( auto i : Index( 0, _data.size() ) | std::views::take(n) ) {
      co_yield _data[i];
    }
  }

private:
  container_t _data;

  [[nodiscard]] static tl::generator<vsize_t> Index(vsize_t lower, vsize_t upper) {
    std::random_device seed{};
    std::mt19937 prng{ seed() };
    std::uniform_int_distribution<vsize_t> dist( lower, upper );
    while(true) {
      auto num = dist( prng );
      co_yield num;
    }
  }

};

static tl::expected<std::vector<std::string>, std::string>
load_vector( const std::string& filename ) {
  std::filesystem::path path{ filename };
  if ( std::filesystem::exists( path ) ) {
    auto input_stream = std::ifstream{ filename };
    if (input_stream) {
    std::vector<std::string> data;
    std::string str;
    while( std::getline(input_stream, str) ) {
      data.emplace_back(str);
    }
    input_stream.close();
    return data;
    }
  }
  return tl::make_unexpected( "Cannot read file" );
}
[[nodiscard]] tl::generator<int> Index(int lower, int upper) {
  std::random_device seed{};
  std::mt19937 prng{ seed() };
  std::uniform_int_distribution<int> dist( lower, upper );
  while(true) {
    auto num = dist( prng );
    co_yield num;
  }
}

[[nodiscard]] tl::generator<std::string> Next(std::vector<std::string>& data, int n = 1 ) {
  // | std::views::take( n )
  for ( auto i : Index( 0, 1000 ) | std::views::take(n) ) {
    co_yield data[i];
  }
}

} // namespace mg::fake

#endif // MG_FAKE_DATA_H
