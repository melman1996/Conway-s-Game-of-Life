#include "engine.h"

Engine::Engine(int rows, int cols)
{
    this->rows = rows;
    this->cols = cols;

    board = std::make_shared<Board<bool>>(rows, cols);
}

void Engine::Evolve()
{
    history.push_back(board);
    board = std::make_shared<Board<bool>>(rows, cols);

    int index = history.size() - 1;

    for(int i = 0; i < rows; i++){
        QtConcurrent::run([=] {
            for(int j = 0; j < cols; j++){
                int neighbours = Neighbours(i, j);
                if(history[index]->Get(i, j)){//cell is alive
                    if(neighbours < 2){//rule no. 1
                        board->Set(i, j, false);
                    }
                    else if (neighbours <= 3){//rule no. 2
                        board->Set(i, j, true);
                    }
                    else{//rule no. 3
                        board->Set(i, j, false);
                    }
                }
                else {//cell is dead
                    if(neighbours == 3){//rule no. 4
                        board->Set(i, j, true);
                    }
                }
            }
        });
    }
}

void Engine::Back()
{
    board = history[history.size() - 1];
    history.pop_back();
}

int Engine::Neighbours(int row, int col)
{
    int counter = 0;

    int index = history.size() - 1;

    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {
            int y = (j + cols) % cols;
            if ((i >= 0 && i < cols) &&
                (i != row || y != col) &&
                history[index]->Get(i, y)) {
                counter++;
            }
        }
    }

    return counter;
}

void Engine::Resize(int rows, int cols)
{
    this->rows = rows;
    this->cols = cols;
    history.clear();
    board = std::make_unique<Board<bool>>(rows, cols);
}

void Engine::ChangeValue(int row, int col)
{
    board->Set(row, col, !board->Get(row, col));
}

bool Engine::Get(int row, int col)
{
    return board->Get(row, col);
}

std::vector<std::vector<bool>> Engine::GetBoard()
{
    return board->Get();
}

std::vector<std::string> Engine::Export()
{
    std::vector<std::string> toExport;

    for(int i = 0; i < rows; i++){
        std::string line = "";
        for(int j = 0; j < cols; j++){
            if(board->Get(i, j)){
                line += "o";
            }
            else{
                line += "b";
            }
        }
        toExport.push_back(line);
    }

    return toExport;
}

void Engine::Import(std::vector<std::string> toImport)
{
    for(int i = 0; i < toImport.size(); i++){
        for(int j = 0; j < toImport[i].size(); j++){
            if(toImport[i][j] == 'o'){
                board->Set(i, j, true);
            }
            else {
                board->Set(i, j, false);
            }
        }
    }
}
