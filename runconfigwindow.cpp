//
// Created by LENOVO on 2023/5/14.
//

// You may need to build the project (run Qt uic code generator) to get "ui_RunConfig.h" resolved

#include "runconfigwindow.h"
#include "ui_RunConfigWindow.h"
#include "mainwindow.h"

RunConfigWindow::RunConfigWindow(QWidget *parent, RunConfigList *runConfig) :
        QWidget(parent), ui(new Ui::RunConfigWindow) {
    ui->setupUi(this);
    setWindowTitle("Run Configuration");
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
    setWindowModality(Qt::WindowModal);
    this->runConfig = runConfig;
    if (runConfig != nullptr) {
        updateUI();
    }
    connect(ui->apply, &QPushButton::clicked, [=]() {
        if(this->runConfig == nullptr) {
            this->runConfig = new RunConfigList();
        }
        this->runConfig->cmakePath = ui->cmakePath->text().isEmpty() ? ui->cmakePath->placeholderText()
                                                               : ui->cmakePath->text();
        this->runConfig->generator = ui->generator->text().isEmpty() ? ui->generator->placeholderText()
                                                                     : ui->generator->text();
        this->runConfig->genPara = ui->genPara->text().isEmpty() ? ui->genPara->placeholderText().split(" ")
                                                             : ui->genPara->text().split(" ");
        this->runConfig->budPara = ui->budPara->text().isEmpty() ? ui->budPara->placeholderText().split(" ")
                                                             : ui->budPara->text().split(" ");
        mainWindow->setConfigList(this->runConfig);
        close();
    });
    connect(ui->cancel, &QPushButton::clicked, [=]() {
        close();
    });
    show();
}

RunConfigWindow::~RunConfigWindow() {
    delete ui;
}

void RunConfigWindow::setMainWindow(MainWindow *mainWindow) {
    this->mainWindow = mainWindow;
}

void RunConfigWindow::updateUI() {
    ui->cmakePath->setText(runConfig->cmakePath);
    ui->generator->setText(runConfig->generator);
    ui->genPara->setText(runConfig->genPara.join(" "));
    ui->budPara->setText(runConfig->budPara.join(" "));
}


