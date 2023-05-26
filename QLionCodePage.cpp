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

QLionCodePage::QLionCodePage(QWidget *parent, bool isInitHighlighter) : QPlainTextEdit(parent) {
    lineNumberArea = new LineNumberArea(this);
    setLineWrapMode(QPlainTextEdit::NoWrap);
    setFrameShape(QPlainTextEdit::NoFrame);
    filePath = QString();
    initConnections();
    if (isInitHighlighter) {
        initHighlighter();
    }
    highlightCurrentLine();
    updateLineNumberAreaWidth();
}

void QLionCodePage::setMyFont() {
    QFont font;
    font.setFamily(mFontFamily);
    font.setPointSize(12);
    this->setFont(font);
    lineNumberFontWidth = fontMetrics().horizontalAdvance(QChar('0'));
    // set tab width looks like 4 spaces
    QFontMetrics metrics(font);
    setTabStopDistance(4 * metrics.horizontalAdvance(' '));
}

void QLionCodePage::initConnections() {
    // highlight current cursor line
    // it may conflict with the highlighter but it is not a big problem
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
    // update lineNumberArea paint event
    connect(this, SIGNAL(updateRequest(QRect, int)), this, SLOT(updateLineNumberArea(QRect, int)));
    // update lineNumber width change
    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth()));
    // update unsaved changes status
    connect(document(), SIGNAL(undoCommandAdded()), this, SLOT(setUnsaved()));
}

void QLionCodePage::resizeEvent(QResizeEvent *event) {
    QPlainTextEdit::resizeEvent(event);
    QRect cr = contentsRect();
    lineNumberArea->setGeometry(0, 0, getLineNumberAreaWidth(), cr.height());

}

void QLionCodePage::lineNumberAreaPaintEvent(QPaintEvent *pEvent) {
    QPainter painter(lineNumberArea);
    QColor lineNumberAreaColor = themeColor.lineNumberAreaColor;
    QColor lineNumberColor = themeColor.lineNumberColor;
    QColor currentLineNumberColor = themeColor.currentLineNumberColor;
    painter.fillRect(pEvent->rect(), lineNumberAreaColor);
    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int currentCursorTop = (int) blockBoundingGeometry(textCursor().block()).translated(contentOffset()).top();

    int bottom = top + (int) blockBoundingRect(block).height();
    while (block.isValid() && top <= pEvent->rect().bottom()) {
        if (block.isVisible() && bottom >= pEvent->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(currentCursorTop == top ? currentLineNumberColor : lineNumberColor);
            painter.drawText(0, top, getLineNumberAreaWidth() - lineNumberFontWidth / 3, fontMetrics().height(),
                             Qt::AlignRight, number);
        }
        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }


}

void QLionCodePage::highlightCurrentLine() {
    QList<QTextEdit::ExtraSelection> extraSelections;
    QTextEdit::ExtraSelection selection;
    QColor lineColor = QColor(50, 50, 50);
    selection.format.setBackground(lineColor);
    selection.format.setProperty(QTextFormat::FullWidthSelection, true);
    selection.cursor = textCursor();
    extraSelections.append(selection);
    setExtraSelections(extraSelections);

}

void QLionCodePage::initHighlighter() {
    mHighlighter = new Highlighter(this->document(), isVaporwaveTheme);
}

int QLionCodePage::getLineNumberAreaWidth() {
    return QString::number(blockCount() + 1).length() * lineNumberFontWidth + lineNumberFontWidth;

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
    setViewportMargins(getLineNumberAreaWidth(), 0, 0, 0);
}

void QLionCodePage::lineNumberAreaMousePressEvent(QMouseEvent *mEvent) {
    // select the current line and jump the cursor to the beginning of the next line
    int clickedLineNumber = qRound(mEvent->position().y()) / fontMetrics().height() + verticalScrollBar()->value();
//    qDebug()<<clickedLineNumber;
    QTextBlock clickedBlock = document()->findBlockByLineNumber(clickedLineNumber);
    QTextCursor cursor(clickedBlock);
    cursor.movePosition(QTextCursor::QTextCursor::NextBlock, QTextCursor::KeepAnchor);
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
    QTextCursor cursor = this->textCursor();
    if (cursor.hasSelection()) {
        // if user select some text, copy the selected text
        copy();
    } else {
        //get the content of the current line and set the clipboard
        QTextBlock block = cursor.block();
        QString text = block.text();
        QApplication::clipboard()->setText(text);
    }

}

