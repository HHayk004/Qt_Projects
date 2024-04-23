#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "game.h"
#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QMessageBox>
#include <QTimer>

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
    QGridLayout* grid_layout;

    QVector<QPushButton*> difficulty_buttons;
    QPushButton* start_button;
    QPushButton* reset_game;
    QLabel* heart_label;
    QLabel* time_label;
    int seconds;
    QTimer* timer;

private:
    void handleStart();
    void addOnGrid();
    void changeHeartLabel();

    void resetGame();
};
#endif // MAINWINDOW_H
