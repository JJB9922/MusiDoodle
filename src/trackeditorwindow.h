#ifndef TRACKEDITORWINDOW_H
#define TRACKEDITORWINDOW_H

#import "componentfactory.h"

#include <QMainWindow>
#include <QAction>
#include <QtWidgets>

namespace Ui {
class TrackEditorWindow;
}

class TrackEditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TrackEditorWindow(QWidget *parent = nullptr);
    ~TrackEditorWindow();

public slots:
    void saveToFile();
    void createComponent(QWidget* componentToUse);

private slots:
    void on_actionQuit_triggered();
    void on_actionSave_As_triggered();

    void on_addComponentButton_clicked();

private:
    Ui::TrackEditorWindow *ui;
    QAction *actionSave_As;
    QLineEdit *lineEdit;
};

#endif // TRACKEDITORWINDOW_H
