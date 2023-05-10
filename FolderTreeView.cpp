//
// Created by LENOVO on 2023/5/9.
//

#include <QMenu>
#include <QLineEdit>
#include <utility>
#include <QVBoxLayout>
#include <QLabel>
#include <fstream>
#include "FolderTreeView.h"
#include "mainwindow.h"

class NewFileWidget : public QWidget {
public:
    NewFileWidget(MainWindow *parent, QString &folderPath) : QWidget(parent), folderPath(folderPath) {
        mainWindow = parent;
        initWidgetUI();
        auto *layout = new QVBoxLayout(this);
        auto *label = new QLabel("New File", this);
        layout->addWidget(label);
        lineEdit = new QLineEdit(this);
        layout->addWidget(lineEdit);
        fileExistedLabel = new QLabel("File already exists", this);
        fileExistedLabel->hide();
        connect(lineEdit, &QLineEdit::textChanged, this, &NewFileWidget::fileExisted);
        layout->addWidget(fileExistedLabel);
        show();
    }

protected:
    // press enter to create a new file
    void keyPressEvent(QKeyEvent *event) override {
        if (((event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return)) && !fileExistedFlag) {
            // create a new file using std::ofstream
            QString newFilePath = folderPath + "/" + lineEdit->text();
            // if the file already exists, do nothing
            if (!QFile::exists(newFilePath)) {
                std::ofstream file(folderPath.toStdString() + "/" + lineEdit->text().toStdString());
                file.close();
            }
            close();
        } else if (event->key() == Qt::Key_Escape)
            close();
        else
            QWidget::keyPressEvent(event);
    }

    void fileExisted(const QString &text) {
        if(text.isEmpty())
        {
            // cannot create a file with empty name but do not show the file existed label
            fileExistedFlag = true;
            return;
        }
        QString newFilePath = folderPath + "/" + text;
        qDebug() << newFilePath;
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
}

void FolderTreeView::mouseReleaseEvent(QMouseEvent *e) {
    if (e->button() == Qt::RightButton) {
        QModelIndex idx = indexAt(e->pos());
        if (idx.isValid()) {
            QMenu m;
            QString filePath = mainWindow->getFileSystemModel()->filePath(idx);
            //check is directory
            if (QFileInfo(filePath).isDir()) {
                m.addAction("New File(&F)");
                m.addAction("Rename(&R)");
                m.addAction("Delete(&D)");
                QAction *selected = m.exec(mapToGlobal(e->pos()));
                if (selected) {

                    if (selected->text() == "Rename(&R)") {
                        new RenameEditRect(visualRect(idx), filePath, this);
                    } else if (selected->text() == "New File(&F)") {
                        // add new file to the directory
                        // pop up a dialog to get the name of the file
                        // add the file to the directory
                        new NewFileWidget(mainWindow, filePath);

                    } else if (selected->text() == "Delete(&D)") {
                    }
                }
            } else if (QFileInfo(filePath).isFile()) {
                m.addAction("Rename(&R)");
                m.addAction("Delete(&D)");
                QAction *selected = m.exec(mapToGlobal(e->pos()));
                if (selected) {

                    if (selected->text() == "Rename(&R)") {
                        new RenameEditRect(visualRect(idx), filePath, this);
                    }
//
//                else if (selected->text() == "Remove")
//                {
//                    removeFile(filePath);
//                }
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
            mainWindow->updateTabWidget(oldFilePath, newFilePath, true);
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
            mainWindow->updateTabWidget(oldFilePath, newFilePath);
        }
        // else do nothing
    }

}
