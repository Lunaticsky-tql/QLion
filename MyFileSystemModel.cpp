//
// Created by LENOVO on 2023/5/11.
//

#include "MyFileSystemModel.h"

MyFileSystemModel::MyFileSystemModel(QObject *parent) : QFileSystemModel(parent) {

}

QVariant MyFileSystemModel::headerData(int section, Qt::Orientation orientation, int role) const {
    return QFileSystemModel::headerData(section, orientation, role);
}
