#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <vector>

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

private slots:
    void datachangedX();
    void datachangedY();

private:
    void addLabel();

private:
    bool play_flag;

    bool lock_x;
    bool lock_y;

    QPushButton* play_button;
    QSlider*  slider_x;
    QSlider*  slider_y;
    QMediaPlayer* media_x;
    QMediaPlayer* media_y;
    QAudioOutput* audio_x;
    QAudioOutput* audio_y;
    //Ui::MainWindow *ui;

    qint64 x_val;
    qint64 y_val;
};
#endif // MAINWINDOW_H
