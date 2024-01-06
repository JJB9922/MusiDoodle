#ifndef TRACKEDITORWINDOW_H
#define TRACKEDITORWINDOW_H

#include <QMainWindow>

namespace Ui {
class TrackEditorWindow;
}

class TrackEditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TrackEditorWindow(QWidget *parent = nullptr);
    ~TrackEditorWindow();

private slots:
    void on_actionQuit_triggered();

    void on_actionSave_As_triggered();

private:
    Ui::TrackEditorWindow *ui;
};

#endif // TRACKEDITORWINDOW_H
