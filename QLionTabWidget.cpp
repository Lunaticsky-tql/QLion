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
    if(mainWindow){
        // get the minimum unused untitledID from the set
        int newID = 1;
        // it will iterate at most size() times
        while(usedUntitledID.count(newID)){
            newID++;
        }
        usedUntitledID.insert(newID);
        QString title = "Untitled-"+QString::number(newID);
        addTab(new QLionCodePage(this), title);
        setCurrentIndex(count() - 1);
        QLionCodePage *currentCodePage = getCurrentCodePage();
        currentCodePage->setParentTabWidget(this);
        currentCodePage->setUntitledID(newID);
    }
}
bool QLionTabWidget::distinguishFileName(const QString &filePath) {
    QString fileName = QFileInfo(filePath).fileName();
    for (int i = 0; i < count(); i++) {
        //get the widget of the tab and get the file path
        QString filePathOfCurrentTab = getCodePage(i)->getFilePath();
        if(filePathOfCurrentTab.isEmpty())
        {
            continue;
        }else if (filePathOfCurrentTab == filePath) {
            // if the function is called by saveAs, it saves the text in file in the opened tab, close the tab
            // because the code page calls this function will change the file path of the code page to the new file path
            removeTab(i);
            return false;
        } else if (QFileInfo(filePathOfCurrentTab).fileName() == fileName) {
            setTabText(i, filePathOfCurrentTab);
            return true;
        }
    }
    return false;
}
void QLionTabWidget::addNewTab(const QString &text, const QString &filePath) {
    //check if the file is already opened
    //else if the opened file has the same name, but different path, change the tabText to distinguish them
    if(mainWindow) {
        bool needToDistinguish = false;
        QString fileName = QFileInfo(filePath).fileName();
        for (int i = 0; i < count(); i++) {
            //get the widget of the tab and get the file path
            QString filePathOfCurrentTab = getCodePage(i)->getFilePath();
            if (filePathOfCurrentTab == filePath) {
                setCurrentIndex(i);
                return;
            } else if (QFileInfo(filePathOfCurrentTab).fileName() == fileName) {
                setTabText(i, filePathOfCurrentTab);
                needToDistinguish = true;
            }
        }
        if (needToDistinguish) {
            fileName = filePath;
        }
        addTab(new QLionCodePage(this), fileName);
        setCurrentIndex(count() - 1);
        auto *codePage = getCurrentCodePage();
        // do not forget to set the parentTabWidget
        getCurrentCodePage()->setParentTabWidget(this);
        codePage->setFilePath(filePath);
        codePage->setPlainText(text);
    }
}

void QLionTabWidget::initConnections() {
    connect(this, &QLionTabWidget::tabCloseRequested, this, [this](int index) {
        QLionCodePage *codePage = getCodePage(index);
        bool canceled = false;
        if(codePage->areChangesUnsaved()){
            canceled=mainWindow->showSaveDialog(codePage);
        }
        if(canceled){
            return;
        }
        // do not forget to update the untitledCount
        if(codePage->getFilePath().isEmpty())
        {
            usedUntitledID.erase(codePage->getUntitledID());
        }
        removeTab(index);
        if(count()==0){
            mainWindow->setActions(false);
        }
    });
}

QLionCodePage *QLionTabWidget::getCurrentCodePage() {
    //thin wrapper for preventing explicit type cast in other places
    return (QLionCodePage *) currentWidget();
}

QLionCodePage *QLionTabWidget::getCodePage(int index) {
    //thin wrapper for preventing explicit type cast in other places
    return (QLionCodePage *) widget(index);
}

void QLionTabWidget::setMainWindow(MainWindow *pWindow) {
    mainWindow = pWindow;
}

QString QLionTabWidget::getLastFilePath() {
    return mainWindow->getLastFilePath();
}



