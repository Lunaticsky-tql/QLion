//
// Created by LENOVO on 2023/5/3.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include <QPushButton>
#include <QStackedWidget>
#include <QTreeWidget>
#include <QVBoxLayout>
#include "mainwindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setUpSideDock();
    setUpConnection();

    this->setCentralWidget(ui->tabWidget);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setUpSideDock() {
    ui->sideDock->setWindowTitle("资源管理器");
    auto *layout = new QVBoxLayout(ui->dockWidgetContents);
    auto *stackWidget1=new QWidget();
    auto *layout2=new QVBoxLayout(stackWidget1);
    auto *test_pushbutton1=new QPushButton("Toggle Push Button1",stackWidget1);
    layout2->addWidget(test_pushbutton1);
    auto *stackWidget2=new QTreeWidget(ui->dockWidgetContents);
    stackedWidget=new QStackedWidget(ui->dockWidgetContents);
    stackedWidget->addWidget(stackWidget1);
    stackedWidget->addWidget(stackWidget2);
    layout->addWidget(stackedWidget);
    auto *treeWidget=new QTreeWidget(ui->dockWidgetContents);
    layout->addWidget(treeWidget);
    qDebug()<<stackedWidget->count();
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::setUpConnection() {

    connect(ui->action_tool_tree_view, SIGNAL(triggered()),this, SLOT(on_act_tool_tree_view_triggered()));
}

void MainWindow::on_act_tool_tree_view_triggered(){
    if(ui->sideDock->isHidden()){
        ui->sideDock->show();
        stackedWidget->setCurrentIndex(0);
        qDebug()<<stackedWidget->currentIndex();
    }else
    {
        ui->sideDock->hide();
    }
}