void QLionCodePage::cutAction() {
    // cut the current line and do not change the cursor position
    QTextCursor cursor = this->textCursor();
    if (cursor.hasSelection()) {
        // if user select some text, cut the selected text
        cut();
    } else {
        //get the content of the current line and set the clipboard
        QTextBlock block = cursor.block();
        QString text = block.text();
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
    myTabWidget->setTabIcon(getMyCurrentIndex(), icon);
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
    myTabWidget = pWidget;
}

bool QLionCodePage::saveFile(bool isSaveAs) {
    QString newFilePath;
    if (isSaveAs || filePath.isEmpty()) {
        // if the file is not saved before or user want to "save as"
        newFilePath = QFileDialog::getSaveFileName(this, "保存文件", myTabWidget->getLastFilePath(),
                                                   tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));
        qDebug() << newFilePath;
        if (newFilePath.isEmpty()) {
            return false;
        } else if (newFilePath == filePath) {
            // if reached here, it means user want to save the file with the same name and path (so we actually do "save" rather than "save as")
            // gap the distinguishFileName function (it will close the tab with old file path) and act as "save"
            isSaveAs = false;
        }
    } else {
        newFilePath = filePath;
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
    if (filePath.isEmpty()) {
        // the untitled file will turn to a normal file after saving
        // so we need to remove the untitledID from the untitledIDSet
        myTabWidget->usingUntitledID.erase(untitledID);
    }
    if (isSaveAs || filePath.isEmpty()) {
        changeFilePath(newFilePath);
    }
    setSaved();
    return true;
}

void QLionCodePage::setUntitledID(int id) {
    untitledID = id;
}

int QLionCodePage::getUntitledID() const {
    return untitledID;
}

void QLionCodePage::changeFilePath(const QString &newFilePath) {
    // things to do when the file path is changed
    if (myTabWidget->distinguishFileName(newFilePath)) {
        // distinguish the file name and set the tab text
        myTabWidget->setTabText(getMyCurrentIndex(), newFilePath);
    } else {
        QString fileName = QFileInfo(newFilePath).fileName();
        myTabWidget->setTabText(getMyCurrentIndex(), fileName);
    }
    // update the file path map
    myTabWidget->usingFilePath.erase(filePath);
    myTabWidget->usingFilePath[newFilePath] = getMyCurrentIndex();
    filePath = newFilePath;
}

void QLionCodePage::setSaved() {
    setMyTabWidgetIcon(QIcon());
    unsaved = false;
}

void QLionCodePage::selectCurrentTabSearchText(const QString &qString, int &i) {
    QTextCursor cursor = textCursor();
    cursor.clearSelection();
    cursor.setPosition(i);
    cursor.setPosition(i + qString.length(), QTextCursor::KeepAnchor);
    setTextCursor(cursor);

}

void QLionCodePage::highlightCurrentTabText(const QString &highlightWord) {
    // just highlight all the text matched, do not select the text
    mHighlighter->setSearchText(highlightWord);
    mHighlighter->rehighlight();
}

void QLionCodePage::clearSelection() {
    QTextCursor cursor = textCursor();
    cursor.clearSelection();
    setTextCursor(cursor);
}

void QLionCodePage::replaceCurrentTabSearchText(QString &searchText, QString &replaceText, int &i) {
    QTextCursor cursor = textCursor();
    cursor.clearSelection();
    cursor.setPosition(i);
    cursor.setPosition(i + searchText.length(), QTextCursor::KeepAnchor);
    // If there is a selection, the selection is deleted and replaced by text according to the document
    // https://doc.qt.io/qt-6/qtextcursor.html#insertText
    cursor.insertText(replaceText);
    setTextCursor(cursor);

}

void QLionCodePage::denoteCurrentLine() {
    QTextCursor cursor = textCursor();
    // record the current position
    int position = cursor.position();
    int positionInBlock = cursor.positionInBlock();
//    qDebug() << position << " " << positionInBlock;
    cursor.movePosition(QTextCursor::StartOfLine);
    QString text = cursor.block().text();
    int i;
    for (i = 0; i < text.length(); i++) {
        if (text[i] == ' ' || text[i] == '\t') {
            continue;
        } else if (text[i] == '/') {
            if (i < text.length() - 1) {
                if (text[i + 1] == '/') {
                    //it is a line with spaces and a double '/', remove the denotation here
                    cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, i);
                    cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, 2);
                    cursor.removeSelectedText();
                    if (positionInBlock <= i) {
                        // if the cursor is at the left of the denotation, move the cursor to the original position
                        cursor.setPosition(position);
                    } else if (positionInBlock == i + 1) {
                        // if the cursor is at the middle of the denotation, move the cursor to the original position with a offset
                        cursor.setPosition(position - 1);
                    } else {
                        // if the cursor is at the right of the denotation
                        cursor.setPosition(position - 2);
                    }
                } else {
                    //it is a line with spaces and a single '/', add a single '/' here
                    cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, i + 1);
                    cursor.insertText("/");
                    if (positionInBlock <= i + 1) {
                        // if the cursor is at the right of the denotation, move the cursor to the original position
                        cursor.setPosition(position);
                    } else {
                        // if the cursor is at the left of the denotation, move the cursor to the original position with a offset
                        cursor.setPosition(position + 1);
                    }
                }
            } else {
                //it is a line with spaces and a single '/', add a single '/' to the end of the line
                cursor.movePosition(QTextCursor::EndOfLine);
                cursor.insertText("/");
                cursor.setPosition(position);
            }
            break;
        } else {
            // not start with spaces and '/', denote at the start of the line
            cursor.insertText(R"(//)");
            cursor.setPosition(position + 2);
            break;
        }
    }
    // move the cursor to the original position
    setTextCursor(cursor);
}

