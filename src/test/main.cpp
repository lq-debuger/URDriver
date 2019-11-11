#include "MainWindow.h"
#include <QApplication>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow mw;
    mw.show();

    return QApplication::exec();
}
