#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , difficulty_buttons(3)
    , start_button(new QPushButton(this))
    , reset_game(new QPushButton(this))
    , heart_label(new QLabel(this))
    , time_label(new QLabel(this))

//, ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    this->setGeometry(100, 100, 700, 900);
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setGeometry(0, 150, 700, 700);
    grid_layout = new QGridLayout(centralWidget);

    const int grid_size = 9;
    for (int row = 0; row < grid_size; ++row) {
        for (int col = 0; col < grid_size; ++col) {
            QPushButton* button = new QPushButton();
            button->setFixedSize(60, 60);
            button->setStyleSheet("background-color: dimGray;"
                                  "font-size: 20px;");
            button->setEnabled(false);

            connect(button, &QPushButton::clicked, this, [row, col, this]()
            {
                int x = game->getX();
                int y = game->getY();

                if (game->checkPos(row, col))
                {
                    game->setCoords(row, col);
                    if (x != -1)
                    {
                        dynamic_cast<QPushButton*>(grid_layout->itemAtPosition(x, y)->widget())->setStyleSheet("background-color: dimGray;");
                    }
                    dynamic_cast<QPushButton*>(grid_layout->itemAtPosition(row, col)->widget())->setStyleSheet("background-color: blue;");
                }
            });

            grid_layout->addWidget(button, row, col);
        }
    }

    game = new Game(this);

    //Difficulty buttons
    QStringList difficulties = {"Easy", "Medium", "Hard"};
    for(int i = 0; i < difficulty_buttons.size(); ++i)
    {
        difficulty_buttons[i] = new QPushButton(difficulties[i], this);
        difficulty_buttons[i]->setGeometry(70 * (i + 1), 50, 70, 50);
        difficulty_buttons[i]->setStyleSheet("background-color: dimGray;");
        connect(difficulty_buttons[i], &QPushButton::clicked, this, [this, i](){
            game->setDifficulty(i);
            start_button->setEnabled(true);
        });
    }

    start_button->setText("Start");
    start_button->setGeometry(280, 50, 70, 50);
    start_button->setStyleSheet("background-color: dimGray;");
    start_button->setEnabled(false);

    connect(start_button, &QPushButton::clicked, this, [this]()
    {
        game->initGame();
        for (int i = 0; i < difficulty_buttons.size(); ++i)
        {
            difficulty_buttons[i]->setEnabled(false);
        }

        start_button->setEnabled(false);
    });

    reset_game->setText("Reset");
    reset_game->setGeometry(400, 50, 70, 50);
    reset_game->setStyleSheet("background-color: dimGray;");

    connect(reset_game, &QPushButton::clicked, this, &MainWindow::resetGame);

    heart_label->setGeometry(500, 50, 70, 50);
    heart_label->setAlignment(Qt::AlignCenter);
    heart_label->setStyleSheet("background-color: dimGray;");
    heart_label->setText("Hearts:");

    time_label->setText("Time");
    time_label->setGeometry(600, 50, 70, 50);
    time_label->setAlignment(Qt::AlignCenter);
    time_label->setStyleSheet("background-color: dimGray;");

    connect(game, &Game::board_is_ready, this, &MainWindow::handleStart);
    connect(game, &Game::add_on_grid, this, &MainWindow::addOnGrid);
    connect(game, &Game::change_hearts_count, this, &MainWindow::changeHeartLabel);
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
    heart_label->setText("Hearts: 3");
    QVector<QVector<int>> board = game->getBoard();
    const int grid_size = 9;
    for (int row = 0; row < grid_size; ++row) {
        for (int col = 0; col < grid_size; ++col) {
            if (board[row][col])
            {
                dynamic_cast<QPushButton*>(grid_layout->itemAtPosition(row, col)->widget())->setText(QString::number(board[row][col]));
            }

            else
            {
                dynamic_cast<QPushButton*>(grid_layout->itemAtPosition(row, col)->widget())->setText("");
            }

            dynamic_cast<QPushButton*>(grid_layout->itemAtPosition(row, col)->widget())->setEnabled(true);
        }
    }
}

void MainWindow::addOnGrid()
{
    int x = game->getX();
    int y = game->getY();
    dynamic_cast<QPushButton*>(grid_layout->itemAtPosition(x, y)->widget())->setText(QString::number(game->getNumber(x, y)));

    game->setCoords(-1, -1);
    dynamic_cast<QPushButton*>(grid_layout->itemAtPosition(x, y)->widget())->setStyleSheet("background-color: dimGray;"
                                                                                            "font-size: 20px;");
}

void MainWindow::changeHeartLabel()
{
    heart_label->setText("Hearts: " + QString::number(game->getHearts()));
    if (game->getHearts() == 0)
    {
        resetGame();
    }
}

void MainWindow::resetGame()
{
    const int grid_size = 9;
    for (int row = 0; row < grid_size; ++row)
    {
        for (int col = 0; col < grid_size; ++col)
        {
            dynamic_cast<QPushButton*>(grid_layout->itemAtPosition(row, col)->widget())->setText("");
            dynamic_cast<QPushButton*>(grid_layout->itemAtPosition(row, col)->widget())->setEnabled(false);
        }
    }

    if (game->getX() != -1)
    {
        dynamic_cast<QPushButton*>(grid_layout->itemAtPosition(game->getX(), game->getY())->widget())->setStyleSheet("background-color: dimGray;"
                                                                                                                      "font-size: 20px;");
        game->setCoords(-1, -1);
    }

    for(int i = 0; i < difficulty_buttons.size(); ++i)
    {
        difficulty_buttons[i]->setEnabled(true);
    }

    heart_label->setText("Hearts:");
}
