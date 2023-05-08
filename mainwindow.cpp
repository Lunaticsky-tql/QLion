//
// Created by LENOVO on 2023/5/3.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include <QPushButton>
#include <QStackedWidget>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_MainWindow.h"
#include "QLionCodePage.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    show();
    ui->tabWidget->setMainWindow(this);
    setUpSideDock();
    setUpConnection();
    setActions(false);
    this->setCentralWidget(ui->tabWidget);
    lastDirPath = QDir::currentPath();
    lastFilePath = QString();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setUpSideDock() {
    ui->sideDock->setWindowTitle("资源管理器");
    auto *layout = new QVBoxLayout(ui->dockWidgetContents);
    auto *stackWidget1 = new QWidget();
    auto *layout2 = new QVBoxLayout(stackWidget1);
    auto *test_pushbutton1 = new QPushButton("Toggle Push Button1", stackWidget1);
    layout2->addWidget(test_pushbutton1);
    auto *stackWidget2 = new QTreeWidget(ui->dockWidgetContents);
    stackedWidget = new QStackedWidget(ui->dockWidgetContents);
    stackedWidget->addWidget(stackWidget1);
    stackedWidget->addWidget(stackWidget2);
    layout->addWidget(stackedWidget);
    auto *treeWidget = new QTreeWidget(ui->dockWidgetContents);
    layout->addWidget(treeWidget);
//    qDebug() << stackedWidget->count();
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::setUpConnection() {

    connect(ui->action_tool_tree_view, SIGNAL(triggered()), this, SLOT(do_act_tool_tree_view_triggered()));
}

void MainWindow::do_act_tool_tree_view_triggered() {
    if (ui->sideDock->isHidden()) {
        ui->sideDock->show();
        stackedWidget->setCurrentIndex(0);
        qDebug() << stackedWidget->currentIndex();
    } else {
        ui->sideDock->hide();
    }
}

void MainWindow::on_action_new_window_triggered() {
    new MainWindow();
}

void MainWindow::on_action_exit_triggered() {
    this->close();
}

void MainWindow::on_action_new_file_triggered() {
    ui->tabWidget->addNewTab();
    setActions(true);
}

void MainWindow::on_action_open_file_triggered() {
    QString filePath = QFileDialog::getOpenFileName(this, "打开文件", lastFilePath,
                                                    tr("All Files (*.*);;C++ Files (*.cpp *.h)"));
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "警告", "无法打开文件: " + file.errorString());
        return;
    }
    lastFilePath = filePath;
    //get the file name from the path
    QString fileName = filePath.split("/").last();
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    file.close();
    //let the tab widget to handle the new tab adding event
    ui->tabWidget->addNewTab(text, filePath);
    setActions(true);
}

void MainWindow::on_action_save_file_triggered() {
    QLionCodePage* currentPage=ui->tabWidget->getCurrentCodePage();
    if(currentPage!= nullptr){
        //is not "save as file"
        currentPage->saveFile(false);
    }
}
void MainWindow::on_action_save_as_file_triggered() {
    QLionCodePage* currentPage=ui->tabWidget->getCurrentCodePage();
    if(currentPage!= nullptr){
        //is "save as file"
        currentPage->saveFile(true);
    }

}
void MainWindow::on_action_copy_triggered() {
    QLionCodePage* currentPage=ui->tabWidget->getCurrentCodePage();
    if(currentPage!= nullptr){
        currentPage->copyAction();
    }
}
void MainWindow::on_action_cut_triggered() {
    QLionCodePage* currentPage=ui->tabWidget->getCurrentCodePage();
    if(currentPage!= nullptr){
        currentPage->cutAction();
    }
}
void MainWindow::on_action_paste_triggered() {
    QLionCodePage* currentPage=ui->tabWidget->getCurrentCodePage();
    if(currentPage!= nullptr){
        currentPage->paste();
    }
}



void MainWindow::setActions(bool isEnable) {
    ui->action_save_file->setEnabled(isEnable);
    ui->action_save_as_file->setEnabled(isEnable);
    ui->action_copy->setEnabled(isEnable);
    ui->action_cut->setEnabled(isEnable);
    ui->action_paste->setEnabled(isEnable);
}

QString MainWindow::getLastFilePath() {
    return lastFilePath;
}

bool MainWindow::showSaveDialog(QLionCodePage *pPage) {
    QString tabTitle=ui->tabWidget->tabText(ui->tabWidget->indexOf(pPage));
    QString msg = "是否保存对\"" + tabTitle + "\"的更改？";
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this, "保存文件", msg,
                                  QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,QMessageBox::Yes);
    if (reply == QMessageBox::Yes) {
        //if not saved successfully,cancel the close event
        return !(pPage->saveFile(false));
    } else if (reply == QMessageBox::No) {
        //do nothing
        return false;
    } else {
        //cancel
        return true;
    }

}

