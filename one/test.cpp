void TestHeuristic() {
  std::cout << "----------------------------------------------------------"
            << "\n";
  std::cout << "Heuristic Function Test: ";
  if (Heuristic(1, 2, 3, 4) != 4) {
    std::cout << "failed"
              << "\n";
    std::cout << "\n"
              << "Heuristic(1, 2, 3, 4) = " << Heuristic(1, 2, 3, 4) << "\n";
    std::cout << "Correct result: 4"
              << "\n";
    std::cout << "\n";
  } else if (Heuristic(2, -1, 4, -7) != 8) {
    std::cout << "TestHeuristic Failed"
              << "\n";
    std::cout << "\n"
              << "Heuristic(2, -1, 4, -7) = " << Heuristic(2, -1, 4, -7)
              << "\n";
    std::cout << "Correct result: 8"
              << "\n";
    std::cout << "\n";
  } else {
    std::cout << "passed"
              << "\n";
  }
  std::cout << "----------------------------------------------------------"
            << "\n";
}

void PrintVectorOfVectors(std::vector<std::vector<int>> v) {
  for (auto row : v) {
    std::cout << "{ ";
    for (auto col : row) {
      std::cout << col << " ";
    }
    std::cout << "}" << "\n";
  }
}

void PrintVectorOfVectors(std::vector<std::vector<State>> v) {
  for (auto row : v) {
    std::cout << "{ ";
    for (auto col : row) {
      std::cout << CellString(col) << " ";
    }
    std::cout << "}" << "\n";
  }
}

void TestAddToOpen() {
  std::cout << "----------------------------------------------------------" << "\n";
  std::cout << "AddToOpen Function Test: ";
  int x = 3;
  int y = 0;
  int g = 5;
  int h = 7;
  std::vector<std::vector<int>> open{{0, 0, 2, 9}, {1, 0, 2, 2}, {2, 0, 2, 4}};
  std::vector<std::vector<int>> solution_open = open; 
  solution_open.push_back(std::vector<int>{3, 0, 5, 7});
  std::vector<std::vector<State>> grid{{State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kEmpty, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty, State::kObstacle, State::kEmpty}};
  std::vector<std::vector<State>> solution_grid = grid;
  solution_grid[3][0] = State::kClosed;
  AddToOpen(x, y, g, h, open, grid);
  if (open != solution_open) {
    std::cout << "failed" << "\n";
    std::cout << "\n";
    std::cout << "Your open list is: " << "\n";
    PrintVectorOfVectors(open);
    std::cout << "Solution open list is: " << "\n";
    PrintVectorOfVectors(solution_open);
    std::cout << "\n";
  } else if (grid != solution_grid) {
    std::cout << "failed" << "\n";
    std::cout << "\n";
    std::cout << "Your grid is: " << "\n";
    PrintVectorOfVectors(grid);
    std::cout << "\n";
    std::cout << "Solution grid is: " << "\n";
    PrintVectorOfVectors(solution_grid);
    std::cout << "\n";
  } else {
    std::cout << "passed" << "\n";
  }
  std::cout << "----------------------------------------------------------" << "\n";
  return;
}

void TestSearch() {
  std::cout << "----------------------------------------------------------" << "\n";
  std::cout << "Search Function Test (Partial): ";
  std::vector<int> goal{4, 5};
  auto board = ReadBoard("board.txt");
  
  std::cout.setstate(std::ios_base::failbit); // Disable cout
  auto output = Search(board, goal, goal);
  std::cout.clear(); // Enable cout

  std::vector<std::vector<State>> solution{{State::kEmpty, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kEmpty, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kEmpty, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kEmpty, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty, State::kObstacle, State::kPath}};

  if (output != solution) {
    std::cout << "failed" << "\n";
    std::cout << "Search(board, {4,5}, {4,5})" << "\n";
    std::cout << "Solution board: " << "\n";
    PrintVectorOfVectors(solution);
    std::cout << "Your board: " << "\n";
    PrintVectorOfVectors(output);
    std::cout << "\n";
  } else {
    std::cout << "passed" << "\n";
  }
  std::cout << "----------------------------------------------------------" << "\n";
}