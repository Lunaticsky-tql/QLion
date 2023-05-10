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
    void renameFile(const QString& oldFilePath, QString newFilePath);
protected:
    MainWindow* mainWindow;
    void mouseReleaseEvent(QMouseEvent* e) override;

};


#endif //QLION_FOLDERTREEVIEW_H
