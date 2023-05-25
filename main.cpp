#include <QApplication>
#include <QStyle>
#include "mainwindow.h"

void setUpStyle(QApplication &a)
{
    QApplication::setStyle("fusion");
    QColor darkGray(53, 53, 53);
    QColor gray(128, 128, 128);
    QColor blue(42, 130, 218);
    QColor lightBlue(75, 110, 175);
    QColor textColor = QColor(187, 187, 187);
    QColor baseGray = QColor(60, 63, 65);
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, darkGray);
    darkPalette.setColor(QPalette::WindowText, textColor);
    darkPalette.setColor(QPalette::Base, baseGray);
    darkPalette.setColor(QPalette::AlternateBase, darkGray);
    darkPalette.setColor(QPalette::ToolTipBase, lightBlue);
    darkPalette.setColor(QPalette::ToolTipText, textColor);
    darkPalette.setColor(QPalette::Text, textColor);
    darkPalette.setColor(QPalette::Button, darkGray);
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::Link, blue);
    darkPalette.setColor(QPalette::Highlight, lightBlue);
    darkPalette.setColor(QPalette::HighlightedText, textColor);
    darkPalette.setColor(QPalette::Active, QPalette::Button, gray.darker());
    darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, gray);
    darkPalette.setColor(QPalette::Disabled, QPalette::WindowText, gray);
    darkPalette.setColor(QPalette::Disabled, QPalette::Text, gray);
    darkPalette.setColor(QPalette::Disabled, QPalette::Light, darkGray);
    QApplication::setPalette(darkPalette); 
    a.setStyleSheet("QToolTip { color: #ffffff; background-color: #46484a; border: none; }"
                        "QPlainTextEdit { background-color: #CAE3FF; }"
    );
}



int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindow w;
//    setUpStyle(a);
    return QApplication::exec();
}
