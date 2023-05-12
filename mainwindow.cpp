//
// Created by LENOVO on 2023/5/3.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QProcessEnvironment>
#include "mainwindow.h"
#include "ui_MainWindow.h"
#include "QLionCodePage.h"
#include "FolderTreeView.h"


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    show();
    ui->tabWidget->setMainWindow(this);
    loadOpenableSuffix();
    setUpSideDock();
    setUpConnection();
    setActions(false);
    this->setCentralWidget(ui->tabWidget);
    lastDirPath = QDir::currentPath();
    lastFilePath = QString();

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setUpSideDock() {
    ui->sideDock->setWindowTitle("File Explorer");
    auto *layout = new QVBoxLayout(ui->dockWidgetContents);
    tipOpenFolderWidget = new QWidget(this);
    auto *layout2 = new QVBoxLayout(tipOpenFolderWidget);
    auto *tipText = new QLabel("You have not yet opened a folder.", tipOpenFolderWidget);
    auto *test_pushbutton1 = new QPushButton("Open folder", tipOpenFolderWidget);
    //connect the button to open folder
    connect(test_pushbutton1, SIGNAL(clicked()), this, SLOT(on_action_open_folder_triggered()));
    auto *spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    layout2->addWidget(tipText);
    layout2->addWidget(test_pushbutton1);
    layout2->addItem(spacer);
    folderTreeView = new FolderTreeView(this);
    findReplaceView = new FindReplaceView(this);
    stackedWidget = new QStackedWidget(ui->dockWidgetContents);
    stackedWidget->addWidget(tipOpenFolderWidget);
    stackedWidget->addWidget(folderTreeView);
    stackedWidget->addWidget(findReplaceView);
    setUpFolderTreeView();
    setUpFolderTreeViewConnections();
    layout->addWidget(stackedWidget);
    stackedWidget->setCurrentIndex(0);
}

void MainWindow::setUpConnection() {
}

void MainWindow::on_action_tool_tree_view_triggered() {
    ui->action_search->setChecked(false);
    if (!ui->sideDock->isHidden()) {
        if (stackedWidget->currentIndex() == 1 || stackedWidget->currentIndex() == 0) {
            ui->sideDock->hide();
            return;
        }
    } else {
        ui->sideDock->show();
    }
    if (hasOpenedFolder) {
        stackedWidget->setCurrentIndex(1);
    } else {
        stackedWidget->setCurrentIndex(0);
    }
}

void MainWindow::on_action_search_triggered() {
    // uncheck the tool tree view action
    ui->action_tool_tree_view->setChecked(false);
    if (!ui->sideDock->isHidden()) {
        if (stackedWidget->currentIndex() == 2) {
            ui->sideDock->hide();
            return;
        }
    } else {
        ui->sideDock->show();
    }
    stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_action_new_window_triggered() {
    new MainWindow();
}

void MainWindow::on_action_exit_triggered() {
    this->close();
}

void MainWindow::on_action_new_file_triggered() {
    ui->tabWidget->addNewTab();
    setActions(true);
}

void MainWindow::openFile(const QString &filePath, bool changeLastFilePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    QString suffix = filePath.split(".").last();
    if (!openableSuffixSet.count(suffix)) {
        return;
    }
    if (changeLastFilePath) {
        lastFilePath = filePath;
    }
    //get the file name from the path
    QString fileName = filePath.split("/").last();
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    file.close();
    //let the tab widget to handle the new tab adding event
    ui->tabWidget->addNewTab(text, filePath);
    setActions(true);
}

void MainWindow::on_action_open_file_triggered() {
    QString filePath = QFileDialog::getOpenFileName(this, "Open File", lastFilePath,
                                                    tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));
    if (filePath.isEmpty()) {
        return;
    }
    openFile(filePath, true);
}

