//
// Created by LENOVO on 2023/5/7.
//

#ifndef QLION_HIGHLIGHTER_H
#define QLION_HIGHLIGHTER_H


#include <QSyntaxHighlighter>
#include <QRegularExpression>

class Highlighter : public QSyntaxHighlighter {
public:
    explicit Highlighter(QTextDocument *parent = nullptr, const QString& fontFamily="JetBrains Mono NL", int fontSize=12);
    void setSearchText(const QString &keyWord);
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
    void initBatchHighlightFormat();
    void addVarFormat(const QString &text);
    void addNumberFormat();
    void addStringFormat(const QString &text);
    void addCommentFormat(const QString &text);
    void addMultiLineCommentFormat(const QString &text);
    void addKeywordsFormat();
    void addClassNameFormat();
    void addFunctionFormat(const QString &text);
    void addVarMemberFormat(const QString &text);
    void addIncludeFormat(const QString &text);
    void highlightSearchText(const QString &text);
    QString searchedText="";

};


#endif //QLION_HIGHLIGHTER_H
