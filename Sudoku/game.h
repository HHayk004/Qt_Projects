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

public:
    Game(QObject* parent);
    QVector<QVector<int>> getBoard() const;

public:
    void setDifficulty(int diff);
    void init_board();
    void setCoords(int i, int j);

    int getX();
    int getY();

    void numberEvent(int number);

    bool checkPos(int i, int j) const;

signals:
    void board_is_ready();

private:
    void init_block(int i, int j);

};

#endif // GAME_H
