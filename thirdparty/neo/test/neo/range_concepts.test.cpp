#include "neo/range_concepts.hpp"

#include "neo/test_concept.hpp"

#include <string>
#include <vector>

NEO_TEST_CONCEPT(neo::ranges::input_range<std::vector<int>>);
NEO_TEST_CONCEPT(neo::ranges::input_range<std::string>);
NEO_TEST_CONCEPT(neo::ranges::random_access_range<std::string>);
