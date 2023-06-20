#include "board.h"

std::uint64_t  SShift (std::uint64_t b) {return  b << 8;}
std::uint64_t  NShift (std::uint64_t b) {return  b >> 8;}
std::uint64_t  EShift (std::uint64_t b) {return (b << 1) & NOT_E;}
std::uint64_t SEShift (std::uint64_t b) {return (b << 9) & NOT_E;}
std::uint64_t NEShift (std::uint64_t b) {return (b >> 7) & NOT_E;}
std::uint64_t  WShift (std::uint64_t b) {return (b >> 1) & NOT_W;}
std::uint64_t SWShift (std::uint64_t b) {return (b << 7) & NOT_W;}
std::uint64_t NWShift (std::uint64_t b) {return (b >> 9) & NOT_W;}

// Dumb7Fill: http://chessprogramming.wikispaces.com/Dumb7Fill
std::uint64_t  SFill(std::uint64_t gen, std::uint64_t prop) {
    std::uint64_t flood = 0ULL;
    flood |= gen = (gen   << 8) & prop;
    flood |= gen = (gen   << 8) & prop;
    flood |= gen = (gen   << 8) & prop;
    flood |= gen = (gen   << 8) & prop;
    flood |= gen = (gen   << 8) & prop;
    flood |=       (gen   << 8) & prop;
    return flood;
}

std::uint64_t  NFill(std::uint64_t gen, std::uint64_t prop) {
    std::uint64_t flood = 0ULL;
    flood |= gen = (gen   >> 8) & prop;
    flood |= gen = (gen   >> 8) & prop;
    flood |= gen = (gen   >> 8) & prop;
    flood |= gen = (gen   >> 8) & prop;
    flood |= gen = (gen   >> 8) & prop;
    flood |=       (gen   >> 8) & prop;
    return flood;
}

std::uint64_t  EFill(std::uint64_t gen, std::uint64_t prop) {
    std::uint64_t flood = 0ULL;
    prop &= NOT_E;
    flood |= gen = (gen   << 1) & prop;
    flood |= gen = (gen   << 1) & prop;
    flood |= gen = (gen   << 1) & prop;
    flood |= gen = (gen   << 1) & prop;
    flood |= gen = (gen   << 1) & prop;
    flood |=       (gen   << 1) & prop;
    return                flood & NOT_E;
}

std::uint64_t NEFill(std::uint64_t gen, std::uint64_t prop) {
    std::uint64_t flood = 0ULL;
    prop &= NOT_E;
    flood |= gen = (gen   >> 7) & prop;
    flood |= gen = (gen   >> 7) & prop;
    flood |= gen = (gen   >> 7) & prop;
    flood |= gen = (gen   >> 7) & prop;
    flood |= gen = (gen   >> 7) & prop;
    flood |=       (gen   >> 7) & prop;
    return                flood & NOT_E;
}

// Dumb7Fill algorithm
std::uint64_t SEFill(std::uint64_t gen, std::uint64_t prop) {
    std::uint64_t flood = 0ULL;
    prop &= NOT_E;
    flood |= gen = (gen   << 9) & prop;
    flood |= gen = (gen   << 9) & prop;
    flood |= gen = (gen   << 9) & prop;
    flood |= gen = (gen   << 9) & prop;
    flood |= gen = (gen   << 9) & prop;
    flood |=       (gen   << 9) & prop;
    return                flood & NOT_E;
}

std::uint64_t  WFill(std::uint64_t gen, std::uint64_t prop) {
    std::uint64_t flood = 0ULL;
    prop &= NOT_W;
    flood |= gen = (gen   >> 1) & prop;
    flood |= gen = (gen   >> 1) & prop;
    flood |= gen = (gen   >> 1) & prop;
    flood |= gen = (gen   >> 1) & prop;
    flood |= gen = (gen   >> 1) & prop;
    flood |=       (gen   >> 1) & prop;
    return                flood & NOT_W;
}

std::uint64_t SWFill(std::uint64_t gen, std::uint64_t prop) {
    std::uint64_t flood = 0ULL;
    prop &= NOT_W;
    flood |= gen = (gen   << 7) & prop;
    flood |= gen = (gen   << 7) & prop;
    flood |= gen = (gen   << 7) & prop;
    flood |= gen = (gen   << 7) & prop;
    flood |= gen = (gen   << 7) & prop;
    flood |=       (gen   << 7) & prop;
    return                flood & NOT_W;
}

