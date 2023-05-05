#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    // set fusion style
    QApplication::setStyle("fusion");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return QApplication::exec();
}
