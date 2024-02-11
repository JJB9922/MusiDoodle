#include "Screens/mainwindow.h"
#include <QApplication>
#include <QGuiApplication>

/**
 * @brief The main entry point for the application.
 *
 * Initializes the QApplication and sets the behavior to not quit when the last window is closed.
 * Creates an instance of the MainWindow class and displays it.
 * Starts the event loop with `QApplication::exec()`.
 *
 * @param argc The number of command line arguments.
 * @param argv An array of command line arguments.
 * @return The exit code of the application.
 */
int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   QGuiApplication::setQuitOnLastWindowClosed(false);
   MainWindow w;
   w.show();

   return a.exec();
}

