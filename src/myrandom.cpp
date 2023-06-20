#include "myrandom.h"

// initialize
zinets::random::random() {
  // init random seed by reverse bit of time value
  this -> rand_seed = bitboard::rotate180(time(nullptr));
}

// algorithm of my prng function
std::uint64_t zinets::random::prng() {
  // using main of xorshift algorithm
  std::uint64_t x = this -> rand_seed;
  x ^= x << 13;
  x ^= x >> 7;
  x ^= x << 17;

  return this -> rand_seed = x;
}

std::uint64_t zinets::random::randint(std::uint64_t L, std::uint64_t R) {
  std::uint64_t val = this -> prng();

  return L + (val % (R - L + 1));
}