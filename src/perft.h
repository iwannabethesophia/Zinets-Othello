#ifndef zinets_perft_h
#define zinets_perft_h

#include "board.h"

namespace zinets {
  class Perft {
  public:
    zinets::board board;
    std::uint64_t perft(int depth, bool passed);

    void perform_perft(int depth);
  };
}

#endif