std::uint64_t NWFill(std::uint64_t gen, std::uint64_t prop) {
    std::uint64_t flood = 0ULL;
    prop &= NOT_W;
    flood |= gen = (gen   >> 9) & prop;
    flood |= gen = (gen   >> 9) & prop;
    flood |= gen = (gen   >> 9) & prop;
    flood |= gen = (gen   >> 9) & prop;
    flood |= gen = (gen   >> 9) & prop;
    flood |=       (gen   >> 9) & prop;
    return                flood & NOT_W;
}

std::uint64_t allSandwiched(std::uint64_t gen1, std::uint64_t gen2, std::uint64_t prop) {
    std::uint64_t flood =  SFill(gen1, prop) &  NFill(gen2, prop);
    flood         |=  NFill(gen1, prop) &  SFill(gen2, prop);
    flood         |=  EFill(gen1, prop) &  WFill(gen2, prop);
    flood         |= SEFill(gen1, prop) & NWFill(gen2, prop);
    flood         |= NEFill(gen1, prop) & SWFill(gen2, prop);
    flood         |=  WFill(gen1, prop) &  EFill(gen2, prop);
    flood         |= SWFill(gen1, prop) & NEFill(gen2, prop);
    flood         |= NWFill(gen1, prop) & SEFill(gen2, prop);
    return flood;
}

std::uint64_t allAttack(std::uint64_t gen, std::uint64_t prop) {
    std::uint64_t flood =  SShift( SFill(gen, prop));
    flood         |=  NShift( NFill(gen, prop));
    flood         |=  EShift( EFill(gen, prop));
    flood         |= SEShift(SEFill(gen, prop));
    flood         |= NEShift(NEFill(gen, prop));
    flood         |=  WShift( WFill(gen, prop));
    flood         |= SWShift(SWFill(gen, prop));
    flood         |= NWShift(NWFill(gen, prop));
    return flood;
}

std::uint64_t allShift(std::uint64_t gen) {
    std::uint64_t result =  SShift(gen);
    result         |=  NShift(gen);
    result         |=  EShift(gen);
    result         |= SEShift(gen);
    result         |= NEShift(gen);
    result         |=  WShift(gen);
    result         |= SWShift(gen);
    result         |= NWShift(gen);
    return result;
}

std::uint64_t (*shift[8])(std::uint64_t) = {
  SShift, NShift, EShift, WShift,
  SEShift, NEShift, SWShift, NWShift,
};

std::uint64_t diagShift(std::uint64_t gen) {
    std::uint64_t result = SEShift(gen);
    result         |= NEShift(gen);
    result         |= SWShift(gen);
    result         |= NWShift(gen);
    return result;
}

