#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "game.h"
#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *event) override;

private:
    //Ui::MainWindow *ui;
    Game* game;
    QGridLayout* gridLayout;

    QVector<QPushButton*> difficultyButtons;
    QPushButton* startButton;
    QLabel* timeLabel;

private:
    void handleStart();
};
#endif // MAINWINDOW_H