void MainWindow::on_action_open_folder_triggered() {
    hasOpenedFolder = true;
    QString dirPath = QFileDialog::getExistingDirectory(this, "Open Folder", lastDirPath);
    if (dirPath.isEmpty()) {
        return;
    }
    lastDirPath = dirPath;
    model->setRootPath(dirPath);
    folderTreeView->setRootIndex(model->index(dirPath));
    //set the title of the tree view
    //that is, set the header title of column 0
    model->setHeaderData(0, Qt::Horizontal, "Folder");
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_action_save_file_triggered() {
    QLionCodePage *currentPage = ui->tabWidget->getCurrentCodePage();
    if (currentPage != nullptr) {
        //is not "save as file"
        currentPage->saveFile(false);
    }
}

void MainWindow::on_action_save_as_file_triggered() {
    QLionCodePage *currentPage = ui->tabWidget->getCurrentCodePage();
    if (currentPage != nullptr) {
        //is "save as file"
        currentPage->saveFile(true);
    }

}

void MainWindow::on_action_copy_triggered() {
    QLionCodePage *currentPage = ui->tabWidget->getCurrentCodePage();
    if (currentPage != nullptr) {
        currentPage->copyAction();
    }
}

void MainWindow::on_action_cut_triggered() {
    QLionCodePage *currentPage = ui->tabWidget->getCurrentCodePage();
    if (currentPage != nullptr) {
        currentPage->cutAction();
    }
}

void MainWindow::on_action_paste_triggered() {
    QLionCodePage *currentPage = ui->tabWidget->getCurrentCodePage();
    if (currentPage != nullptr) {
        currentPage->paste();
    }
}


void MainWindow::setActions(bool isEnable) {
    ui->action_save_file->setEnabled(isEnable);
    ui->action_save_as_file->setEnabled(isEnable);
    ui->action_copy->setEnabled(isEnable);
    ui->action_cut->setEnabled(isEnable);
    ui->action_paste->setEnabled(isEnable);
    ui->action_undo->setEnabled(isEnable);
    findReplaceView->setCannotSearch(!isEnable);
}

QString MainWindow::getLastFilePath() {
    return lastFilePath;
}

bool MainWindow::showSaveDialog(QLionCodePage *pPage) {
    QString tabTitle = ui->tabWidget->tabText(ui->tabWidget->indexOf(pPage));
    QString msg = "Do you want to save the changes to \"" + tabTitle + "\"?";
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this, "Save File", msg,
                                 QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, QMessageBox::Yes);
    if (reply == QMessageBox::Yes) {
        //if not saved successfully,cancel the close event
        return !(pPage->saveFile(false));
    } else if (reply == QMessageBox::No) {
        //do nothing
        return false;
    } else {
        //cancel
        return true;
    }

}

FolderTreeView *MainWindow::getFolderTreeView() {
    return (FolderTreeView *) stackedWidget->widget(1);
}

void MainWindow::setUpFolderTreeView() {
    model = new QFileSystemModel(this);
    model->setRootPath(lastDirPath);
    // set the file filter
    model->setNameFilters(openableSuffixList);
    folderTreeView->setModel(model);
    folderTreeView->setRootIndex(model->index(lastDirPath));
    //only show the file name
    folderTreeView->setColumnHidden(1, true);
    folderTreeView->setColumnHidden(2, true);
    folderTreeView->setColumnHidden(3, true);
}

void MainWindow::setUpFolderTreeViewConnections() {
    connect(folderTreeView, SIGNAL(doubleClicked(QModelIndex)), this,
            SLOT(do_folderTreeView_doubleClicked(QModelIndex)));

}

void MainWindow::do_folderTreeView_doubleClicked(const QModelIndex &index) {

    QString filePath = model->filePath(index);
    if (QFileInfo(filePath).isDir()) {
        return;
    } else {
        //if the file is a file,open it
        openFile(filePath, false);
    }
}

QFileSystemModel *MainWindow::getFileSystemModel() {
    return model;
}

