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
    connect(ui->lineEditFind, &QLineEdit::textChanged, this, &FindReplaceView::onFindInitRequested);
    connect(ui->prevoiusOccurence, &QToolButton::clicked, this, &FindReplaceView::findPrevious);
    connect(ui->nextOccurence, &QToolButton::clicked, this, &FindReplaceView::findNext);
    connect(ui->findAndReplace, &QToolButton::clicked, this, &FindReplaceView::replace);
    connect(ui->replaceAll, &QToolButton::clicked, this, &FindReplaceView::replaceAll);
}

FindReplaceView::~FindReplaceView() {
    delete ui;
}

void FindReplaceView::onFindInitRequested(const QString &text) {
    if(text.isEmpty()){
        setToolButtons(false);
        showCountLabel(false);
        mainWindow->clearFoundState();
        mainWindow->setCurrentPageReadOnly(false);
        return;
    }
    mainWindow->setSearchWord(text);
    mainWindow->findInitial();

}
void FindReplaceView::replace(){
    QString text = ui->lineEditReplace->text();
    mainWindow->replace(text);
}
void FindReplaceView::replaceAll() {
    QString text = ui->lineEditReplace->text();
    mainWindow->replaceAll(text);
}
void FindReplaceView::setToolButtons(bool isEnable) {
    setPreviousButton(isEnable);
    setNextButton(isEnable);
    ui->replaceAll->setEnabled(isEnable);
    ui->findAndReplace->setEnabled(isEnable);
}

void FindReplaceView::setCannotSearch(bool cannotSearch) {
    ui->lineEditFind->setEnabled(!cannotSearch);
    ui->lineEditReplace->setEnabled(!cannotSearch);
    if(cannotSearch)
    {
        setToolButtons(false);
        showCountLabel(false);
    }
    if(cannotSearch){
        ui->noTabLabel->show();
    }else{
        ui->noTabLabel->hide();
    }
}

void FindReplaceView::findPrevious() {
    mainWindow->findPrevious();
}

void FindReplaceView::findNext() {
    mainWindow->findNext();
}
void FindReplaceView::setPreviousButton(bool isEnable) {
    ui->prevoiusOccurence->setEnabled(isEnable);

}

void FindReplaceView::setNextButton(bool isEnable) {
    ui->nextOccurence->setEnabled(isEnable);

}

void FindReplaceView::setNotFoundText() {
    //set the text in lineEditFind to red
    ui->lineEditFind->setStyleSheet("color: red");

}

void FindReplaceView::clearNotFoundText() {
    ui->lineEditFind->setStyleSheet("color: rgb(187, 187, 187)");
}
void FindReplaceView::updateCountLabel(int current, int total) {
    QString countText = QString::number(current) + "/" + QString::number(total);
    ui->countLabel->setText(countText);
}

void FindReplaceView::showCountLabel(bool isShow) {
    if(isShow){
        ui->countLabel->show();
    }else{
        ui->countLabel->hide();
    }
}

void FindReplaceView::setSearchWord(QString keyWord) {
    ui->lineEditFind->setText(keyWord);
}

QString FindReplaceView::getCurrentSearchWord() {
    return ui->lineEditFind->text();
}


