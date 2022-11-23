#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;

private slots:
    void NumPressed();
    void MathBottonPressed();
    void EqualButton();
    void on_ChangeSign_clicked();
    void on_Clear_clicked();
    void on_Precent_clicked();
    void on_Dot_clicked();
};

#endif // CALCULATOR_H