void MainWindow::updateTabWidgetForRename(const QString &oldFilePath, const QString &newFilePath, bool isDir) {
    //let the tab widget to handle the file path change event
    if (isDir) {
        // update all files in the dir
        //traverse dir
        // the dir has been renamed, so we need to use the new file path to traverse
        QDir dir(newFilePath);
        if (!dir.exists()) {
            qDebug() << "dir not exist";
            return;
        }
        QStringList fileList;
        traverseDir(newFilePath, fileList);
        for (auto filePath: fileList) {
            // notice that replace will change the value of filePath !!!
            QString temp = filePath;
            ui->tabWidget->updateTabWidgetForRename(filePath.replace(newFilePath, oldFilePath), temp);
        }
    } else {
        ui->tabWidget->updateTabWidgetForRename(oldFilePath, newFilePath);
    }


}

bool MainWindow::isOnTab(const QString &filePath) {
    return ui->tabWidget->isOnTab(filePath);
}

bool MainWindow::saveFile(const QString &filePath) {
    return ui->tabWidget->saveFile(filePath);
}

void MainWindow::traverseDir(const QString &dirPath, QStringList &fileList) {
    QDir dir(dirPath);
    QFileInfoList infoList = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    for (const auto &fileInfo: infoList) {
        if (fileInfo.isDir()) {
            traverseDir(fileInfo.filePath(), fileList);
        } else {
            QString suffix = QFileInfo(fileInfo.filePath()).suffix();
            if (openableSuffixSet.count(suffix) != 0) {
                fileList.append(fileInfo.filePath());
            }
        }
    }
}


bool MainWindow::deleteDir(const QString &dirPath) {
    bool result;
    QDir dir(dirPath);
    QFileInfoList infoList = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    for (const auto &fileInfo: infoList) {
        if (fileInfo.isDir()) {
            deleteDir(fileInfo.filePath());
        } else {
            //delete the file
            result = QFile::remove(fileInfo.filePath());
            if (!result) {
                QMessageBox::warning(this, "Delete File", "Delete file failed!");
                return false;
            }
        }
    }
    //delete the dir
    result = dir.rmdir(dirPath);
    if (!result) {
        QMessageBox::warning(this, "Delete Dir", "Delete dir failed!");
        return false;
    }
    return true;
}

void MainWindow::removeFile(const QString &removeFilePath, bool isDir) {
    if (isDir) {
        //traverse dir
        // the dir has been renamed, so we need to use the new file path to traverse
        QDir dir(removeFilePath);
        if (!dir.exists()) {
            qDebug() << "dir not exist";
            return;
        }
        QStringList fileList;
        traverseDir(removeFilePath, fileList);
        deleteDir(removeFilePath);
        for (const auto &filePath: fileList) {
            ui->tabWidget->closeTabByFilePath(filePath);
        }
    } else {
        //delete the file
        QFile file(removeFilePath);
        if (!file.exists()) {
            qDebug() << "file not exist";
            return;
        }
        bool result = file.remove();
        if (!result) {
            QMessageBox::warning(this, "Delete File", "Delete file failed!");
            return;
        }
        ui->tabWidget->closeTabByFilePath(removeFilePath);
    }
}

QString MainWindow::copyDir(const QString &oldDirPath, const QString &newDirPath) {
    QDir dir(oldDirPath);
    QString dirName = dir.dirName();
    QString newDirPathWithDirName = newDirPath + "/" + dirName;
    bool result = QDir().mkdir(newDirPathWithDirName);
    if (!result) {
        QMessageBox::warning(this, "Copy Dir", "Copy dir failed!");
        return "";
    }
    QFileInfoList infoList = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    for (const auto &fileInfo: infoList) {
        if (fileInfo.isDir()) {
            copyDir(fileInfo.filePath(), newDirPathWithDirName);
        } else {
            //copy the file
            QFile::copy(fileInfo.filePath(), newDirPathWithDirName + "/" + fileInfo.fileName());
        }
    }
    return newDirPathWithDirName;
}

