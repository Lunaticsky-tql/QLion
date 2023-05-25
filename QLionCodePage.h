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
    explicit QLionCodePage(QWidget *parent = nullptr,bool isInitHighLighter=true);
    void lineNumberAreaPaintEvent(QPaintEvent *pEvent);
    void lineNumberAreaMousePressEvent(QMouseEvent *mEvent);
    void lineNumberAreaWheelEvent(QWheelEvent *wEvent);
    void setParentTabWidget(QLionTabWidget *pWidget);
    QString getFilePath();
    void changeFilePath(const QString &filePath);
    bool areChangesUnsaved() const;
    void setFilePath(const QString &filePath);
    void copyAction();
    void cutAction();
    bool saveFile(bool isSaveAs);
    int getUntitledID() const;
    void setUntitledID(int id);
    void selectCurrentTabSearchText(const QString &qString, int &i);
    void highlightCurrentTabText(const QString &highlightWord);
    void replaceCurrentTabSearchText(QString &qString, QString &qString1, int &i);
    void denoteCurrentLine();
    void clearSelection();
    void setThemeColor(bool isVaporwave);
private:
    LineNumberArea *lineNumberArea;
    QLionTabWidget *myTabWidget;
    QString filePath;
    int lineNumberFontWidth=0;
    Highlighter * mHighlighter;
    bool unsaved;
    QString mFontFamily="JetBrains Mono NL";
    int untitledID=-1;
    struct ThemeColor{
        QColor textColor=QColor(255, 255, 255);
        QColor lineNumberAreaColor = QColor(49, 51, 53);
        QColor lineNumberColor = QColor(96, 99, 102);
        QColor currentLineNumberColor = QColor(164, 163, 163);
    }themeColor;
    void initConnections();

    void setMyFont();
    void initHighlighter();
    int getLineNumberAreaWidth();
    int getMyCurrentIndex();
    void setMyTabWidgetIcon(const QIcon &icon);
    void setSaved();
    void closeParenthesis(const QString &startStr, const QString &endStr);
    bool isVaporwaveTheme=false;



private slots:
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int dy);
    void updateLineNumberAreaWidth();
    void setUnsaved();


protected:
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
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
