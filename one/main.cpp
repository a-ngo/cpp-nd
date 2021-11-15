#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

enum class State { kEmpty, kObstacle };

std::vector<std::vector<int>> CreateBoard() {
  std::vector<std::vector<int>> board{{0, 1, 0, 0, 0, 0},
                                      {0, 1, 0, 0, 0, 0},
                                      {0, 1, 0, 0, 0, 0},
                                      {0, 1, 0, 0, 0, 0},
                                      {0, 0, 0, 0, 1, 0}};

  return board;
}

std::vector<State> ParseLine(std::string line) {
  std::istringstream row_stream(line);
  std::vector<State> row;
  int n;
  char c;
  while (row_stream >> n >> c && c == ',') {
    if (n == 1) {
      row.push_back(State::kObstacle);
    } else {
      row.push_back(State::kEmpty);
    }
  }
  return row;
}

std::vector<std::vector<State>> ReadBoard(std::string path_to_board) {
  std::vector<std::vector<State>> board;
  std::ifstream board_input(path_to_board);
  std::string line;
  if (board_input) {
    while (getline(board_input, line)) {
      auto row = ParseLine(line);
      board.push_back(row);
    }
  }
  return board;
}

std::string CellString(State state) {
  std::string state_string;
  switch (state) {
    case State::kEmpty:
      state_string = "0   ";
      break;
    case State::kObstacle:
      state_string = "⛰️   ";
      break;
    default:
      std::cerr << "Not supported state!" << std::endl;
  }
  return state_string;
}

void PrintBoard(std::vector<std::vector<State>> board) {
  for (auto row : board) {
    for (auto value : row) {
      std::cout << CellString(value);
    }
    std::cout << "\n";
  }
}

int main() {
  // read or create a board
  // auto board = CreateBoard();
  std::string path_to_board_file = "board.txt";
  auto board = ReadBoard(path_to_board_file);

  PrintBoard(board);

  return 1;
}
