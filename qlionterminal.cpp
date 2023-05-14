//
// Created by LENOVO on 2023/5/13.
//

// You may need to build the project (run Qt uic code generator) to get "ui_QLionTerminal.h" resolved

#include <QMessageBox>
#include "qlionterminal.h"
#include "ui_QLionTerminal.h"


QLionTerminal::QLionTerminal(QWidget *parent) :
        QWidget(parent), ui(new Ui::QLionTerminal) {
    process = new QProcess();
    ui->setupUi(this);
    initConnections();

}

QLionTerminal::~QLionTerminal() {
    delete ui;
}

void QLionTerminal::runCommand() {
    ui->toolButton_run->setEnabled(false);
    ui->toolButton_stop->setEnabled(true);
    QString fullCommand = command + " " + args.join(" ");
    qDebug() << fullCommand;
    ui->plainTextEdit->appendPlainText(fullCommand);
    process->setReadChannel(QProcess::StandardOutput);
    process->start(command, args);
    ui->plainTextEdit->clear();
}

void QLionTerminal::readData() {
    QByteArray data = process->readAllStandardOutput();
    QString str = QString::fromLocal8Bit(data);
    ui->plainTextEdit->appendPlainText(str);
}


void QLionTerminal::setCommand(const QString &command, const QStringList &args, RunStatus type) {
    this->command = command;
    this->args = args;
    this->status = type;
//    qDebug()<<static_cast<int>(status);
}


void QLionTerminal::showError(QProcess::ProcessError errorCode) {
    switch (errorCode) {
        case QProcess::FailedToStart:
            QMessageBox::warning(this, "Error", "Process FailedToStart");
            break;
        case QProcess::Crashed:
            ui->plainTextEdit->appendPlainText("Process killed");
            break;
        case QProcess::Timedout:
            QMessageBox::warning(this, "Error", "Timeout");
            break;
        case QProcess::WriteError:
            QMessageBox::warning(this, "Error", "WriteError");
            break;
        case QProcess::ReadError:
            QMessageBox::warning(this, "Error", "ReadError");
            break;
        case QProcess::UnknownError:
            QMessageBox::warning(this, "Error", "UnknownError");
            break;
    }
    ui->toolButton_run->setEnabled(true);
    ui->toolButton_stop->setEnabled(false);

}

void QLionTerminal::showFinished(int exitCode, QProcess::ExitStatus exitStatus) {
    if (exitStatus == QProcess::CrashExit) {
        return;
    }
    QString tip = "Process finished with exit code " + QString::number(exitCode);
    ui->plainTextEdit->appendPlainText(tip);
    ui->toolButton_run->setEnabled(true);
    ui->toolButton_stop->setEnabled(false);
//    qDebug()<<static_cast<int>(status);
    switch (status){
        case RunStatus::IDLE:
            break;
        case RunStatus::GENERATE:
            emit runFinished(exitCode,RunStatus::GENERATE);
            break;
        case RunStatus::BUILD:
            emit runFinished(exitCode,RunStatus::BUILD);
            break;
        case RunStatus::RUN:
            emit runFinished(exitCode,RunStatus::RUN);
            ui->plainTextEdit->appendPlainText("Who are you....? I am....");
            status=RunStatus::IDLE;
            break;
        default:
            break;
    }
}


void QLionTerminal::stopCommand() {
    process->kill();
    ui->toolButton_run->setEnabled(true);
}

void QLionTerminal::initConnections() {
    connect(ui->toolButton_run, &QToolButton::clicked, this, &QLionTerminal::runCommand);
    connect(ui->toolButton_stop, &QToolButton::clicked, this,&QLionTerminal::stopCommand);
    connect(process, &QProcess::readyReadStandardOutput, this, &QLionTerminal::readData);
    connect(process, &QProcess::errorOccurred, this, &QLionTerminal::showError);
    connect(process, &QProcess::finished, this, &QLionTerminal::showFinished);
    connect(ui->toolButton_hide, &QToolButton::clicked, this, &QLionTerminal::hideTerminal);

}

void QLionTerminal::hideTerminal() {
    stopCommand();
    this->hide();
}



