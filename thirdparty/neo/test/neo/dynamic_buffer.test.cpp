#include <catch2/catch_all.hpp>

#include <neo/dynamic_buffer.hpp>

#include <neo/test_concept.hpp>

NEO_TEST_CONCEPT(neo::dynamic_buffer<neo::proto_dynamic_buffer>);
