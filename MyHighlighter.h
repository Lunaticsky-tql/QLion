//
// Created by LENOVO on 2023/5/7.
//

#ifndef QLION_MYHIGHLIGHTER_H
#define QLION_MYHIGHLIGHTER_H


#include <QSyntaxHighlighter>
#include <QRegularExpression>

class MyHighlighter : public QSyntaxHighlighter {
public:
    explicit MyHighlighter(QTextDocument *parent = nullptr);
protected:
    void highlightBlock(const QString &text) override;
private:
    QString mFontFamily="Consolas";
    int mFontSize=12;
    struct HighlightRule{
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightRule> highlightRules;
    void initFormat();
    void addNormalTextFormat();
    void addNumberFormat();
    void addStringFormat();
    void addCommentFormat();
    void addMultiLineCommentFormat(const QString &text);
};


#endif //QLION_MYHIGHLIGHTER_H
