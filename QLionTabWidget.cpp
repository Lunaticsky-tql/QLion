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
    if (mainWindow) {
        // get the minimum unused untitledID from the set
        int newID = 1;
        // it will iterate at most size() times
        while (usingUntitledID.count(newID)) {
            newID++;
        }
        usingUntitledID.insert(newID);
        QString title = "Untitled-" + QString::number(newID);
        addTab(new QLionCodePage(this), title);
        setCurrentIndex(count() - 1);
        QLionCodePage *currentCodePage = getCurrentCodePage();
        currentCodePage->setParentTabWidget(this);
        currentCodePage->setUntitledID(newID);
    }
}

bool QLionTabWidget::distinguishFileName(const QString &filePath) {
    // as it is "distinguish", it will potentially check all the tabs
    QString fileName = QFileInfo(filePath).fileName();
    for (int i = 0; i < count(); i++) {
        //get the widget of the tab and get the file path
        QString filePathOfCurrentTab = getCodePage(i)->getFilePath();
        if (filePathOfCurrentTab.isEmpty()) {
            continue;
        } else if (filePathOfCurrentTab == filePath) {
            // if the function is called by saveAs, it saves the text in file in the opened tab, close the tab
            // because the code page calls this function will change the file path of the code page to the new file path
            closeTabWithoutSaving(i);
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
    if (mainWindow) {
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

        // if the text is too long, do not init Highlighter
        if (text.length() > 10000) {
            addTab(new QLionCodePage(this, false), fileName);
        } else {
            addTab(new QLionCodePage(this), fileName);
        }
        usingFilePath[filePath] = count() - 1;
        setCurrentIndex(count() - 1);
        auto *codePage = getCurrentCodePage();
        // do not forget to set the parentTabWidget
        getCurrentCodePage()->setParentTabWidget(this);
        codePage->setFilePath(filePath);
        codePage->setPlainText(text);
    }
}


void QLionTabWidget::closeTab(int index) {
    QLionCodePage *codePage = getCodePage(index);
    if(!codePage){
        return;
    }
    bool canceled = false;
    if (codePage->areChangesUnsaved()) {
        canceled = mainWindow->showSaveDialog(codePage);
    }
    if (canceled) {
        return;
    }
    // do not forget to update the untitledCount
    QString filePath = codePage->getFilePath();
    if (filePath.isEmpty()) {
        usingUntitledID.erase(codePage->getUntitledID());
    }
    else{
        usingFilePath.erase(filePath);
    }
    removeTab(index);
    if (count() == 0) {
        mainWindow->setActions(false);
    }
    //delete the codePage
    delete codePage;
}

void QLionTabWidget::closeTabWithoutSaving(int index) {

    QLionCodePage *codePage = getCodePage(index);
    if(!codePage){
        return;
    }
    // do not forget to update the untitledCount
    QString filePath = codePage->getFilePath();
    if (filePath.isEmpty()) {
        usingUntitledID.erase(codePage->getUntitledID());
    }
    else{
        usingFilePath.erase(filePath);
    }
    removeTab(index);
    if (count() == 0) {
        mainWindow->setActions(false);
    }
    //delete the codePage
    delete codePage;
}


void QLionTabWidget::initConnections() {
    connect(this, &QLionTabWidget::tabCloseRequested, this, &QLionTabWidget::closeTab);
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

bool QLionTabWidget::isOnTab(const QString& filePath) const {
    // directly check if the filePath is in the set can be faster
    if (usingFilePath.count(filePath)) {
        return true;
    }
    return false;

}

bool QLionTabWidget::saveFile(const QString &filePath) {
    if(!isOnTab(filePath)){
        return false;
    }
    //isOnTab guarantees that the filePath is in the map
    return getCodePage(filePath)->saveFile(false);

}

QLionCodePage *QLionTabWidget::getCodePage(const QString &filePath) {
    if(!isOnTab(filePath)){
        return nullptr;
    }
    return getCodePage(usingFilePath[filePath]);

}

void QLionTabWidget::updateTabWidgetForRename(const QString &oldFilePath, const QString &newFilePath) {
    //isOnTab guarantees that the filePath is in the map
//    qDebug()<<"updateTabWidgetForRename"<<"oldFilePath"<<oldFilePath<<"newFilePath"<<newFilePath;
    QLionCodePage* codePage=getCodePage(oldFilePath);
    if(codePage==nullptr){
        return;
    }
    codePage->changeFilePath(newFilePath);

}

void QLionTabWidget::closeTabByFilePath(const QString &filePath) {
    if(!isOnTab(filePath)){
        return;
    }
    closeTabWithoutSaving(usingFilePath[filePath]);

}

int QLionTabWidget::findCurrentTabText(const QString &qString, int i) {
    QLionCodePage* codePage=getCurrentCodePage();
    if(codePage==nullptr){
        return -1;
    }
    return codePage->toPlainText().indexOf(qString, i);
}

bool QLionTabWidget::hasTab() {
    return count()>0;
}

void QLionTabWidget::selectCurrentTabSearchText(const QString &qString, int &i) {
    QLionCodePage* codePage=getCurrentCodePage();
    if(codePage==nullptr){
        return;
    }
    codePage->selectCurrentTabSearchText(qString, i);

}

void QLionTabWidget::highlightCurrentTabText(const QString &highlightWord) {
    QLionCodePage* codePage=getCurrentCodePage();
    if(codePage==nullptr){
        return;
    }
    codePage->highlightCurrentTabText(highlightWord);
}







