//
// Created by LENOVO on 2023/5/6.
//

#ifndef QLION_QLIONTABWIDGET_H
#define QLION_QLIONTABWIDGET_H


#include <QTabWidget>

class QLionTabWidget: public  QTabWidget{
    Q_OBJECT

public:
    QLionTabWidget(QWidget *parent);

    void addNewTab();
};


#endif //QLION_QLIONTABWIDGET_H
