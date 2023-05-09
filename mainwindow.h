//
// Created by LENOVO on 2023/5/3.
//

#ifndef QLION_MAINWINDOW_H
#define QLION_MAINWINDOW_H

#include <QMainWindow>
#include<QStackedWidget>
#include <QFileSystemModel>
#include "QLionCodePage.h"
#include "FolderTreeView.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT




public:
    explicit MainWindow(QWidget *parent = nullptr);
    void setActions(bool isEnable);
    QString getLastFilePath();
    bool showSaveDialog(QLionCodePage *pPage);
    ~MainWindow() override;
    FolderTreeView *getFolderTreeView();


private:
    Ui::MainWindow *ui;
    QString lastFilePath;
    QString lastDirPath;
    QFileSystemModel* model;


    void setUpSideDock();
    void setUpConnection();
    void setUpFolderTreeView();
    QStackedWidget *stackedWidget{};

private slots:
    void do_act_tool_tree_view_triggered();
    void on_action_new_window_triggered();
    void on_action_exit_triggered();
    void on_action_new_file_triggered();
    void on_action_open_file_triggered();
    void on_action_save_file_triggered();
    void on_action_save_as_file_triggered();
    void on_action_copy_triggered();
    void on_action_cut_triggered();
    void on_action_paste_triggered();


};


#endif //QLION_MAINWINDOW_H
