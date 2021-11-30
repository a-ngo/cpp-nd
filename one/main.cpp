#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

enum class State { kEmpty, kObstacle, kClosed, kPath, kStart, kFinish };

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
    case State::kObstacle:
      state_string = "⛰️   ";
      break;
    case State::kPath:
      state_string = "🚗  ";
      break;
    case State::kStart:
      state_string = "🚦  ";
      break;
    case State::kFinish:
      state_string = "🏁  ";
      break;
    default:
      state_string = "0   ";
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
 * @brief add a node to the open vector and mark their position as visited in
 * the grid
 *
 */
void AddToOpen(int x, int y, int g, int h,
               std::vector<std::vector<int>> &open_nodes,
               std::vector<std::vector<State>> &grid) {
  open_nodes.push_back(std::vector<int>{x, y, g, h});
  grid.at(x).at(y) = State::kClosed;
}

/**
 * @brief sort (descending) open nodes by h-value
 * @pre assume that h-value is the third value
 *
 */
void CellSort(std::vector<std::vector<int>> &open_nodes) {
  std::sort(open_nodes.begin(), open_nodes.end(),
            [](const std::vector<int> &v1, const std::vector<int> &v2) {
              return v1.at(3) > v2.at(3);
            });
}

/**
 * @brief checks if a given neighbor cell is valid, i.e. it hasn't been closed
 *        and is not an obstacle
 *
 * @return returns true if valid cell
 */
bool CheckValidCell(int x, int y, const std::vector<std::vector<State>> &grid) {
  // check if position is on the grid
  bool not_on_grid_x = x >= grid.size() || x < 0;
  bool not_on_grid_y = y >= grid[0].size() || y < 0;
  if (not_on_grid_x || not_on_grid_y) {
    return false;
  }
  return grid.at(x).at(y) == State::kEmpty;
}

/**
 * @brief loop through the current nodes neighbors and add valid neighbors to
 * the open list
 *
 */
void ExpandNeighbors(const std::vector<int> &current_node,
                     const std::vector<int> &goal_point,
                     std::vector<std::vector<int>> &open_nodes,
                     std::vector<std::vector<State>> &grid) {
  int current_node_pos_x = current_node.at(0);
  int current_node_pos_y = current_node.at(1);
  int g = current_node.at(2);

  // loop over neighbors
  std::vector<std::vector<int>> delta{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
  for (auto d : delta) {
    int neighbor_x = current_node_pos_x + d.at(0);
    int neighbor_y = current_node_pos_y + d.at(1);
    if (CheckValidCell(neighbor_x, neighbor_y, grid)) {
      int neighbor_g = g + 1;
      int neighbor_h =
          Heuristic(neighbor_x, neighbor_y, goal_point.at(0), goal_point.at(1));
      AddToOpen(neighbor_x, neighbor_y, neighbor_g, neighbor_h, open_nodes,
                grid);
    }
  }
}

/**
 * @brief A* path search function
 *
 * @return grid with optimal path found
 */
std::vector<std::vector<State>> Search(std::vector<std::vector<State>> grid,
                                       std::vector<int> initial_point,
                                       std::vector<int> goal_point) {
  std::vector<std::vector<int>> open_nodes{};
  
  // initialize a starting node and add to open list
  int initial_point_x = initial_point.at(0);
  int initial_point_y = initial_point.at(1);
  int g = 0;
  int h = Heuristic(initial_point_x, initial_point_y, goal_point.at(0), goal_point.at(1));
  AddToOpen(initial_point_x, initial_point_y, g, h, open_nodes, grid);

  while (open_nodes.size() > 0) {
    CellSort(open_nodes);
    auto current_node = open_nodes.back();
    open_nodes.pop_back();
    grid.at(current_node.at(0)).at(current_node.at(1)) = State::kPath;

    if (current_node.at(0) == goal_point.at(0) &&
        current_node.at(1) == goal_point.at(1)) {
      // set start and finish point
      grid.at(initial_point_x).at(initial_point_y) = State::kStart;
      grid.at(goal_point.at(0)).at(goal_point.at(1)) = State::kFinish;
      std::cout << "Goal is reached!" << std::endl;
      return grid;
    }

    // loop through the current nodes neighbors and add valid neighbors to the
    // open list
    ExpandNeighbors(current_node, goal_point, open_nodes, grid);
  }
  std::cout << "No path found!" << std::endl;
  return grid;
}

#include "test.cpp"  // For testing solution

int main() {
  // Tests
  TestHeuristic();
  TestAddToOpen();
  TestSearch();
  TestCheckValidCell();
  TestExpandNeighbors();

  // TODO: measure runtime
  // read or create a board
  // auto board = CreateBoard();
  std::string path_to_board_file = "board.txt";
  auto board = ReadBoard(path_to_board_file);

  // A* path search function
  std::vector<int> initial_point{0, 0};
  std::vector<int> goal_point{4, 5};
  auto board_with_path = Search(board, initial_point, goal_point);

  PrintBoard(board_with_path);

  return 1;
}
