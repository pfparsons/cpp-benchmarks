#ifndef CPP_BENCHMARKS_FILE_H
#define CPP_BENCHMARKS_FILE_H

#include "fmt/core.h"
#include "tl/expected.hpp"
#include <cstddef>
#include <cstring>
#include <filesystem>

namespace mg {

class File {
public:
  explicit File( std::filesystem::path path ) noexcept : _path{ std::move( path ) } {}

  [[nodiscard]] tl::expected<std::size_t, std::string> GetSize() const {
    std::error_code error_code;
    if ( std::filesystem::exists( _path, error_code ) ) {
      auto size = std::filesystem::file_size( _path );
      return size;
    }
    return tl::make_unexpected( fmt::format( "Error getting file size for {}: {}",
                                             _path.string(), error_code.message() ) );
  }

private:
  std::filesystem::path _path;
};

} // namespace mg
#endif // CPP_BENCHMARKS_FILE_H
