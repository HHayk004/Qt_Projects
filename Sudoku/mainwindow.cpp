#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    ,startButton(new QPushButton(this))
    ,timeLabel(new QLabel(this))
    ,difficultyButtons(3)
    //, ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    this->setGeometry(100, 100, 700, 900);
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setGeometry(0, 150, 700, 700);
    gridLayout = new QGridLayout(centralWidget);

    const int gridSize = 9;
    for (int row = 0; row < gridSize; ++row) {
        for (int col = 0; col < gridSize; ++col) {
            QPushButton* button = new QPushButton();
            button->setFixedSize(60, 60);
            button->setStyleSheet("background-color: dimGray;");

            connect(button, &QPushButton::clicked, this, [row, col, this]()
            {
                int x = game->getX();
                int y = game->getY();

                if (game->checkPos(row, col))
                {
                    game->setCoords(row, col);
                    if (x != -1)
                    {
                        dynamic_cast<QPushButton*>(gridLayout->itemAtPosition(x, y)->widget())->setStyleSheet("background-color: dimGray;");
                    }

                    dynamic_cast<QPushButton*>(gridLayout->itemAtPosition(row, col)->widget())->setStyleSheet("background-color: blue;");
                }
            });

            gridLayout->addWidget(button, row, col);
        }
    }

    game = new Game(this);

    //Difficulty buttons
    QStringList difficulties = {"Easy", "Medium", "Hard"};
    for(int i = 0; i < difficultyButtons.size(); ++i)
    {
        difficultyButtons[i] = new QPushButton(difficulties[i], this);
        difficultyButtons[i]->setGeometry(70 * (i + 1), 50, 70, 50);
        difficultyButtons[i]->setStyleSheet("background-color: dimGray;");
        connect(difficultyButtons[i], &QPushButton::clicked, [this, i]{
            game->setDifficulty(i);
            startButton->setEnabled(true);
        });
    }

    startButton->setText("Start");
    startButton->setGeometry(280, 50, 70, 50);
    startButton->setStyleSheet("background-color: dimGray;");
    startButton->setEnabled(false);

    timeLabel->setText("Time");
    timeLabel->setGeometry(580, 50, 70, 50);
    timeLabel->setAlignment(Qt::AlignCenter);
    timeLabel->setStyleSheet("background-color: dimGray;");

    connect(startButton, &QPushButton::clicked, this, [this]
    {
        game->init_board();
        for (int i = 0; i < difficultyButtons.size(); ++i)
        {
            difficultyButtons[i]->setEnabled(false);
        }

        startButton->setEnabled(false);
    });

    connect(game, &Game::board_is_ready, this, &MainWindow::handleStart);
}

MainWindow::~MainWindow()
{
    //delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() >= Qt::Key_1 && event->key() <= Qt::Key_9)
    {
        int number = event->key() - Qt::Key_0;
        game->numberEvent(number);
    }
}

void MainWindow::handleStart()
{
    QVector<QVector<int>> board = game->getBoard();
    const int gridSize = 9;
    for (int row = 0; row < gridSize; ++row) {
        for (int col = 0; col < gridSize; ++col) {
            if (board[row][col])
            {
                dynamic_cast<QPushButton*>(gridLayout->itemAtPosition(row, col)->widget())->setText(QString::number(board[row][col]));
            }
        }
    }
}
