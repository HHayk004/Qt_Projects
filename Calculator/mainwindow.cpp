#include "mainwindow.h"
#include "calc.h"
//#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_expr()
    , m_expr_index(0)
    , m_buttons(5, std::vector<QPushButton*>(4))
    , m_display(new QLabel("", this))
    , m_display_index(0)
    //, ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    this->setGeometry(100, 200, 500, 375);
    this->setMinimumWidth(500);
    this->setMinimumHeight(375);

    m_display->setStyleSheet("color: white;" "font-size: 35px;");
    m_display->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    std::vector<std::vector<QString>> symbols = {
        {"(", ")", "%", "CE"},
        {"7", "8", "9", "/"},
        {"4", "5", "6", "*"},
        {"1", "2", "3", "-"},
        {"0", ".", "=", "+"}
    };

    for (int i = 0; i < m_buttons.size(); ++i)
    {
        for (int j = 0; j < m_buttons[i].size(); ++j)
        {
            m_buttons[i][j] = new QPushButton(this);
            m_buttons[i][j]->setText(symbols[i][j]);
        }
    }

    m_buttons[4][2]->setStyleSheet("background-color: darkBlue;");

    for (int i = 0; i < 3; ++i) // for 1->9
    {
        for (int j = 0; j < 3; ++j)
        {
            m_buttons[i + 1][j]->setStyleSheet("background-color: dimGrey;");
            connect(m_buttons[i + 1][j], &QPushButton::clicked, [i, j, this]()
            {
                if(m_expr.empty() || m_expr[m_expr_index - 1] != ")")
                {
                    addText(m_buttons[i + 1][j]->text());
                }
            });
        }
    }

    m_buttons[4][0]->setStyleSheet("background-color: dimGrey;");
    connect(m_buttons[4][0], &QPushButton::clicked, [this]() // for 0
    {
        if (lastIsNumber())
        {
            addText("0");
        }
    });

    m_buttons[4][1]->setStyleSheet("background-color: dimGrey;");
    connect(m_buttons[4][1], &QPushButton::clicked, [this]() // for .
    {
        if (m_expr.empty() || lastIsOperator()) // lastIsOperator classi mej avelacra u implemtacian
                // stuguma verjiny operatora mutqagre te che
        {
            addText("0.");
        }

        else if (lastIsNumber() && checkPoint()) // CheckNum classi mej avelacra u implementacian
                        // stuguma toxi tvi mej ket ka te che;
        {
            addText(".");
        }
    });

    for (int i = 0; i < 4; ++i) // +, -, *, /
    {
        m_buttons[i + 1][3]->setStyleSheet("background-color: #212121;");
        connect(m_buttons[i + 1][3], &QPushButton::clicked, [i, this]()
        {
            if ((m_buttons[i + 1][3]->text() == "-" && m_expr.empty() || m_expr[m_expr_index - 1] == "(") ||
                (lastIsNumber() && m_display->text()[m_display_index - 1] != '.') || m_expr[m_expr_index - 1] == ")")
            {
                addText(m_buttons[i + 1][3]->text());
            }
        });
    }

    m_buttons[0][0]->setStyleSheet("background-color: #212121;");
    connect(m_buttons[0][0], &QPushButton::clicked, [this] { // for (
        if (m_expr.empty() || lastIsOperator())
        {
            addText("()");
        }
    });

    m_buttons[0][1]->setStyleSheet("background-color: #212121;");
    connect(m_buttons[0][1], &QPushButton::clicked, [this] { // for )
        if ((lastIsNumber() || m_expr[m_expr_index - 1] == ")") && m_expr[m_expr_index] == ")")
        {
            addText("");
        }
    });

    m_buttons[0][2]->setStyleSheet("background-color: #212121;");
    connect(m_buttons[0][2], &QPushButton::clicked, [this] { // for %
        if (lastIsNumber())
        {
            addText("%*");
        }
    });

    m_buttons[0][3]->setStyleSheet("background-color: #212121;");
    connect(m_buttons[0][3], &QPushButton::clicked, [this] { // for CE
        QString str = m_display->text();
        if (!str.isEmpty())
        {
            if (m_expr[m_expr_index - 1] == ")")
            {
                --m_display_index;
                --m_expr_index;
            }

            if (str[m_display_index - 1] == '*' && str[m_display_index - 2] == '%')
            {
                m_expr_index -= 3;
                for (int i = 0; i < 3; ++i)
                {
                    m_expr.pop_back();
                }

                m_display_index -= 2;
            }

            else if (lastIsNumber() || lastIsOperator())
            {
                str.remove(m_display_index - 1, 1);
                --m_display_index;
                m_expr[m_expr_index - 1].chop(1);
                if (m_expr[m_expr_index - 1].isEmpty())
                {
                    m_expr.pop_back();
                    --m_expr_index;
                }
            }

            else if (m_expr[m_expr_index - 1] == "(")
            {
                m_expr_index -= 1;
                m_display_index -= 1;
                m_expr.pop_back();
                m_expr.pop_back();
                str.remove(m_display_index, 2);
            }

            m_display->setText(str);
        }
    });

    connect(m_buttons[4][2], &QPushButton::clicked, [this] {
        if (m_expr.size() > 1)
        {
            ExprSolver().exprSolver(m_expr);

            m_expr_index = 1;
            m_display_index = m_expr[0].size();

            m_display->setText(m_expr[0]);
        }
    });

    // connectnery mnatsats functionneri
}

