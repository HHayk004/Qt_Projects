#include "game.h"

Game::Game(QObject* parent) : board(9, QVector<int>(9, 0))
{
}

void Game::initGame()
{
    hearts = 3;
    empty_fields = 0;
    x = -1;
    y = -1;
    full_board = SudokuGenerator::getGeneratedSudoku();

    for (int i = 0; i < board.size(); ++i){
        for (int j = 0; j < board.size(); ++j){
            board[i][j] = 0;
        }
    }

    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            init_block(i * 3, j * 3);
        }
    }

    emit board_is_ready();
}

void Game::numberEvent(int number)
{
    if (x != -1)
    {
        if (full_board[x][y] == number)
        {
            board[x][y] = number;
            --empty_fields;
            emit add_on_grid();
        }

        else
        {
            --hearts;
            emit change_hearts_count();
        }
    }
}

void Game::init_block(int i, int j)
{
    int count = 0;
    switch(difficulty)
    {
    case 0:{
        count = std::rand() % 3 + 4;
        break;
    }

    case 1:{
        count = std::rand() % 3 + 3;
        break;
    }

    case 2:{
        count = std::rand() % 3 + 2;
        break;
    }

    default:{
        count = 1;
    }
    }

    empty_fields += 9 - count;

    int index = 0;
    while (index != count)
    {
        int x = std::rand() % 3 + i;
        int y = std::rand() % 3 + j;

        if (board[x][y] == 0)
        {
            ++index;
            board[x][y] = full_board[x][y];
        }
    }
}

QVector<QVector<int>> Game::getBoard() const
{
    return board;
}

void Game::setDifficulty(int diff)
{
    difficulty = diff;
}

void Game::setCoords(int i, int j)
{
    x = i;
    y = j;
}

int Game::getX() const
{
    return x;
}

int Game::getY() const
{
    return y;
}

int Game::getNumber(int i, int j) const
{
    return board[i][j];
}

int Game::getHearts() const
{
    return hearts;
}

int Game::getEmptyCount() const
{
    return empty_fields;
}

bool Game::checkPos(int i, int j) const
{
    return !board[i][j];
}
