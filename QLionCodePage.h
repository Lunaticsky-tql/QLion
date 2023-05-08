//
// Created by LENOVO on 2023/5/6.
//

#ifndef QLION_QLIONCODEPAGE_H
#define QLION_QLIONCODEPAGE_H
#include <QWidget>
#include <QTextBrowser>
#include <QPlainTextEdit>
#include <QClipboard>
#include <QApplication>
#include "Highlighter.h"


class LineNumberArea;
class QLionTabWidget;
class QLionCodePage :public QPlainTextEdit
{
    Q_OBJECT



public:
    explicit QLionCodePage(QWidget *parent = nullptr);
    void lineNumberAreaPaintEvent(QPaintEvent *pEvent);
    void lineNumberAreaMousePressEvent(QMouseEvent *mEvent);
    void lineNumberAreaWheelEvent(QWheelEvent *wEvent);
    void setParentTabWidget(QLionTabWidget *pWidget);
    QString getFilePath();
    bool areChangesUnsaved() const;
    void setFilePath(const QString &filePath);
    void copyAction();
    void cutAction();
    bool saveFile(bool isSaveAs);
    int getUntitledID() const;
    void setUntitledID(int id);
private:
    LineNumberArea *lineNumberArea;
    QLionTabWidget *myTabWidget;
    QString filePath;
    int lineNumberFontWidth=0;
    Highlighter * mHighlighter;
    bool unsaved;
    int untitledID=-1;
    void initConnections();
    void initFont();
    void initHighlighter();
    int getLineNumberAreaWidth();
    int getMyCurrentIndex();
    void setMyTabWidgetIcon(const QIcon &icon);


private slots:
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int dy);
    void updateLineNumberAreaWidth();
    void setUnsaved();

protected:
    void resizeEvent(QResizeEvent *event) override;
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
    void mousePressEvent(QMouseEvent *event) override{
        codeEditor->lineNumberAreaMousePressEvent(event);
    }
    void wheelEvent(QWheelEvent *event) override{
        codeEditor->lineNumberAreaWheelEvent(event);
    }
private:
    QLionCodePage *codeEditor;

};

#endif //QLION_QLIONCODEPAGE_H
