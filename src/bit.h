#pragma once

#ifndef zinets_bit_h
#define zinets_bit_h

#include <cstdint>
#include <cstring>
#include <string>

#define get_bit(bitboard, idx) ( bitboard & ( 1ULL << idx ) )
#define set_bit(bitboard, idx) ( bitboard |= ( 1ULL << idx ) )
#define pop_bit(bitboard, idx) ( get_bit(bitboard, idx) ? bitboard ^= (1ULL << idx) : 0 )

#define is_alpha(x) ( ('a' <= x && x <= 'z') || ('A' <= x && x <= 'Z') )
#define is_digit(x) ( '0' <= x && x <= '9' )
#define in_range(x, a, b) ( a <= x && x <= b )

// bitboard utility

// define some constant that can use bitboard efficiently
const std::uint64_t NOT_A_FILE  = 18374403900871474942ULL;
const std::uint64_t NOT_H_FILE  = 9187201950435737471ULL;
const std::uint64_t NOT_HG_FILE = 4557430888798830399ULL;
const std::uint64_t NOT_AB_FILE = 18229723555195321596ULL;
const std::uint64_t NOT_E       = 0xFEFEFEFEFEFEFEFEULL;
const std::uint64_t NOT_W       = 0x7F7F7F7F7F7F7F7FULL;

// define square position on number
enum {
  a8, b8, c8, d8, e8, f8, g8, h8,
  a7, b7, c7, d7, e7, f7, g7, h7,
  a6, b6, c6, d6, e6, f6, g6, h6,
  a5, b5, c5, d5, e5, f5, g5, h5,
  a4, b4, c4, d4, e4, f4, g4, h4,
  a3, b3, c3, d3, e3, f3, g3, h3,
  a2, b2, c2, d2, e2, f2, g2, h2,
  a1, b1, c1, d1, e1, f1, g1, h1, no_sq
};

const std::string sq_ascii[65] = {
  "A8", "B8", "C8", "D8", "E8", "F8", "G8", "H8",
  "A7", "B7", "C7", "D7", "E7", "F7", "G7", "H7",
  "A6", "B6", "C6", "D6", "E6", "F6", "G6", "H6",
  "A5", "B5", "C5", "D5", "E5", "F5", "G5", "H5",
  "A4", "B4", "C4", "D4", "E4", "F4", "G4", "H4",
  "A3", "B3", "C3", "D3", "E3", "F3", "G3", "H3",
  "A2", "B2", "C2", "D2", "E2", "F2", "G2", "H2",
  "A1", "B1", "C1", "D1", "E1", "F1", "G1", "H1", "-"
};

enum { black, white, both_side, game_done }; // side to move

enum { OTHELLO, REVERSI }; // rule

const std::string piece_ascii = "XO";

namespace bitboard {
  int popcount(std::uint64_t x);
  int ls1b(std::uint64_t x);

  // rotate bitboard
  std::uint64_t rotate180(std::uint64_t x);
}

#endif
