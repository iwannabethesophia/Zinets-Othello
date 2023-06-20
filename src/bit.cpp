#include "bit.h"

// population count algorithms
// https://www.chessprogramming.org/Population_Count
int bitboard::popcount (std::uint64_t x) {
  x =  x     - ((x >> 1)  & 0x5555555555555555ULL); /* put count of each 2 bits into those 2 bits */
  x = (x & 0x3333333333333333) + ((x >> 2)  & 0x3333333333333333ULL); /* put count of each 4 bits into those 4 bits */
  x = (x     +  (x >> 4)) & 0x0f0f0f0f0f0f0f0fULL; /* put count of each 8 bits into those 8 bits */
  x = (x * 0x0101010101010101ULL) >> 56; /* returns 8 most significant bits of x + (x<<8) + (x<<16) + (x<<24) + ... */
  return (int)x;
}

// bitscan by popcount
// https://www.chessprogramming.org/BitScan
int bitboard::ls1b(std::uint64_t x) {
  if ( x == 0 )
    return -1;

  return popcount( (x & -x) - 1 );
}

// rotate bitboard by 180 degree
std::uint64_t bitboard::rotate180(std::uint64_t x) {
  x = ((x >>  1) & 0x5555555555555555ULL) | ((x & 0x5555555555555555ULL) <<  1);
  x = ((x >>  2) & 0x3333333333333333ULL) | ((x & 0x3333333333333333ULL) <<  2);
  x = ((x >>  4) & 0x0F0F0F0F0F0F0F0FULL) | ((x & 0x0F0F0F0F0F0F0F0FULL) <<  4);
  x = ((x >>  8) & 0x00FF00FF00FF00FFULL) | ((x & 0x00FF00FF00FF00FFULL) <<  8);
  x = ((x >> 16) & 0x0000FFFF0000FFFFULL) | ((x & 0x0000FFFF0000FFFFULL) << 16);
  x = ( x >> 32)       | ( x       << 32);
  return x;
}