//
// Created by LENOVO on 2023/5/3.
//

#ifndef QLION_MAINWINDOW_H
#define QLION_MAINWINDOW_H

#include <QMainWindow>
#include<QStackedWidget>
#include <QFileSystemModel>
#include<unordered_set>
#include<QLabel>
#include "QLionCodePage.h"
#include "FolderTreeView.h"
#include "findreplaceview.h"
#include "runconfig.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
struct RunConfigList {
    QString cmakePath="";
    QString ninjaPath="";
    QStringList genPara;
    QStringList budPara;
};


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
    QString copyDir(const QString& oldDirPath, const QString& newDirPath);
    void dragFileAndOpen(const QString& oldPath, const QString& newDirPath, bool isShow=false);
    void findInitial();
    void findPrevious();
    void findNext();
    void clearFoundState();
    void replace(QString replaceWord);
    void replaceAll(QString replaceWord);
    void setSearchWord(const QString& searchWord);
    void setCurrentPageReadOnly(bool isReadOnly);
    void triggerFindIfOnSearch();
    void notFoundUIAction();
    void setConfigList(RunConfigList *pList);



private:
    Ui::MainWindow *ui;
    QString lastFilePath;
    QString lastDirPath;
    QString currentProjectPath="";
    QFileSystemModel* model;
    FolderTreeView *folderTreeView;
    FindReplaceView *findReplaceView;
    QWidget *tipOpenFolderWidget;
    std::unordered_set<QString> openableSuffixSet;
    QStringList openableSuffixList;
    QVector<int> findPositions;
    int currentFindIndex{0};
    int totalFindCount{0};
    bool hasOpenedFolder{false};
    QString searchWord;
    RunConfig *runConfig= nullptr;
    RunConfigList *runConfigList= nullptr;
    void saveProjectFiles();


    void setUpSideDock();
    void setUpConnection();
    void setUpFolderTreeViewConnections();
    void setUpFolderTreeView();
    void loadOpenableSuffix();

    QStackedWidget *stackedWidget{};

private slots:
    void on_action_tool_tree_view_triggered();
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
    void on_action_search_triggered();
    void on_action_run_project_triggered();

    void do_folderTreeView_doubleClicked(const QModelIndex &index);
    void on_action_find_triggered();
    void on_action_replace_triggered();
    void on_action_denote_triggered();

    void on_action_edit_configurations_triggered();
};


#endif //QLION_MAINWINDOW_H
