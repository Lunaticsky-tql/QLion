//
// Created by LENOVO on 2023/5/9.
//

#ifndef QLION_FOLDERTREEVIEW_H
#define QLION_FOLDERTREEVIEW_H


#include <QTreeView>
class MainWindow;



class FolderTreeView : public QTreeView{
    Q_OBJECT

public:
    explicit FolderTreeView(MainWindow *parent = nullptr);
    void renameFile(const QString& oldFilePath, const QString& newFilePath);
protected:
    MainWindow* mainWindow;
    void mouseReleaseEvent(QMouseEvent* e) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
};


#endif //QLION_FOLDERTREEVIEW_H
