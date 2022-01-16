#include <neo/buffer_sink.hpp>

#include <neo/buffers_consumer.hpp>

#include <neo/test_concept.hpp>

#include <catch2/catch_all.hpp>

NEO_TEST_CONCEPT(neo::buffer_sink<neo::proto_buffer_sink>);

NEO_TEST_CONCEPT(neo::buffer_sink<neo::buffers_consumer<neo::mutable_buffer>>);
NEO_TEST_CONCEPT(neo::buffer_sink<neo::buffers_consumer<neo::proto_mutable_buffer_range>>);
