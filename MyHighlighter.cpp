//
// Created by LENOVO on 2023/5/7.
//

#include "MyHighlighter.h"

MyHighlighter::MyHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent) {
    initFormat();

}

void MyHighlighter::addNormalTextFormat() {
    HighlightRule rule;
    rule.pattern = QRegularExpression("[a-zA-Z0-9_]+");
    QColor color(169, 183, 198);
    rule.format.setForeground(color);
    highlightRules.append(rule);
}

void MyHighlighter::addNumberFormat() {
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

void MyHighlighter::addStringFormat() {

    QColor color(106, 135, 89);
    HighlightRule rule1;
    //"xxx"
    rule1.pattern = QRegularExpression(R"("[^"]*")");
    rule1.format.setForeground(color);
    highlightRules.append(rule1);
    HighlightRule rule2;
    //'xxx'
    rule2.pattern = QRegularExpression(R"('[^']*')");
    rule2.format.setForeground(color);
    highlightRules.append(rule2);

}

void MyHighlighter::addCommentFormat() {
    HighlightRule rule;
    rule.pattern = QRegularExpression(R"(//[^\n]*)");
    QColor color(128, 128, 128);
    rule.format.setForeground(color);
    highlightRules.append(rule);
}

//notice: it was called line by line
void MyHighlighter::addMultiLineCommentFormat(const QString &text) {
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
        long long commentLength=0;
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

//notice: it was called line by line
void MyHighlighter::highlightBlock(const QString &text) {
    for (HighlightRule &rule: highlightRules) {
        rule.format.setFont(QFont(mFontFamily, mFontSize));
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
    addMultiLineCommentFormat(text);
}

void MyHighlighter::initFormat() {
    addNormalTextFormat();
    addNumberFormat();
    addStringFormat();
    addCommentFormat();
}







