#ifndef CPP_BENCHMARKS_TEST_FILE_H
#define CPP_BENCHMARKS_TEST_FILE_H
#include "catch2/catch_all.hpp"
#include "fmt/core.h"
#include "spdlog/spdlog.h"
#include "util/fake_data.h"
#include <filesystem>
#include <string>

TEST_CASE( "basic file test", "" ) {
  // **************************************
  // Arrange
  //  const std::filesystem::path test_file("/Users/pparsons/data/tpc-h/lineitem.tbl");
  //
  //  mg::File file(test_file);
  //
  //  auto sz_res = file.GetSize();
  //  CHECK(sz_res.has_value() );
  //  size_t size = sz_res.value();
  //  std::string mesg = test_file.string();
  //  spdlog::info("File: Size: {}", size );

  const std::string first_names_file = "../test/data/first_names.txt";

  spdlog::info( "CWD: {} ", std::filesystem::current_path().string() );
  auto res = mg::fake::load_vector( first_names_file );
  if ( res.has_value() ) {
    spdlog::info("line 20 {}", res.value()[20]);
    spdlog::info("line 21 {}", res.value()[21]);
    spdlog::info("line 29 {}", res.value()[29]);
    spdlog::info("line 31 {}", res.value()[31]);
    for ( const auto& name : mg::fake::Next(res.value(), 5 ) ) {
      spdlog::info( "Name: {}", name );
    }
  } else {
    spdlog::error( "Could not open file" );
  }

  auto fn_res = mg::fake::FakeArray::FromFile(first_names_file);
  CHECK( fn_res.has_value() );

  for(auto name : fn_res.value().Get(10)) {
    spdlog::info("  Fake Name: {}", name);
  }
}
#endif // CPP_BENCHMARKS_TEST_FILE_H
