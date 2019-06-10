#pragma once

#include <vector>

template<typename T>
class Board
{
private:
    int rows;
    int cols;
    std::vector<std::vector<T>> board;
public:
    Board(int rows, int cols)
    {
        this->rows = rows;
        this->cols = cols;
        for(int i = 0; i < rows; i++){
            std::vector<T> row(cols);
            std::fill(row.begin(), row.end(), false);
            board.push_back(row);
        }
    }
    std::vector<std::vector<T>> Get()
    {
        return board;
    }
    T Get(int row, int col)
    {
        return board[row][col];
    }
    void Set(int row, int col, T value)
    {
        board[row][col] = value;
    }

    int Rows()
    {
        return rows;
    }
    int Cols()
    {
        return cols;
    }
};
