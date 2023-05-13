//
// Created by LENOVO on 2023/5/9.
//

#include <QMenu>
#include <QLineEdit>
#include <utility>
#include <QVBoxLayout>
#include <QLabel>
#include <fstream>
#include <QMessageBox>
#include "FolderTreeView.h"
#include "mainwindow.h"
#include <QMimeData>

class NewFileWidget : public QWidget {
public:
    NewFileWidget(MainWindow *parent, QString &folderPath, bool isDir = false) : QWidget(parent),
                                                                                 folderPath(folderPath) {
        mainWindow = parent;
        isDirFlag = isDir;
        initWidgetUI();
        auto *layout = new QVBoxLayout(this);
        QLabel *label;
        if (isDir) {
            label = new QLabel("New Folder", this);
        } else {
            label = new QLabel("New File", this);
        }
        layout->addWidget(label);
        lineEdit = new QLineEdit(this);
        layout->addWidget(lineEdit);
        if (isDir) {
            fileExistedLabel = new QLabel("Folder already exists", this);
        } else {
            fileExistedLabel = new QLabel("File already exists", this);
        }
        fileExistedLabel->hide();
        connect(lineEdit, &QLineEdit::textChanged, this, &NewFileWidget::fileExistedDetection);
        layout->addWidget(fileExistedLabel);
        show();
    }

protected:
    // press enter to create a new file
    void keyPressEvent(QKeyEvent *event) override {
        if (((event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return)) && !fileExistedFlag) {
            QString newFilePath = folderPath + "/" + lineEdit->text();
            if (isDirFlag) {
                QDir dir(folderPath);
                // if the folder already exists, do nothing
                if (!dir.exists(newFilePath)) {
                    dir.mkdir(newFilePath);
                    FolderTreeView *folderTreeView = mainWindow->getFolderTreeView();
                    // unfold the folder
                    folderTreeView->expand(folderTreeView->currentIndex());
                    // select the new folder
                    folderTreeView->setCurrentIndex(mainWindow->getFileSystemModel()->index(newFilePath));
                }
            } else {
                // if the file already exists, do nothing
                if (!QFile::exists(newFilePath)) {
                    std::ofstream file(folderPath.toStdString() + "/" + lineEdit->text().toStdString());
                    file.close();
                    FolderTreeView *folderTreeView = mainWindow->getFolderTreeView();
                    // unfold the folder
                    folderTreeView->expand(folderTreeView->currentIndex());
                    // select the new file
                    folderTreeView->setCurrentIndex(mainWindow->getFileSystemModel()->index(newFilePath));
                    // open the new file
                    mainWindow->openFile(newFilePath);
                }
            }
            close();
        } else if (event->key() == Qt::Key_Escape)
            close();
        else
            QWidget::keyPressEvent(event);
    }

    void fileExistedDetection(const QString &text) {
        if (text.isEmpty()) {
            // cannot create a file with empty name but do not show the file existed label
            fileExistedFlag = true;
            return;
        }
        QString newFilePath = folderPath + "/" + text;
//        qDebug() << newFilePath;
        if (QFile::exists(newFilePath)) {
            fileExistedLabel->show();
            fileExistedFlag = true;
        } else {
            fileExistedFlag = false;
            fileExistedLabel->hide();
        }
    }

private:
    MainWindow *mainWindow;
    QString folderPath;
    QLineEdit *lineEdit;
    QLabel *fileExistedLabel;
    bool fileExistedFlag = true;
    bool isDirFlag = false;

    void initWidgetUI() {
        setWindowFlags(Qt::Popup);
        //get the position of the left top corner of the parent widget
        QPoint pos = mainWindow->mapToGlobal(QPoint(0, 0));
        //get the size of the parent widget
        QSize size = mainWindow->size();
        //set the position of the left top corner of the new widget
        setGeometry(pos.x() + size.width() / 2 - 150, pos.y() + size.height() / 2 - 35, 300, 70);
    }

};

class RenameEditRect : public QLineEdit {

    using QLineEdit::QLineEdit;
public:
    RenameEditRect(QRect rect, QString filePath, FolderTreeView *parent)
            : QLineEdit(parent), oldFilePath(std::move(filePath)) {
        treeView = parent;
        show();
        setGeometry(QRect(rect.x(), rect.y() + rect.height(), rect.width(), rect.height()));
        setFocus(Qt::MouseFocusReason);
    }

protected:
    void focusOutEvent(QFocusEvent *event) override {
        Q_UNUSED(event);
        if (text() != oldFilePath) {
            renameTreeViewEntry();
        }
        close();
    }

    void keyPressEvent(QKeyEvent *event) override {

        if ((event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return)) {
            renameTreeViewEntry();
            close();
        } else if (event->key() == Qt::Key_Escape)
            close();

        else
            QLineEdit::keyPressEvent(event);
    }

private:
    QString oldFilePath;
    FolderTreeView *treeView;

    void renameTreeViewEntry() {
        if (treeView) {
            QString newFilePath = QFileInfo(oldFilePath).absoluteDir().path() + '/' + text();
            treeView->renameFile(oldFilePath, newFilePath);
        }
    }

};


FolderTreeView::FolderTreeView(MainWindow *parent) {
    mainWindow = parent;
    setAcceptDrops(true);
}

