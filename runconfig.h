//
// Created by LENOVO on 2023/5/14.
//

#ifndef QLION_RUNCONFIG_H
#define QLION_RUNCONFIG_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class RunConfig; }
QT_END_NAMESPACE
class MainWindow;
struct RunConfigList;
class RunConfig : public QWidget {
Q_OBJECT

public:
    explicit RunConfig(QWidget *parent = nullptr, RunConfigList* runConfig= nullptr);

    void setMainWindow(MainWindow *mainWindow);
    void updateUI();

    ~RunConfig() override;

private:
    Ui::RunConfig *ui;
    MainWindow *mainWindow;
    RunConfigList *runConfig;

};


#endif //QLION_RUNCONFIG_H
