//
// Created by LENOVO on 2023/5/14.
//

// You may need to build the project (run Qt uic code generator) to get "ui_RunConfig.h" resolved

#include "runconfig.h"
#include "ui_RunConfig.h"
#include "mainwindow.h"

RunConfig::RunConfig(QWidget *parent, RunConfigList *runConfig) :
        QWidget(parent), ui(new Ui::RunConfig) {
    ui->setupUi(this);
    setWindowTitle("Run Configuration");
    setAttribute(Qt::WA_DeleteOnClose);
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
        this->runConfig->ninjaPath = ui->ninjaPath->text().isEmpty() ? ui->ninjaPath->placeholderText()
                                                               : ui->ninjaPath->text();
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

RunConfig::~RunConfig() {
    delete ui;
}

void RunConfig::setMainWindow(MainWindow *mainWindow) {
    this->mainWindow = mainWindow;
}

void RunConfig::updateUI() {
    ui->cmakePath->setText(runConfig->cmakePath);
    ui->ninjaPath->setText(runConfig->ninjaPath);
    ui->genPara->setText(runConfig->genPara.join(" "));
    ui->budPara->setText(runConfig->budPara.join(" "));
}


