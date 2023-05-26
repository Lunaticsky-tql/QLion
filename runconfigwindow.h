//
// Created by LENOVO on 2023/5/14.
//

#ifndef QLION_RUNCONFIGWINDOW_H
#define QLION_RUNCONFIGWINDOW_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class RunConfigWindow; }
QT_END_NAMESPACE
class MainWindow;
struct RunConfigList;
class RunConfigWindow : public QWidget {
Q_OBJECT

public:
    explicit RunConfigWindow(QWidget *parent = nullptr, RunConfigList* runConfig= nullptr);

    void setMainWindow(MainWindow *mainWindow);
    void updateUI();

    ~RunConfigWindow() override;

private:
    Ui::RunConfigWindow *ui;
    MainWindow *mainWindow;
    RunConfigList *runConfig;

};


#endif //QLION_RUNCONFIGWINDOW_H
