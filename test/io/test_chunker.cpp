#include "catch2/catch_all.hpp"
#include "io/chunker.h"
#include "spdlog/spdlog.h"

TEST_CASE( "basic chunker test", "" ) {

  // *********************************
  // Arrange
  const size_t chunk_size = 4096 << 10; // 1024 pages ~4.2MB
  const size_t file_size = 1520346495;
  const size_t num_chunks = file_size / chunk_size;
  const size_t expected_tail_length = mg::mod<chunk_size>( file_size );
  const size_t total_bytes_chunked = num_chunks * chunk_size + expected_tail_length;

  CHECK(total_bytes_chunked == file_size);

  // *********************************
  // Act
  size_t second_last_chunk_end = num_chunks * chunk_size;
  size_t last_chunk_end = second_last_chunk_end + expected_tail_length;

  // *********************************
  // Assert
  CHECK( last_chunk_end == file_size);
  CHECK( last_chunk_end - second_last_chunk_end == expected_tail_length);
}
