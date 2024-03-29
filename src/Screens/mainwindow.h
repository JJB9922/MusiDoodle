#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "trackeditorwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void loadFromFile();

private slots:
    void on_newTrackButton_clicked();
    void on_loadTrackButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    TrackEditorWindow *trackEditorWindow;

};
#endif // MAINWINDOW_H
