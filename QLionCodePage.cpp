//
// Created by LENOVO on 2023/5/6.
//

#include <QVBoxLayout>

#include "QLionCodePage.h"

QLionCodePage::QLionCodePage(QWidget *parent) : QWidget(parent) {
    auto *hLayout = new QHBoxLayout(this);
    textEdit = new QTextEdit();
    lineNumberArea = new LineNumberArea(this);
    hLayout->setSpacing(0);
    hLayout->setContentsMargins(0,0,0,0);
    lineNumberArea->setMinimumWidth(25);
    lineNumberArea->setMaximumWidth(25);
    hLayout->addWidget(lineNumberArea);
    hLayout->addWidget(textEdit);
    initFont();
}

void QLionCodePage::initFont() {
    QFont font;
    font.setFamily("Consolas");
    font.setPointSize(12);
    textEdit->setFont(font);

}

void QLionCodePage::lineNumberAreaPaintEvent(QPaintEvent *pEvent) {

}
