#ifndef zinets_rand_h
#define zinets_rand_h

#include "bit.h"

#include <ctime>
#include <cstdint> // for std::uint64_t

namespace zinets {
  class random {
  private:
    std::uint64_t rand_seed = 0;
  public:
    // prevent the pseudo number generator

    // initialize function
    random();

    // psuedo number generator function
    std::uint64_t prng();

    std::uint64_t randint(std::uint64_t L, std::uint64_t R); // random in range from [L, R] using pre-defined prng
  };
}

#endif