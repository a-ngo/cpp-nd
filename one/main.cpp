#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

enum class State { kEmpty, kObstacle, kClosed };

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

/**
 * @brief compute a heuristic between a pair of 2D coordinates.
 *        the manhatten distance is calculated.
 */
int Heuristic(const int x1, const int y1, const int x2, const int y2) {
  // TODO: try other admissible heuristics
  return std::abs(x2 - x1) + std::abs(y2 - y1);
}

/**
 * @brief add a node to the open vector and mark their position as visited in the grid
 *
 */
void AddToOpen(int x, int y, int g, int h,
               std::vector<std::vector<int>> open_nodes,
               std::vector<std::vector<State>> grid) {                 
  open_nodes.push_back(std::vector<int>{x, y, g, h});
  grid.at(x).at(y) = State::kClosed;  
}

/**
 * @brief A* path search function
 *
 * @return grid with optimal path found
 */
std::vector<std::vector<State>> Search(std::vector<std::vector<State>> grid,
                                       std::vector<int> initial_point,
                                       std::vector<int> goal_point) {
  // 1. initlize empty list of open nodes based on input grid/board
  std::vector<std::vector<State>> open_nodes;

  // 2. initialize a starting node and add to open list

  // 3. while list of open nodes is non empty
  // CellSort();

  // ExpandNeighbors();

  // CheckValidCell();

  // Heuristic();

  // AddToOpen();

  return grid;
}

#include "test.cpp"  // For testing solution

int main() {
  // Tests
  TestHeuristic();

  // TODO: measure runtime
  // read or create a board
  // auto board = CreateBoard();
  std::string path_to_board_file = "board.txt";
  auto board = ReadBoard(path_to_board_file);

  // A* path search function
  std::vector<int> initial_point{0, 0};
  std::vector<int> goal_point{5, 5};
  auto board_with_path = Search(board, initial_point, goal_point);

  PrintBoard(board_with_path);

  return 1;
}
