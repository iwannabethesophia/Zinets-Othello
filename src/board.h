#ifndef zinets_board_h
#define zinets_board_h

#include "bit.h"
#include "myrandom.h"

#include <iostream>
#include <vector>
#include <cstring>

namespace zinets {
  class move_history {
  public:

    std::uint64_t black;
    std::uint64_t white;
    std::uint64_t adj;
    int move;
    int turn;

    move_history();
  };

  class board {
  public:
    // support for fast zobrist
    random rand;

    std::uint64_t hash_table[2]; // hash table for black and white
    std::uint64_t zobrist_key; // zobrist hashing key

    // game state core
    std::vector<move_history> history;

    std::uint64_t bitboard[2];
    std::uint64_t adjacent_table[64];
    std::uint64_t adj_bitboard = 0x3c24243c0000ULL; // adjacent bitboard

    // in reversi rule both have explicit 30 disc to play
    short reversi_remain[2];

    short rule = OTHELLO; // set the default rule to othello
    short turn = black; // set the default turn is black

    std::uint64_t valid_move; // current valid move under bitboard

    board();

    bool make_move(std::string move);
    bool make_move(std::uint8_t move);
    bool undo_move();

    bool make_pass();

    std::vector<std::uint8_t> generate_move();

    #ifdef DEBUG
    void stats();
    #endif
  };
}

#endif
