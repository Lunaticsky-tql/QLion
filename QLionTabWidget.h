//
// Created by LENOVO on 2023/5/6.
//

#ifndef QLION_QLIONTABWIDGET_H
#define QLION_QLIONTABWIDGET_H


#include <QTabWidget>
#include "QLionCodePage.h"
#include "mainwindow.h"

class QLionTabWidget: public  QTabWidget{
    Q_OBJECT

public:
    QLionTabWidget(QWidget *parent);

    void addNewTab();

    void addNewTab(const QString& qString, const QString& filePath);
    QLionCodePage* getCurrentCodePage();
    QLionCodePage* getCodePage(int index);

    void initConnections();
private:
    MainWindow *mainWindow;
};


#endif //QLION_QLIONTABWIDGET_H
