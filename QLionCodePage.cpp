//
// Created by LENOVO on 2023/5/6.
//

#include <QVBoxLayout>
#include <QPainter>
#include <QTextBlock>

#include "QLionCodePage.h"

QLionCodePage::QLionCodePage(QWidget *parent) : QPlainTextEdit(parent) {
    lineNumberArea = new LineNumberArea(this);
    initConnections();
    initFont();
    highlightCurrentLine();
    updateLineNumberAreaWidth();
}

void QLionCodePage::initFont() {
    QFont font;
    font.setFamily("Consolas");
    font.setPointSize(12);
    this->setFont(font);

}

void QLionCodePage::initConnections() {
    // highlight current cursor line
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
    // update lineNumberArea paint event
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));

}
void QLionCodePage::resizeEvent(QResizeEvent *event) {
    QPlainTextEdit::resizeEvent(event);
    QRect cr = contentsRect();
    lineNumberArea->setGeometry(0,0, 25, cr.height());

}

void QLionCodePage::lineNumberAreaPaintEvent(QPaintEvent *pEvent) {
    QPainter painter(lineNumberArea);
    QColor lineNumberColor = QColor(49, 51, 53);
    painter.fillRect(pEvent->rect(), lineNumberColor);
    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();
    while (block.isValid() && top <= pEvent->rect().bottom()) {
        if (block.isVisible() && bottom >= pEvent->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(QColor(255, 255, 255));
            painter.drawText(0, top, getLineNumberAreaWidth(), fontMetrics().height(),
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

}

int QLionCodePage::getLineNumberAreaWidth() {
    return 25;

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


