#ifndef CALC_H
#define CALC_H

#include <vector>
#include <string>
#include <unordered_map>

class ExprSolver
{
private:
    std::unordered_map<QString, int> m_op_presedence = {{"+", 0}, {"-", 0}, {"*", 1}, {"/", 1}, {"%", 1}, {"(", 2}};

private:
    void makeCalc(std::vector<QString>& expr, std::vector<QString>::iterator it);

    std::vector<QString>::iterator firstOperatorIndex(std::vector<QString>& expr);
    bool isOperator(const QString& op) const;

public:
    void exprSolver(std::vector<QString>& expr);
};

void ExprSolver::exprSolver(std::vector<QString>& expr)
{
    while (expr.size() != 1)
    {
        std::vector<QString>::iterator it = firstOperatorIndex(expr);
        makeCalc(expr, it);
    }
}

void ExprSolver::makeCalc(std::vector<QString>& expr, std::vector<QString>::iterator it)
{
    if (*it == "(")
    {
        if (*(it + 1) == ")")
        {
            expr = {"Error"};
        }

        else
        {
            expr.erase(it + 2);
            expr.erase(it);
        }
    }

    else
    {
        double num1 = stod((it - 1)->toStdString());
        double num2 = stod((it + 1)->toStdString());
        
        double result = 0;
        switch ((*it)[0].unicode())
        {
            case '+':
                result = num1 + num2;
                break;

            case '-':
                result = num1 - num2;
                break;

            case '*':
                result = num1 * num2;
                break;

            case '/':
                if (num2 == 0)
                {
                    expr = {"Error"};
                    return;
                }

                else
                {
                    result = num1 / num2;
                }

                break;
        }

        QString str = QString::fromStdString(std::to_string(result));

        while (str[str.size() - 1] == '0')
        {
            str.chop(1);
        }

        if (str[str.size() - 1] == '.')
        {
            str.chop(1);
        }

        *(it - 1) = str;
        expr.erase(it, it + 2);
    }
}

std::vector<QString>::iterator ExprSolver::firstOperatorIndex(std::vector<QString>& expr)
{
    auto max_op = expr.end();
    for (auto it = expr.begin(); it != expr.end(); ++it)
    {
        if (*it == ")")
        {
            break;
        }

        if (isOperator(*it) && (max_op == expr.end() ||
            *max_op == "(" || m_op_presedence[*it] > m_op_presedence[*max_op]))
        {
            max_op = it;
        }
    }

    return max_op;
}

bool ExprSolver::isOperator(const QString& op) const
{
    if (m_op_presedence.find(op) == m_op_presedence.end())
    {
        return false;
    }

    return true;
}

#endif
