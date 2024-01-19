#ifndef TRACKEDITORWINDOW_H
#define TRACKEDITORWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "newcomponentpicker.h"
#include "componentfactory.h"

namespace Ui {
class TrackEditorWindow;
}

class TrackEditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    TrackEditorWindow(QWidget *parent = nullptr);
    ~TrackEditorWindow();

private slots:
    void on_actionQuit_triggered();
    void on_actionSave_As_triggered();
    void showNewComponentPicker();  // Declaration of the new slot

private:
    void saveToFile();
    void createComponent(QWidget *componentToUse);

    Ui::TrackEditorWindow *ui;
};

#endif // TRACKEDITORWINDOW_H
