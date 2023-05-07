//
// Created by LENOVO on 2023/5/6.
//

#include <QFileInfo>
#include "QLionTabWidget.h"
#include "QLionCodePage.h"

QLionTabWidget::QLionTabWidget(QWidget *parent) : QTabWidget(parent) {
    setTabsClosable(true);
    setMovable(true);
    initConnections();


}

void QLionTabWidget::addNewTab() {
    addTab(new QLionCodePage(), "Untitled");
    setCurrentIndex(count() - 1);
}

void QLionTabWidget::addNewTab(const QString &text, const QString &filePath) {
    //check if the file is already opened
    //else if the opened file has the same name, but different path, change the tabText to distinguish them
    bool needToDistinguish = false;
    QString fileName = QFileInfo(filePath).fileName();
    for (int i = 0; i < count(); i++) {
        //get the widget of the tab and get the file path
        QString filePathOfCurrentTab = ((QLionCodePage *) widget(i))->getFilePath();
        if (filePathOfCurrentTab == filePath) {
            setCurrentIndex(i);
            return;
        } else if (QFileInfo(filePathOfCurrentTab).fileName() == fileName) {
            setTabText(i, filePathOfCurrentTab);
            needToDistinguish = true;
        }
    }
    if(needToDistinguish){
        fileName = filePath;
    }
    addTab(new QLionCodePage(), fileName);
    setCurrentIndex(count() - 1);
    auto *codePage = (QLionCodePage *) widget(count() - 1);
    codePage->setFilePath(filePath);
    codePage->setPlainText(text);
}

void QLionTabWidget::initConnections() {
    connect(this, &QLionTabWidget::tabCloseRequested, this, [this](int index) {
        removeTab(index);
    });
}

