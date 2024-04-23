#ifndef GAME_H
#define GAME_H

#include <QVector>
#include <QObject>
#include <cstdlib>
#include <ctime>
#include "SudokuGenerator.h"

class Game : public QObject
{
    Q_OBJECT

private:
    QVector<QVector<int>> full_board;
    QVector<QVector<int>> board;
    int difficulty;
    int x;
    int y;
    int hearts;
    int empty_fields;

public:
    Game(QObject* parent);
    QVector<QVector<int>> getBoard() const;

public:
    void setDifficulty(int diff);
    void initGame();
    void setCoords(int i, int j);

    void numberEvent(int number);

    int getX() const;
    int getY() const;
    int getNumber(int i, int j) const;
    int getHearts() const;
    int getEmptyCount() const;
    bool checkPos(int i, int j) const;

signals:
    void board_is_ready();
    void add_on_grid();
    void change_hearts_count();

private:
    void init_block(int i, int j);

};

#endif // GAME_H
