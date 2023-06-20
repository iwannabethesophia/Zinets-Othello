# Zinets Othello: Debug suite for Othello, Reversi


## Features:
* Perft test
* Board test

## Usage:
* First use `Makefile` to compile program by using.
  ```
  $ make
  ```
* Run program using `zinets`.
  ```
  $ ./zinets
  ```
* To graduate version of zinets use this:
  ```
  ENGINE-PROTOCOL get-version
  ```
  The output of this command should be:
  ```
  version: zinets 0.1
  ready.
  ```
* To use the debug suite:
  * Show the current state of the board:
    ```
    debug show
    ```
  * Make a move in current board (for example using D6 move):
    ```
    debug move D6
    ```
  * Using perft test use: `debug perft <depth number>`:
    ```
    debug perft 11
    ```
    For the perft test debug you can use `perft_test_result` file that precomputed perft test at depth 11.
