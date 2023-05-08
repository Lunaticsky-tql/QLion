//
// Created by LENOVO on 2023/5/7.
//

#include <QFile>
#include "Highlighter.h"

Highlighter::Highlighter(QTextDocument *parent, const QString &fontFamily, int fontSize) : QSyntaxHighlighter(
        parent) {
    initBatchHighlightFormat();
}

void Highlighter::addVarFormat(const QString &text) {
    HighlightRule normalVarRole;
    normalVarRole.pattern = QRegularExpression("[a-zA-Z0-9_]+");
    QColor color(169, 183, 198);
    normalVarRole.format.setForeground(color);
    normalVarRole.format.setFont(QFont(mFontFamily, mFontSize));
    QRegularExpressionMatchIterator matchIterator = normalVarRole.pattern.globalMatch(text);
    while (matchIterator.hasNext()) {
        QRegularExpressionMatch match = matchIterator.next();
        setFormat(match.capturedStart(), match.capturedLength(), normalVarRole.format);
    }
}

void Highlighter::addNumberFormat() {
    HighlightRule intRule;
    intRule.pattern = QRegularExpression(R"(\b[0-9]+\b)");
    HighlightRule hexIntRule;
    hexIntRule.pattern = QRegularExpression(R"(\b0[Xx][0-9a-fA-F]+\b)");
    HighlightRule floatRule;
//    floatRule.pattern = QRegularExpression(R"(([-+]?[0-9]+[.]?[0-9]*([eE][-+]?[0-9]+)?[fL1L]?)|([-+]?[0-9]*[.]?[0-9]+([eE][-+]?[0-9]+)?[fLlL]?))");
    // a better float pattern
    floatRule.pattern = QRegularExpression(R"(((([0-9]*[.][0-9]*([eE][+-]?[0-9]+)?)|([0-9]+[eE][+-]?[0-9]+))[fLlL]?))");
    QColor color(104, 151, 187);
    intRule.format.setForeground(color);
    highlightRules.append(intRule);
    hexIntRule.format.setForeground(color);
    highlightRules.append(hexIntRule);
    floatRule.format.setForeground(color);
    highlightRules.append(floatRule);
}

void Highlighter::addStringFormat(const QString &text) {
    QVector<HighlightRule> stringHighlightRules;
    QColor color(106, 135, 89);
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
    for(auto &rule:stringHighlightRules){
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}

void Highlighter::addCommentFormat(const QString &text) {
    HighlightRule rule;
    rule.pattern = QRegularExpression(R"(//[^\n]*)");
    QColor color(128, 128, 128);
    rule.format.setForeground(color);
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
    QColor color(128, 128, 128);
    QTextCharFormat multiLineCommentFormat;
    multiLineCommentFormat.setForeground(color);
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
    QColor VarMemberColor(147, 115, 165);
    varMemberRole.format.setForeground(VarMemberColor);
    varMemberRole.format.setFont(QFont(mFontFamily, mFontSize));
    QRegularExpressionMatchIterator matchIterator = varMemberRole.pattern.globalMatch(text);
    QTextCharFormat plainFormat;
    QColor plainColor(169, 183, 198);
    plainFormat.setForeground(plainColor);
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
    QColor stringColor(106, 135, 89);
    QColor includeColor(255, 198, 109);
    rule.format.setForeground(stringColor);
    rule.format.setFont(QFont(mFontFamily, mFontSize));
    QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
    while (matchIterator.hasNext()) {
        QRegularExpressionMatch match = matchIterator.next();
        // set the "#include" to includeColor and others to stringColor
        setFormat(match.capturedStart(), 8, includeColor);
        setFormat(match.capturedStart() + 8, match.capturedLength() - 8, rule.format);
    }
}

//notice: it was called line by line
void Highlighter::highlightBlock(const QString &text) {
    addVarFormat(text);
    for (HighlightRule &rule: highlightRules) {
        rule.format.setFont(QFont(mFontFamily, mFontSize));
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
    addFunctionFormat(text);
    addVarMemberFormat(text);
    addIncludeFormat(text);
    addStringFormat(text);
    // comments should be highlighted after all the other formats
    // or the comment will be highlighted by other formats like keywords
    addCommentFormat(text);
    addMultiLineCommentFormat(text);
}

void Highlighter::addKeywordsFormat() {
    QString keywords0Path = ":/resources/keywords/0.txt";
    QString keywords1Path = ":/resources/keywords/1.txt";
    QString keywords2Path = ":/resources/keywords/2.txt";
    QString punctuatesPath = ":/resources/keywords/punctuations.txt";
    QStringList keywordsPathList;
    keywordsPathList.append(keywords0Path);
    keywordsPathList.append(keywords1Path);
    keywordsPathList.append(keywords2Path);
    keywordsPathList.append(punctuatesPath);

    HighlightRule rule;
    QTextCharFormat keywordsFormat;
    QColor color(204, 120, 48);
    keywordsFormat.setForeground(color);
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
                highlightRules.append(rule);
            }
            file.close();
        }
    }
}


void Highlighter::addClassNameFormat() {
    HighlightRule rule;
    rule.pattern = QRegularExpression(R"(\b[A-Z][a-zA-Z0-9_]*\b)");
    QColor color(181, 182, 227);
    rule.format.setForeground(color);
    highlightRules.append(rule);
}

void Highlighter::addFunctionFormat(const QString &text) {
    HighlightRule rule;
    rule.pattern = QRegularExpression(R"(\b[a-zA-Z0-9_]+\s*\()");
    QColor color(255, 198, 109);
    rule.format.setForeground(color);
    rule.format.setFont(QFont(mFontFamily, mFontSize));
    QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
    while (matchIterator.hasNext()) {
        QRegularExpressionMatch match = matchIterator.next();
        //we should not highlight the '('
        setFormat(match.capturedStart(), match.capturedLength() - 1, rule.format);
    }

}


void Highlighter::initBatchHighlightFormat() {
    addNumberFormat();
    addKeywordsFormat();
    addClassNameFormat();
}











