#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , play_flag(false)
    , lock_x(false)
    , lock_y(false)
    , play_button(new QPushButton(this))
    , slider_x(new QSlider(Qt::Orientation::Horizontal, this))
    , slider_y(new QSlider(Qt::Orientation::Vertical, this))
    , media_x(new QMediaPlayer(this))
    , media_y(new QMediaPlayer(this))
    , audio_x(new QAudioOutput(this))
    , audio_y(new QAudioOutput(this))
    , x_val(-1)
    , y_val(-1)
    //, ui(new Ui::MainWindow)
{
    //ui->setupUi(this);

    this->setGeometry(0, 0, 600, 600);
    this->setFixedSize(650, 650);

    play_button->setGeometry(50, 550, 50, 50);
    play_button->setStyleSheet("background-color: dimGray;");
    play_button->setText("▶");

    slider_x->setGeometry(150, 500, 450, 25);

    slider_y->setGeometry(100, 50, 25, 450);


    media_x->setAudioOutput(audio_x);
    media_y->setAudioOutput(audio_y);

    media_x->setSource(QUrl("D:/Qt_Projects/GraphicMP3/GraphicWithSerial/Songs/gucci.mp3"));
    media_y->setSource(QUrl("D:/Qt_Projects/GraphicMP3/GraphicWithSerial/Songs/noguidance.mp3"));

    audio_x->setVolume(30);
    audio_y->setVolume(30);

    connect(play_button, &QPushButton::clicked, [this](){
        if (!play_flag)
        {
            media_x->play();
            media_y->play();
            play_flag = true;
            play_button->setText("▐▐");
        }
        else
        {
            media_x->pause();
            media_y->pause();
            play_flag = false;
            play_button->setText("▶");
        }
    });

    connect(slider_x, &QSlider::valueChanged, [this]() {
        if (!lock_x)
        {
            lock_x = true;
            media_x->setPosition(slider_x->value());
            lock_x = false;
        }
    });

    connect(slider_y, &QSlider::valueChanged, [this]() {
        if (!lock_y)
        {
            lock_y = true;
            media_y->setPosition(slider_y->value());
            lock_y = false;
        }
    });

    connect(media_x, &QMediaPlayer::positionChanged, [this](qint64 position){
        if (!lock_x)
        {
            addLabel();
            lock_x = true;
            slider_x->setValue(position);
            lock_x = false;
        }
    });

    connect(media_y, &QMediaPlayer::positionChanged, [this](qint64 position){
        if (!lock_y)
        {
            addLabel();
            lock_y = true;
            slider_y->setValue(position);
            lock_y = false;
        }
    });

    connect(media_x, &QMediaPlayer::metaDataChanged, this, &MainWindow::datachangedX);
    connect(media_y, &QMediaPlayer::metaDataChanged, this, &MainWindow::datachangedY);
}

MainWindow::~MainWindow()
{
    //delete ui;
}

void MainWindow::datachangedX()
{
    const qint64 duration = media_x->duration();
    slider_x->setMaximum(duration);
}

void MainWindow::datachangedY()
{
    const qint64 duration = media_y->duration();
    slider_y->setMaximum(duration);
}

void MainWindow::addLabel()
{   
    qint64 x = slider_x->value();
    qint64 y = slider_y->value();

    if (x == x_val && y == y_val)
    {
        return;
    }

    x_val = x;
    y_val = y;

    qint64 x_val_1px = slider_x->maximum() / 428;
    qint64 y_val_1px = slider_y->maximum() / 420;

    QLabel* new_label = new QLabel(this);
    new_label->setGeometry(x / x_val_1px + 157, 487 - y / y_val_1px, 3, 3);
    new_label->setStyleSheet("background-color: red;");
    new_label->show();
}
