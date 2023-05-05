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

private slots:
    void on_act_tool_tree_view_triggered();

private:
    Ui::MainWindow *ui;

    void setUpSideDock();

    void setUpConnection();
    QStackedWidget *stackedWidget;
};


#endif //QLION_MAINWINDOW_H