void QLionCodePage::keyPressEvent(QKeyEvent *event) {

    if (event->key() == Qt::Key_BraceLeft) {
        closeParenthesis("{", "}");
        return;
    } else if (event->key() == Qt::Key_ParenLeft) {
        closeParenthesis("(", ")");
        return;
    } else if (event->key() == Qt::Key_BracketLeft) {
        closeParenthesis("[", "]");
        return;
    } else if (event->key() == Qt::Key_BracketRight) {
        // if the cursor is at the left of the ']', move the cursor to the right
        if (checkGapClosing("]")) {
            return;
        }
    } else if (event->key() == Qt::Key_ParenRight) {
        if (checkGapClosing(")")) {
            return;
        }
    } else if (event->key() == Qt::Key_BraceRight) {
        if (checkGapClosing("}")) {
            return;
        }
    }

    // change tab to 4 spaces
    if (event->key() == Qt::Key_Tab) {
        auto cursor = textCursor();
        if (cursor.hasSelection()) {
            // insert 4 spaces at the start of each line
            auto start = cursor.selectionStart();
            auto end = cursor.selectionEnd();
            cursor.setPosition(start, cursor.MoveAnchor);
            int startBlock = cursor.blockNumber();
            cursor.setPosition(end, cursor.MoveAnchor);
            int endBlock = cursor.blockNumber();
            cursor.setPosition(start, cursor.MoveAnchor);
            cursor.movePosition(QTextCursor::StartOfLine);
            cursor.insertText("    ");
            for (int i = startBlock; i < endBlock; i++) {
                cursor.movePosition(QTextCursor::NextBlock);
                cursor.insertText("    ");
            }
            cursor.setPosition(end + 4 * (endBlock - startBlock + 1), cursor.MoveAnchor);
            setTextCursor(cursor);
        } else {
            auto pos = cursor.position();
            cursor.setPosition(pos, cursor.MoveAnchor);
            cursor.insertText("    ");
            cursor.setPosition(pos + 4);
            setTextCursor(cursor);
        }
        return;
    }
    QPlainTextEdit::keyPressEvent(event);
    // after insert \n, add spaces according to the previous line
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
        handleKeyEnterPressed();

}

