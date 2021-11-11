#include <iostream>
#include <vector>

std::vector<std::vector<int>> CreateBoard() {
    std::vector<std::vector<int>> board{{0, 1, 0, 0, 0, 0},
                            {0, 1, 0, 0, 0, 0},
                            {0, 1, 0, 0, 0, 0},
                            {0, 1, 0, 0, 0, 0},
                            {0, 0, 0, 0, 1, 0}};
    
    return board;
}

void PrintBoard(std::vector<std::vector<int>> board) {
    for (auto row: board) {
        for (auto value: row)
            std::cout << value;
        std::cout << "\n";
    }
}

int main(){
    auto board = CreateBoard();
    PrintBoard(board);

    return 1;
}