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


};


#endif //QLION_FOLDERTREEVIEW_H
