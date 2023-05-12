//
// Created by LENOVO on 2023/5/12.
//

// You may need to build the project (run Qt uic code generator) to get "ui_FindReplaceView.h" resolved

#include "findreplaceview.h"
#include "ui_FindReplaceView.h"
#include "mainwindow.h"


FindReplaceView::FindReplaceView(MainWindow *parent) :
        QWidget(parent), ui(new Ui::FindReplaceView) {
    ui->setupUi(this);
    mainWindow = parent;
    // set tool buttons
    setToolButtons(false);
    connect(ui->lineEditFind, &QLineEdit::textChanged, this, &FindReplaceView::onFindTextChanged);
}

FindReplaceView::~FindReplaceView() {
    delete ui;
}

void FindReplaceView::onFindTextChanged(const QString &text) {
    if(text.isEmpty()){
        setToolButtons(false);
        return;
    }
    mainWindow->findInitial(text);

}

void FindReplaceView::setToolButtons(bool isEnable) {
    ui->prevoiusOccurence->setEnabled(isEnable);
    ui->nextOccurence->setEnabled(isEnable);
    ui->replace->setEnabled(isEnable);
    ui->findAndReplace->setEnabled(isEnable);
    if(isEnable){
        ui->countLabel->show();
    }else{
        ui->countLabel->hide();
    }
}

void FindReplaceView::setCannotSearch(bool cannotSearch) {
    ui->lineEditFind->setEnabled(!cannotSearch);
    ui->lineEditReplace->setEnabled(!cannotSearch);
    if(cannotSearch){
        ui->noTabLabel->show();
    }else{
        ui->noTabLabel->hide();
    }
}
