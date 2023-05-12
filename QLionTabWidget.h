//
// Created by LENOVO on 2023/5/6.
//

#ifndef QLION_QLIONTABWIDGET_H
#define QLION_QLIONTABWIDGET_H


#include <QTabWidget>
#include "QLionCodePage.h"
#include "mainwindow.h"
#include <unordered_set>
#include <unordered_map>
class QLionTabWidget: public  QTabWidget{
    Q_OBJECT



public:
    QLionTabWidget(QWidget *parent);
    void addNewTab();
    void addNewTab(const QString& qString, const QString& filePath);
    QLionCodePage* getCurrentCodePage();
    QLionCodePage* getCodePage(int index);
    QLionCodePage* getCodePage(const QString& filePath);
    void setMainWindow(MainWindow *pWindow);
    QString getLastFilePath();
    bool distinguishFileName(const QString &filePath);
    void initConnections();
    void closeTab(int index);
    void closeTabByFilePath(const QString& filePath);
    void closeTabWithoutSaving(int index);
    bool isOnTab(const QString& filePath) const;
    bool saveFile(const QString& filePath);
    bool hasTab();
    void updateTabWidgetForRename(const QString &oldFilePath, const QString &newFilePath);
    int findCurrentTabText(const QString &qString, int i);
    void selectCurrentTabSearchText(const QString &qString, int &i);
    void highlightCurrentTabText(const QString &highlightWord);
    void highlightTabText(int index, const QString &highlightWord);
    void clearCurrentTabHighlight();
    void clearTabHighlight(int index);
    // public for QLionCodePage to remove the untitledID from the set
    std::unordered_set<int> usingUntitledID;
    std::unordered_map<QString, int> usingFilePath;
    void clearSelection();
    void clearSelection(int index);
    void replaceCurrentTabSearchText(QString qString, QString qString1, int &i);
    void setCurrentPageReadOnly(bool readOnly);
    void setPageReadOnly(int index, bool readOnly);
    void updateFindReplaceHighlight(int i);
private:
    MainWindow *mainWindow;
    int lastTabIndex=-1;
};


#endif //QLION_QLIONTABWIDGET_H