std::uint64_t cardShift(std::uint64_t gen) {
    std::uint64_t result =  SShift(gen);
    result         |=  NShift(gen);
    result         |=  EShift(gen);
    result         |=  WShift(gen);
    return result;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

zinets::move_history::move_history() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// zobrist hashing

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

zinets::board::board() {

  this -> bitboard[black] = 0x810000000ULL;
  this -> bitboard[white] = 0x1008000000ULL;

  this -> reversi_remain[black] = 30;
  this -> reversi_remain[white] = 30;

  this -> valid_move = allAttack(this -> bitboard[black], this -> bitboard[white]) & ~0x0ULL;

  for (int i = 0; i < 64; ++i) {
    this -> adjacent_table[i] = allShift((1ULL << i));
  }

  // test 0x3c24243c0000

  // init hash table
  this -> hash_table[black] = this -> rand.randint(100000000ULL, 999999999ULL);
  this -> hash_table[white] = this -> rand.randint(100000000ULL, 999999999ULL);
  // init zobrist key
  this -> zobrist_key = (this -> bitboard[black] ^ this -> hash_table[black]) ^ (this -> bitboard[white] ^ this -> hash_table[white]);
}



bool zinets::board::make_move(std::string move) {
  int y = move[0] - 'A';
  int x = move[1] - '1';

  int p = (7 - x) * 8 + y;
  if (get_bit(this -> valid_move, p)) {
    move_history h;
    h.black = this -> bitboard[black];
    h.white = this -> bitboard[white];
    h.adj   = this -> adj_bitboard;
    h.move  = p & 0x3f;
    h.turn  = turn;

    this -> history.push_back(h);

    std::uint64_t move = (1ULL << p);
    std::uint64_t flip = allSandwiched(move, this -> bitboard[turn], this -> bitboard[!turn]);

    this -> bitboard[turn] |= move;
    this -> bitboard[turn] |= flip;
    this -> bitboard[!turn] ^= flip;

    this -> turn = !this -> turn;

    // update adjacent bitboard
    std::uint64_t both = (this -> bitboard[black] | this -> bitboard[white]);
    this -> adj_bitboard = allShift(both) & ~both;


    this -> valid_move = allAttack(this -> bitboard[turn], this -> bitboard[!turn]) & this -> adj_bitboard;

    // if turn after move cannot make any move make a pass move
    /*
    if (this -> valid_move == 0x0) {
      this -> turn = !this -> turn;
      this -> valid_move = allAttack(this -> bitboard[turn], this -> bitboard[!turn]) & ~0x0ULL;

      // if both side cannot make any move done the game
      if (this -> valid_move == 0x0) {
        this -> turn = game_done;
      }
    }
    */
    // update zobrist
    this -> zobrist_key = (this -> bitboard[black] ^ this -> hash_table[black]) ^ (this -> bitboard[white] ^ this -> hash_table[white]);

    return true;
  }

  return false;
}

bool zinets::board::make_pass() {
    move_history h;
    h.black = this -> bitboard[black];
    h.white = this -> bitboard[white];
    h.adj   = this -> adj_bitboard;
    h.move  = 0;
    h.turn  = turn;

    this -> history.push_back(h);
    this -> turn = !this -> turn;

    this -> valid_move = allAttack(this -> bitboard[turn], this -> bitboard[!turn]) & this -> adj_bitboard;

    return true;
}

bool zinets::board::make_move(std::uint8_t move) {
  return this -> make_move(sq_ascii[move]);
}

bool zinets::board::undo_move() {
  if (this -> history.size() > (size_t) 0) {
    move_history mh = this -> history.back();

    this -> bitboard[black] = mh.black;
    this -> bitboard[white] = mh.white;
    this -> adj_bitboard    = mh.adj;
    this -> turn = mh.turn;

    this -> valid_move = allAttack(this -> bitboard[turn], this -> bitboard[!turn]) & this -> adj_bitboard;

    this -> history.pop_back();

    return true;
  }
  return false;
}

std::vector<std::uint8_t> zinets::board::generate_move() {
  std::vector<std::uint8_t> result;
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      int p = i * 8 + j;

      if (get_bit(this -> valid_move, p))
        result.push_back(p & 0x3f);
    }
  }
  return result;
}

#ifdef DEBUG
void zinets::board::stats() {

  std::cout << "  a b c d e f g h\n" << std::flush;
  for (int i = 0; i < 8; ++i) {
    std::cout << 8 - i << " " << std::flush;
    for (int j = 0; j < 8; ++j) {
      int p = i * 8 + j;

      if (get_bit(this -> bitboard[black], p)) {
        std::cout << piece_ascii[0] << ' ' << std::flush;
      }
      else if (get_bit(this -> bitboard[white], p)) {
        std::cout << piece_ascii[1] << ' ' << std::flush;
      }
      else if (get_bit(this -> valid_move, p)) {
        std::cout << "# " << std::flush;
      }
      else {
        std::cout << ". " << std::flush;
      }
    }
    std::cout << "\n" << std::flush;
  }
  std::cout << "rule: " << (this -> rule == OTHELLO ? "othello\n" : "reversi\n") << std::flush;
  std::cout << "turn: " << (this -> turn == 0 ? "black\n" : (this -> turn == game_done ? "done\n" : "white\n")) << std::flush;
  std::cout << "move: " << std::flush;
  for (size_t i = 0; i < this -> history.size(); ++i) {
    std::cout << sq_ascii[this -> history[i].move] << std::flush;
  } 
  std::cout << '\n' << std::flush;
  std::cout << "hash_seed = black: " << this -> hash_table[black] << " white: " << this -> hash_table[white] << '\n' << std::flush;
  std::cout << "hash: " << this -> zobrist_key << '\n' << std::flush;
  std::cout << "adjacent board: \n" << std::flush;


  std::cout << "  a b c d e f g h\n" << std::flush;
  for (int i = 0; i < 8; ++i) {
    std::cout << 8 - i << " " << std::flush;
    for (int j = 0; j < 8; ++j) {
      int p = i * 8 + j;

      if (get_bit(this -> adj_bitboard, p)) {
        std::cout << "# " << std::flush;
      }
      else {
        std::cout << ". " << std::flush;
      }
    }
    std::cout << "\n" << std::flush;
  }
  //std::cout << "zobrist: " << this -> zobrist_key << '\n' << std::flush;
}
#endif