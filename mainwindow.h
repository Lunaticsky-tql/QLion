//
// Created by LENOVO on 2023/5/3.
//

#ifndef QLION_MAINWINDOW_H
#define QLION_MAINWINDOW_H

#include <QMainWindow>
#include<QStackedWidget>
#include <QFileSystemModel>
#include<unordered_set>
#include "QLionCodePage.h"
#include "FolderTreeView.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT




public:
    explicit MainWindow(QWidget *parent = nullptr);
    void setActions(bool isEnable);
    QString getLastFilePath();
    bool showSaveDialog(QLionCodePage *pPage);
    ~MainWindow() override;
    QFileSystemModel* getFileSystemModel();
    FolderTreeView *getFolderTreeView();
    bool isOnTab(const QString& filePath);
    void updateTabWidgetForRename(const QString& oldFilePath, const QString& newFilePath, bool isDir= false);
    void removeFile(const QString& removeFilePath, bool isDir=false);
    void traverseDir(const QString& dirPath, QStringList &fileList);
    bool deleteDir(const QString& dirPath);
    bool saveFile(const QString& filePath);
    void revealFileInOS(const QString &pathToReveal);
    // make public for FolderTreeView
    void openFile(const QString& filePath, bool changeLastFilePath=false);
    void addAndOpenFile(const QString& oldFilePath, const QString& newFilePath,bool isDir=false);
    QString copyDir(const QString& oldDirPath, const QString& newDirPath);
    void dragFileAndOpen(const QString& oldPath, const QString& newDirPath, bool isShow=false);

private:
    Ui::MainWindow *ui;
    QString lastFilePath;
    QString lastDirPath;
    QFileSystemModel* model;
    FolderTreeView *folderTreeView;
    QWidget *tipOpenFolderWidget;
    std::unordered_set<QString> openableSuffixSet;
    QStringList openableSuffixList;


    void setUpSideDock();
    void setUpConnection();
    void setUpFolderTreeViewConnections();
    void setUpFolderTreeView();
    void loadOpenableSuffix();

    QStackedWidget *stackedWidget{};

private slots:
    void do_act_tool_tree_view_triggered();
    void on_action_new_window_triggered();
    void on_action_exit_triggered();
    void on_action_new_file_triggered();
    void on_action_open_file_triggered();
    void on_action_open_folder_triggered();
    void on_action_save_file_triggered();
    void on_action_save_as_file_triggered();
    void on_action_copy_triggered();
    void on_action_cut_triggered();
    void on_action_paste_triggered();

    void do_folderTreeView_doubleClicked(const QModelIndex &index);


};


#endif //QLION_MAINWINDOW_H