void QLionCodePage::closeParenthesis(const QString &startStr, const QString &endStr) {
    auto cursor = textCursor();

    if (cursor.hasSelection()) {
        auto start = cursor.selectionStart();
        auto end = cursor.selectionEnd();
        cursor.setPosition(start, cursor.MoveAnchor);
        cursor.insertText(startStr);
        cursor.setPosition(end + startStr.size(), cursor.MoveAnchor);
        cursor.insertText(endStr);
    } else if (startStr == "{") {
        if (checkCharacterBefore(")")) {
            // only need to auto indent when the previous character is ')', which means it is a function
            auto pos = cursor.position();
            cursor.setPosition(pos, cursor.MoveAnchor);
            cursor.insertText("{\n");
            int indentation = getIndentation(cursor);
            cursor.insertText(QString(" ").repeated(indentation));
            cursor.insertText("\n");
            cursor.insertText(QString(" ").repeated(indentation - 4));
            cursor.insertText("}");
            cursor.setPosition(pos + 2 + indentation, cursor.MoveAnchor);
        } else {
            auto pos = cursor.position();
            cursor.setPosition(pos, cursor.MoveAnchor);
            cursor.insertText(startStr + endStr);
            cursor.setPosition(pos + 1, cursor.MoveAnchor);
        }
    } else {
        auto pos = cursor.position();
        cursor.setPosition(pos, cursor.MoveAnchor);
        cursor.insertText(startStr + endStr);
        cursor.setPosition(pos + 1, cursor.MoveAnchor);
    }

    setTextCursor(cursor);
}

bool QLionCodePage::checkGapClosing(const QString &endstr) {
    auto cursor = textCursor();
    auto blockText = cursor.block().text();
    auto positionInBlock = cursor.positionInBlock();
    if (positionInBlock < blockText.length() && blockText[positionInBlock] == endstr[0]) {
        cursor.movePosition(QTextCursor::Right);
        setTextCursor(cursor);
        return true;
    }
    return false;
}

bool QLionCodePage::checkCharacterBefore(const QString &endstr) {
    auto cursor = textCursor();
    auto blockText = cursor.block().text();
    auto positionInBlock = cursor.positionInBlock();
    while (positionInBlock > 0) {
        if (blockText[positionInBlock - 1] == endstr[0]) {
            return true;
        } else if (blockText[positionInBlock - 1] == ' ') {
            positionInBlock--;
        } else {
            return false;
        }
    }
    return false;
}

void QLionCodePage::setThemeColor(bool isVaporwave) {
    if (isVaporwave) {
        themeColor.textColor = QColor(0, 0, 0);
        themeColor.lineNumberAreaColor = QColor(245, 243, 235);
        themeColor.lineNumberColor = QColor(96, 96, 96);
        themeColor.currentLineNumberColor = QColor(32, 32, 32);
        mFontFamily = "Fixedsys";
        // clear extra selection
        QList<QTextEdit::ExtraSelection> extraSelections;
        setExtraSelections(extraSelections);
        disconnect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
    } else {
        themeColor.textColor = QColor(187, 187, 187);
        themeColor.lineNumberAreaColor = QColor(49, 51, 53);
        themeColor.lineNumberColor = QColor(96, 99, 102);
        themeColor.currentLineNumberColor = QColor(164, 163, 163);
        mFontFamily = "JetBrains Mono NL";
        connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
    }
    setStyleSheet("color:rgb(" + QString::number(themeColor.textColor.red()) + "," +
                  QString::number(themeColor.textColor.green()) + "," +
                  QString::number(themeColor.textColor.blue()) + ");");
    setMyFont();
    updateLineNumberAreaWidth();
    mHighlighter->setThemeColor(isVaporwave);
    mHighlighter->rehighlight();
    this->isVaporwaveTheme = isVaporwave;
}

int QLionCodePage::getIndentation(QTextCursor cursor) {
    const auto prevLineText = cursor.block().previous().text();
    int n = leadingSpaces(prevLineText);
    if (isEndingBraceOrColon(prevLineText)) {
        n += 4;
    }
//    qDebug() << n;
    return n;
}

int QLionCodePage::leadingSpaces(const QString &str) {
    int n = 0;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '\t') {
            // 4-1, because i already add 1 in the for loop
            n += 3;
        } else if (!str[i].isSpace()) {
            return i + n;
        }
    }
    return str.size() + n;
}

bool QLionCodePage::isEndingBraceOrColon(const QString &str) {
    for (int i = str.size() - 1; i >= 0; i--) {
        if (str[i] == ' ') {
            continue;
        } else if (str[i] == '{' || str[i] == ':') {
            return true;
        } else {
            return false;
        }
    }
    return false;
}

void QLionCodePage::handleKeyEnterPressed() {
    auto cursor = textCursor();
    int indentation = getIndentation(cursor);
    cursor.insertText(QString(" ").repeated(indentation));
    setTextCursor(cursor);


}



