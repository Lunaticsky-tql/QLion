//
// Created by LENOVO on 2023/5/6.
//

#ifndef QLION_QLIONCODEPAGE_H
#define QLION_QLIONCODEPAGE_H
#include <QWidget>
#include <QTextEdit>
#include <QTextBrowser>
class LineNumberArea;
class QLionCodePage :public QWidget
{
    Q_OBJECT



public:
    explicit QLionCodePage(QWidget *parent = nullptr);
    void lineNumberAreaPaintEvent(QPaintEvent *pEvent);
private:
    QTextEdit *textEdit;
    LineNumberArea *lineNumberArea;
    void initFont();
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
