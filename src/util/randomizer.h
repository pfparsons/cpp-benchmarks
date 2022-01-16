#ifndef MG_RANDOM_H
#define MG_RANDOM_H
#include <random>

namespace mg {

static auto uniform_rnd_int = []( auto lb, auto ub ) {
  static auto seed = std::random_device{};
  static auto prng = std::mt19937{ seed() };
  auto distribution = std::uniform_int_distribution<decltype( lb )>{ lb, ub };
  return distribution( prng );
};

}

#endif // MG_RANDOM_H
