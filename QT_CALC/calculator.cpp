#include "calculator.h"
#include "./ui_calculator.h"
#include <iostream>

double calcVal = 0.0;
bool divTrigger = false;
bool mulTrigger = false;
bool subTrigger = false;
bool addTrigger = false;
bool precentTrigger = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

//    ui->Display->setText(QString::number(calcVal));
    QPushButton* numBottons[10];

    for (int i = 0; i < 10; ++i) {
        QString butName = "Button_" + QString::number(i);
        numBottons[i] = Calculator::findChild<QPushButton*>(butName);
        connect(numBottons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    connect(ui->Add, SIGNAL(released()), this, SLOT(MathBottonPressed()));
    connect(ui->Multiple, SIGNAL(released()), this, SLOT(MathBottonPressed()));
    connect(ui->Sub, SIGNAL(released()), this, SLOT(MathBottonPressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathBottonPressed()));
    connect(ui->Equal, SIGNAL(released()), this, SLOT(EqualButton()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed() {
    QPushButton* button = (QPushButton*)sender();
    QString butval = button->text();
    QString displayVal = ui->Display->text();

    if ((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)) {
        ui->Display->setText(displayVal + butval);
    } else {
        QString newVal = displayVal + butval;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal, 'g', 15));
        std::cout << ", ic heto" << std::endl;
    }
}

void Calculator::MathBottonPressed() {
    divTrigger = false;
    mulTrigger = false;
    subTrigger = false;
    addTrigger = false;
    precentTrigger = false;

    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton* button = (QPushButton*)sender();
    QString butVal = button->text();

    if (QString::compare(butVal, "÷", Qt::CaseInsensitive) == 0) {
        divTrigger = true;
    }
    else if (QString::compare(butVal, "+", Qt::CaseInsensitive) == 0) {
        addTrigger = true;
    }
    else if (QString::compare(butVal, "x", Qt::CaseInsensitive) == 0) {
        mulTrigger = true;
    }
    else if (QString::compare(butVal, "-", Qt::CaseInsensitive) == 0) {
        subTrigger = true;
    }

    ui->Display->setText("");
}

void Calculator::EqualButton() {
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();

    if (addTrigger || subTrigger || mulTrigger || divTrigger) {
        if (addTrigger) {
            solution = calcVal + dblDisplayVal;
        }
        else if (mulTrigger) {
            solution = calcVal * dblDisplayVal;
        }
        else if (subTrigger) {
            solution = calcVal - dblDisplayVal;
        }
        else if (divTrigger) {
            solution = calcVal / dblDisplayVal;
        }
    }
    ui->Display->setText(QString::number(solution));
}

void Calculator::on_ChangeSign_clicked() {
    ui->Display->setText(QString::number((ui->Display->text()).toDouble() * (-1)));
}

void Calculator::on_Clear_clicked() {
    ui->Display->clear();
    ui->Display->setText("0");
}

void Calculator::on_Precent_clicked() {
    ui->Display->setText(QString::number((ui->Display->text()).toDouble() * (0.01)));
}

void Calculator::on_Dot_clicked() {
    if (!(ui->Display->text().contains(','))) {
        std::cout << "," << std::endl;
        ui->Display->setText(ui->Display->text() + ",");
    }
}

