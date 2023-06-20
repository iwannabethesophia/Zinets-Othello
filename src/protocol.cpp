#include "protocol.h"
#include "board.h"
#include "perft.h"

#include <iostream>
#include <cstring>

#define engine_ready std::cout << "ready.\n" << std::flush

zinets_protocol::protocol::protocol() {}

void zinets_protocol::protocol::start() {
  zinets::board board;

  std::string token;

  // protocol while loop
  while (true) {
    std::cin >> token;

    // use for engine protocol that used in Cassio software
    if (token == "ENGINE-PROTOCOL") {
      std::cin >> token; // get next token

      // engine initialize
      if (token == "init") {
        // board init
        board = zinets::board();

        engine_ready; // protocol ready
      }

      else if (token == "get-version") {
        std::cout << "version: zinets 0.1\n" << std::flush;
        engine_ready; // protocol ready
      }
    }
    // exit the engine
    else if (token == "exit") {
      exit(0);
    }
    // debug mode
    #ifdef DEBUG
    else if (token == "debug") {
      std::cin >> token; // get next token

      // show the current state of the board
      if (token == "show") {
        board.stats();
      }
      // make a move into a state
      else if (token == "move") {
        std::cin >> token; // get move

        board.make_move(token);
      }
      // undo a move itno a state
      else if (token == "undo") {
        board.undo_move();
      }
      // start perft debug benchmark
      else if (token == "perft") {
        int d;
        std::cin >> d;

        zinets::Perft p;
        p.perform_perft(d);
      }
      engine_ready; // protocol ready
    }
    #endif
  }
}