double MainWindow::percent(int val, double p) const
{
    return val * p / 100;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    int w = this->size().width();
    int h = this->size().height();

    m_display->setGeometry(0, 0, w, percent(h, 20));

    for (int i = 0; i < m_buttons.size(); ++i)
    {
        for (int j = 0; j < m_buttons[i].size(); ++j)
        {
            double b_x = percent(w, 25 * j);
            double b_y = percent(h, 20 + 16 * i);
            double b_h = percent(w, 25);
            double b_w = percent(h, 16);
            m_buttons[i][j]->setGeometry(b_x, b_y, b_h, b_w);
        }
    }
}

MainWindow::~MainWindow()
{
    //delete ui;
}

void MainWindow::addText(const QString& str)
{
    if (str.isEmpty())
    {
        ++m_display_index;
        ++m_expr_index;
        return;
    }

    QString tmp = m_display->text();
    for (QChar ch : str)
    {
        tmp.insert(m_display_index, ch);
        ++m_display_index;
    }

    if ('0' <= str[0] && str[0] <= '9')
    {
        if ((m_expr.empty() || (lastIsOperator() || m_expr[m_expr_index - 1] == "(") &&
            !(m_expr[m_expr_index - 1] == "-" && (m_expr.size() == 1 || m_expr[m_expr_index - 2] == "("))))
        {
            m_expr.insert(m_expr.begin() + m_expr_index, str);
            ++m_expr_index;
        }

        else
        {
            m_expr[m_expr_index - 1] += str;
        }
    }

    else if (str == '.')
    {
        m_expr[m_expr_index - 1] += str;
    }

    else if (isOperator(str))
    {
        m_expr.insert(m_expr.begin() + m_expr_index, str);
        ++m_expr_index;
    }

    else if (str == "%*")
    {
        m_expr.insert(m_expr.begin() + m_expr_index, "/");
        ++m_expr_index;
        m_expr.insert(m_expr.begin() + m_expr_index, "100");
        ++m_expr_index;
        m_expr.insert(m_expr.begin() + m_expr_index, "*");
        ++m_expr_index;
    }

    else if (str == "()")
    {
        m_expr.insert(m_expr.begin() + m_expr_index, "(");
        ++m_expr_index;
        m_expr.insert(m_expr.begin() + m_expr_index, ")");
        --m_display_index;
    }

    m_display->setText(tmp);
}

bool MainWindow::isOperator(const QString& str)
{
    return str == "+" || str == "-" || str == "*" || str == "/";
}

bool MainWindow::lastIsNumber()
{
    if (m_expr.empty())
    {
        return false;
    }

    return ('0' <= m_expr[m_expr_index - 1][0] && m_expr[m_expr_index - 1][0] <= '9') ||
            (m_expr[m_expr_index - 1].size() > 1 && m_expr[m_expr_index - 1][0] == '-' &&
            '0' <= m_expr[m_expr_index - 1][1] && m_expr[m_expr_index - 1][1] <= '9');
}

bool MainWindow::lastIsOperator()
{
    if (m_expr.empty())
    {
        return false;
    }

    return isOperator(m_expr[m_expr_index - 1]);
}

bool MainWindow::checkPoint()
{
    QString str = m_expr[m_expr_index - 1];
    for (QChar ch : str)
    {
        if (ch == '.')
        {
            return false;
        }
    }

    return true;
}
