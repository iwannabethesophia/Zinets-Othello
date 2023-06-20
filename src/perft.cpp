#include "perft.h"

#include <iomanip>
#include <ctime>

std::uint64_t zinets::Perft::perft(int depth, bool passed) {

  if (depth == 0)
    return 1;

  std::uint64_t nodes = 0;

  auto moves = this -> board.generate_move();
  if (moves.size() == 0) {
    if (passed == true)
      return 1;
    this -> board.make_pass();
    nodes += perft(depth - 1, true);
    this -> board.undo_move();
  }
  else {
    for (auto m : moves) {
      this -> board.make_move(m);
      nodes += perft(depth - 1, false);
      this -> board.undo_move();
    }
  }
  return nodes;
}

void zinets::Perft::perform_perft(int depth) {

  for (int i = 1; i <= depth; ++i) {
    this -> board = zinets::board();

    clock_t start = clock();
    std::uint64_t nodes = this -> perft(i, false);
    clock_t end = clock();

    double diff = (double)(end - start) / CLOCKS_PER_SEC;

    int speed = (double)nodes / diff;

    if (i > 6) {
      std::cout << "depth " << i << ": " << nodes << " time: " << std::fixed << std::setprecision(3) << diff << std::setprecision(0) << "s speed: " << speed << " node/s\n" << std::flush;
    }
    else {
      std::cout << "depth " << i << ": " << nodes << '\n' << std::flush;
    }
  }
}