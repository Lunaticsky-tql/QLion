//
// Created by LENOVO on 2023/5/6.
//

#include "QLionTabWidget.h"
#include "QLionCodePage.h"

QLionTabWidget::QLionTabWidget(QWidget* parent):QTabWidget(parent) {
    setTabsClosable(true);
    setMovable(true);


}

void QLionTabWidget::addNewTab() {
    addTab(new QLionCodePage(),"Untitled");
}
