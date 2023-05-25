//
// Created by LENOVO on 2023/5/7.
//

#include <QFile>
#include "Highlighter.h"

Highlighter::Highlighter(QTextDocument *parent,bool isVaporwaveTheme) : QSyntaxHighlighter(
        parent){
    setThemeColor(isVaporwaveTheme);
    addKeywordsFormat();
}

void Highlighter::addVarFormat(const QString &text) {
    HighlightRule normalVarRole;
    normalVarRole.pattern = QRegularExpression("[a-zA-Z0-9_]+");
    normalVarRole.format.setForeground(themeColor.varColor);
    normalVarRole.format.setFont(QFont(mFontFamily, mFontSize));
    QRegularExpressionMatchIterator matchIterator = normalVarRole.pattern.globalMatch(text);
    while (matchIterator.hasNext()) {
        QRegularExpressionMatch match = matchIterator.next();
        setFormat(match.capturedStart(), match.capturedLength(), normalVarRole.format);
    }
}


void Highlighter::addNumberFormat(const QString &text) {
    QVector<HighlightRule> numberHighlightRules;
    QColor color = themeColor.numberColor;
    HighlightRule intRule;
    intRule.pattern = QRegularExpression(R"(\b[0-9]+\b)");
    intRule.format.setForeground(color);
    HighlightRule hexIntRule;
    hexIntRule.pattern = QRegularExpression(R"(\b0[Xx][0-9a-fA-F]+\b)");
    hexIntRule.format.setForeground(color);
    HighlightRule floatRule;
    floatRule.pattern = QRegularExpression(R"(((([0-9]*[.][0-9]*([eE][+-]?[0-9]+)?)|([0-9]+[eE][+-]?[0-9]+))[fLlL]?))");
    floatRule.format.setForeground(color);
    numberHighlightRules.append(intRule);
    numberHighlightRules.append(hexIntRule);
    numberHighlightRules.append(floatRule);
    for (auto &rule: numberHighlightRules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}


void Highlighter::addStringFormat(const QString &text) {
    QVector<HighlightRule> stringHighlightRules;
    QColor color = themeColor.stringColor;
    HighlightRule rule1;
    //"xxx"
    rule1.pattern = QRegularExpression(R"("[^"]*")");
    rule1.format.setForeground(color);
    stringHighlightRules.append(rule1);
    HighlightRule rule2;
    //'xxx'
    rule2.pattern = QRegularExpression(R"('[^']*')");
    rule2.format.setForeground(color);
    stringHighlightRules.append(rule2);
    for (auto &rule: stringHighlightRules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}


void Highlighter::addPunctuationFormat(const QString &text) {
// ; and ,
    HighlightRule rule;
    rule.pattern = QRegularExpression(R"([,;])");
    rule.format.setForeground(themeColor.punctuationColor);
    rule.format.setFont(QFont(mFontFamily, mFontSize));
    QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
    while (matchIterator.hasNext()) {
        QRegularExpressionMatch match = matchIterator.next();
        setFormat(match.capturedStart(), match.capturedLength(), rule.format);
    }
}


void Highlighter::addCommentFormat(const QString &text) {
    HighlightRule rule;
    rule.pattern = QRegularExpression(R"(//[^\n]*)");
    rule.format.setForeground(themeColor.commentColor);
    rule.format.setFont(QFont(mFontFamily, mFontSize));
    QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
    while (matchIterator.hasNext()) {
        QRegularExpressionMatch match = matchIterator.next();
        setFormat(match.capturedStart(), match.capturedLength(), rule.format);
    }
}

//notice: it was called line by line
void Highlighter::addMultiLineCommentFormat(const QString &text) {
    //mark the start of the comment
    setCurrentBlockState(0);
    QRegularExpression startExpression(R"(/\*)");
    QRegularExpression endExpression(R"(\*/)");
    QTextCharFormat multiLineCommentFormat;
    multiLineCommentFormat.setForeground(themeColor.commentColor);
    multiLineCommentFormat.setFont(QFont(mFontFamily, mFontSize));
    long long startIndex = 0;
    // that is, if the previous line is not a comment
    if (previousBlockState() != 1)
        startIndex = startExpression.match(text).capturedStart();
    //if the previous line is a comment, we should start from the beginning of the line (startIndex=0)
    while (startIndex >= 0) {
        QRegularExpressionMatch endMatch = endExpression.match(text, startIndex);
        long long endIndex = endMatch.capturedStart();
        long long commentLength = 0;
        if (endIndex == -1) {
            // we still in a comment
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            // we find the end of the comment
            commentLength = endIndex - startIndex + endMatch.capturedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = startExpression.match(text, startIndex + commentLength).capturedStart();
    }
}

void Highlighter::addVarMemberFormat(const QString &text) {
    HighlightRule varMemberRole;
    // we assume that the var member is like this: .varMember ('.' implies the var is a member of a class)
    varMemberRole.pattern = QRegularExpression(R"([.][a-zA-Z_][a-zA-Z0-9_]*)");
    varMemberRole.format.setForeground(themeColor.varMemberColor);
    varMemberRole.format.setFont(QFont(mFontFamily, mFontSize));
    QRegularExpressionMatchIterator matchIterator = varMemberRole.pattern.globalMatch(text);
    QTextCharFormat plainFormat;
    plainFormat.setForeground(themeColor.plainTextColor);
    plainFormat.setFont(QFont(mFontFamily, mFontSize));
    while (matchIterator.hasNext()) {
        QRegularExpressionMatch match = matchIterator.next();
        // skip the first character '.'
        // the '.' is matched by the float pattern, so we should set it to plain format here
        setFormat(match.capturedStart(), 1, plainFormat);
        setFormat(match.capturedStart() + 1, match.capturedLength() - 1, varMemberRole.format);
    }
}

void Highlighter::addIncludeFormat(const QString &text) {
    HighlightRule rule;
    rule.pattern = QRegularExpression(R"(#include\s*[<"][a-zA-Z0-9_./\\]*[>"])");
    rule.format.setForeground(themeColor.stringColor);
    rule.format.setFont(QFont(mFontFamily, mFontSize));
    QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
    while (matchIterator.hasNext()) {
        QRegularExpressionMatch match = matchIterator.next();
        // set the "#include" to includeColor and others to stringColor
        setFormat(match.capturedStart(), 8, themeColor.includeColor);
        setFormat(match.capturedStart() + 8, match.capturedLength() - 8, rule.format);
    }
}

//notice: it was called line by line
void Highlighter::highlightBlock(const QString &text) {
    addVarFormat(text);
    addNumberFormat(text);
    for (HighlightRule &rule: keywordRules) {
        rule.format.setFont(QFont(mFontFamily, mFontSize));
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
    addPunctuationFormat(text);
    addClassNameFormat(text);
    addFunctionFormat(text);
    addVarMemberFormat(text);
    addIncludeFormat(text);
    addStringFormat(text);
    // comments should be highlighted after all the other formats
    // or the comment will be highlighted by other formats like keywords
    addCommentFormat(text);
    addMultiLineCommentFormat(text);
    highlightSearchText(text);

}

void Highlighter::addKeywordsFormat() {
    QString keywords0Path = ":/resources/keywords/0.txt";
    QString keywords1Path = ":/resources/keywords/1.txt";
    QString keywords2Path = ":/resources/keywords/2.txt";
    QStringList keywordsPathList;
    keywordsPathList.append(keywords0Path);
    keywordsPathList.append(keywords1Path);
    keywordsPathList.append(keywords2Path);

    HighlightRule rule;
    QTextCharFormat keywordsFormat;
    keywordsFormat.setForeground(themeColor.keywordsColor);
    keywordsFormat.setFont(QFont(mFontFamily, mFontSize));
    rule.format = keywordsFormat;
    for (const auto &path: keywordsPathList) {
        QFile file(path);
        QTextStream keywordsStream(&file);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            keywordsStream.seek(0);
            QString line;
            while (!keywordsStream.atEnd()) {
                line = keywordsStream.readLine();
                if (line != "") {
                    if (line.length() == 1) {
                        //it is a punctuate
                        rule.pattern = QRegularExpression(line);
                    } else {
                        rule.pattern = QRegularExpression("\\b" + line + "\\b");
                    }
                }
                keywordRules.append(rule);
            }
            file.close();
        }
    }
}




void Highlighter::addClassNameFormat(const QString & text){
    HighlightRule rule;
    rule.pattern = QRegularExpression(R"(\b[A-Z][a-zA-Z0-9_]*\b)");
    rule.format.setForeground(themeColor.classNameColor);
    rule.format.setFont(QFont(mFontFamily, mFontSize));
    QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
    while (matchIterator.hasNext()) {
        QRegularExpressionMatch match = matchIterator.next();
        setFormat(match.capturedStart(), match.capturedLength(), rule.format);
    }
}



void Highlighter::addFunctionFormat(const QString &text) {
    HighlightRule rule;
    rule.pattern = QRegularExpression(R"(\b[a-zA-Z0-9_]+\s*\()");
    rule.format.setForeground(themeColor.functionColor);
    rule.format.setFont(QFont(mFontFamily, mFontSize));
    QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
    while (matchIterator.hasNext()) {
        QRegularExpressionMatch match = matchIterator.next();
        //we should not highlight the '('
        setFormat(match.capturedStart(), match.capturedLength() - 1, rule.format);
    }
}

void Highlighter::highlightSearchText(const QString &text) {

    if (searchedText.isEmpty()) {
        return;
    }
    HighlightRule rule;
    rule.pattern = QRegularExpression(searchedText);
    rule.format.setBackground(themeColor.searchedTextBackgroundColor);
    rule.format.setFont(QFont(mFontFamily, mFontSize));
    QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
    while (matchIterator.hasNext()) {
//        qDebug()<<"text:"<<text;
        QRegularExpressionMatch match = matchIterator.next();
        setFormat(match.capturedStart(), match.capturedLength(), rule.format);
//        qDebug()<<match.capturedStart()<<match.capturedLength()<<" ";
    }
}

void Highlighter::setSearchText(const QString &keyWord) {
    searchedText = keyWord;

}

void Highlighter::setThemeColor(bool isVaporwave) {
    if (isVaporwave) {
        mFontFamily = "Fixedsys";
        themeColor.plainTextColor = QColor(0, 0, 0);
        themeColor.varColor = QColor(0, 0, 0);
        themeColor.numberColor = QColor(0, 0, 0);
        themeColor.stringColor = QColor(0, 0, 0);
        themeColor.commentColor = QColor(0,128,0);
        themeColor.varMemberColor = QColor(0, 0, 0);
        themeColor.includeColor = QColor(8, 8, 255);
        themeColor.keywordsColor = QColor(8, 8, 255);
        themeColor.punctuationColor=QColor(0, 0, 0);
        themeColor.classNameColor = QColor(8, 8, 255);
        themeColor.functionColor = QColor(0, 0, 0);
        themeColor.searchedTextBackgroundColor = QColor(23,255,240);

    } else {
        mFontFamily = "JetBrains Mono NL";
        themeColor.plainTextColor = QColor(169, 183, 198);
        themeColor.varColor = QColor(169, 183, 198);
        themeColor.numberColor = QColor(104, 151, 187);
        themeColor.stringColor = QColor(106, 135, 89);
        themeColor.commentColor = QColor(128, 128, 128);
        themeColor.varMemberColor = QColor(147, 115, 165);
        themeColor.includeColor = QColor(255, 198, 109);
        themeColor.keywordsColor = QColor(204, 120, 48);
        themeColor.punctuationColor=QColor(204, 120, 48);
        themeColor.classNameColor = QColor(181, 182, 227);
        themeColor.functionColor = QColor(255, 198, 109);
        themeColor.searchedTextBackgroundColor = QColor(50, 89, 61, 100);
    }

    for (auto &rule: keywordRules) {
        QTextCharFormat format = rule.format;
        format.setFont(QFont(mFontFamily, mFontSize));
        format.setForeground(themeColor.keywordsColor);
        rule.format = format;
    }

}














