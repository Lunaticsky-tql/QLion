//
// Created by LENOVO on 2023/5/9.
//

#include <QMenu>
#include <QLineEdit>
#include <utility>
#include "FolderTreeView.h"
#include "mainwindow.h"





class RenameEditRect: public QLineEdit {

    using QLineEdit::QLineEdit;
public:
    RenameEditRect(QRect rect, QString  filePath, FolderTreeView* parent)
            : QLineEdit(parent)
            , oldFilePath(std::move(filePath))
    {
        treeView =parent;
        show();
        setGeometry(QRect(rect.x(), rect.y() + rect.height() + 1, rect.width(), rect.height()));
        setFocus(Qt::MouseFocusReason);
    }

    protected:
    void focusOutEvent(QFocusEvent* event) override
    {
        Q_UNUSED(event);
        if (text()!=oldFilePath){
            renameTreeViewEntry();
        }
        close();
    }

    void keyPressEvent(QKeyEvent* event) override
    {

        if ((event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return)) {
            renameTreeViewEntry();
            close();
        }

        else if (event->key() == Qt::Key_Escape)
            close();

        else
            QLineEdit::keyPressEvent(event);
    }

private:
    QString oldFilePath;
    FolderTreeView* treeView;

    void renameTreeViewEntry()
    {
        if (treeView)
        {
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
            m.addAction("Rename(&R)");
            m.addAction("Delete(&D)");

            QAction* selected = m.exec(mapToGlobal(e->pos()));

            if (selected) {

                QString filePath = mainWindow->getFileSystemModel()->filePath(idx);

                if (selected->text() == "Rename(&R)")
                {
                    new RenameEditRect(visualRect(idx), filePath, this);
                }
//
//                else if (selected->text() == "Remove")
//                {
//                    removeFile(filePath);
//                }
            }
        }
    }
    else
    {
        QTreeView::mouseReleaseEvent(e);
    }

}

void FolderTreeView::renameFile(const QString& oldFilePath, QString newFilePath) {
    //if oldFilePath is on the tab, save the file first
    if (mainWindow->isOnTab(oldFilePath))
    {
        mainWindow->saveFile(oldFilePath);
    }
    bool success = QFile::rename(oldFilePath, newFilePath);
    if (success)
    {
        //check if the file is opened in the editor
        mainWindow->updateTabWidget(oldFilePath, newFilePath);
    }
    // else do nothing
}
