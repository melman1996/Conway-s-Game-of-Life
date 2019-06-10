#pragma once
#include <QtConcurrent/QtConcurrent>
#include <vector>
#include <memory>

#include "board.h"

class Engine
{
private:
    int rows, cols;
    std::shared_ptr<Board<bool>> board;
    std::vector<std::shared_ptr<Board<bool>>> history;
public:
    Engine(int, int);
    void Evolve();
    void Back();
    int Neighbours(int, int);

    void Resize(int, int);
    void ChangeValue(int, int);
    bool Get(int, int);

    std::vector<std::vector<bool>> GetBoard();

    //RLE
    std::vector<std::string> Export();
    void Import(std::vector<std::string>);
};
