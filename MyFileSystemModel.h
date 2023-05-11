//
// Created by LENOVO on 2023/5/11.
//

#ifndef QLION_MYFILESYSTEMMODEL_H
#define QLION_MYFILESYSTEMMODEL_H


#include <QFileSystemModel>

class MyFileSystemModel : public QFileSystemModel{
    Q_OBJECT
public:
    explicit MyFileSystemModel(QObject *parent = nullptr);
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;


};


#endif //QLION_MYFILESYSTEMMODEL_H
