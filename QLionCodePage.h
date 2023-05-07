//
// Created by LENOVO on 2023/5/6.
//

#ifndef QLION_QLIONCODEPAGE_H
#define QLION_QLIONCODEPAGE_H
#include <QWidget>
#include <QTextBrowser>
#include <QPlainTextEdit>

class LineNumberArea;
class QLionCodePage :public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit QLionCodePage(QWidget *parent = nullptr);
    void lineNumberAreaPaintEvent(QPaintEvent *pEvent);
private:
    LineNumberArea *lineNumberArea;
    void initConnections();
    void initFont();
    void initHighlighter();
    int getLineNumberAreaWidth();


private slots:
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int dy);
    void updateLineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event) override;
//    void keyPressEvent(QKeyEvent *event) override;
//    void focusInEvent(QFocusEvent *event) override;
//    void focusOutEvent(QFocusEvent *event) override;

};

class LineNumberArea:public QWidget{
public :
    explicit LineNumberArea(QLionCodePage *editor):QWidget(editor){
        codeEditor = editor;
    }
protected:
    void paintEvent(QPaintEvent *event) override{
        codeEditor->lineNumberAreaPaintEvent(event);
    }
private:
    QLionCodePage *codeEditor;
};

#endif //QLION_QLIONCODEPAGE_H
