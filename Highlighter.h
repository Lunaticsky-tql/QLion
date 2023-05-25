//
// Created by LENOVO on 2023/5/7.
//

#ifndef QLION_HIGHLIGHTER_H
#define QLION_HIGHLIGHTER_H


#include <QSyntaxHighlighter>
#include <QRegularExpression>

class Highlighter : public QSyntaxHighlighter {
public:
    Highlighter(QTextDocument *parent = nullptr, bool isVaporwaveTheme=false);
    void setSearchText(const QString &keyWord);
    void setThemeColor(bool isVaporwave);
protected:
    void highlightBlock(const QString &text) override;
private:
    QString mFontFamily="JetBrains Mono NL";
    int mFontSize=12;
    struct HighlightRule{
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightRule> keywordRules;

    void addVarFormat(const QString &text);
    void addNumberFormat(const QString &text);
    void addStringFormat(const QString &text);
    void addCommentFormat(const QString &text);
    void addMultiLineCommentFormat(const QString &text);
    void addKeywordsFormat();
    void addPunctuationFormat(const QString &text);
    void addClassNameFormat(const QString & text);
    void addFunctionFormat(const QString &text);
    void addVarMemberFormat(const QString &text);
    void addIncludeFormat(const QString &text);
    void highlightSearchText(const QString &text);
    QString searchedText="";
    struct HighlighterThemeColor{
        QColor plainTextColor;
        QColor varColor = QColor(255, 255, 255);
        QColor numberColor = QColor(255, 255, 255);
        QColor stringColor = QColor(255, 255, 255);
        QColor commentColor = QColor(255, 255, 255);
        QColor keywordsColor = QColor(255, 255, 255);
        QColor punctuationColor = QColor(255, 255, 255);
        QColor classNameColor = QColor(255, 255, 255);
        QColor functionColor = QColor(255, 255, 255);
        QColor varMemberColor = QColor(255, 255, 255);
        QColor includeColor = QColor(255, 255, 255);
        QColor searchedTextBackgroundColor = QColor(255, 255, 255);
    }themeColor;

};


#endif //QLION_HIGHLIGHTER_H
