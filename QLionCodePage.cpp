//
// Created by LENOVO on 2023/5/6.
//

#include <QVBoxLayout>
#include <QPainter>
#include <QTextBlock>
#include<QScrollBar>
#include "QLionCodePage.h"

QLionCodePage::QLionCodePage(QWidget *parent) : QPlainTextEdit(parent) {
    lineNumberArea = new LineNumberArea(this);
    setLineWrapMode(QPlainTextEdit::NoWrap);
    setFrameShape(QPlainTextEdit::NoFrame);
    QColor textColor = QColor(187, 187, 187);
    setStyleSheet("color:rgb(" + QString::number(textColor.red()) + "," + QString::number(textColor.green()) + "," +
                  QString::number(textColor.blue()) + ");");
    filePath=QString();
    initConnections();
    initHighlighter();
    initFont();
    highlightCurrentLine();
    updateLineNumberAreaWidth();

}

void QLionCodePage::initFont() {
    QFont font;
    font.setFamily("Consolas");
    font.setPointSize(12);
    this->setFont(font);
    lineNumberFontWidth=fontMetrics().horizontalAdvance(QChar('0'));

}

void QLionCodePage::initConnections() {
    // highlight current cursor line
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
    // update lineNumberArea paint event
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    // update lineNumber width change
    connect(this,SIGNAL(blockCountChanged(int)),this,SLOT(updateLineNumberAreaWidth()));

}
void QLionCodePage::resizeEvent(QResizeEvent *event) {
    QPlainTextEdit::resizeEvent(event);
    QRect cr = contentsRect();
    lineNumberArea->setGeometry(0,0, getLineNumberAreaWidth(), cr.height());

}

void QLionCodePage::lineNumberAreaPaintEvent(QPaintEvent *pEvent) {
    QPainter painter(lineNumberArea);
    QColor lineNumberAreaColor = QColor(49, 51, 53);
    QColor lineNumberColor = QColor(96,99,102);
    QColor currentLineNumberColor=QColor(164, 163, 163);
    painter.fillRect(pEvent->rect(), lineNumberAreaColor);
    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int currentCursorTop=(int)blockBoundingGeometry(textCursor().block()).translated(contentOffset()).top();

    int bottom = top + (int) blockBoundingRect(block).height();
    while (block.isValid() && top <= pEvent->rect().bottom()) {
        if (block.isVisible() && bottom >= pEvent->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(currentCursorTop==top ? currentLineNumberColor : lineNumberColor);
            painter.drawText(0, top, getLineNumberAreaWidth()-lineNumberFontWidth/3, fontMetrics().height(),
                             Qt::AlignRight, number);
        }
        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }


}

void QLionCodePage::highlightCurrentLine() {
    QList <QTextEdit::ExtraSelection> extraSelections;
    QTextEdit::ExtraSelection selection;
    QColor lineColor = QColor(50, 50, 50);
    selection.format.setBackground(lineColor);
    selection.format.setProperty(QTextFormat::FullWidthSelection, true);
    selection.cursor = textCursor();
    extraSelections.append(selection);
    setExtraSelections(extraSelections);

}

void QLionCodePage::initHighlighter() {
    mHighlighter = new MyHighlighter(this->document());

}

int QLionCodePage::getLineNumberAreaWidth() {
    return QString::number(blockCount()+1).length()*lineNumberFontWidth+lineNumberFontWidth;

}


void QLionCodePage::updateLineNumberArea(const QRect &, int dy) {
    // for scroll: https://doc.qt.io/qt-6/qwidget.html#scroll
    // After scrolling, the widgets will receive paint events for the areas that need to be repainted.
    // For widgets that Qt knows to be opaque, this is only the newly exposed parts
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, 0, lineNumberArea->width(), lineNumberArea->height());

}

void QLionCodePage::updateLineNumberAreaWidth() {
    setViewportMargins(getLineNumberAreaWidth(),0,0,0);
}

void QLionCodePage::lineNumberAreaMousePressEvent(QMouseEvent *mEvent) {
    // select the current line and jump the cursor to the beginning of the next line
    int clickedLineNumber=qRound(mEvent->position().y())/fontMetrics().height()+verticalScrollBar()->value();
//    qDebug()<<clickedLineNumber;
    QTextBlock clickedBlock=document()->findBlockByLineNumber(clickedLineNumber);
    QTextCursor cursor(clickedBlock);
       cursor.movePosition(QTextCursor::QTextCursor::NextBlock,QTextCursor::KeepAnchor);
    setTextCursor(cursor);
}

void QLionCodePage::lineNumberAreaWheelEvent(QWheelEvent *wEvent) {
    // scroll the text area
    QPlainTextEdit::wheelEvent(wEvent);
}



QString QLionCodePage::getFilePath() {
    return filePath;
}

void QLionCodePage::setFilePath(const QString &filePath) {
    QLionCodePage::filePath = filePath;
}


