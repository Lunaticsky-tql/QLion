//
// Created by LENOVO on 2023/5/6.
//

#include <QVBoxLayout>
#include <QPainter>
#include <QTextBlock>
#include<QScrollBar>
#include <QTabWidget>
#include <QFileDialog>
#include <QMessageBox>
#include "QLionCodePage.h"
#include "QLionTabWidget.h"

QLionCodePage::QLionCodePage(QWidget *parent,bool isInitHighlighter) : QPlainTextEdit(parent) {
    lineNumberArea = new LineNumberArea(this);
    setLineWrapMode(QPlainTextEdit::NoWrap);
    setFrameShape(QPlainTextEdit::NoFrame);
    QColor textColor = QColor(187, 187, 187);
    setStyleSheet("color:rgb(" + QString::number(textColor.red()) + "," + QString::number(textColor.green()) + "," +
                  QString::number(textColor.blue()) + ");");
    filePath=QString();
    initConnections();
    if(isInitHighlighter)
    {
        initHighlighter();
    }
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
    // update unsaved changes status
    connect(document(), SIGNAL(undoCommandAdded()), this,SLOT(setUnsaved()));

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
    mHighlighter = new Highlighter(this->document());
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

void QLionCodePage::copyAction() {
    // copy the current line and do not change the cursor position
    QTextCursor cursor=this->textCursor();
    if(cursor.hasSelection()){
        // if user select some text, copy the selected text
        copy();
    }
    else{
        //get the content of the current line and set the clipboard
        QTextBlock block=cursor.block();
        QString text=block.text();
        QApplication::clipboard()->setText(text);
    }

}

void QLionCodePage::cutAction() {
    // cut the current line and do not change the cursor position
    QTextCursor cursor=this->textCursor();
    if(cursor.hasSelection()){
        // if user select some text, cut the selected text
        cut();
    }
    else{
        //get the content of the current line and set the clipboard
        QTextBlock block=cursor.block();
        QString text=block.text();
        QApplication::clipboard()->setText(text);
        // delete the current line
        cursor.select(QTextCursor::LineUnderCursor);
        cursor.removeSelectedText();
    }
}

bool QLionCodePage::areChangesUnsaved() const {
    return unsaved;
}


void QLionCodePage::setMyTabWidgetIcon(const QIcon &icon) {
    myTabWidget->setTabIcon(getMyCurrentIndex(),icon);
}



int QLionCodePage::getMyCurrentIndex() {
//    qDebug()<<myTabWidget->indexOf(this);
    return myTabWidget->indexOf(this);
}

void QLionCodePage::setUnsaved() {
    if (!unsaved) {
        setMyTabWidgetIcon(QIcon(":/resources/icons/unsaved.png"));
        unsaved = true;
    }
}

void QLionCodePage::setParentTabWidget(QLionTabWidget *pWidget) {
    myTabWidget=pWidget;
}

bool QLionCodePage::saveFile(bool isSaveAs) {
    QString newFilePath;
    if (isSaveAs || filePath.isEmpty()) {
        // if the file is not saved before or user want to "save as"
        newFilePath = QFileDialog::getSaveFileName(this, "保存文件", myTabWidget->getLastFilePath(),
                                                        tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));
        qDebug()<<newFilePath;
        if (newFilePath.isEmpty()) {
            return false;
        }
        else if(newFilePath==filePath)
        {
            // if reached here, it means user want to save the file with the same name and path (so we actually do "save" rather than "save as")
            // gap the distinguishFileName function (it will close the tab with old file path) and act as "save"
            isSaveAs=false;
        }
    }
    else{
        newFilePath=filePath;
    }
    QFile file(newFilePath);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, "无法打开文件", file.errorString());
        return false;
    }
    QTextStream out(&file);
    out << toPlainText();
    file.close();
    // we saved the file successfully but still have a lot of things to do...
    // save a file with a new name may need to distinguish the file with the same name and different path
    if(filePath.isEmpty()){
        // the untitled file will turn to a normal file after saving
        // so we need to remove the untitledID from the untitledIDSet
        myTabWidget->usingUntitledID.erase(untitledID);
    }
    if(isSaveAs || filePath.isEmpty())
    {
        changeFilePath(newFilePath);
    }
    setSaved();
    return true;
}

void QLionCodePage::setUntitledID(int id) {
    untitledID=id;
}

int QLionCodePage::getUntitledID() const {
    return untitledID;
}

void QLionCodePage::changeFilePath(const QString &newFilePath) {
    // things to do when the file path is changed
    if(myTabWidget->distinguishFileName(newFilePath)){
        // distinguish the file name and set the tab text
        myTabWidget->setTabText(getMyCurrentIndex(),newFilePath);
    }
    else{
        QString fileName=QFileInfo(newFilePath).fileName();
        myTabWidget->setTabText(getMyCurrentIndex(),fileName);
    }
    // update the file path map
    myTabWidget->usingFilePath.erase(filePath);
    myTabWidget->usingFilePath[newFilePath]=getMyCurrentIndex();
    filePath = newFilePath;
}

void QLionCodePage::setSaved() {
    setMyTabWidgetIcon(QIcon());
    unsaved = false;
}