void FolderTreeView::mouseReleaseEvent(QMouseEvent *e) {
    if (e->button() == Qt::RightButton) {
        QModelIndex idx = indexAt(e->pos());
        if (idx.isValid()) {
            QMenu m;
            QString filePath = mainWindow->getFileSystemModel()->filePath(idx);
            //check is directory
            if (QFileInfo(filePath).isDir()) {
                auto *openSubMenu = new QMenu("New(&N)", &m);
                openSubMenu->addAction("New File(&F)");
                openSubMenu->addAction("New Folder(&D)");
                m.addMenu(openSubMenu);
                m.addAction("Rename(&R)");
                m.addAction("Delete(&D)");
#if defined(Q_OS_WIN)
                m.addAction("Open in Explorer(&O)");
#elif defined(Q_OS_MACOS)
                m.addAction("Open in Finder(&O)");
#else
                m.addAction("Open in File Manager(&O)");
#endif
                QAction *selected = m.exec(mapToGlobal(e->pos()));
                if (selected) {
                    QString selectedText = selected->text();
                    if (selectedText == "Rename(&R)") {
                        new RenameEditRect(visualRect(idx), filePath, this);
                    } else if (selectedText == "New File(&F)") {
                        new NewFileWidget(mainWindow, filePath);

                    } else if (selectedText == "New Folder(&D)") {
                        new NewFileWidget(mainWindow, filePath, true);
                    } else if (selectedText == "Delete(&D)") {
                        QMessageBox::StandardButton reply;
                        reply = QMessageBox::question(this, "Delete File",
                                                      "Are you sure to delete the dir? You may not be able to recover it.",
                                                      QMessageBox::Yes | QMessageBox::No);
                        if (reply == QMessageBox::Yes) {
                            mainWindow->removeFile(filePath, true);
                        }
                    } else if (selectedText == "Open in Explorer(&O)" || selectedText == "Open in Finder(&O)") {
                        mainWindow->revealFileInOS(filePath);
                    }
                }
            } else if (QFileInfo(filePath).isFile()) {
                m.addAction("Rename(&R)");
                m.addAction("Delete(&D)");
#if defined(Q_OS_WIN)
                m.addAction("Open in Explorer(&O)");
#elif defined(Q_OS_MACOS)
                m.addAction("Open in Finder(&O)");
#else
                m.addAction("Open in File Manager(&O)");
#endif
                QAction *selected = m.exec(mapToGlobal(e->pos()));
                if (selected) {
                    if (selected->text() == "Rename(&R)") {
                        new RenameEditRect(visualRect(idx), filePath, this);
                    } else if (selected->text() == "Delete(&D)") {
                        QMessageBox::StandardButton reply;
                        reply = QMessageBox::question(this, "Delete File",
                                                      "Are you sure to delete the file? You may not be able to recover it.",
                                                      QMessageBox::Yes | QMessageBox::No);
                        if (reply == QMessageBox::Yes) {
                            mainWindow->removeFile(filePath);
                        }
                    } else if (selected->text() == "Open in Explorer(&O)" || selected->text() == "Open in Finder(&O)") {
                        mainWindow->revealFileInOS(filePath);
                    }
                }
            } else {
                return;
            }

        }
    } else {
        QTreeView::mouseReleaseEvent(e);
    }

}

void FolderTreeView::renameFile(const QString &oldFilePath, const QString &newFilePath) {
    //if it is folder, rename the folder
    if (QFileInfo(oldFilePath).isDir()) {
        bool success = QDir().rename(oldFilePath, newFilePath);
        if (success) {
            mainWindow->updateTabWidgetForRename(oldFilePath, newFilePath, true);
        }
        // else do nothing
        return;
    } else {
        //if oldFilePath is on the tab, save the file first
        if (mainWindow->isOnTab(oldFilePath)) {
            mainWindow->saveFile(oldFilePath);
        }
        bool success = QFile::rename(oldFilePath, newFilePath);
        if (success) {
            //check if the file is opened in the editor
            mainWindow->updateTabWidgetForRename(oldFilePath, newFilePath);
        }
        // else do nothing
    }

}

void FolderTreeView::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void FolderTreeView::dropEvent(QDropEvent *event) {
    if (event->mimeData()->hasUrls()) {
        QList<QUrl> urls = event->mimeData()->urls();
        // get the tree node under the cursor
        QModelIndex idx = indexAt(event->position().toPoint());
        QString newDirPath;
        if (!idx.isValid()) {
            // newDirPath is the base path
            newDirPath = mainWindow->getFileSystemModel()->rootPath();
        } else {
            newDirPath = mainWindow->getFileSystemModel()->filePath(idx);
            if (!QFileInfo(newDirPath).isDir()) {
                newDirPath = QFileInfo(newDirPath).absolutePath();
            }
        }
        //  let the user ensure the action
        QMessageBox::StandardButton reply;
        QString popupText = "Are you sure to move the file(s) to" + newDirPath +
                            "?";
        reply = QMessageBox::question(this, "Move File", popupText,
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::No) {
            return;
        }
        for (int i = 0; i < urls.size(); i++) {
            QString url = urls.at(i).toLocalFile();
            if (i == urls.size() - 1) {
                mainWindow->dragFileAndOpen(url, newDirPath, true);
            } else {
                mainWindow->dragFileAndOpen(url, newDirPath, false);
            }
        }
    }
}

void FolderTreeView::dragMoveEvent(QDragMoveEvent *event) {
    if (event->mimeData()->hasUrls()) {

        event->acceptProposedAction();
    }
}

