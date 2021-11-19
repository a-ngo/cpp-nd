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