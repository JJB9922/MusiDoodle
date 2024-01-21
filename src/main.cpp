#include "mainwindow.h"
#include "chordselector.h"
#include <QApplication>
#include <QGuiApplication>

// int main(int argc, char *argv[])
// {
//     QApplication a(argc, argv);
//     QGuiApplication::setQuitOnLastWindowClosed(false);
//     MainWindow w;
//     w.show();

//     return a.exec();
// }

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    ChordSelector chordSelector;
    chordSelector.show();

    return a.exec();
}
