//
// Created by LENOVO on 2023/5/3.
//

#ifndef QLION_MAINWINDOW_H
#define QLION_MAINWINDOW_H

#include <QMainWindow>
#include<QStackedWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;


private:
    Ui::MainWindow *ui;
    QString lastFilePath;
    QString lastDirPath;

    void setUpSideDock();

    void setUpConnection();
    QStackedWidget *stackedWidget{};

private slots:
    void do_act_tool_tree_view_triggered();
    void on_action_new_window_triggered();
    void on_action_exit_triggered();
    void on_action_new_file_triggered();
    void on_action_open_file_triggered();


};


#endif //QLION_MAINWINDOW_H