void MainWindow::revealFileInOS(const QString &pathToReveal) {

    // See http://stackoverflow.com/questions/3490336/how-to-reveal-in-finder-or-show-in-explorer-with-qt
    // for details

    // Mac, Windows support folder or file.
#if defined(Q_OS_WIN)
    const QString explorer = QProcessEnvironment::systemEnvironment().value("WINDIR") + "\\explorer.exe";
    if (explorer.isEmpty()) {
        QMessageBox::warning(this,
                             tr("Launching Windows Explorer failed"),
                             tr("Could not find explorer.exe in path to launch Windows Explorer."));
        return;
    }
    QStringList param;
    if (!QFileInfo(pathToReveal).isDir())
        param << QLatin1String("/select,");
    param << QDir::toNativeSeparators(pathToReveal);
    auto *process = new QProcess(this);
    process->start(explorer, param);

#elif defined(Q_OS_MAC)
    Q_UNUSED(parent)
    QStringList scriptArgs;
    scriptArgs << QLatin1String("-e")
            << QString::fromLatin1("tell application \"Finder\" to reveal POSIX file \"%1\"")
            .arg(pathToReveal);
    QProcess::execute(QLatin1String("/usr/bin/osascript"), scriptArgs);
    scriptArgs.clear();
    scriptArgs << QLatin1String("-e")
            << QLatin1String("tell application \"Finder\" to activate");
    QProcess::execute("/usr/bin/osascript", scriptArgs);
#else
    // we cannot select a file here, because no file browser really supports it...
    const QFileInfo fileInfo(pathIn);
    const QString folder = fileInfo.absoluteFilePath();
    const QString app = Utils::UnixUtils::fileBrowser(Core::ICore::instance()->settings());
    QProcess browserProc;
    const QString browserArgs = Utils::UnixUtils::substituteFileBrowserParameters(app, folder);
    if (debug)
        qDebug() <<  browserArgs;
    bool success = browserProc.startDetached(browserArgs);
    const QString error = QString::fromLocal8Bit(browserProc.readAllStandardError());
    success = success && error.isEmpty();
    if (!success)
        showGraphicalShellError(parent, app, error);
#endif

}

void MainWindow::loadOpenableSuffix() {
    QFile file(":resources/keywords/suffix_support.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "open suffix file failed";
        return;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        openableSuffixSet.insert(line);
        line.prepend("*.");
        openableSuffixList.append(line);
    }
    file.close();
}


void MainWindow::dragFileAndOpen(const QString &oldPath, const QString &newDirPath, bool isShow) {
    bool isDir = QFileInfo(oldPath).isDir();
    if (isDir) {
        QString newDirPathWithDirName = copyDir(oldPath, newDirPath);
        if (!newDirPathWithDirName.isEmpty() && isShow) {
            folderTreeView->expand(folderTreeView->currentIndex());
            folderTreeView->setCurrentIndex(model->index(newDirPath));
        }
    } else {
        QString newFilePath = newDirPath + "/" + QFileInfo(oldPath).fileName();
        if (QFile::exists(newFilePath)) {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Replace File",
                                          "The file already exists, do you want to replace it?",
                                          QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                QFile::remove(newFilePath);
            } else {
                return;
            }
        }
        bool success = QFile::copy(oldPath, newFilePath);
        if (!success) {
            QMessageBox::warning(this, "Copy File", "Copy file failed!");
            return;
        }
        if (isShow) {
            folderTreeView->expand(folderTreeView->currentIndex());
            folderTreeView->setCurrentIndex(model->index(newFilePath));
            openFile(newFilePath);
        }
    }
}

void MainWindow::findInitial(const QString &searchWord) {
    if (!findIndices.empty()) {
        findIndices.clear();
    }
    int searchingIndex = 0;
    searchingIndex = ui->tabWidget->findCurrentTabText(searchWord, searchingIndex);
    while((searchingIndex = ui->tabWidget->findCurrentTabText(searchWord, searchingIndex))!=-1){
        findIndices.append(searchingIndex);
        searchingIndex+=searchWord.length();
    }
    if(!findIndices.empty()){
        ui->tabWidget->highlightCurrentTabText(searchWord);
        ui->tabWidget->selectCurrentTabSearchText(searchWord, findIndices[0]);
    }

}

bool MainWindow::hasTab() {
    return ui->tabWidget->hasTab();
}








